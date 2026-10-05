use std::collections::HashMap;
use std::fmt;
use std::path::{Path, PathBuf};

const SHT_SYMTAB: u32 = 2;
const SHT_REL: u32 = 9;
pub const STT_NOTYPE: u8 = 0;
pub const STT_OBJECT: u8 = 1;
pub const STT_FUNC: u8 = 2;
pub const STT_SECTION: u8 = 3;
const STT_FILE: u8 = 4;
pub const SHN_UNDEF: u16 = 0;
pub const R_MIPS_32: u8 = 2;

#[derive(Debug)]
pub struct ElfError(pub String);

impl fmt::Display for ElfError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}
impl std::error::Error for ElfError {}

fn elf_err(msg: impl Into<String>) -> ElfError {
    ElfError(msg.into())
}

#[derive(Clone, Debug)]
pub struct Section {
    pub index: usize,
    pub name: String,
    pub r#type: u32,
    pub offset: u32,
    pub size: u32,
    #[allow(dead_code)]
    pub entsize: u32,
    pub link: u32,
    #[allow(dead_code)]
    pub info: u32,
}

#[derive(Clone, Debug)]
pub struct Symbol {
    pub name: String,
    pub value: u32,
    pub size: u32,
    pub info: u8,
    pub shndx: u16,
}

impl Symbol {
    pub fn r#type(&self) -> u8 {
        self.info & 0xF
    }
}

#[derive(Clone, Copy, Debug)]
pub struct Relocation {
    #[allow(dead_code)]
    pub offset: u32,
    pub sym_index: u32,
    pub r#type: u8,
    pub symtab_index: usize,
}

fn c_string(data: &[u8], offset: usize) -> String {
    let end = data[offset..]
        .iter()
        .position(|&b| b == 0)
        .map(|p| offset + p)
        .unwrap_or(data.len());
    String::from_utf8_lossy(&data[offset..end]).into_owned()
}

pub struct Elf32 {
    #[allow(dead_code)]
    pub path: PathBuf,
    pub sections: Vec<Section>,
    pub symbols: Vec<Symbol>,
    pub symtabs: HashMap<usize, Vec<Symbol>>,
    pub source_path: Option<String>,
    /// keyed by target section index -> offset -> relocation
    pub relocations: HashMap<usize, HashMap<u32, Relocation>>,
    data: Vec<u8>,
}

fn read_u16(data: &[u8], off: usize, big_endian: bool) -> u16 {
    let b = [data[off], data[off + 1]];
    if big_endian {
        u16::from_be_bytes(b)
    } else {
        u16::from_le_bytes(b)
    }
}

fn read_u32(data: &[u8], off: usize, big_endian: bool) -> u32 {
    let b = [data[off], data[off + 1], data[off + 2], data[off + 3]];
    if big_endian {
        u32::from_be_bytes(b)
    } else {
        u32::from_le_bytes(b)
    }
}

impl Elf32 {
    pub fn open(path: &Path) -> Result<Elf32, ElfError> {
        let data = std::fs::read(path).map_err(|e| elf_err(format!("{e}")))?;
        if data.len() < 52 || &data[0..4] != b"\x7fELF" {
            return Err(elf_err("not an ELF file"));
        }
        if data[4] != 1 {
            return Err(elf_err("not an ELF32 file"));
        }
        let big_endian = match data[5] {
            1 => false,
            2 => true,
            _ => return Err(elf_err("unknown ELF endianness")),
        };

        let shoff = read_u32(&data, 0x20, big_endian);
        let shentsize = read_u16(&data, 0x2E, big_endian);
        let shnum = read_u16(&data, 0x30, big_endian);
        let shstrndx = read_u16(&data, 0x32, big_endian);

        let sections = Self::read_sections(&data, shoff, shentsize, shnum, shstrndx, big_endian)?;
        let (symbols, symtabs) = Self::read_symbols(&data, &sections, big_endian)?;
        let source_path = symbols
            .iter()
            .find(|s| s.r#type() == STT_FILE && !s.name.is_empty())
            .map(|s| s.name.clone());
        let relocations = Self::read_relocations(&data, &sections, &symtabs, big_endian)?;

        Ok(Elf32 {
            path: path.to_path_buf(),
            sections,
            symbols,
            symtabs,
            source_path,
            relocations,
            data,
        })
    }

    fn read_sections(
        data: &[u8],
        shoff: u32,
        shentsize: u16,
        shnum: u16,
        shstrndx: u16,
        big_endian: bool,
    ) -> Result<Vec<Section>, ElfError> {
        struct Raw {
            name_off: u32,
            sh_type: u32,
            sh_offset: u32,
            sh_size: u32,
            sh_link: u32,
            sh_info: u32,
            sh_entsize: u32,
        }
        let mut raw_sections = Vec::with_capacity(shnum as usize);
        for i in 0..shnum as usize {
            let off = shoff as usize + i * shentsize as usize;
            raw_sections.push(Raw {
                name_off: read_u32(data, off, big_endian),
                sh_type: read_u32(data, off + 4, big_endian),
                sh_offset: read_u32(data, off + 16, big_endian),
                sh_size: read_u32(data, off + 20, big_endian),
                sh_link: read_u32(data, off + 24, big_endian),
                sh_info: read_u32(data, off + 28, big_endian),
                sh_entsize: read_u32(data, off + 36, big_endian),
            });
        }

        let shstrndx = shstrndx as usize;
        if shstrndx >= raw_sections.len() {
            return Err(elf_err("invalid section string table index"));
        }
        let shstr = &raw_sections[shstrndx];
        let shstr_data =
            &data[shstr.sh_offset as usize..(shstr.sh_offset + shstr.sh_size) as usize];

        Ok(raw_sections
            .iter()
            .enumerate()
            .map(|(i, r)| Section {
                index: i,
                name: c_string(shstr_data, r.name_off as usize),
                r#type: r.sh_type,
                offset: r.sh_offset,
                size: r.sh_size,
                entsize: r.sh_entsize,
                link: r.sh_link,
                info: r.sh_info,
            })
            .collect())
    }

    fn read_symbols(
        data: &[u8],
        sections: &[Section],
        big_endian: bool,
    ) -> Result<(Vec<Symbol>, HashMap<usize, Vec<Symbol>>), ElfError> {
        let mut symbols = Vec::new();
        let mut symtabs = HashMap::new();

        for section in sections {
            if section.r#type != SHT_SYMTAB || section.entsize == 0 {
                continue;
            }
            let link = section.link as usize;
            if link >= sections.len() {
                return Err(elf_err(format!(
                    "invalid symbol string table for {}",
                    section.name
                )));
            }
            let strtab = &sections[link];
            let strtab_data =
                &data[strtab.offset as usize..(strtab.offset + strtab.size) as usize];
            let count = section.size / section.entsize;
            let mut cur_symbols = Vec::with_capacity(count as usize);
            for i in 0..count {
                let off = section.offset as usize + i as usize * section.entsize as usize;
                let st_name = read_u32(data, off, big_endian);
                let st_value = read_u32(data, off + 4, big_endian);
                let st_size = read_u32(data, off + 8, big_endian);
                let st_info = data[off + 12];
                let st_shndx = read_u16(data, off + 14, big_endian);
                cur_symbols.push(Symbol {
                    name: c_string(strtab_data, st_name as usize),
                    value: st_value,
                    size: st_size,
                    info: st_info,
                    shndx: st_shndx,
                });
            }
            symtabs.insert(section.index, cur_symbols.clone());
            symbols.extend(cur_symbols);
        }
        Ok((symbols, symtabs))
    }

