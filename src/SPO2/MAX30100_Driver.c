/*
** MAX30100 communication driver
** (c) mikroe, 2015
*/
#include "MAX30100_Driver.h"
#include "stdlib.h"
#include "MAX30100_Defs.h"
//#include "stdint.h"

/*#if defined(DEBUG_LOG)
uint8_t
  debugText[16];
#endif*/

/*
** write data to the sensor
** @param wrAddr address to write to
** @param wrData data to write
*/

int debug;
// MAX30100_SendToSensor
static void MAX30100_SendToSensor (uint8_t wrAddr, uint8_t wrData) {
  //uint8_t dataToSend[2];
  //dataToSend[0] = wrAddr;
  //dataToSend[1] = wrData;
  //I2C1_Start();  // I2C start signal
  // send address to write to and then data to be written
  //I2C1_Write(MAX30100_I2C_ADR, dataToSend, 2, END_MODE_STOP); // MAX30100_I2C_ADR
    
    TM_I2C_Write(MAX30100_I2C, MAX30100_I2C_ADR, wrAddr, wrData);
    
    /* Send to device */
    //TM_I2C_Write(BMP180_I2C, BMP180_I2C_ADDRESS, BMP180_REGISTER_CONTROL, command);
    
}

 /**
  * read data from the sensor
  * @param rAddr   register address to read from
  * @param rxBuff  buffer where read data are to be placed
  * @param dataNum number of bytes to read
  */

// MAX30100_ReadFromSensor
static void MAX30100_ReadFromSensor (uint8_t rAddr, uint8_t* rxBuff, uint8_t dataNum)
{
    // I2C1_Start(); // I2C start signal
    //I2C1_Write(MAX30100_I2C_ADR, &rAddr, 1, END_MODE_RESTART);   // send the register address
    //TM_I2C_ReadMulti(BMP180_I2C, BMP180_I2C_ADDRESS, BMP180_REGISTER_RESULT, data, 3);
   // if(dataNum == 1){
   //     *rxBuff=TM_I2C_Read(MAX30100_I2C, MAX30100_I2C_ADR, rAddr);
   // uint8_t TM_I2C_Read(I2C_TypeDef* I2Cx, uint8_t address, uint8_t reg)
   // }
   // else{
        TM_I2C_ReadMulti(MAX30100_I2C, MAX30100_I2C_ADR, rAddr, rxBuff, dataNum); // receive data
        
   // }
}

//MAX30100_ReadFromSensor(FIFO_DATA_REG, samples, 4);

/*******************************************************
* getters
*******************************************************/

// get wanted ID
// @return wanted ID
// MAX30100_Get
uint8_t MAX30100_Get(uint8_t anID) {
  uint8_t readData;
  MAX30100_ReadFromSensor(anID, &readData, 1);
  return readData;
}


// get revision ID
// @return revision ID
// MAX30100_GetRevisionID()
uint8_t MAX30100_GetRevisionID() {
  uint8_t readData;
  MAX30100_ReadFromSensor(REVISION_ID, &readData, 1);
  return readData;
}


// get part ID
// @return part ID
// MAX30100_GetPartID()
uint8_t MAX30100_GetPartID() {
  uint8_t readData;
  MAX30100_ReadFromSensor(PART_ID, &readData, 1);
  return readData;
}

// get config
// @return config
// MAX30100_GetConfig()
uint8_t MAX30100_GetConfig() {
  uint8_t readData;
  MAX30100_ReadFromSensor(MODE_CONFIG, &readData, 1);
  return readData;
}

// get status
// @return status
// MAX30100_GetStatus()
uint8_t MAX30100_GetStatus() {
  uint8_t readData;
  MAX30100_ReadFromSensor(INT_STATUS, &readData, 1);
  return readData;
}

/*******************************************************
* setters
*******************************************************/

// send configuration
// @param cfg desired config value
// MAX30100_SetConfig ()
void MAX30100_SetConfig (uint8_t cfg) {
  MAX30100_SendToSensor(MODE_CONFIG, cfg); // MAX30100_SendToSensor
}

// set interrupts
// @param intrpts desired interrupts
// MAX30100_SetInterrupt()
void MAX30100_SetInterrupt(uint8_t intrpts) {
  MAX30100_SendToSensor(MODE_CONFIG, intrpts); // MAX30100_SendToSensor
}

