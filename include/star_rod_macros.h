#ifndef _STAR_ROD_MACROS_H_
#define _STAR_ROD_MACROS_H_
// macros used by Star Rod's script generation

#define EVT_MAKE_ITEM_ENTITY(item, x, y, z, spawnMode, flag) \
    Call(MakeItemEntity, item, x, y, z, spawnMode, flag)

#define EVT_GEN_ITEM_ENTITY(args) \
    EVT_MAKE_ITEM_ENTITY(args)

#define EVT_MAKE_BASIC_ENTITY(type, x, y, z, a) \
    Call(MakeEntity, Ref(Entity_##type), x, y, z, a, MAKE_ENTITY_END)

#define EVT_GEN_BASIC_ENTITY(args) \
    EVT_MAKE_BASIC_ENTITY(args)

#define EVT_MAKE_ITEM_BLOCK(type, x, y, z, a, item, flag) \
    Call(MakeEntity, Ref(Entity_##type), x, y, z, a, item, MAKE_ENTITY_END) \
    Call(AssignBlockFlag, flag)

#define EVT_GEN_ITEM_BLOCK(args) \
    EVT_MAKE_ITEM_BLOCK(args)

#define EVT_MAKE_HAMMER_BLOCK(type, x, y, z, a, script) \
    Call(MakeEntity, Ref(Entity_##type), x, y, z, a, MAKE_ENTITY_END) \
    Call(AssignScript, Ref(script))

#define EVT_GEN_HAMMER_BLOCK(args) \
    EVT_MAKE_HAMMER_BLOCK(args)

#define EVT_MAKE_BOMBABLE_ROCK(type, x, y, z, a, script) \
    Call(MakeEntity, Ref(Entity_##type), x, y, z, a, MAKE_ENTITY_END) \
    Call(AssignScript, Ref(script))

#define EVT_GEN_BOMBABLE_ROCK(args) \
    EVT_MAKE_BOMBABLE_ROCK(args)

#define EVT_MAKE_SIGNPOST(type, x, y, z, a, script) \
    Call(MakeEntity, Ref(Entity_##type), x, y, z, a, MAKE_ENTITY_END) \
    Call(AssignScript, Ref(script))

#define EVT_GEN_SIGNPOST(args) \
    EVT_MAKE_SIGNPOST(args)

#define EVT_MAKE_HIDDEN_PANEL(x, y, z, a, model, flag) \
    Call(MakeEntity, Ref(Entity_HiddenPanel), -650, 75, -50, 0, model, MAKE_ENTITY_END) \
    Call(AssignPanelFlag, flag)

#define EVT_GEN_HIDDEN_PANEL(args) \
    EVT_MAKE_HIDDEN_PANEL(args)

#endif
