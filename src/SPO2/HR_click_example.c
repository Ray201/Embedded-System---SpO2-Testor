/*
** Revision: Nikola Golubovic
** Mikroe, 2015.
*/

#include <stdint.h>
#include "MAX30100_Driver.h" // MAX30100_Driver.h
#include "MAX30100_Defs.h"   // MAX30100_Defs.h
#define DataIsReady()     ( dataReady == 0 )
#define DataIsNotReady()  ( dataReady != 0 )
#define OGR 750

// TFT module connections
uint16_t TFT_DataPort at GPIOE_ODR;
sbit     TFT_RST at GPIOE_ODR.B8;
sbit     TFT_RS at GPIOE_ODR.B12;
sbit     TFT_CS at GPIOE_ODR.B15;
sbit     TFT_RD at GPIOE_ODR.B10;
sbit     TFT_WR at GPIOE_ODR.B11;
sbit     TFT_BLED at GPIOE_ODR.B9;
// End TFT module connections

sbit dataReady at GPIOD_IDR.B10;

// Resources
char const extern Arial_Black24x33_Regular[], Arial_Black27x38_Regular[],
                  Arial_Black64x90_Regular[], Tahoma19x23_Regular[],
                  active_jpg[6823], idle_red_jpg[6089];
int IRScreenText[16], HBScreenText[16], REDScreenText[16], SPScreenText[16];

// MCU Initialize
static void MCU_Init(){
  GPIO_Digital_Input(&GPIOD_BASE, _GPIO_PINMASK_10);
  I2C1_Init_Advanced(400000, &_GPIO_MODULE_I2C1_PB67);
  Delay_ms(100);
}

// Display Initialize
static void DisplayInit() {
  TFT_Init_ILI9341_8bit(320, 240);
  TFT_BLED = 1;
  TFT_Image_Jpeg(0, 0, idle_red_jpg); // Set background
  // Set label
  TFT_Set_Font(Tahoma19x23_Regular, CL_WHITE, FO_HORIZONTAL);
  TFT_Write_Text("PLACE YOUR FINGER ON THE CLICK", 10, 194);
}

// Update Values on TFT screen
void UpdateValues ( uint16_t irVal, uint16_t redVal) {
  TFT_Set_Font(Tahoma19x23_Regular, 0xE8C4, FO_HORIZONTAL);
  TFT_Write_Text(IRScreenText, 10, 50);                       // ERASE InfraRed Sensor Data
  WordToStr(irVal, IRScreenText);
  TFT_Set_Font(Tahoma19x23_Regular, CL_WHITE, FO_HORIZONTAL); // WRITE NEW Data
  TFT_Write_Text(IRScreenText, 10, 50);

  TFT_Set_Font(Tahoma19x23_Regular, 0xE8C4, FO_HORIZONTAL);
  TFT_Write_Text(REDScreenText, 10, 80);                      // ERASE Red Sensor Data
  WordToStr(redVal, REDScreenText);
  TFT_Set_Font(Tahoma19x23_Regular, CL_WHITE, FO_HORIZONTAL); // WRITE NEW Data
  TFT_Write_Text(REDScreenText, 10, 80);
}

// Setting background and labels
void SetActiveScreen() {
  TFT_Image_Jpeg(0, 0, active_jpg); // Set background
  // Set labels
  TFT_Set_Font(Arial_Black64x90_Regular, 0xE8C4, FO_HORIZONTAL);
  TFT_Write_Text(HBScreenText, 105, 65);
  TFT_Set_Font(Arial_Black27x38_Regular, CL_WHITE, FO_HORIZONTAL);
  TFT_Write_Text("BPM", 126, 182);
  TFT_Set_Font(Arial_Black24x33_Regular, CL_WHITE, FO_HORIZONTAL);
  TFT_Write_Text("SpO2:", 87, 10);
  TFT_Write_Text(SPScreenText, 167, 10);
}

