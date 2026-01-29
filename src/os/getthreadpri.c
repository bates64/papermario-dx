#include "PR/osint.h"

OSPri osGetThreadPri(OSThread *thread) {
    if (thread == nullptr) {
        thread = __osRunningThread;
    }

    return thread->priority;
}
