#include <stdio.h>
#include <stdint.h>
#include "wiced_bt_ble.h"
#include "btutil_adv_decode.h"
#include "btutil_company_ids.h"

#define TEMP_PRINTF printf

void btutil_adv_printBytesOffset(uint8_t *bytes,uint32_t offset);
void btutil_adv_printFieldBytes(uint8_t *bytes);
void btutil_adv_printNameField(uint8_t *bytes);
void btutbtutil_adv_printUnknownField(char *buff, uint8_t *bytes);
void btutil_adv_printFlagsField(uint8_t *bytes);
void btutil_adv_printMfgDataField(uint8_t *bytes);
void btutil_adv_printTxPowerField(uint8_t *bytes);
void btutil_adv_printSlaveIntervalRangeField(uint8_t *bytes);
void btutil_adv_PrintAdvIntervalField(uint8_t *bytes);
void btutil_adv_printLERoleField(uint8_t *bytes);
void btutil_adv_decodeSecurityManagerOOBField(uint8_t *bytes);
void btutil_adv_print16bitServiceUUID(uint8_t *bytes);
void btutil_adv_decode32bitServiceUUID(uint8_t *bytes);
void btutil_adv_decode128bitServiceUUID( uint8_t *bytes);
void btutil_adv_decodePublicAddress(uint8_t *bytes);
void btutil_adv_print128bitUUID(uint8_t *bytes);
void btutil_adv_print32bitUUID(uint8_t *bytes);
void btutil_adv_print16bitUUID(uint8_t *bytes);
void btutil_adv_printFieldDecode(uint8_t *bytes);

//////////////////////////////////////////////////////
//
// Public
//
///////////////////////////////////////////////////////


int btutil_adv_len(uint8_t *packet)
{
	int i;
	for(i=packet[0]+1;packet[i-1];i=i+packet[i]+1);
	return i-1;

}

void btutil_adv_printPacketBytes(uint8_t *packet)
{
	int len = btutil_adv_len(packet);
	for(int i=0;i<len;i++)
	{
		TEMP_PRINTF("%02X ",packet[i]);
	}
}

// Iterate over the whole ADV Pack and print out each field as a row
void btutil_adv_printPacketDecode(uint8_t *packet)
{
	int i = 0;
	do
	{
		btutil_adv_printFieldDecode(&packet[i]);
		i = i + packet[i] + 1;
	} while(packet[i]);

}

//////////////////////////////////////////////////////
//
// General
//
///////////////////////////////////////////////////////

// Prints the bytes of a field starting at the offset (using the length of bytes[0])
void btutil_adv_printBytesOffset(uint8_t *bytes,uint32_t offset)
{
    int i;
    for(i=offset;i<bytes[0]-1;i++)
        TEMP_PRINTF("%02X ",bytes[2+i]);
}

// Print the whole field starting at offset 0
void btutil_adv_printFieldBytes(uint8_t *bytes)
{
    btutil_adv_printBytesOffset(bytes,0);
 }



///////////////////////////////////////////////////////////////
//
// Specific Field Types
//
///////////////////////////////////////////////////////////////

void btutil_adv_printNameField(uint8_t *bytes)
{
    for(int i = 0; i < bytes[0]; i++){
        TEMP_PRINTF("%c",bytes[1+i]);
    }
}
void btutbtutil_adv_printUnknownField(char *buff, uint8_t *bytes)
{
    TEMP_PRINTF("Len:%02X Type:%02X",bytes[0],bytes[1]);
}

void btutil_adv_printFlagsField(uint8_t *bytes)
{

    TEMP_PRINTF("%02X ",bytes[2]);

    if(bytes[2] & 0x01)
        TEMP_PRINTF("LE Ltd Discoverable ");

    if(bytes[2] & 0x02)
        TEMP_PRINTF("LE General Discoverable ");

    if(bytes[2] & 0x04)
        TEMP_PRINTF("BR/EDR Not Supported ");

    if(bytes[2] & 0x08)
        TEMP_PRINTF("BR/EDR Controller ");

    if(bytes[2] & 0x10)
        TEMP_PRINTF("BR/EDR Host ");
}



void btutil_adv_printMfgDataField(uint8_t *bytes)
{
    uint16_t mfg;
    mfg = bytes[2] | bytes[3]<<8;
    TEMP_PRINTF("%s ",btutil_getCompanyName(mfg));
    if(mfg == 0x004C && bytes[4] == 0x02)
    {
        TEMP_PRINTF("iBeacon ");
        btutil_adv_printBytesOffset(bytes,3);
    }
    else
        btutil_adv_printBytesOffset(bytes,2);
}

