#pragma once

wiced_bool_t btutil_isEddystone(uint8_t *data);
wiced_bool_t btutil_is_iBeacon(uint8_t *data);
wiced_bool_t btutil_isCypress(uint8_t *data);

int btutil_adv_len(uint8_t *packet);
void btutil_adv_printPacketDecode(uint8_t *packet);
void btutil_adv_printPacketBytes(uint8_t *packet);

