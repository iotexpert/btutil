#pragma once
#include "wiced_bt_stack.h"
#include "wiced_bt_dev.h"

wiced_result_t app_bt_management_callback(wiced_bt_management_evt_t event, wiced_bt_management_evt_data_t *p_event_data);
void btm_printTable();