//0xXX:-127 to +127dBm
//Note: when the TX Power Level tag is not present,
//the TX power level of the packet is unknown.
void btutil_adv_printTxPowerField(uint8_t *bytes)
{
    uint16_t power;
    power = bytes[0];
    TEMP_PRINTF("%d ",(signed int)power);
}



void btutil_adv_printSlaveIntervalRangeField(uint8_t *bytes)
{
    TEMP_PRINTF("%dms-", (5*(bytes[2] | (bytes[3]<<8)))>>2);
    TEMP_PRINTF("%dms ", (5*(bytes[4] | (bytes[5]<<8)))>>2);
}


void btutil_adv_PrintAdvIntervalField(uint8_t *bytes)
{
    TEMP_PRINTF("%dms ", (5*(bytes[2] | (bytes[3]<<8)))>>3);
}


void btutil_adv_printLERoleField(uint8_t *bytes)
{

    TEMP_PRINTF("%02X ",bytes[2]);

    if(bytes[2] == 0x00)
        TEMP_PRINTF("Only Peripheral Role supported ");

    if(bytes[2] == 0x01)
        TEMP_PRINTF("Only Central Role supported ");

    if(bytes[2] == 0x02)
        TEMP_PRINTF("Peripheral Role preferred ");

    if(bytes[2] == 0x03)
        TEMP_PRINTF("Central Role preferred ");
}

void btutil_adv_decodeSecurityManagerOOBField(uint8_t *bytes)
{

    TEMP_PRINTF("%02X ",bytes[2]);

    if(bytes[2] & 0x00)
        TEMP_PRINTF("OOB Flags Field ");

    if(bytes[2] & 0x01)
        TEMP_PRINTF("LE supported ");

    if(bytes[2] & 0x02)
        TEMP_PRINTF("Simultaneous LE and BR/EDR Capable ");

    if(bytes[2] & 0x03)
        TEMP_PRINTF("Address type ");
}


void btutil_adv_print16bitServiceUUID(uint8_t *bytes)
{
	btutil_adv_print16bitUUID(&bytes[2]);
}

void btutil_adv_decode32bitServiceUUID(uint8_t *bytes)
{
	btutil_adv_print128bitUUID(&bytes[2]);
}

void btutil_adv_decode128bitServiceUUID( uint8_t *bytes)
{
	btutil_adv_print128bitUUID(&bytes[2]);
}

void btutil_adv_decodePublicAddress(uint8_t *bytes)
{
	btutil_adv_printFieldBytes(bytes);
}


void btutil_adv_print128bitUUID(uint8_t *bytes)
{
    TEMP_PRINTF(
            "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
            bytes[15],
            bytes[14],
            bytes[13],
            bytes[12],
            bytes[11],
            bytes[10],
            bytes[9],
            bytes[8],
            bytes[7],
            bytes[6],
            bytes[5],
            bytes[4],
            bytes[3],
            bytes[2],
            bytes[1],
            bytes[0]
    );
}


void btutil_adv_print32bitUUID(uint8_t *bytes)
{
    TEMP_PRINTF(
            "%02X%02X%02X%02X",
            bytes[3],
            bytes[2],
            bytes[1],
            bytes[0]
    );
}

void btutil_adv_print16bitUUID(uint8_t *bytes)
{
    TEMP_PRINTF(
            "%02X%02X",
            bytes[1],
            bytes[0]
    );
}


struct btutil_adv_decode_t {
    uint8_t code;
    char *name;
    void (*fcn)(uint8_t *bytes);
};