// Erase labels
void UndoActiveScreen() {
 // Set labels
  TFT_Set_Font(Arial_Black64x90_Regular, CL_WHITE, FO_HORIZONTAL);
  TFT_Write_Text(HBScreenText, 105, 65);
  TFT_Set_Font(Arial_Black27x38_Regular, 0xE8C4, FO_HORIZONTAL);
  TFT_Write_Text("BPM", 126, 182);
  TFT_Set_Font(Arial_Black24x33_Regular, 0xE8C4, FO_HORIZONTAL);
  TFT_Write_Text("SpO2:", 87, 10);
  TFT_Write_Text(SPScreenText, 167, 10);
 }
uint16_t buffer[2000];
uint16_t maks[2000];
int br, cnt, brojac, brmaks, max_fl;
long suma;

// Main program
void main() {
  char volatile i, sampleNum;                          // sampleNum - number of read samples
  unsigned long volatile  
                tempValue,                             // Raw value from the temperature sensor
                irBuff[16]  = {0}, redBuff[16] = {0},  // Raw values from LED diodes
                averIrVal, averRedVal;                 // AverIrVal, averRedVal - averaged values
                float spVal;
  
  MCU_Init();         // MCU Initialize
  DisplayInit();      // Display the initial screen
  MAX30100_Reset();   // Reset the sensor MAX30100_Reset()
  MAX30100_Init();    // Initialize the sensor MAX30100_Init()

  // Wait for the temperature reading
  while ( DataIsNotReady() || ( ( MAX30100_GetStatus() & 0x70 ) == 0 ) ) {  // MAX30100_GetStatus()
     MAX30100_ReadTemp(&tempValue);                                         // Read temperature MAX30100_ReadTemp()
  }
  
  while (1) {
    if DataIsReady()  // Wait for data
    {
      if ( ( MAX30100_GetStatus() & 0x20 ) != 0 ) {   // MAX30100_GetStatus()
          // MAX30100_Read() - Read IR and RED sensor data and store it in sampleNum
          sampleNum = MAX30100_Read(irBuff, redBuff);
          // Average data
          if ( sampleNum >= 1 ) {
            averIrVal = 0;
            averRedVal = 0;
            spVal=0;
              for ( i = 0; i < sampleNum; i++ ) {
                averIrVal += irBuff[i];                            // IrVal SUM
                averRedVal += redBuff[i];                          // RedVal SUM
                
                  spVal+=((redBuff[i]*100)/irBuff[i]);
                  
                  
                  
                  // SPVal SUM (SPVal measures SpO2 as ratio R/IR)
                if(br < OGR && irBuff[i]>30000 && irBuff[i]<60000) // OGR = 750
                      buffer[br++] = irBuff[i];
              }
            averIrVal  /= sampleNum; // Average IR data
            averRedVal /= sampleNum; // Average RED data
            spVal      /= sampleNum; // Average SP data
            UpdateValues(averIrVal, averRedVal); // Update Values on TFT screen
            spVal/=100; // ???
            if(br >= OGR) break;     // OGR is 750
          }
      }
    }
  }
  
  for(cnt = 12; cnt<br ;cnt++) {   // Moving average
      suma = 0;
      for(brojac = cnt; brojac>=cnt-7; brojac--) {
          suma+=buffer[brojac];
      }
      suma/=10;
      buffer[cnt] = suma;
  }
  
  for(cnt = 15; cnt<br-12; cnt++)  // Searching max
  {
      max_fl = 1;
      for(brojac = cnt-15; (brojac<=cnt+15) && max_fl;brojac++) {
          if(buffer[cnt]<buffer[brojac])max_fl = 0;
      }
      if(max_fl)
          maks[brmaks++] = buffer[cnt];
  }

     brmaks=brmaks*4;
     WordToStr(brmaks, HBScreenText);
       spVal=118-(36*spVal);        //getting value of SpO2 in % (r/ir=0,5 for SpO2 100% r/ir=1 for SpO2 82% and r/ir=2 for 0%
     FloatToStr(spVal,SPScreenText);

     SetActiveScreen();
     Delay_ms (2000);
     //UndoActiveScreen();
 }