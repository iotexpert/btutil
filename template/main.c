#include "bluetoothManager.h"
#include "cycfg_bt_settings.h"
#include "bt_platform_cfg_settings.h"


    cybt_platform_config_init(&bt_platform_cfg_settings);
    wiced_bt_stack_init (app_bt_management_callback, &wiced_bt_cfg_settings);