// https://www.bluetooth.com/specifications/assigned-numbers/generic-access-profile
struct btutil_adv_decode_t btutil_adv_decodeArray[] = {
        {0x01, "Flags",btutil_adv_printFlagsField},
        {0x02, "16-bit Service UUID",btutil_adv_print16bitServiceUUID},
        {0x03, "16-bit Service UUID",btutil_adv_print16bitServiceUUID},
        {0x04, "32-bit Service UUID",btutil_adv_decode32bitServiceUUID},
        {0x05, "32-bit Service UUID",btutil_adv_decode32bitServiceUUID},
        {0x06, "128-bit Service UUIDs", btutil_adv_decode128bitServiceUUID},
        {0x07, "128-bit Service UUIDs", btutil_adv_decode128bitServiceUUID},
        {0x08, "Short Name ", btutil_adv_printNameField},
        {0x09, "Complete Name", btutil_adv_printNameField},
        {0x0A, "Tx Power Level", btutil_adv_printTxPowerField},
        {0x0D, "Device Class", btutil_adv_printFieldBytes},
        {0x0E, "Pairing Hash C", btutil_adv_printFieldBytes},
        {0x0E, "Pairing Hash C-192", btutil_adv_printFieldBytes},
        {0x0F, "Pairing Randomizer R", btutil_adv_printFieldBytes},
        {0x0F, "Pairing Randomizer R-192", btutil_adv_printFieldBytes},
        {0x10, "Device ID", btutil_adv_printFieldBytes},
        {0x10, "Security Manager TK Value", btutil_adv_printFieldBytes},
        {0x11, "Security Manager Out of Band Flags", btutil_adv_decodeSecurityManagerOOBField},
        {0x12, "Slave Connection Interval Range", btutil_adv_printSlaveIntervalRangeField},
        {0x14, "16-bit Service Solicitation UUIDs", btutil_adv_print16bitServiceUUID},
        {0x15, "128-bit Service Solicitation UUIDs", btutil_adv_decode128bitServiceUUID},
        {0x16, "Service Data", btutil_adv_printFieldBytes},
        {0x16, "16-bit Service Data UUID", btutil_adv_printFieldBytes},
        {0x17, "Public Target Address", btutil_adv_printFieldBytes},
        {0x18, "Random Target Address", btutil_adv_printFieldBytes},
        {0x19, "Appearance", btutil_adv_printFieldBytes},
        {0x1A, "Advertising Interval", btutil_adv_PrintAdvIntervalField},
        {0x1B, "LE Bluetooth Device Address", btutil_adv_printFieldBytes},
        {0x1C, "LE Role", btutil_adv_printLERoleField},
        {0x1D, "Simple Pairing Hash C-256", btutil_adv_printFieldBytes},
        {0x1E, "Simple Pairing Randomizer R-256", btutil_adv_printFieldBytes},
        {0x1F, "32-bit Service Solitication UUIDs",btutil_adv_decode32bitServiceUUID},
        {0x20, "32-bit Service Data UUID",btutil_adv_decode32bitServiceUUID},
        {0x21, "128-bit Service Data UUID",btutil_adv_decode128bitServiceUUID},
        {0x22, "LE Secure Connections Confirmation Value",btutil_adv_printFieldBytes},
        {0x23, "LE Secure Connections Random Value",btutil_adv_printFieldBytes},
        {0x24, "URI",btutil_adv_printFieldBytes},
        {0x25, "Indoor Positioning",btutil_adv_printFieldBytes},
        {0x26, "Transport Discovery Data",btutil_adv_printFieldBytes},
        {0x27, "LE Supported Features",btutil_adv_printFieldBytes},
        {0x28, "Channel Map Update Indication",btutil_adv_printFieldBytes},
        {0x29, "PB-ADV",btutil_adv_printFieldBytes},
        {0x2A, "Mesh Message",btutil_adv_printFieldBytes},
        {0x2B, "Mesh Beacon",btutil_adv_printFieldBytes},
        {0x3D, "3D Information Data",btutil_adv_printFieldBytes},
        {0xFF, "MFG Data", btutil_adv_printMfgDataField}
};




//// Look at the type of field then call the function which prints that type of field
void btutil_adv_printFieldDecode(uint8_t *bytes)
{
    int numElements = sizeof(btutil_adv_decodeArray)/sizeof(struct btutil_adv_decode_t);
    int i;

    for(i = 0; i < numElements; i++)
    {
        if(bytes[1] == btutil_adv_decodeArray[i].code)
        {
            TEMP_PRINTF("%s ",btutil_adv_decodeArray[i].name);
            (*btutil_adv_decodeArray[i].fcn)(bytes);
            TEMP_PRINTF("\n");
            return;
        }
    }
    TEMP_PRINTF("Unknown\n");
}

// Eddystone prefix: 02 01 06 03 03 AA FE
wiced_bool_t btutil_adv_isEddystone(uint8_t *data)
{
    if(
            data[0] == 0x02 &&
            data[1] == 0x01 &&
            data[2] == 0x06 &&
            data[3] == 0x03 &&
            data[4] == 0x03 &&
            data[5] == 0xAA &&
            data[6] == 0xFE
    )
        return WICED_TRUE;
    else
        return WICED_FALSE;
}

// iBeacon prefix: 02 01 06 1A FF 4C 00 02
wiced_bool_t btutil_adv_isiBeacon(uint8_t *data)
{
    if(
            data[0] == 0x02 &&
            data[1] == 0x01 &&
            data[4] == 0xFF &&
            data[5] == 0x4C &&
            data[6] == 0x00 &&
            data[7] == 0x02
    )
        return WICED_TRUE;
    else
        return WICED_FALSE;
}

// Cypress Company code: 0x0131
wiced_bool_t btutil_adv_isCypress(uint8_t *data)
{
    uint8_t mfgLen;
    uint8_t* mfgData = wiced_bt_ble_check_advertising_data(data,0xFF,&mfgLen);

    if(
            mfgData &&
            mfgLen == 3 &&
            mfgData[0] == 0x31 &&
            mfgData[1] == 0x01
    )
        return WICED_TRUE;
    else
        return WICED_FALSE;
}