// read data from the sensor
// @param irValue  data from IR LED
// @param redValue data from red LED
// MAX30100_Read()
uint8_t MAX30100_Read (uint16_t* irBuff,uint16_t* redBuff) {
  uint8_t i, sampleNum = 0;
  uint8_t volatile wrPtr, rdPtr, ovPtr, samples[4];

  wrPtr = MAX30100_Get(FIFO_WRITE_PTR);
  rdPtr = MAX30100_Get(FIFO_READ_PTR);
  
  sampleNum = abs( 16 + wrPtr-rdPtr ) % 16;

  /*#if defined(DEBUG_LOG)
  if ( sampleNum > 1 )
  {
    asm nop;
  }
  #endif*/
    /*
  
  if ( sampleNum >= 1 )
  {
    for ( i = 0; i < sampleNum; ++i )
    {
      // read data
      MAX30100_ReadFromSensor(FIFO_DATA_REG, samples, 4);
      ( (uint8_t*)irBuff   )[0]  = samples[1];
      ( (uint8_t*)irBuff++ )[1]  = samples[0];

      ( (uint8_t*)redBuff   )[0]  = samples[3];
      ( (uint8_t*)redBuff++ )[1]  = samples[2];
    }
   //   printf("sample0 is %d\n",samples[0]);
    //  printf("sample1 is %d\n",samples[1]);
     // printf("sample2 is %d\n",samples[2]);
     // printf("sample3 is %d\n",samples[3]);
  }
    
    printf("wrPtr is %d\n",wrPtr);
    printf("rdPtr is %d\n",rdPtr);
   // printf("sample0 is %d\n",samples[0]);
    printf("sample1 is %d\n",samples[1]);
    printf("sample2 is %d\n",samples[2]);
   // printf("sample3 is %d\n",samples[3]);
     */
    
    MAX30100_ReadFromSensor(FIFO_DATA_REG, samples, 4);
    ( (uint8_t*)irBuff   )[0]  = samples[1];
    ( (uint8_t*)irBuff++ )[1]  = samples[0];
    
    ( (uint8_t*)redBuff   )[0]  = samples[3];
    ( (uint8_t*)redBuff++ )[1]  = samples[2];
    
  return sampleNum;
}

// read calibration temperature from the sensor
// @param tempValue data from temperature sensor
// MAX30100_ReadTemp()
void MAX30100_ReadTemp(uint16_t* tempValue) {
  uint8_t tempInt, tempFrac;
  MAX30100_ReadFromSensor(TEMP_INTEGER, &tempInt, 1); // read temperature - integer part
  MAX30100_ReadFromSensor(TEMP_FRACTION, &tempFrac, 1); // read temperature - fraction part

  ( (uint8_t*)tempValue )[1]  = tempInt;
  ( (uint8_t*)tempValue )[0]  = tempFrac;
}

// reset the sensor
// MAX30100_Reset()

void MAX30100_Reset() {
  char cfg;
  MAX30100_ReadFromSensor(MODE_CONFIG, &cfg, 1);
  cfg |= (1 << (6));
  MAX30100_SendToSensor(MODE_CONFIG, cfg);
  
  // wait for the RESET bit to clear itself
  
    while (1) {
    MAX30100_ReadFromSensor(MODE_CONFIG, &cfg, 1);
    if ( (cfg &= (1 << (6))) == 0 )
    {
      return;
    }
  }
    
}

void MAX30100_Set() {
    char cfg;
    MAX30100_ReadFromSensor(MODE_CONFIG, &cfg, 1);
    cfg &= ~(1 << (6));
    MAX30100_SendToSensor(MODE_CONFIG, cfg);
}
// initialize the sensor
// MAX30100_Init()
void MAX30100_Init()
{
  uint8_t cfg = 0;

  /* Initialize I2C */
  TM_I2C_Init(MAX30100_I2C, MAX30100_I2C_PINSPACK, MAX30100_I2C_SPEED);
  /* Test if device is connected */
 // if (!TM_I2C_IsDeviceConnected(MAX30100_I2C, MAX30100_I2C_ADR)) {
      /* Device is not connected */
 //     return MAX30100_I2C_Result_DeviceNotConnected;
 // }
    
    
  // read old and set new mode
  MAX30100_ReadFromSensor(MODE_CONFIG, &cfg, 1);
  cfg = ( cfg & ~0x07 ) | HR_ONLY;
  cfg = ( cfg & ~0x07 ) | SPO2_EN | TEMP_EN;

  MAX30100_SendToSensor(MODE_CONFIG, cfg);
  MAX30100_ReadFromSensor(SPO2_CONFIG, &cfg, 1); // read SpO2 configuration
  cfg |= SPO2_HI_RES_EN; // enable High Resolution SpO2
  cfg |= SAMPLES_50; // set samples per second
  cfg |= PULSE_WIDTH_1600; // set 16-bit ADC resolution
  MAX30100_SendToSensor(SPO2_CONFIG, cfg); // send new SpO2 configuration


  MAX30100_ReadFromSensor(LED_CONFIG, &cfg, 1); // read LED current control config
  cfg |= IR_CURRENT_500; // set IR LED current to be 50 mA
  cfg |= RED_CURRENT_240; // set RED LED current to be 24 mA
  MAX30100_SendToSensor(LED_CONFIG, cfg); // send new LED current control config

  // interrupt settings
  MAX30100_ReadFromSensor(INT_ENABLE, &cfg, 1);
  cfg |= ENA_HR_RDY;
  cfg |= ENA_SO2_RDY;
  cfg |= ENA_TEP_RDY;

  // send new interrupt settings
  MAX30100_SendToSensor(INT_ENABLE, cfg);
  debug=cfg;
}