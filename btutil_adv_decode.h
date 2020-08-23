#pragma once

//void bleDecodeAdInfo(uint8_t *bytes);
wiced_bool_t btutil_isEddystone(uint8_t *data);
wiced_bool_t btutil_is_iBeacon(uint8_t *data);
wiced_bool_t btutil_isCypress(uint8_t *data);

int btutil_adv_len(uint8_t *packet);
void btutil_adv_dumpDecodePacket(uint8_t *packet);
void btutil_adv_format128bitUUID(uint8_t *bytes);
void btutil_adv_format16bitUUID(uint8_t *bytes);
void btutil_adv_decodeField(uint8_t *bytes);
void btutil_adv_dumpBytesPacket(uint8_t *packet);

