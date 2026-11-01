#include "flo_00.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    IfLt(GB_StoryProgress, STORY_EPILOGUE)
        Call(MakeMarkerEntity, $SavePoint_1)
    EndIf
    Return
    End
};
