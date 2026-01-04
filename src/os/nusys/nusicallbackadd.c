#include "common.h"
#include "nu/nusys.h"

void nuSiCallBackAdd(NUCallBackList* list) {
    OSIntMask mask;
    NUCallBackList** siCallBackListPtr = &nuSiCallBackList;
    u32 i;

    while (*siCallBackListPtr != nullptr) {
        if ((*siCallBackListPtr)->majorNo == list->majorNo) {
            return;
        }
        siCallBackListPtr = &(*siCallBackListPtr)->next;
    }

    for (i = 1; list->func[i] != nullptr; i++);

    mask = osSetIntMask(OS_IM_NONE);
    *siCallBackListPtr = list;
    list->next = nullptr;
    list->funcNum = i;
    osSetIntMask(mask);
}
