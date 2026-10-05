//! A stand-in for --symbol-regex that only understands the one pattern
//! shape ever used to select EvtScript symbols: `(^|_)LITERAL`, matching
//! a name that starts with LITERAL or contains `_LITERAL`. Pulling in a
//! full regex engine for that isn't worth the dependency (compile time,
//! binary size, a Nix vendoring step) when a couple of string
//! comparisons do the same job faster.

pub struct SymbolPattern {
    prefix_marker: String, // "_" + literal, searched anywhere in the name
    literal: String,       // literal, checked against the start of the name
}

impl SymbolPattern {
    pub fn parse(pattern: &str) -> Result<SymbolPattern, String> {
        let literal = pattern.strip_prefix("(^|_)").ok_or_else(|| {
            format!(
                "unsupported --symbol-regex {pattern:?}: only patterns of the exact form \
                 (^|_)LITERAL are supported"
            )
        })?;
        Ok(SymbolPattern {
            prefix_marker: format!("_{literal}"),
            literal: literal.to_string(),
        })
    }

    pub fn matches(&self, name: &str) -> bool {
        name.starts_with(self.literal.as_str()) || name.contains(self.prefix_marker.as_str())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn matches_prefix_and_underscore_variants() {
        let p = SymbolPattern::parse("(^|_)EVS_").unwrap();
        assert!(p.matches("EVS_Foo"));
        assert!(p.matches("SomeThing_EVS_Bar"));
        assert!(!p.matches("NotAScriptSymbol"));
        assert!(!p.matches("XEVS_Foo")); // no underscore, doesn't start with it either
    }

    #[test]
    fn rejects_other_shapes() {
        assert!(SymbolPattern::parse("EVS_.*").is_err());
        assert!(SymbolPattern::parse("^EVS_").is_err());
    }
}
