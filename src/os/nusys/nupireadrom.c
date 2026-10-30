#include "common.h"
#include "nu/nusys.h"

void nuPiReadRom(u32 rom_addr, void* buf_ptr, u32 size) {
    OSIoMesg ioMesg;
    OSMesg mesg;
    OSMesgQueue queue;
    u32 mesgSize;

    // PI DMA into an address that isn't 8-byte aligned drops bytes from the end of the transfer, so a misaligned read
    // goes through an aligned buffer. It's 16-byte aligned so no live stack data shares its cache lines.
    if ((u32) buf_ptr & 7) {
        u64 bounce[0x40] ALIGNED16;

        while (size != 0) {
            mesgSize = MIN(size, sizeof(bounce));
            nuPiReadRom(rom_addr, bounce, mesgSize);
            bcopy(bounce, buf_ptr, mesgSize);
            rom_addr += mesgSize;
            buf_ptr += mesgSize;
            size -= mesgSize;
        }
        return;
    }

    osCreateMesgQueue(&queue, &mesg, 1);

    ioMesg.hdr.pri = OS_MESG_PRI_NORMAL;
    ioMesg.hdr.retQueue = &queue;
    osInvalDCache(buf_ptr, size);
    osInvalICache(buf_ptr, size);

    while (size != 0) {
        mesgSize = size;

        if (size > 0x4000) {
            mesgSize = 0x4000;
        }

        ioMesg.dramAddr = buf_ptr;
        ioMesg.devAddr = rom_addr;
        ioMesg.size = mesgSize;

        osEPiStartDma(nuPiCartHandle, &ioMesg, OS_READ);
        osRecvMesg(&queue, &mesg, OS_MESG_BLOCK);

        rom_addr += mesgSize;
        buf_ptr += mesgSize;
        size -= mesgSize;
    }
}
