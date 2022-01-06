/*******************************************************************************
*
* PSoC ADXL345 driver using I2C.
* Copyright (C) 2021, Etienne Roberge
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
*
* 3. Neither the name of the copyright holder nor the names of its contributors
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************/

#include "ADXL345.h"

uint32 initAccel()
{
    uint32 status = TRANSFER_ERROR;
    
    (void) I2CM_I2CMasterClearStatus();
    
    uint32 aaa = I2CM_I2CMasterSendStart(0x53,I2CM_I2C_WRITE_XFER_MODE, 0);
   
    if(I2CM_I2C_MSTR_NO_ERROR == aaa)
    {
         aaa = I2CM_I2CMasterWriteByte(0x2D,0);
         if(I2CM_I2C_MSTR_NO_ERROR == aaa)
         {
            aaa = I2CM_I2CMasterWriteByte(8,0);
            if(I2CM_I2C_MSTR_NO_ERROR == aaa)
            {
              status = TRANSFER_CMPLT;
            }
         }
    }
    I2CM_I2CMasterSendStop(0);
    return (status);     
}

uint32 readAccel()
{
    uint8  buffer[1];
    uint32 status = TRANSFER_ERROR;

    buffer[0] = 0x32;
    
    (void) I2CM_I2CMasterClearStatus();
    
    uint32 aaa=I2CM_I2CMasterWriteBuf(0x53, buffer, 1, I2CM_I2C_MODE_COMPLETE_XFER);
   
    if(I2CM_I2C_MSTR_NO_ERROR == aaa)
    {
        
        while (0u == (I2CM_I2CMasterStatus() & I2CM_I2C_MSTAT_WR_CMPLT))
        {
            /* Wait */
        }
        
            uint8 sizeToRead = 6;
            uint8 sensorValueBuffer[6];
    
            aaa=I2CM_I2CMasterReadBuf(0x53, sensorValueBuffer, sizeToRead, I2CM_I2C_MODE_COMPLETE_XFER);
            
            if(I2CM_I2C_MSTR_NO_ERROR ==  aaa)
            {
                /* If I2C read started without errors, 
                / wait until master complete read transfer */
                while (0u == (I2CM_I2CMasterStatus() & I2CM_I2C_MSTAT_RD_CMPLT))
                {
                    /* Wait */
                }
                float X_out = ( sensorValueBuffer[0] | sensorValueBuffer[1] << 8); // X-axis value
                X_out = X_out/256.0;
                float Y_out = ( sensorValueBuffer[2] | sensorValueBuffer[3] << 8); // Y-axis value
                Y_out = Y_out/256.0;
                float Z_out = ( sensorValueBuffer[4] | sensorValueBuffer[5] << 8); // Z-axis value
                Z_out = Z_out/256.0;
                I2CM_I2CMasterSendStop(0);
            }
       
         
    }
    return (status);     
}

/* [] END OF FILE */
