#line 1 "C:/Users/Korisnik/Desktop/Nikola Golubovic/Heartrate and Oximetry click/Verzija OLD pulse oximeter/HR_click/code/HR_click_example.c"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"





typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;
typedef signed long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;
typedef unsigned long long uint_least64_t;



typedef signed long int int_fast8_t;
typedef signed long int int_fast16_t;
typedef signed long int int_fast32_t;
typedef signed long long int_fast64_t;


typedef unsigned long int uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef signed long int intptr_t;
typedef unsigned long int uintptr_t;


typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
#line 1 "c:/users/korisnik/desktop/nikola golubovic/heartrate and oximetry click/verzija old pulse oximeter/hr_click/code/max30100_driver.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"
#line 14 "c:/users/korisnik/desktop/nikola golubovic/heartrate and oximetry click/verzija old pulse oximeter/hr_click/code/max30100_driver.h"
uint8_t MAX30100_Get( uint8_t anID );
uint8_t MAX30100_GetRevisionID();
uint8_t MAX30100_GetPartID();
uint8_t MAX30100_GetConfig();
uint8_t MAX30100_GetStatus();




void MAX30100_SetConfig ( uint8_t cfg );
void MAX30100_SetInterrupt( uint8_t intrpts );
void MAX30100_Reset();
void MAX30100_Init();



uint8_t MAX30100_Read( int16_t* irBuff, int16_t* redBuff );


void MAX30100_ReadTemp( uint16_t* tempValue );
#line 1 "c:/users/korisnik/desktop/nikola golubovic/heartrate and oximetry click/verzija old pulse oximeter/hr_click/code/max30100_defs.h"
#line 14 "C:/Users/Korisnik/Desktop/Nikola Golubovic/Heartrate and Oximetry click/Verzija OLD pulse oximeter/HR_click/code/HR_click_example.c"
uint16_t TFT_DataPort at GPIOE_ODR;
sbit TFT_RST at GPIOE_ODR.B8;
sbit TFT_RS at GPIOE_ODR.B12;
sbit TFT_CS at GPIOE_ODR.B15;
sbit TFT_RD at GPIOE_ODR.B10;
sbit TFT_WR at GPIOE_ODR.B11;
sbit TFT_BLED at GPIOE_ODR.B9;


sbit dataReady at GPIOD_IDR.B10;


char const extern Arial_Black24x33_Regular[], Arial_Black27x38_Regular[],
 Arial_Black64x90_Regular[], Tahoma19x23_Regular[],
 active_jpg[6823], idle_red_jpg[6089];
int IRScreenText[16], HBScreenText[16], REDScreenText[16], SPScreenText[16];


static void MCU_Init(){
 GPIO_Digital_Input(&GPIOD_BASE, _GPIO_PINMASK_10);
 I2C1_Init_Advanced(400000, &_GPIO_MODULE_I2C1_PB67);
 Delay_ms(100);
}


static void DisplayInit() {
 TFT_Init_ILI9341_8bit(320, 240);
 TFT_BLED = 1;
 TFT_Image_Jpeg(0, 0, idle_red_jpg);

 TFT_Set_Font(Tahoma19x23_Regular, CL_WHITE, FO_HORIZONTAL);
 TFT_Write_Text("PLACE YOUR FINGER ON THE CLICK", 10, 194);
}


void UpdateValues ( uint16_t irVal, uint16_t redVal) {
 TFT_Set_Font(Tahoma19x23_Regular, 0xE8C4, FO_HORIZONTAL);
 TFT_Write_Text(IRScreenText, 10, 50);
 WordToStr(irVal, IRScreenText);
 TFT_Set_Font(Tahoma19x23_Regular, CL_WHITE, FO_HORIZONTAL);
 TFT_Write_Text(IRScreenText, 10, 50);

 TFT_Set_Font(Tahoma19x23_Regular, 0xE8C4, FO_HORIZONTAL);
 TFT_Write_Text(REDScreenText, 10, 80);
 WordToStr(redVal, REDScreenText);
 TFT_Set_Font(Tahoma19x23_Regular, CL_WHITE, FO_HORIZONTAL);
 TFT_Write_Text(REDScreenText, 10, 80);
}


void SetActiveScreen() {
 TFT_Image_Jpeg(0, 0, active_jpg);

 TFT_Set_Font(Arial_Black64x90_Regular, 0xE8C4, FO_HORIZONTAL);
 TFT_Write_Text(HBScreenText, 105, 65);
 TFT_Set_Font(Arial_Black27x38_Regular, CL_WHITE, FO_HORIZONTAL);
 TFT_Write_Text("BPM", 126, 182);
 TFT_Set_Font(Arial_Black24x33_Regular, CL_WHITE, FO_HORIZONTAL);
 TFT_Write_Text("SpO2:", 87, 10);
 TFT_Write_Text(SPScreenText, 167, 10);
}


void UndoActiveScreen() {

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


void main() {
 char volatile i, sampleNum;
 unsigned long volatile
 tempValue,
 irBuff[16] = {0}, redBuff[16] = {0},
 averIrVal, averRedVal;
 float spVal;

 MCU_Init();
 DisplayInit();
 MAX30100_Reset();
 MAX30100_Init();


 while (  ( dataReady != 0 )  || ( ( MAX30100_GetStatus() & 0x70 ) == 0 ) ) {
 MAX30100_ReadTemp(&tempValue);
 }

 while (1) {
 if  ( dataReady == 0 ) 
 {
 if ( ( MAX30100_GetStatus() & 0x20 ) != 0 ) {

 sampleNum = MAX30100_Read(irBuff, redBuff);

 if ( sampleNum >= 1 ) {
 averIrVal = 0;
 averRedVal = 0;
 spVal=0;
 for ( i = 0; i < sampleNum; i++ ) {
 averIrVal += irBuff[i];
 averRedVal += redBuff[i];
 spVal+=((redBuff[i]*100)/irBuff[i]);
 if(br <  750  && irBuff[i]>30000 && irBuff[i]<60000)
 buffer[br++] = irBuff[i];
 }
 averIrVal /= sampleNum;
 averRedVal /= sampleNum;
 spVal /= sampleNum;
 UpdateValues(averIrVal, averRedVal);
 spVal/=100;
 if(br >=  750 ) break;
 }
 }
 }
 }

 for(cnt = 12; cnt<br ;cnt++) {
 suma = 0;
 for(brojac = cnt; brojac>=cnt-7; brojac--) {
 suma+=buffer[brojac];
 }
 suma/=10;
 buffer[cnt] = suma;
 }

 for(cnt = 15; cnt<br-12; cnt++)
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
 spVal=118-(36*spVal);
 FloatToStr(spVal,SPScreenText);

 SetActiveScreen();
 Delay_ms (2000);

 }
