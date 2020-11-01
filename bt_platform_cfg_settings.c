#include "cybt_platform_config.h"
#include "cybsp.h"
#include "wiced_bt_stack.h"

const cybt_platform_config_t bt_platform_cfg_settings =
{
    .hci_config =
    {
        .hci_transport = CYBT_HCI_UART,

        .hci =
        {
            .hci_uart =
            {
                .uart_tx_pin = CYBSP_BT_UART_TX,
                .uart_rx_pin = CYBSP_BT_UART_RX,
                .uart_rts_pin = CYBSP_BT_UART_RTS,
                .uart_cts_pin = CYBSP_BT_UART_CTS,

                .baud_rate_for_fw_download = 115200,
                .baud_rate_for_feature     = 115200,

                .data_bits = 8,
                .stop_bits = 1,
                .parity = CYHAL_UART_PARITY_NONE,
                .flow_control = WICED_TRUE
            }
        }
    },

    .controller_config =
    {
        .bt_power_pin      = CYBSP_BT_POWER,
        .sleep_mode =
        {
            #if (bt_0_power_0_ENABLED == 1) /* BT Power control is enabled in the LPA */
            #if (CYCFG_BT_LP_ENABLED == 1) /* Low power is enabled in the LPA, use the LPA configuration */
            .sleep_mode_enabled = true,
            .device_wakeup_pin = CYCFG_BT_DEV_WAKE_GPIO,
            .host_wakeup_pin = CYCFG_BT_HOST_WAKE_GPIO,
            .device_wake_polarity = CYCFG_BT_DEV_WAKE_POLARITY,
            .host_wake_polarity = CYCFG_BT_HOST_WAKE_IRQ_EVENT
            #else /* Low power is disabled in the LPA, disable low power */
            .sleep_mode_enabled = false
            #endif
            #else /* BT Power control is disabled in the LPA – default to BSP low power configuration */
            .sleep_mode_enabled = true,
            .device_wakeup_pin = CYBSP_BT_DEVICE_WAKE,
            .host_wakeup_pin = CYBSP_BT_HOST_WAKE,
            .device_wake_polarity = CYBT_WAKE_ACTIVE_LOW,
            .host_wake_polarity = CYBT_WAKE_ACTIVE_LOW
            #endif
        }
    },

    .task_mem_pool_size    = 2048
};