    fn read_relocations(
        data: &[u8],
        sections: &[Section],
        symtabs: &HashMap<usize, Vec<Symbol>>,
        big_endian: bool,
    ) -> Result<HashMap<usize, HashMap<u32, Relocation>>, ElfError> {
        let mut relocations: HashMap<usize, HashMap<u32, Relocation>> = HashMap::new();

        for section in sections {
            if section.r#type != SHT_REL || section.entsize == 0 {
                continue;
            }
            let target = section.info as usize;
            if target >= sections.len() {
                return Err(elf_err(format!(
                    "invalid relocation target section for {}",
                    section.name
                )));
            }
            if !symtabs.contains_key(&(section.link as usize)) {
                return Err(elf_err(format!(
                    "invalid relocation symbol table for {}",
                    section.name
                )));
            }

            let target_relocations = relocations.entry(target).or_default();
            let count = section.size / section.entsize;
            for i in 0..count {
                let off = section.offset as usize + i as usize * section.entsize as usize;
                let r_offset = read_u32(data, off, big_endian);
                let r_info = read_u32(data, off + 4, big_endian);
                let relocation = Relocation {
                    offset: r_offset,
                    sym_index: r_info >> 8,
                    r#type: (r_info & 0xFF) as u8,
                    symtab_index: section.link as usize,
                };
                if target_relocations.contains_key(&r_offset) {
                    return Err(elf_err(format!(
                        "duplicate relocation at {}+0x{:X}",
                        section.name, r_offset
                    )));
                }
                target_relocations.insert(r_offset, relocation);
            }
        }
        Ok(relocations)
    }

    pub fn section_data_for_symbol<'a>(
        &'a self,
        symbol: &Symbol,
    ) -> Result<(&'a Section, &'a [u8]), ElfError> {
        let shndx = symbol.shndx as usize;
        if shndx >= self.sections.len() {
            return Err(elf_err(format!(
                "{}: invalid section index {}",
                symbol.name, symbol.shndx
            )));
        }
        let section = &self.sections[shndx];
        if symbol.value + symbol.size > section.size {
            return Err(elf_err(format!(
                "{}: symbol extent 0x{:X}+0x{:X} exceeds section {} size 0x{:X}",
                symbol.name, symbol.value, symbol.size, section.name, section.size
            )));
        }
        let start = section.offset as usize + symbol.value as usize;
        Ok((section, &self.data[start..start + symbol.size as usize]))
    }

    pub fn relocation_at(&self, section_index: usize, offset: u32) -> Option<&Relocation> {
        self.relocations.get(&section_index)?.get(&offset)
    }

    pub fn symbol_for_relocation(&self, relocation: &Relocation) -> Result<&Symbol, ElfError> {
        let symtab = self
            .symtabs
            .get(&relocation.symtab_index)
            .ok_or_else(|| {
                elf_err(format!(
                    "invalid symbol table index {} for relocation",
                    relocation.symtab_index
                ))
            })?;
        symtab
            .get(relocation.sym_index as usize)
            .ok_or_else(|| elf_err(format!("invalid relocation symbol index {}", relocation.sym_index)))
    }

    pub fn section_data(&self, section_index: usize) -> &[u8] {
        let section = &self.sections[section_index];
        &self.data[section.offset as usize..(section.offset + section.size) as usize]
    }
}
