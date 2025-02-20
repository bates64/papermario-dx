#pragma once
// macros used by Star Rod's script generation

#define EVT_MAKE_ITEM_ENTITY(args...) \
    Call(MakeItemEntity, args)

#define EVT_MAKE_ENTITY(type, args...) \
    Call(MakeEntity, Ref(Entity_##type), args, MAKE_ENTITY_END)

#define GEN_FLOWER_SPAWN_REGION(args...) \
    EVT_FLOWER_SPAWN_REGION(args)
