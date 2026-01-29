#include "PR/piint.h"

OSMesgQueue *osPiGetCmdQueue(void) {
    if (!__osPiDevMgr.active) {
        return nullptr;
    }

    return __osPiDevMgr.cmdQueue;
}
