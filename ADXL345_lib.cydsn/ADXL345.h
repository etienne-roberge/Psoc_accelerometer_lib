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

#include <stdlib.h>
#include "project.h"
#include <stdio.h>

#define NUMBER_OF_SENSORS   (0x16)
#define TRANSFER_CMPLT      (0x00u)
#define SLAVE_NOT_READY     (0x01u)
#define TRANSFER_ERROR      (0xFFu)

uint32 initAccel();
uint32 readAccel();

/* [] END OF FILE */
