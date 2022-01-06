/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "ADXL345.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Start the I2C Master */
    I2CM_Start();

    while(TRANSFER_CMPLT != initAccel())
    {
        CyDelay(500u);
    }
    CyDelay(10u);

    for(;;)
    {
        readAccel();
    }
}

/* [] END OF FILE */
