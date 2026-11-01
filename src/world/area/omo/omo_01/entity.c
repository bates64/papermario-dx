#include "omo_01.h"
#include "entity.h"

EvtScript EVS_MakeEntities = {
    IfEq(GF_OMO09_Defeated_CalculatorThief, true)
        IfEq(GF_OMO01_Item_Calculator, false)
            Call(MakeMarkerEntity, $Item_Calculator_1)
        EndIf
    EndIf
    Call(MakeMarkerEntity, $HiddenYellowBlock_Mystery_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_FrightJar_1)
    Return
    End
};
