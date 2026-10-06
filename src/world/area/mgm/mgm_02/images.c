#include "mgm_02.h"
#include "include_asset.h"

#include "world/area/mgm/mgm_02/panel_peach.png.h"
INCLUDE_IMG("world/area/mgm/mgm_02/panel_peach.png", mgm_02_panel_peach_img);
INCLUDE_PAL("world/area/mgm/mgm_02/panel_peach.pal", mgm_02_panel_peach_pal);

MessageImageData MsgImg_PeachPanel[] = {
    {
        .raster   = mgm_02_panel_peach_img,
        .palette  = mgm_02_panel_peach_pal,
        .width    = mgm_02_panel_peach_img_width,
        .height   = mgm_02_panel_peach_img_height,
        .format   = G_IM_FMT_CI,
        .bitDepth = G_IM_SIZ_4b,
    }
};

API_CALLABLE(SetMsgImgs_Panel) {
    set_message_images(MsgImg_PeachPanel);
    return ApiStatus_DONE2;
}
