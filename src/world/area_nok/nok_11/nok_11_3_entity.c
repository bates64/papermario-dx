#include "nok_11.h"
#include "entity.h"

EvtScript N(EVS_MakeEntities) = {
    Call(MakeItemEntity, ITEM_BADGE_EMBLEM_A, -675, 0, -30, ITEM_SPAWN_MODE_FIXED_NEVER_VANISH, GF_NOK11_Item_BadgeEmblem_A)
    Call(MakeItemEntity, ITEM_BADGE_EMBLEM_B, -640, 0, -30, ITEM_SPAWN_MODE_FIXED_NEVER_VANISH, GF_NOK11_Item_BadgeEmblem_B)
    Call(MakeItemEntity, ITEM_BADGE_EMBLEM_C, -605, 0, -30, ITEM_SPAWN_MODE_FIXED_NEVER_VANISH, GF_NOK11_Item_BadgeEmblem_C)
    Call(MakeItemEntity, ITEM_BADGE_EMBLEM_X, -600, 0, -30, ITEM_SPAWN_MODE_FIXED_NEVER_VANISH, GF_NOK11_Item_BadgeEmblem_X)
    Call(MakeItemEntity, ITEM_BADGE_EMBLEM_Y, -570, 0, -30, ITEM_SPAWN_MODE_FIXED_NEVER_VANISH, GF_NOK11_Item_BadgeEmblem_Y)

    Call(MakeEntity, Ref(Entity_BrickBlock), 30, 60, -85, 0, MAKE_ENTITY_END)
    Call(MakeEntity, Ref(Entity_YellowBlock), 110, 60, -85, 0, ITEM_COIN, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_NOK11_ItemBlock_Coin)
    Call(MakeEntity, Ref(Entity_BrickBlock), 330, 60, -85, 0, MAKE_ENTITY_END)
    Call(MakeEntity, Ref(Entity_RedBlock), 380, 60, -85, 0, ITEM_DIZZY_ATTACK, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_NOK11_BadgeBlock_DizzyAttack)
    Call(MakeEntity, Ref(Entity_BrickBlock), 650, 60, -85, 0, MAKE_ENTITY_END)
    Call(MakeEntity, Ref(Entity_BrickBlock), 700, 60, -85, 0, MAKE_ENTITY_END)
    Call(MakeEntity, Ref(Entity_YellowBlock), 750, 60, -85, 0, ITEM_FRIGHT_JAR, MAKE_ENTITY_END)
    Call(AssignBlockFlag, GF_NOK11_ItemBlock_FrightJar)
    Return
    End
};
