
#include <stdio.h>
#include "wiced_bt_types.h"

/**************************************************************************************************
* Function Name: btutil_printBDaddress()
***************************************************************************************************
* Summary:
*   This is the utility function that prints the address of the Bluetooth device
*
* Parameters:
*   wiced_bt_device_address_t bdadr                : Bluetooth address
*
* Return:
*  void
*
**************************************************************************************************/
void btutil_printBDaddress(wiced_bt_device_address_t bdadr)
{
  // printf("0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,",bdadr[0],bdadr[1],bdadr[2],bdadr[3],bdadr[4],bdadr[5]);
    printf("%02X:%02X:%02X:%02X:%02X:%02X",bdadr[0],bdadr[1],bdadr[2],bdadr[3],bdadr[4],bdadr[5]);

}
