// H revision sketch
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------

//#define INCLUDE_TM1638 //{"Name":"INCLUDE_TM1638","Type":"autodefine","Condition":"[TM1638_ENABLEDMODULES]>0"}

//#define INCLUDE_WS2801 //{"Name":"INCLUDE_WS2801","Type":"autodefine","Condition":"[WS2801_RGBLEDCOUNT]>0"}

#define INCLUDE_WS2812B //{"Name":"INCLUDE_WS2812B","Type":"autodefine","Condition":"[WS2812B_RGBLEDCOUNT]>0"}

//#define INCLUDE_LEDBACKPACK //{"Name":"INCLUDE_LEDBACKPACK","Type":"autodefine","Condition":"[ENABLE_ADA_HT16K33_7SEGMENTS]>0 || [ENABLE_ADA_HT16K33_Matrix]>0"}

//#define INCLUDE_TM1637 //{"Name":"INCLUDE_TM1637","Type":"autodefine","Condition":"[TM1637_ENABLEDMODULES]>0"}

//#define INCLUDE_I2CLCD //{"Name":"INCLUDE_I2CLCD","Type":"autodefine","Condition":"[I2CLCD_enabled]>0"}

//#define INCLUDE_NOKIALCD //{"Name":"INCLUDE_NOKIALCD","Type":"autodefine","Condition":"[ENABLED_NOKIALCD]>0"}

//#define INCLUDE_OLED //{"Name":"INCLUDE_OLED","Type":"autodefine","Condition":"[ENABLED_OLEDLCD]>0"}

//#define INCLUDE_MAX7221MATRIX //{"Name":"INCLUDE_MAX7221MATRIX","Type":"autodefine","Condition":"[MAX7221_MATRIX_ENABLED]>0"}

//#define INCLUDE_74HC595_GEAR_DISPLAY //{"Name":"INCLUDE_74HC595_GEAR_DISPLAY","Type":"autodefine","Condition":"[ENABLE_74HC595_GEAR_DISPLAY]>0"}

//#define INCLUDE_MAX7221_MODULES //{"Name":"INCLUDE_MAX7221_MODULES","Type":"autodefine","Condition":"[MAX7221_ENABLEDMODULES]>0"}

//#define INCLUDE_6c595_GEAR_DISPLAY  //{"Name":"INCLUDE_6c595_GEAR_DISPLAY ","Type":"autodefine","Condition":"[ENABLE_6C595_GEAR_DISPLAY]>0"}

//#define INCLUDE_TACHOMETER  //{"Name":"INCLUDE_TACHOMETER ","Type":"autodefine","Condition":"[ENABLE_TACHOMETER]>0"}

//#define INCLUDE_BOOSTGAUGE  //{"Name":"INCLUDE_BOOSTGAUGE ","Type":"autodefine","Condition":"[ENABLE_BOOSTGAUGE]>0"}

#define INCLUDE_ILI9341

#define INCLUDE_TEENSY

#define INCLUDE_PL9823

#ifdef INCLUDE_TACHOMETER
#include <Tone.h>
#endif
#include <avr/pgmspace.h>
#include <EEPROM.h>

#include <SPI.h>
#include "Arduino.h"
#include <avr/pgmspace.h>

#include <Wire.h>
#include "LedControl.h"
#ifndef  INCLUDE_ILI9341
#include "Adafruit_GFX.h"
#endif
#include "FlowSerialRead.h"

//#ifdef INCLUDE_TM1638
#include <TM1638.h>
//#endif

#ifdef INCLUDE_WS2812B
#include <Adafruit_NeoPixel.h>
#endif

#ifdef INCLUDE_WS2801
#include <Adafruit_WS2801.h>
#endif

#ifdef INCLUDE_ILI9341
#include "ILI9341_t3.h"

//COLOR CODE
#define LIGHTRED 0xF8A0
#define LIGHTGREEN 0xAFEC
#define GREEN 0xFF00
#define RED 0xFF00

//Teensy 3.2 SPI pin
#define _sclk 13
#define _miso 12
#define _mosi 11
#define _cs 10
#define _dc 15
#define _rst 14

struct FramePosition {
  int X;
  int Y;
};

#define DATA_NUM 10

const int dataGEAR = 0;
const int dataRPM  = 1;
const int dataSPD  = 2;
const int dataLAP  = 3;
const int dataFUEL = 4;
const int dataTIME = 5;
const int dataTIRE = 6;
const int dataPOS  = 7;
const int dataTOGO = 8;
const int dataLAST = 9;

const int leftFront =0;
const int leftRear =1;
const int rightFront =2;
const int rightRear =3;

const int oilPres = 0;
const int oilTemp = 1;

//----------------------------------------------------------------------------------------------------------------------------//
//LCD Layout Constant
// X
const int Frame_Hor_Left = 5;
const int Frame_Hor_Center = 110; 
const int Frame_Hor_Right = 215;

// Y
const int Frame_Vert_Top = 10;
const int Frame_Vert_TopCenter = 70;
const int Frame_Vert_ButtomCenter = 130;
const int Frame_Vert_Buttom = 190;

// FRAME WIDTH and etc
const int Frame_Width = 100;
const int Frame_Width_Large = 310;
const int Frame_Height = 47;
const int Frame_Height_Large = 107;
const int Frame_Height_Huge = 167;
const int Frame_Round = 10;

const int LABEL_FRAME_WIDTH = Frame_Width - 20;
const int LABEL_FRAME_HEIGHT = 20;
const int Label_Frame_Round = 3;

const int LABEL_FRAME_OFFSET_X = 10;
const int LABEL_FRAME_OFFSET_Y = -10;

const int LABEL_OFFSET4_X = 27;
const int LABEL_OFFSET3_X = 33;
const int LABEL_OFFSET_Y = -7;
 

//Font Size 
const int FONT_MINI =1;
const int FONT_SMALL = 2;
const int FONT_LARGE = 7;
const int FONT_SMALL_FILL_OFFSET_X = 0;
const int FONT_SMALL_FILL_OFFSET_Y = 0;
const int FONT_LARGE_FILL_OFFSET_X = 0;
const int FONT_LARGE_FILL_OFFSET_Y = 0;

//size of Fill Black when update value;
const int FONT_SMALL_FILL_WIDTH = 7;
const int FONT_SMALL_FILL_HEIGHT = 10;

const int FONT_LARGE_FILL_WIDTH = 20;
const int FONT_LARGE_FILL_HEIGHT = 40;

const int LABEL_FONT = FONT_SMALL;

//----------------------------------------------------------------------------------------------------------------------------//
//  LCD Layout Setting
//  When you  edit layout , edit these values.  
//----------------------------------------------------------------------------------------------------------------------------//
// item align setting
// if you don't show a item , set the value to 0
// else set it to position number.
// Position Number is below
// 0x11:Top Left 0x12:Top Center 0x13: Top Right
// 0x21: Upper Middle Left 0x22: Upper Middle Center 0x23: Upper Middle Riht 
// 0x31: Lower Middle Left 0x32: Lower Middle Center 0x33: Lower Middle Right
// 0x41: Buttom Left 0x42: Buttom Center 0x43: Buttom Right 

const word GEAR_FRAME_POS =0x22;
const word RPM_FRAME_POS =0x12;
const word SPD_FRAME_POS =0x42;
const word LAP_FRAME_POS =0x21;
const word FUEL_FRAME_POS =0x33;
const word TIME_FRAME_POS = 0x31;
const word TIRE_FRAME_POS =0x00;
const word POS_FRAME_POS=0x23;
const word TOGO_FRAME_POS=0x43;
const word LAST_FRAME_POS=0x41;

//Frame Size Setting
//
const int GEAR_FRAME_SIZE = Frame_Height_Large;
const int RPM_FRAME_SIZE = Frame_Height;
const int SPD_FRAME_SIZE = Frame_Height;
const int LAP_FRAME_SIZE = Frame_Height;
const int FUEL_FRAME_SIZE = Frame_Height;
const int TIME_FRAME_SIZE = Frame_Height;
const int TIRE_FRAME_SIZE = Frame_Height_Huge;
const int POS_FRAME_SIZE= Frame_Height;
const int TOGO_FRAME_SIZE= Frame_Height;
const int LAST_FRAME_SIZE = Frame_Height;

//GEAR
const uint16_t GEAR_COLOR = ILI9341_WHITE;
const int GEAR_FONT_SIZE = FONT_LARGE;
const int GEAR_Cursor_Offset_X = 33;
const int GEAR_Cursor_Offset_Y = 30;
const int GEAR_RECT_X = 40;
const int GEAR_RECT_Y = 60;
const int GEAR_COUNT = 1;

//RPM
const uint16_t RPM_COLOR = ILI9341_GREEN;
const int RPM_FONT_SIZE = FONT_SMALL;
const int RPM_Cursor_Offset_X = 21;
const int RPM_Cursor_Offset_Y = 20;
const int RPM_RECT_X = 70;
const int RPM_RECT_Y = 16;
const int RPM_COUNT = 5;

//LAP
const uint16_t LAP_COLOR = LIGHTRED;
const int LAP_FONT_SIZE = FONT_SMALL;
const int LAP_Cursor_Offset_X = 34;
const int LAP_Cursor_Offset_Y = 20;
const int LAP_RECT_X = 50;
const int LAP_RECT_Y = 16;
const int LAP_COUNT = 5;

//FUEL
const uint16_t FUEL_COLOR = ILI9341_YELLOW;
const int FUEL_FONT_SIZE = FONT_SMALL;
const int FUEL_Cursor_Offset_X = 21;
const int FUEL_Cursor_Offset_Y = 20;
const int FUEL_RECT_X = 58;
const int FUEL_RECT_Y = 16;
const int FUEL_COUNT = 5;

//SPD
const uint16_t SPD_COLOR = ILI9341_CYAN;
const int SPD_FONT_SIZE = FONT_SMALL;
const int SPD_Cursor_Offset_X = 34;
const int SPD_Cursor_Offset_Y = 20;
const int SPD_RECT_X = 50;
const int SPD_RECT_Y = 16;
const int SPD_COUNT = 5;

//TIME
const uint16_t TIME_COLOR = LIGHTGREEN;
const int TIME_FONT_SIZE = FONT_SMALL;
const int TIME_Cursor_Offset_X = 3;
const int TIME_Cursor_Offset_Y = 20;
const int TIME_RECT_X = 96;
const int TIME_RECT_Y = 16;
const int TIME_COUNT = 7;

//POS
const uint16_t POS_COLOR = ILI9341_LIGHTGREY;
const int POS_FONT_SIZE = FONT_SMALL;
const int POS_Cursor_Offset_X = 40;
const int POS_Cursor_Offset_Y = 20;
const int POS_RECT_X = 40;
const int POS_RECT_Y = 16;
const int POS_COUNT = 2;

//TIRE
const uint16_t TIRE_COLOR = ILI9341_ORANGE;
const int TIRE_FONT_SIZE = FONT_SMALL;
const int TIRE_Cursor_Offset_X = 34;
const int TIRE_Cursor_Offset_Y = 29;
const int TIRE_Cursor_Span_Y = 38;
const int TIRE_RECT_X = 35;
const int TIRE_RECT_Y = 16;
const int dataLF = 0;
const int dataRF = 1;
const int dataLR = 2;
const int dataRR = 3;
const int TIRE_COUNT = 3;

//toGO
const uint16_t TOGO_COLOR = ILI9341_DARKCYAN;
const int TOGO_FONT_SIZE = FONT_SMALL;
const int TOGO_Cursor_Offset_X = 31;
const int TOGO_Cursor_Offset_Y = 20;
const int TOGO_RECT_X = 60;
const int TOGO_RECT_Y = 16;
const int TOGO_COUNT = 4;

//LASTTIME
const uint16_t LAST_COLOR = ILI9341_DARKGREEN;
const int LAST_FONT_SIZE = FONT_SMALL;
const int LAST_Cursor_Offset_X = 3;
const int LAST_Cursor_Offset_Y = 20;
const int LAST_RECT_X = 96;
const int LAST_RECT_Y = 16;
const int LAST_COUNT = 7;

//FrameLABEL
const int LABEL_FONT_SIZE = FONT_SMALL;

String oldData[DATA_NUM][4]={{"","","",""},{"","","",""},{"","","",""},{"","","",""},{"","","",""},{"","","",""},{"","","",""},{"","","",""},{"","","",""},{"","","",""}};
String rcvData[DATA_NUM][4]={{"N","","",""},{"00000","","",""},{"000","","",""},{"000","","",""},{"000.0","","",""},{"00:00:00","","",""},{"000","000","000","000"},{"00","","",""},{"00.0","","",""},{"00:00:00","","",""}};
word FramePos[DATA_NUM] = {GEAR_FRAME_POS,RPM_FRAME_POS,SPD_FRAME_POS,LAP_FRAME_POS,FUEL_FRAME_POS,TIME_FRAME_POS,TIRE_FRAME_POS,POS_FRAME_POS,TOGO_FRAME_POS,LAST_FRAME_POS};
int FrameSize[DATA_NUM] = {GEAR_FRAME_SIZE,RPM_FRAME_SIZE,SPD_FRAME_SIZE,LAP_FRAME_SIZE,FUEL_FRAME_SIZE,TIME_FRAME_SIZE,TIRE_FRAME_SIZE,POS_FRAME_SIZE,TOGO_FRAME_SIZE,LAST_FRAME_SIZE};
int Cursor_Offset_X[DATA_NUM] = {GEAR_Cursor_Offset_X, RPM_Cursor_Offset_X,SPD_Cursor_Offset_X,LAP_Cursor_Offset_X,FUEL_Cursor_Offset_X,TIME_Cursor_Offset_X,TIRE_Cursor_Offset_X,POS_Cursor_Offset_X,TOGO_Cursor_Offset_X,LAST_Cursor_Offset_X};
int Cursor_Offset_Y[DATA_NUM] = {GEAR_Cursor_Offset_Y, RPM_Cursor_Offset_Y,SPD_Cursor_Offset_Y,LAP_Cursor_Offset_Y,FUEL_Cursor_Offset_Y,TIME_Cursor_Offset_Y,TIRE_Cursor_Offset_Y,POS_Cursor_Offset_Y,TOGO_Cursor_Offset_Y,LAST_Cursor_Offset_Y};
int Cursor_Span_Y[DATA_NUM] = {0,0,0,0,0,0,TIRE_Cursor_Span_Y,0,0,0};
int RectSize_X[DATA_NUM]= {GEAR_RECT_X,RPM_RECT_X,SPD_RECT_X,LAP_RECT_X,FUEL_RECT_X,TIME_RECT_X,TIRE_RECT_X,POS_RECT_X,TOGO_RECT_X,LAST_RECT_X};
int RectSize_Y[DATA_NUM]= {GEAR_RECT_Y,RPM_RECT_Y,SPD_RECT_Y,LAP_RECT_Y,FUEL_RECT_Y,TIME_RECT_Y,TIRE_RECT_Y,POS_RECT_Y,TOGO_RECT_Y,LAST_RECT_Y};
uint16_t FrameColor[DATA_NUM] = {GEAR_COLOR,RPM_COLOR,SPD_COLOR,LAP_COLOR,FUEL_COLOR,TIME_COLOR,TIRE_COLOR,POS_COLOR,TOGO_COLOR,LAST_COLOR};
int FontSize[DATA_NUM] =  {GEAR_FONT_SIZE,SPD_FONT_SIZE,RPM_FONT_SIZE,LAP_FONT_SIZE,FUEL_FONT_SIZE,TIME_FONT_SIZE,TIRE_FONT_SIZE,POS_FONT_SIZE,TOGO_FONT_SIZE,LAST_FONT_SIZE};
String FrameCaption[DATA_NUM] = {"GEAR","RPM","SPD","LAP","FUEL","CURR","TIRE","POS","TOGO","LAST"};
int dataCount[DATA_NUM] ={1,1,1,1,1,1,4,1,1,1};
int strCount[DATA_NUM] ={GEAR_COUNT,SPD_COUNT,RPM_COUNT,LAP_COUNT,FUEL_COUNT,TIME_COUNT,TIRE_COUNT,POS_COUNT,TOGO_COUNT,LAST_COUNT};

ILI9341_t3 tft = ILI9341_t3(_cs, _dc, _rst);
#endif
//end of ili9341 

#ifdef INCLUDE_TEENSY
#include <Encoder.h>
//joystick Setting;
#define BTNNum 17
#define BTN_OFF 0
#define BTN_ON 1
#define MAXBTN 32
#define NBTNNum 11
#define ENCNum 3
#define ENC_CW 0
#define ENC_CCW 1
#define ENC_BTN_ON 30 //ms
#define ENC_BTN_OFF_SPAN 250 //us
#define BTNRefleshRate 7 //ms

//joistick button control
int btnRefresh = 0;
byte btnStatus[BTNNum];
byte btnStatusOLD[BTNNum];
const int btnPin[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 23};
const int encPin1[] = {17, 19, 21};
const int encPin2[] = {18, 20, 22};
const int encJNum[2][3] = {{13, 15, 17}, {14, 16, 18}};
long encCurrntPos[3];
int encBtnTime[3];
int btnRefreshTime;

Encoder je1(encPin1[0], encPin2[0]);
Encoder je2(encPin1[1], encPin2[1]);
Encoder je3(encPin1[2], encPin2[2]);
#endif

#ifdef INCLUDE_TM1637
#include "TM1637.h"
#endif

#ifdef INCLUDE_I2CLCD
#include <LiquidCrystal_I2C.h>
#endif

#ifdef INCLUDE_LEDBACKPACK
#include "Adafruit_LEDBackpack.h"
#endif

#ifdef INCLUDE_NOKIALCD
#include <Adafruit_PCD8544.h>
#endif
#if defined(INCLUDE_NOKIALCD) || defined(INCLUDE_OLED)
#include "ACHubCustomFonts/Open24DisplaySt12pt7b.h"
#define CUSTOM_LCD_FONT_1 Open24DisplaySt12pt7b
#include "ACHubCustomFonts/Open24DisplaySt18pt7b.h"
#define CUSTOM_LCD_FONT_2 Open24DisplaySt18pt7b
#endif

#ifdef INCLUDE_OLED
#include <Adafruit_SSD1306.h>
#endif // INCLUDE_OLED

#define MESSAGE_HEADER 0x03

// ----------------------------------------------------- HW SETTINGS, PLEASE REVIEW ALL -------------------------------------------
String DEVICE_NAME = String("LCDBOX"); //{"Group":"General","Name":"DEVICE_NAME","Title":"Device name","DefaultValue":"SimHub Dash","Type":"string","Template":"String DEVICE_NAME = String(\"{0}\");"}

// -------------------------------------------------------------------------------------------------------
// TM1638 Modules ----------------------------------------------------------------------------------------
// http://www.dx.com/p/jy-mcu-8x-green-light-digital-tube-8x-key-8x-double-color-led-module-104329
// https://www.fasttech.com/products/0/10006503/1497600-jy-mcu-8x-digital-tube-red-led-module
// -------------------------------------------------------------------------------------------------------

// Number of Connected TM1638/1639 modules
// 0 disabled, > 0 enabled
int TM1638_ENABLEDMODULES = 0; //{"Group":"TM1638","Name":"TM1638_ENABLEDMODULES","Title":"TM1638 modules connected\r\nSet to 0 if none","DefaultValue":"0","Type":"integer","Template":"int TM1638_ENABLEDMODULES = {0};"}

#ifdef INCLUDE_TM1638
// 0 disabled, 1 enabled
int TM1638_SWAPLEDCOLORS = 0; //{"Group":"TM1638","Name":"TM1638_SWAPLEDCOLORS","Title":"Reverse Red and green colors \r\n0 = No, 1 = Yes","DefaultValue":"0","Type":"boolean","Template":"int TM1638_SWAPLEDCOLORS = {0};","Condition":"TM1638_ENABLEDMODULES > 0"}
// TM1638 Modules common pins
#define TM1638_DIO 8 //{"Group":"TM1638","Name":"TM1638_DIO","Title":"Common data (DIO) digital pin number","DefaultValue":"8","Type":"integer","Template":"#define TM1638_DIO {0}","Condition":"TM1638_ENABLEDMODULES > 0"}
#define TM1638_CLK 7 //{"Group":"TM1638","Name":"TM1638_CLK","Title":"Common clock (CLK) digital pin number","DefaultValue":"7","Type":"integer","Template":"#define TM1638_CLK {0}","Condition":"TM1638_ENABLEDMODULES > 0"}
// TM1638 1st module strobe pin
#define TM1638_STB1 9 //{"Group":"TM1638","Name":"TM1638_STB1","Title":"1st module strobe (STB0) digital pin number","DefaultValue":"9","Type":"integer","Template":"#define TM1638_STB1 {0}","Condition":"TM1638_ENABLEDMODULES > 0"}
// TM1638 2nd screen strobe pin
#define TM1638_STB2 10 //{"Group":"TM1638","Name":"TM1638_STB2","Title":"2d module strobe (STB1) digital pin number","DefaultValue":"10","Type":"integer","Template":"#define TM1638_STB2 {0}","Condition":"TM1638_ENABLEDMODULES > 1"}
// TM1638 3nd screen strobe pin
#define TM1638_STB3 11 //{"Group":"TM1638","Name":"TM1638_STB3","Title":"3rd module strobe (STB2) digital pin number","DefaultValue":"11","Type":"integer","Template":"#define TM1638_STB3 {0}","Condition":"TM1638_ENABLEDMODULES > 2"}
// TM1638 4rd screen strobe pin
#define TM1638_STB4 12 //{"Group":"TM1638","Name":"TM1638_STB4","Title":"4th module strobe (STB3) digital pin number","DefaultValue":"12","Type":"integer","Template":"#define TM1638_STB4 {0}","Condition":"TM1638_ENABLEDMODULES > 3"}
// TM1638 5th screen strobe pin
#define TM1638_STB5 0 //{"Group":"TM1638","Name":"TM1638_STB5","Title":"5th module strobe (STB4) digital pin number","DefaultValue":"0","Type":"integer","Template":"#define TM1638_STB5 {0}","Condition":"TM1638_ENABLEDMODULES > 4"}
// TM1638 6th screen strobe pin
#define TM1638_STB6 0 //{"Group":"TM1638","Name":"TM1638_STB6","Title":"6th module strobe (STB5) digital pin number","DefaultValue":"0","Type":"integer","Template":"#define TM1638_STB6 {0}","Condition":"TM1638_ENABLEDMODULES > 5"}
#endif

// -------------------------------------------------------------------------------------------------------
// TM1637 Modules ----------------------------------------------------------------------------------------
// http://www.dx.com/p/0-36-led-4-digit-display-module-for-arduino-black-blue-works-with-official-arduino-boards-254978
// -------------------------------------------------------------------------------------------------------

// Number of Connected TM1637 modules
// 0 disabled, > 0 enabled
int TM1637_ENABLEDMODULES = 0; //{"Group":"TM1637","Name":"TM1637_ENABLEDMODULES","Title":"TM1637 modules connected\r\nSet to 0 if none","DefaultValue":"0","Type":"integer","Template":"int TM1637_ENABLEDMODULES = {0};"}
#ifdef INCLUDE_TM1637
#define TM1637_DIO1 4 //{"Group":"TM1637","Name":"TM1637_DIO1","Title":"1st TM1637 DIO digital pin number","DefaultValue":"4","Type":"integer","Template":"#define TM1637_DIO1 {0}","Condition":"TM1637_ENABLEDMODULES >=1"}
#define TM1637_CLK1 3 //{"Group":"TM1637","Name":"TM1637_CLK1","Title":"1st TM1637 CLK digital pin number","DefaultValue":"3","Type":"integer","Template":"#define TM1637_CLK1 {0}","Condition":"TM1637_ENABLEDMODULES >=1"}

#define TM1637_DIO2 4 //{"Group":"TM1637","Name":"TM1637_DIO2","Title":"2nd TM1637 DIO digital pin number","DefaultValue":"4","Type":"integer","Template":"#define TM1637_DIO2 {0}","Condition":"TM1637_ENABLEDMODULES >=2"}
#define TM1637_CLK2 3 //{"Group":"TM1637","Name":"TM1637_CLK2","Title":"2nd TM1637 CLK digital pin number","DefaultValue":"3","Type":"integer","Template":"#define TM1637_CLK2 {0}","Condition":"TM1637_ENABLEDMODULES >=2"}

#define TM1637_DIO3 4 //{"Group":"TM1637","Name":"TM1637_DIO3","Title":"3rd TM1637 DIO digital pin number","DefaultValue":"4","Type":"integer","Template":"#define TM1637_DIO3 {0}","Condition":"TM1637_ENABLEDMODULES >=3"}
#define TM1637_CLK3 3 //{"Group":"TM1637","Name":"TM1637_CLK3","Title":"3rd TM1637 CLK digital pin number","DefaultValue":"3","Type":"integer","Template":"#define TM1637_CLK3 {0}","Condition":"TM1637_ENABLEDMODULES >=3"}

#define TM1637_DIO4 4 //{"Group":"TM1637","Name":"TM1637_DIO4","Title":"4th TM1637 DIO digital pin number","DefaultValue":"4","Type":"integer","Template":"#define TM1637_DIO4 {0}","Condition":"TM1637_ENABLEDMODULES >=4"}
#define TM1637_CLK4 3 //{"Group":"TM1637","Name":"TM1637_CLK4","Title":"4th TM1637 CLK digital pin number","DefaultValue":"3","Type":"integer","Template":"#define TM1637_CLK4 {0}","Condition":"TM1637_ENABLEDMODULES >=4"}

#define TM1637_DIO5 4 //{"Group":"TM1637","Name":"TM1637_DIO5","Title":"5th TM1637 DIO digital pin number","DefaultValue":"4","Type":"integer","Template":"#define TM1637_DIO5 {0}","Condition":"TM1637_ENABLEDMODULES >=5"}
#define TM1637_CLK5 3 //{"Group":"TM1637","Name":"TM1637_CLK5","Title":"5th TM1637 CLK digital pin number","DefaultValue":"3","Type":"integer","Template":"#define TM1637_CLK5 {0}","Condition":"TM1637_ENABLEDMODULES >=5"}

#define TM1637_DIO6 4 //{"Group":"TM1637","Name":"TM1637_DIO6","Title":"6th TM1637 DIO digital pin number","DefaultValue":"4","Type":"integer","Template":"#define TM1637_DIO6 {0}","Condition":"TM1637_ENABLEDMODULES >=6"}
#define TM1637_CLK6 3 //{"Group":"TM1637","Name":"TM1637_CLK6","Title":"6th TM1637 CLK digital pin number","DefaultValue":"3","Type":"integer","Template":"#define TM1637_CLK6 {0}","Condition":"TM1637_ENABLEDMODULES >=6"}
#endif

// -------------------------------------------------------------------------------------------------------
// MAX7219 / MAX7221 7 Segment modules -----------------------------------------------------------------------------
// http://www.dx.com/p/max7219-led-dot-matrix-digital-led-display-tube-module-cascade-391256
// -------------------------------------------------------------------------------------------------------

// 0 disabled, > 0 enabled
int MAX7221_ENABLEDMODULES = 0; //{"Group":"MAX7221","Name":"MAX7221_ENABLEDMODULES","Title":"MAX7219 / MAX7221 7 Segment modules connected \r\nSet to 0 if none\r\nMultiple modules can be cascaded connected module output to next module input","DefaultValue":"0","Type":"integer","Template":"int MAX7221_ENABLEDMODULES = {0};"}

#ifdef INCLUDE_MAX7221_MODULES
// DATA IN - pin of the first MAX7221
#define MAX7221_DATA 3 //{"Group":"MAX7221","Name":"MAX7221_DATA","Title":"DATA (DIN) digital pin number","DefaultValue":"3","Type":"integer","Template":"#define MAX7221_DATA {0}","Condition":"MAX7221_ENABLEDMODULES > 0"}
// CLK - pin of the first MAX7221
#define MAX7221_CLK 5 //{"Group":"MAX7221","Name":"MAX7221_CLK","Title":"CLOCK (CLK) digital pin number","DefaultValue":"5","Type":"integer","Template":"#define MAX7221_CLK {0}","Condition":"MAX7221_ENABLEDMODULES > 0"}
// LOAD(/ CS) - pin of the first MAX7221
#define MAX7221_LOAD 4 //{"Group":"MAX7221","Name":"MAX7221_LOAD","Title":"LOAD (LD) digital pin number","DefaultValue":"4","Type":"integer","Template":"#define MAX7221_LOAD {0}","Condition":"MAX7221_ENABLEDMODULES > 0"}
LedControl MAX7221 = LedControl(MAX7221_DATA, MAX7221_CLK, MAX7221_LOAD, MAX7221_ENABLEDMODULES);

#endif // INCLUDE_MAX7221_MODULES
// -------------------------------------------------------------------------------------------------------
// MAX7219 / MAX7221 Led Matrix module -----------------------------------------------------------------------------
// http://www.dx.com/p/max7219-dot-matrix-module-w-5-dupont-lines-184854
// -------------------------------------------------------------------------------------------------------

int MAX7221_MATRIX_ENABLED = 0; //{"Group":"MAX7221_MATRIX","Name":"MAX7221_MATRIX_ENABLED","Title":"MAX7221 led matrix enabled \r\n0 = disabled, 1 = enabled","DefaultValue":"0","Type":"integer","Template":"int MAX7221_MATRIX_ENABLED = {0};"}
#ifdef INCLUDE_MAX7221MATRIX
// 0 disabled, 1 enabled
int MAX7221_MATRIX_LUMINOSITY = 15;
// DATA IN - pin of the first MAX7221
#define MAX7221_MATRIX_DATA 3 //{"Group":"MAX7221_MATRIX","Name":"MAX7221_MATRIX_DATA","Title":"DATA (DIN) digital pin number","DefaultValue":"3","Type":"integer","Template":"#define MAX7221_MATRIX_DATA {0}","Condition":"MAX7221_MATRIX_ENABLED>0"}
// CLK - pin of the first MAX7212
#define MAX7221_MATRIX_CLK 5 //{"Group":"MAX7221_MATRIX","Name":"MAX7221_MATRIX_CLK","Title":"CLOCK (CLK) digital pin number","DefaultValue":"5","Type":"integer","Template":"#define MAX7221_MATRIX_CLK {0}","Condition":"MAX7221_MATRIX_ENABLED>0"}
// LOAD(/ CS) - pin of the first MAX7221
#define MAX7221_MATRIX_LOAD 4 //{"Group":"MAX7221_MATRIX","Name":"MAX7221_MATRIX_LOAD","Title":"LOAD (LD) digital pin number","DefaultValue":"4","Type":"integer","Template":"#define MAX7221_MATRIX_LOAD {0}","Condition":"MAX7221_MATRIX_ENABLED>0"}
LedControl MAX7221_MATRIX = LedControl(MAX7221_MATRIX_DATA, MAX7221_MATRIX_CLK, MAX7221_MATRIX_LOAD, MAX7221_MATRIX_ENABLED);
#endif // INCLUDE_MAX7221MATRIX

// -------------------------------------------------------------------------------------------------------
// WS2812b RGBLEDS ---------------------------------------------------------------------------------------
// http://www.dx.com/p/8-bit-ws2812-5050-rgb-led-development-board-w-built-in-full-color-drive-387667
// -------------------------------------------------------------------------------------------------------

// WS2812b chained RGBLEDS count
// 0 disabled, > 0 enabled
int WS2812B_RGBLEDCOUNT = 8; //{"Group":"WS2812B_RGBLED","Name":"WS2812B_RGBLEDCOUNT","Title":"WS2812B RGB leds count\r\nSet to 0 if none","DefaultValue":"0","Type":"integer","Template":"int WS2812B_RGBLEDCOUNT = {0};"}

#ifdef INCLUDE_WS2812B
// 0 leds will be used from left to right, 1 leds will be used from right to left
int WS2812B_RIGHTTOLEFT = 1; //{"Group":"WS2812B_RGBLED","Name":"WS2812B_RIGHTTOLEFT","Title":"Reverse led order \r\n0 = No, 1 = Yes","DefaultValue":"0","Type":"boolean","Template":"int WS2812B_RIGHTTOLEFT = {0};","Condition":"WS2812B_RGBLEDCOUNT>0"}
// WS2812b chained RGBLEDS pins
#define WS2812B_DATAPIN 16 //{"Group":"WS2812B_RGBLED","Name":"WS2812B_DATAPIN","Title":"Data (DIN) digital pin number","DefaultValue":"6","Type":"boolean","Template":"#define WS2812B_DATAPIN {0}","Condition":"WS2812B_RGBLEDCOUNT>0"}
#ifdef INCLUDE_PL9823
Adafruit_NeoPixel WS2812B_strip = Adafruit_NeoPixel(WS2812B_RGBLEDCOUNT, WS2812B_DATAPIN, NEO_RGB + NEO_KHZ800);
#else
Adafruit_NeoPixel WS2812B_strip = Adafruit_NeoPixel(WS2812B_RGBLEDCOUNT, WS2812B_DATAPIN, NEO_GRB + NEO_KHZ800);
#endif
#endif

// -------------------------------------------------------------------------------------------------------
// WS2801 RGBLEDS ----------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------

// 0 disabled, > 0 enabled
int WS2801_RGBLEDCOUNT = 0; //{"Group":"WS2801_RGBLED","Name":"WS2801_RGBLEDCOUNT","Title":"WS2801 RGB leds count\r\nSet to 0 if none","DefaultValue":"0","Type":"integer","Template":"int WS2801_RGBLEDCOUNT = {0};"}

#ifdef INCLUDE_WS2801
// 0 leds will be used from left to right, 1 leds will be used from right to left
int WS2801_RIGHTTOLEFT = 0; //{"Group":"WS2801_RGBLED","Name":"WS2801_RIGHTTOLEFT","Title":"WS2801 right to left\r\nSet to 0 for left to right, 1 for right to left","DefaultValue":"0","Type":"integer","Template":"int WS2801_RIGHTTOLEFT = {0};","Condition":"WS2801_RGBLEDCOUNT>0"}
#define WS2801_DATAPIN 5 //{"Group":"WS2801_RGBLED","Name":"WS2801_DATAPIN","Title":"Data (DIN) digital pin number","DefaultValue":"5","Type":"integer","Template":"#define WS2801_DATAPIN {0}","Condition":"WS2801_RGBLEDCOUNT>0"}
#define WS2801_CLOCKPIN 6 //{"Group":"WS2801_RGBLED","Name":"WS2801_CLOCKPIN","Title":"Clock (DIN) digital pin number","DefaultValue":"6","Type":"integer","Template":"#define WS2801_CLOCKPIN {0}","Condition":"WS2801_RGBLEDCOUNT>0"}
Adafruit_WS2801 WS2801_strip = Adafruit_WS2801(WS2801_RGBLEDCOUNT, WS2801_DATAPIN, WS2801_CLOCKPIN);

#endif

// -------------------------------------------------------------------------------------------------------
// I2C LiquidCristal - WIP no finished
// http://www.dx.com/p/arduino-iic-i2c-serial-3-2-lcd-2004-module-display-138611#.Vb0QtW7tlBd
// Board				I2C / TWI pins
// Uno, Ethernet, Nano	A4(SDA), A5(SCL)
// Mega2560				20 (SDA), 21 (SCL)
// Leonardo				2 (SDA), 3 (SCL)
// Due					20 (SDA), 21 (SCL), SDA1, SCL1
// -------------------------------------------------------------------------------------------------------

int I2CLCD_enabled = 1; //{"Group":"I2C LCD","Name":"I2CLCD_enabled","Title":"I2C LCD (2004) enabled\r\n0 = disabled, 1 = enabled\r\nUno, Ethernet, Nano : A4(SDA), A5(SCL)\r\nMega2560 : 20 (SDA), 21 (SCL)\r\nLeonardo : 2 (SDA), 3 (SCL)\r\nDue : 20 (SDA), 21 (SCL), SDA1, SCL1","DefaultValue":"0","Type":"integer","Template":"int I2CLCD_enabled = {0};"}
#ifdef INCLUDE_I2CLCD
int I2CLCD_width = 20;
int I2CLCD_height = 4;
byte I2CLCD_address = 0x3f; //{"Group":"I2C LCD","Name":"I2CLCD_address","Title":"I2C address","DefaultValue":"0x3f","Type":"hex","Template":"byte I2CLCD_address = {0};","Condition":"I2CLCD_enabled>0"}
LiquidCrystal_I2C I2CLCD(I2CLCD_address, I2CLCD_width, I2CLCD_height);
#endif

// --------------------------------------------------------------------------------------------------------
// 74HC595 Shift register, one 7seg module for gear indicator ---------------------------------------------
// DIY : http://lucidtronix.com/tutorials/2
// --------------------------------------------------------------------------------------------------------

// 0 disabled, 1 enabled
int ENABLE_74HC595_GEAR_DISPLAY = 0; //{"Group":"74HC595 GEAR DISPLAY","Name":"ENABLE_74HC595_GEAR_DISPLAY","Title":"74HC595 gear display enabled\r\n0 = disabled, 1 = enabled","DefaultValue":"0","Type":"hex","Template":"int ENABLE_74HC595_GEAR_DISPLAY = {0};"}
// Reverse led state

#ifdef INCLUDE_74HC595_GEAR_DISPLAY
int RS_74HC595_INVERT = 0;
#define RS_74HC595_DATAPIN 2 //{"Group":"74HC595 GEAR DISPLAY","Name":"RS_74HC595_DATAPIN","Title":"DATA digital pin number","DefaultValue":"2","Type":"hex","Template":"#define RS_74HC595_DATAPIN {0}","Condition":"ENABLE_74HC595_GEAR_DISPLAY >0"}
#define RS_74HC595_LATCHPIN 3 //{"Group":"74HC595 GEAR DISPLAY","Name":"RS_74HC595_LATCHPIN","Title":"LATCH digital pin number","DefaultValue":"3","Type":"hex","Template":"#define RS_74HC595_LATCHPIN {0}","Condition":"ENABLE_74HC595_GEAR_DISPLAY > 0"}
#define RS_74HC595_CLOCKPIN 4 //{"Group":"74HC595 GEAR DISPLAY","Name":"RS_74HC595_CLOCKPIN","Title":"CLOCK digital pin number","DefaultValue":"4","Type":"hex","Template":"#define RS_74HC595_CLOCKPIN {0}","Condition":"ENABLE_74HC595_GEAR_DISPLAY > 0"}
// RS_74HC595 DIGITS
// 0,1,2 ....
byte RS_74HC595_dec_digits[] = { 0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110, 0b10110110, 0b10111110, 0b11100000, 0b11111110, 0b11110110 };
// Empty
byte RS_74HC595_ClearDigit = 0b00000000;
// R
byte RS_74HC595_ReverseDigit = 0b10001100;
// N
byte RS_74HC595_NeutralDigit = 0b11101100;
#endif // INCLUDE_74HC595_GEAR_DISPLAY

// --------------------------------------------------------------------------------------------------------
// 6c595 Shift register, one 7seg module for gear indicator ---------------------------------------------
// DIY : https://www.xsimulator.net/community/threads/12cm-12v-7segments-gear-indicator-with-gamedash.5747/
// --------------------------------------------------------------------------------------------------------
#ifdef INCLUDE_6c595_GEAR_DISPLAY
int ENABLE_6c595_GEAR_DISPLAY = 0; //{"Group":"6c595 GEAR DISPLAY","Name":"ENABLE_6C595_GEAR_DISPLAY","Title":"6C595 gear display enabled\r\n0 = disabled, 1 = enabled","DefaultValue":"0","Type":"hex","Template":"int ENABLE_6c595_GEAR_DISPLAY = {0};"}
#define RS_6c595_DATAPIN 11 //{"Group":"6c595 GEAR DISPLAY","Name":"RS_6c595_DATAPIN","Title":"DATA digital pin number, can't be changed !","DefaultValue":"11","Type":"hex","Template":"#define RS_6c595_DATAPIN {0}","Condition":"ENABLE_6C595_GEAR_DISPLAY>0"}
#define RS_6c595_LATCHPIN 13 //{"Group":"6c595 GEAR DISPLAY","Name":"RS_6c595_LATCHPIN","Title":"LATCH digital pin number, can't be changed !","DefaultValue":"13","Type":"hex","Template":"#define RS_6c595_LATCHPIN {0}","Condition":"ENABLE_6C595_GEAR_DISPLAY>0"}
#define RS_6c595_SLAVEPIN 10 //{"Group":"6c595 GEAR DISPLAY","Name":"RS_6c595_SLAVEPIN","Title":"SLAVE digital pin number","DefaultValue":"10","Type":"hex","Template":"#define RS_6c595_SLAVEPIN {0}","Condition":"ENABLE_6C595_GEAR_DISPLAY>0"}

byte g_6c595fontArray[] = {
	// dp-a-b-c-d-e-f-g
	0b10100001, // 0
	0b00101000, // 1
	0b11001101, // 2
	0b01101101, // 3
	0b00101011, // 4
	0b01100111, // 5
	0b11100111, // 6
	0b00101100, // 7
	0b00000000, // OFF empty
	0b10000001, // REVERSE SPEED
};
byte g_6c595LEDarray; //computed order that will be sent to the LED display
#endif

// --------------------------------------------------------------------------------------------------------
// Adafruit 4x7segment with HT16K33 I2C Backpack
// These displays use I2C to communicate, 2 pins are required to interface.
// There are multiple selectable I2C addresses.
// For backpacks with 2 Address Select addresses : 0x70, 0x71, 0x72 or 0x73.
// For backpacks with 3 Address Select addresses : 0x70 thru 0x77
// --------------------------------------------------------------------------------------------------------
// 0 disabled, 1 enabled
int ENABLE_ADA_HT16K33_7SEGMENTS = 0; //{"Group":"HT16K33_7SEGMENTS","Name":"ENABLE_ADA_HT16K33_7SEGMENTS","Title":"Adafruit HT16K33 7 segments display enabled\r\n0 = disabled, 1 = enabled","DefaultValue":"0","Type":"hex","Template":"int ENABLE_ADA_HT16K33_7SEGMENTS = {0};"}
#ifdef INCLUDE_LEDBACKPACK
// I2C Adress
byte ADA_HT16K33_7SEGMENTS_I2CADDRESS = 0x70;
Adafruit_7segment ADA_HT16K33_7SEGMENTS = Adafruit_7segment();
#endif

// --------------------------------------------------------------------------------------------------------
// Adafruit 8x8 bi color with HT16K33 I2C Backpack
// These displays use I2C to communicate, 2 pins are required to interface.
// There are multiple selectable I2C addresses.
// For backpacks with 2 Address Select addresses : 0x70, 0x71, 0x72 or 0x73.
// For backpacks with 3 Address Select addresses : 0x70 thru 0x77
// --------------------------------------------------------------------------------------------------------
// 0 disabled, 1 enabled
int ENABLE_ADA_HT16K33_Matrix = 0; //{"Group":"HT16K33_Matrix","Name":"ENABLE_ADA_HT16K33_Matrix","Title":"Adafruit HT16K33 matrix display enabled\r\n0 = disabled, 1 = enabled","DefaultValue":"0","Type":"hex","Template":"int ENABLE_ADA_HT16K33_Matrix = {0};"}
// I2C Adress
#ifdef INCLUDE_LEDBACKPACK
byte ADA_HT16K33_MATRIX_I2CADDRESS = 0x71;
Adafruit_BicolorMatrix ADA_HT16K33_MATRIX = Adafruit_BicolorMatrix();
byte ADA_HT16K33_Matrix_luminosity = 0;
#endif

// ------------------------ TACHOMETER ----------------------------------------------------------------------
// https://github.com/zegreatclan/AssettoCorsaTools/wiki/Arduino-After-Market-Tach-support
// ----------------------------------------------------------------------------------------------------------

#ifdef INCLUDE_TACHOMETER
int ENABLE_TACHOMETER = 0; //{"Group":"TACHOMETER","Name":"ENABLE_TACHOMETER","Title":"After market tachometer enabled\r\n0 = disabled, 1 = enabled\r\nsee wiki for wiring instructions","DefaultValue":"0","Type":"hex","Template":"int ENABLE_TACHOMETER = {0};"}
int pinTacho = 9; //{"Group":"TACHOMETER","Name":"TACHOMETER_PIN","Title":"Tachometer pin","DefaultValue":"9","Type":"hex","Template":"int pinTacho = {0};","Condition":"ENABLE_TACHOMETER > 0 "}
Tone rpmTone;
#endif

#ifdef INCLUDE_BOOSTGAUGE
int ENABLE_BOOSTGAUGE = 0; //{"Group":"BOOST GAUGE","Name":"ENABLE_BOOSTGAUGE","Title":"After market boost gauge enabled\r\n0 = disabled, 1 = enabled\r\nsee wiki for wiring instructions","DefaultValue":"0","Type":"hex","Template":"int ENABLE_BOOSTGAUGE = {0};"}
int pinBoost = 5; //{"Group":"BOOST GAUGE","Name":"BOOST_PIN","Title":"Boost pwm pin","DefaultValue":"5","Type":"hex","Template":"int pinBoost = {0};","Condition":"ENABLE_BOOSTGAUGE >0"}
#endif

// ----------------------- ADDITIONAL BUTTONS ---------------------------------------------------------------
// https://www.arduino.cc/en/Tutorial/InputPullupSerial
// ----------------------------------------------------------------------------------------------------------
#ifndef INCLLUDE_TEENSY
int ENABLED_BUTTONS_COUNT = 1; //{"Group":"ADDITIONAL BUTTONS","Name":"ENABLED_BUTTONS_COUNT","Title":"Additional buttons (directly connected to the arduino) buttons count\r\n0 = disabled, >0  = enabled","DefaultValue":"0","Type":"integer","Template":"int ENABLED_BUTTONS_COUNT = {0};"}
int BUTTON_PIN_1 = 3; //{"Group":"ADDITIONAL BUTTONS","Name":"BUTTON_PIN_1","Title":"1'st Additional button digital pin","DefaultValue":"3","Type":"integer","Template":"int BUTTON_PIN_1 = {0};","Condition":"ENABLED_BUTTONS_COUNT>=1"}
int BUTTON_PIN_2 = 3; //{"Group":"ADDITIONAL BUTTONS","Name":"BUTTON_PIN_2","Title":"2'nd Additional button digital pin","DefaultValue":"3","Type":"integer","Template":"int BUTTON_PIN_2 = {0};","Condition":"ENABLED_BUTTONS_COUNT>=2"}
int BUTTON_PIN_3 = 3; //{"Group":"ADDITIONAL BUTTONS","Name":"BUTTON_PIN_3","Title":"3'rd Additional button digital pin","DefaultValue":"3","Type":"integer","Template":"int BUTTON_PIN_3 = {0};","Condition":"ENABLED_BUTTONS_COUNT>=3"}
int BUTTON_PIN_4 = 3; //{"Group":"ADDITIONAL BUTTONS","Name":"BUTTON_PIN_4","Title":"4'th Additional button digital pin","DefaultValue":"3","Type":"integer","Template":"int BUTTON_PIN_4 = {0};","Condition":"ENABLED_BUTTONS_COUNT>=4"}
int BUTTON_PIN_5 = 3; //{"Group":"ADDITIONAL BUTTONS","Name":"BUTTON_PIN_5","Title":"5'th Additional button digital pin","DefaultValue":"3","Type":"integer","Template":"int BUTTON_PIN_5 = {0};","Condition":"ENABLED_BUTTONS_COUNT>=5"}
int BUTTON_PIN_6 = 3; //{"Group":"ADDITIONAL BUTTONS","Name":"BUTTON_PIN_6","Title":"6'th Additional button digital pin","DefaultValue":"3","Type":"integer","Template":"int BUTTON_PIN_6 = {0};","Condition":"ENABLED_BUTTONS_COUNT>=6"}
int BUTTON_PIN_7 = 3; //{"Group":"ADDITIONAL BUTTONS","Name":"BUTTON_PIN_7","Title":"7'th Additional button digital pin","DefaultValue":"3","Type":"integer","Template":"int BUTTON_PIN_7 = {0};","Condition":"ENABLED_BUTTONS_COUNT>=7"}
int BUTTON_PIN_8 = 3; //{"Group":"ADDITIONAL BUTTONS","Name":"BUTTON_PIN_8","Title":"8'th Additional button digital pin","DefaultValue":"3","Type":"integer","Template":"int BUTTON_PIN_8 = {0};","Condition":"ENABLED_BUTTONS_COUNT>=8"}
int BUTTON_PINS[] = { BUTTON_PIN_1, BUTTON_PIN_2, BUTTON_PIN_3, BUTTON_PIN_4, BUTTON_PIN_5, BUTTON_PIN_6, BUTTON_PIN_7, BUTTON_PIN_8 };
#endif
// -------------------- NOKIA GLCD -------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------------------------------------
int ENABLED_NOKIALCD = 0; //{"Group":"NOKIA_GLCD","Name":"ENABLED_NOKIALCD","Title":"Number of Nokia GLCD connected (up to 2)\r\n0 = disabled, >0  = enabled","DefaultValue":"0","Type":"integer","Template":"int ENABLED_NOKIALCD = {0};"}
//#define ENABLE_SECONDARY_NOKIALCD //{"Name":"ENABLE_SECONDARY_NOKIALCD","Type":"autodefine","Condition":"[ENABLED_NOKIALCD]>1"}

#ifdef INCLUDE_NOKIALCD
// Adafruit_PCD8544 display = Adafruit_PCD8544(SCLK, DIN, DC, CS or SCE, RST);
Adafruit_PCD8544 glcd1 = Adafruit_PCD8544(A0, A1, A2, A4, A3);
#ifdef ENABLE_SECONDARY_NOKIALCD
Adafruit_PCD8544 glcd2 = Adafruit_PCD8544(3, 4, 5, 7, 6);
Adafruit_PCD8544 * nokiaLCDs[] = { &glcd1, &glcd2 };
#else
Adafruit_PCD8544 * nokiaLCDs[] = { &glcd1 };
#endif
#endif

int ENABLED_OLEDLCD = 0; //{"Group":"OLED_LCD","Name":"ENABLED_OLEDLCD","Title":"Number of OLED LCD connected (up to 2)\r\n0 = disabled, >0  = enabled","DefaultValue":"0","Type":"integer","Template":"int ENABLED_OLEDLCD = {0};"}
//#define ENABLE_SECONDARY_OLEDLCD //{"Name":"ENABLE_SECONDARY_OLEDLCD","Type":"autodefine","Condition":"[ENABLED_OLEDLCD]>1"}
#ifdef INCLUDE_OLED
#define OLED_RESET 4
Adafruit_SSD1306 glcd1(OLED_RESET);
#ifdef ENABLE_SECONDARY_OLEDLCD
Adafruit_SSD1306 glcd2(OLED_RESET);
Adafruit_SSD1306 * nokiaLCDs[] = { &glcd1, &glcd2 };
#else
Adafruit_SSD1306 * nokiaLCDs[] = { &glcd1 };
#endif
#endif

// ----------------------------------------------------- END OF HW SETTINGS --------------------------------------------------------------

#if defined(INCLUDE_TM1638) || defined(INCLUDE_MAX7221_MODULES)
struct ScreenItem {
public:
#ifdef INCLUDE_TM1638
	TM1638 * Screen;
#endif
	byte Buttons;
	byte Oldbuttons;
	byte Intensity;

	ScreenItem() { }
#ifdef INCLUDE_TM1638
	ScreenItem(TM1638 * module) : Screen(module) {
		this->Buttons = 0;
		this->Oldbuttons = 0;
		this->Intensity = 7;
	}
#endif
};
#endif

#ifdef INCLUDE_TM1638
TM1638 TM1638_module1(TM1638_DIO, TM1638_CLK, TM1638_STB1, false);
ScreenItem TM1638_screen1(&TM1638_module1);

TM1638 TM1638_module2(TM1638_DIO, TM1638_CLK, TM1638_STB2, false);
ScreenItem TM1638_screen2(&TM1638_module2);

TM1638 TM1638_module3(TM1638_DIO, TM1638_CLK, TM1638_STB3, false);
ScreenItem TM1638_screen3(&TM1638_module3);

TM1638 TM1638_module4(TM1638_DIO, TM1638_CLK, TM1638_STB4, false);
ScreenItem TM1638_screen4(&TM1638_module4);

TM1638 TM1638_module5(TM1638_DIO, TM1638_CLK, TM1638_STB5, false);
ScreenItem TM1638_screen5(&TM1638_module5);

TM1638 TM1638_module6(TM1638_DIO, TM1638_CLK, TM1638_STB6, false);
ScreenItem TM1638_screen6(&TM1638_module6);

// Screen referencing
ScreenItem * TM1638_screens[] = { &TM1638_screen1, &TM1638_screen2, &TM1638_screen3, &TM1638_screen4, &TM1638_screen5, &TM1638_screen6 };
#endif

#ifdef INCLUDE_MAX7221_MODULES

ScreenItem MAX7221_screen1;
ScreenItem MAX7221_screen2;
ScreenItem MAX7221_screen3;
ScreenItem MAX7221_screen4;
ScreenItem MAX7221_screen5;
ScreenItem MAX7221_screen6;

ScreenItem * MAX7221_screens[] = { &MAX7221_screen1, &MAX7221_screen2, &MAX7221_screen3, &MAX7221_screen4, &MAX7221_screen5, &MAX7221_screen6 };

byte MAX7221_ByteReorder(byte x)
{
	x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa);
	x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc);
	x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0);
	return (x >> 1) | ((x & 1) << 7);
}

#endif // INCLUDE_MAX7221_MODULES

#ifdef INCLUDE_TM1637
TM1637 TM1637_module1(TM1637_CLK1, TM1637_DIO1);
TM1637 TM1637_module2(TM1637_CLK2, TM1637_DIO2);
TM1637 TM1637_module3(TM1637_CLK3, TM1637_DIO3);
TM1637 TM1637_module4(TM1637_CLK4, TM1637_DIO4);
TM1637 TM1637_module5(TM1637_CLK5, TM1637_DIO5);
TM1637 TM1637_module6(TM1637_CLK6, TM1637_DIO6);

TM1637 * TM1637_screens[] = { &TM1637_module1, &TM1637_module2, &TM1637_module3, &TM1637_module4, &TM1637_module5, &TM1637_module6 };
#endif

int i;
byte displayValues[] = { 1, 2, 4, 8, 16, 32, 64, 128 };

#ifdef INCLUDE_74HC595_GEAR_DISPLAY
void RS_74HC595_SendData(byte data) {
	// take the latchPin low so
	// the LEDs don't change while you're sending in bits:
	digitalWrite(RS_74HC595_LATCHPIN, LOW);
	// shift out the bits:
	shiftOut(RS_74HC595_DATAPIN, RS_74HC595_CLOCKPIN, MSBFIRST, data);
	//take the latch pin high so the LEDs will light up:
	digitalWrite(RS_74HC595_LATCHPIN, HIGH);
}

void RS_74HC595_SetChar(char c) {
	byte data = 0;
	if (c == ' ') {
		data = RS_74HC595_ClearDigit;
	}
	else if (c == 'R') {
		data = RS_74HC595_ReverseDigit;
	}
	else if (c == 'N') {
		data = RS_74HC595_NeutralDigit;
	}
	else {
		int value = c - '0';
		if (value >= 0 && value < 10) {
			data = RS_74HC595_dec_digits[value];
		}
	}

	if (RS_74HC595_INVERT == 1) {
		data = data ^ 0xFF;
	}
	RS_74HC595_SendData(data);
}

void RS_74HC595_Init() {
	//set pins to output so you can control the shift register
	pinMode(RS_74HC595_DATAPIN, OUTPUT);
	pinMode(RS_74HC595_LATCHPIN, OUTPUT);
	pinMode(RS_74HC595_CLOCKPIN, OUTPUT);
	RS_74HC595_SetChar(' ');
}
#endif // INCLUDE_74HC595_GEAR_DISPLAY

#ifdef INCLUDE_6c595_GEAR_DISPLAY
void RS_6c595_SetChar(char c) {
	byte data = 0;
	if (c == ' ') {
		data = g_6c595fontArray[8];
	}
	else if (c == 'R') {
		data = g_6c595fontArray[9];
	}
	else if (c == 'N') {
		data = g_6c595fontArray[0];
	}
	else {
		int value = c - '0';
		if (value >= 0 && value < 10) {
			data = g_6c595fontArray[value];
		}
	}
	digitalWrite(RS_6c595_SLAVEPIN, LOW); // << RCLK line goes low
	SPI.transfer(data);  //  << SRCLK goes  high-low 8 times to output 8 bits of data
	digitalWrite(RS_6c595_SLAVEPIN, HIGH); // data outputs change on this rising edge << RCLK line goes high to move data into output register
}
#endif //INCLUDE_6c595_GEAR_DISPLAY

void setup()
{
	FlowSerialBegin(19200);

#ifdef INCLUDE_TM1638
	// TM1638 INIT
	for (i = 0; i < TM1638_ENABLEDMODULES; i++)
	{
		TM1638_screens[i]->Screen->setupDisplay(true, 7);
		TM1638_screens[i]->Screen->clearDisplay();
	}
#endif

	// NOKIALCD INIT
#ifdef INCLUDE_NOKIALCD
	if (ENABLED_NOKIALCD) {
		glcd1.begin();
		glcd1.clearDisplay();
		glcd1.setRotation(2);
		//nokiaLCD.setFont(&DJB_Get_Digital15pt7b);
		glcd1.setContrast(45);
		glcd1.setCursor(0, 20);
		//nokiaLCD.setFont(&FONT_1);
		glcd1.setTextSize(1);

		glcd1.print("123");

		glcd1.display();
		glcd1.setCursor(0, 20);

#ifdef ENABLE_SECONDARY_NOKIALCD
		glcd2.begin();
		glcd2.setRotation(2);
		glcd2.setContrast(54);
		glcd2.clearDisplay();
		glcd2.print("2 345");
		glcd2.display();
#endif
	}
#endif

	// TM1637 INIT
#ifdef INCLUDE_TM1637
	for (int i = 0; i < TM1637_ENABLEDMODULES; i++) {
		TM1637_screens[i]->init();
		TM1637_screens[i]->set(BRIGHT_TYPICAL);
		TM1637_screens[i]->clearDisplay();
	}
#endif
#ifdef INCLUDE_WS2812B
	// WS2812B INIT
	if (WS2812B_RGBLEDCOUNT > 0) {
		WS2812B_strip.begin();
		WS2812B_strip.show();
	}
#endif

	// WS2801 INIT
#ifdef INCLUDE_WS2801
	if (WS2801_RGBLEDCOUNT > 0) {
		WS2801_strip.begin();
		WS2801_strip.show();
	}
#endif

#ifdef INCLUDE_MAX7221_MODULES
	for (i = 0; i < MAX7221_ENABLEDMODULES; i++) {
		MAX7221.shutdown(i, false);
		MAX7221.setIntensity(i, 15);
		MAX7221.clearDisplay(i);
	}
#endif // INCLUDE_MAX7221_MODULES

	// MAX7221 7SEG INIT
#ifdef INCLUDE_MAX7221MATRIX
	// MAX7221 MATRIX INIT
	for (i = 0; i < MAX7221_MATRIX_ENABLED; i++) {
		MAX7221_MATRIX.shutdown(i, false);
		MAX7221_MATRIX.setIntensity(i, 15);
		MAX7221_MATRIX.clearDisplay(i);
	}
#endif

	// 74HC595 INIT
#ifdef INCLUDE_74HC595_GEAR_DISPLAY
	if (ENABLE_74HC595_GEAR_DISPLAY == 1)
	{
		RS_74HC595_Init();
	}
#endif // INCLUDE_74HC595_GEAR_DISPLAY

#ifdef INCLUDE_TACHOMETER
	if (ENABLE_TACHOMETER) {
		rpmTone.begin(pinTacho);
	}
#endif

#ifdef INCLUDE_6c595_GEAR_DISPLAY
	if (ENABLE_6c595_GEAR_DISPLAY == 1) {
		pinMode(RS_6c595_DATAPIN, OUTPUT);
		pinMode(RS_6c595_LATCHPIN, OUTPUT);
		pinMode(RS_6c595_SLAVEPIN, OUTPUT);
		SPI.begin();
		digitalWrite(RS_6c595_SLAVEPIN, LOW); // << RCLK line goes low
		SPI.transfer(g_6c595fontArray[8]);  //  << SRCLK goes  high-low 8 times to output 8 bits of data
		digitalWrite(RS_6c595_SLAVEPIN, HIGH); // data outputs change on this rising edge << RCLK line goes high to move data into output register
	}
#endif // INCLUDE_6c595_GEAR_DISPLAY

	// LCD INIT
#ifdef INCLUDE_I2CLCD
	if (I2CLCD_enabled == 1) {
		I2CLCD.init();
		I2CLCD.backlight();
		I2CLCD.print("Hello world...");
		I2CLCD.clear();
	}
#endif

#ifdef INCLUDE_LEDBACKPACK
	// ADA_HT16K33_7SEGMENTS INIT
	if (ENABLE_ADA_HT16K33_7SEGMENTS == 1) {
		ADA_HT16K33_7SEGMENTS.begin(ADA_HT16K33_7SEGMENTS_I2CADDRESS);
	}

	// ADA_HT16K33_MATRIX INIT
	if (ENABLE_ADA_HT16K33_Matrix == 1) {
		ADA_HT16K33_MATRIX.begin(ADA_HT16K33_MATRIX_I2CADDRESS);
	}
#endif

#ifdef INCLUDE_OLED
	glcd1.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	glcd1.display();
#endif

#ifdef INCLUDE_ILI9341
  initLCD();
#endif //INCLUDE_ILI9341

#ifdef INCLUDE_TEENSY
  initJoystick();
#else
	// EXTERNAL BUTTONS INIT
	for (int btnIdx = 0; btnIdx < ENABLED_BUTTONS_COUNT; btnIdx++) {
		pinMode(BUTTON_PINS[btnIdx], INPUT_PULLUP);
	}
#endif // INCLUDE_TEENSY
}

#ifdef INCLUDE_TM1638
void TM1638_SetDisplayFromSerial(TM1638 * screen)
{
	for (i = 0; i < 8; i++) {
		displayValues[i] = FlowSerialRead();
	}
	screen->setDisplay(displayValues);

	// Leds

	for (i = 0; i < 8; i++) {
		char state = (char)FlowSerialRead();

		// Swap led colors if requested
		if (TM1638_SWAPLEDCOLORS == 1) {
			if (state == 'G')
			{
				state = 'R';
			}
			else if (state == 'R')
			{
				state = 'G';
			}
		}

		if (state == 'G') {
			screen->setLED(TM1638_COLOR_GREEN, i);
		}
		else if (state == 'R') {
			screen->setLED(TM1638_COLOR_RED, i);
		}
		else if (state == 'Y') {
			screen->setLED(TM1638_COLOR_RED + TM1638_COLOR_GREEN, i);
		}
		else {
			screen->setLED(TM1638_COLOR_NONE, i);
		}
	}
}
#endif

#ifdef INCLUDE_MAX7221_MODULES
void MAX7221_SetDisplayFromSerial(int idx)
{
	while (FlowSerialAvailable() < 8) {
	}
	// Digits
	for (i = 0; i < 8; i++) {
		while (FlowSerialAvailable() < 1) {
		}
		displayValues[i] = MAX7221_ByteReorder((char)FlowSerialRead());
	}

	for (i = 0; i < 8; i++) {
		MAX7221.setRow(idx, 7 - i, displayValues[i]);
	}
}
#endif

#ifdef INCLUDE_LEDBACKPACK
void ADA7SEG_SetDisplayFromSerial(int idx)
{
	// Digits
	for (i = 0; i < 8; i++) {
		displayValues[i] = (char)FlowSerialRead();
	}

	for (i = 0; i < 2; i++) {
		ADA_HT16K33_7SEGMENTS.writeDigitRaw(i, displayValues[i]);
	}

	ADA_HT16K33_7SEGMENTS.writeDigitRaw(2, 0);

	for (i = 2; i < 4; i++) {
		ADA_HT16K33_7SEGMENTS.writeDigitRaw(i + 1, displayValues[i]);
	}

	ADA_HT16K33_7SEGMENTS.writeDisplay();
}
#endif

void sendButtonState() {
	bool sendButtons = false;
#ifdef INCLUDE_TM1638
	for (i = 0; i < TM1638_ENABLEDMODULES; i++) {
		TM1638_screens[i]->Buttons = TM1638_screens[i]->Screen->getButtons();
		if (TM1638_screens[i]->Buttons != TM1638_screens[i]->Oldbuttons) {
			sendButtons = true;
		}
		TM1638_screens[i]->Oldbuttons = TM1638_screens[i]->Buttons;
	}
#endif

	//if (sendButtons)
	{
#ifdef INCLUDE_TM1638
		for (i = 0; i < TM1638_ENABLEDMODULES; i++) {
			FlowSerialWrite(TM1638_screens[i]->Buttons);
		}
#endif

#ifndef INCLUDE_TEENSY
     for (i = 0; i < ENABLED_BUTTONS_COUNT; i++) {
			FlowSerialWrite(digitalRead(BUTTON_PINS[i]) == HIGH ? 0 : 1);
		}
#endif

		FlowSerialFlush();
	}
}
#ifdef INCLUDE_MAX7221MATRIX
void MAX7221_MATRIX_Read() {
	while (FlowSerialAvailable() < 1) {
	}

	int luminosity = FlowSerialRead();

	if (MAX7221_MATRIX_LUMINOSITY != luminosity) {
		MAX7221_MATRIX.setIntensity(0, luminosity);
		MAX7221_MATRIX_LUMINOSITY = luminosity;
	}

	while (FlowSerialAvailable() < 8) {
	}

	for (int j = 0; j < 8; j++) {
		MAX7221_MATRIX.setRow(0, 7 - j, FlowSerialRead());
	}
}
#endif // INCLUDE_MAX7221MATRIX

#ifdef INCLUDE_LEDBACKPACK
void ADA_HT16K33_Matrix_Read() {
	while (FlowSerialAvailable() < 9) {
	}

	int luminosity = FlowSerialRead();

	if (ADA_HT16K33_Matrix_luminosity != luminosity) {
		ADA_HT16K33_MATRIX.setBrightness(luminosity);
		ADA_HT16K33_Matrix_luminosity = luminosity;
	}

	for (int j = 0; j < 8; j++) {
		byte row = FlowSerialRead();
		for (int c = 0; c < 8; c++) {
			ADA_HT16K33_MATRIX.drawPixel(j, c, ((row & (2 ^ c)) > 0) ? LED_GREEN : LED_OFF);
		}
	}

	ADA_HT16K33_MATRIX.writeDisplay();
}
#endif

#ifdef INCLUDE_TM1637
void TM1637_SetDisplayFromSerial(TM1637 * screen)
{
	for (i = 0; i < 4; i++) {
		screen->rawDisplay(i, FlowSerialRead());
	}

	// Skip 4 remaining chars
	for (i = 0; i < 4; i++) {
		FlowSerialRead();
	}
}
#endif

#ifdef INCLUDE_I2CLCD
void Read20x4LCD() {
	while (FlowSerialAvailable() < 2)
	{
	}
	if (FlowSerialRead() > 0) {
		//I2CLCD.backlight();
	}
	else {
		//I2CLCD.noBacklight();
	}
	int row = FlowSerialRead();

	I2CLCD.setCursor(0, row);

	/*for (i = 0; i < I2CLCD_width; i++)
	{
	while (FlowSerialAvailable() < 1)
	{
	}
	I2CLCD.write((char)FlowSerialRead());
	}*/
	I2CLCD.print(FlowSerialReadStringUntil('\n'));
}
#endif

void SetBaudrate() {
	while (FlowSerialAvailable() < 1) {
	}
	int br = FlowSerialRead();

	delay(200);

	if (br == 1) FlowSerialBegin(300);
	if (br == 2) FlowSerialBegin(1200);
	if (br == 3) FlowSerialBegin(2400);
	if (br == 4) FlowSerialBegin(4800);
	if (br == 5) FlowSerialBegin(9600);
	if (br == 6) FlowSerialBegin(14400);
	if (br == 7) FlowSerialBegin(19200);
	if (br == 8) FlowSerialBegin(28800);
	if (br == 9) FlowSerialBegin(38400);
	if (br == 10) FlowSerialBegin(57600);
	if (br == 11) FlowSerialBegin(115200);
	if (br == 12) FlowSerialBegin(230400);
	if (br == 13) FlowSerialBegin(250000);
	if (br == 14) FlowSerialBegin(1000000);
	if (br == 15) FlowSerialBegin(2000000);
	if (br == 16) FlowSerialBegin(200000);
}

#if defined(INCLUDE_NOKIALCD) || defined(INCLUDE_OLED)
uint8_t  fontSize;
int16_t  posX;
int16_t  posY;
char action;
int16_t v[4 * 2];
uint16_t color;
int16_t w;
int16_t h;
int16_t r;
uint8_t align = 0;
boolean wrap = 0;

int16_t boundX;
int16_t boundY;
uint16_t boundW;
uint16_t boundH;

uint8_t nokiaIndex;
int fontType;

#endif
#if defined(INCLUDE_NOKIALCD)
Adafruit_PCD8544* currentNokia;
#endif
#if defined(INCLUDE_OLED)
Adafruit_SSD1306* currentNokia;
#endif

uint8_t header = 0;
char opt;

void loop() {
	// Wait for data
	if (FlowSerialAvailable() >= 2) {
		// Reader header
		header = FlowSerialRead();
		if (header == 0x03)
		{
			// Read command
			opt = FlowSerialRead();

			// Hello command
			if (opt == '1') {
				while (FlowSerialAvailable() < 1) {
				}
				FlowSerialTrigger = FlowSerialRead();
				delay(10);
				FlowSerialPrint('h');
				FlowSerialFlush();
			}

			// Set baudrate
			if (opt == '8') {
				SetBaudrate();
			}

			// Simple buttons count
			if (opt == 'J') {
				FlowSerialWrite((byte)(ENABLED_BUTTONS_COUNT));
				FlowSerialFlush();
			}

			//  Module count command
			if (opt == '2') {
				FlowSerialWrite((byte)(TM1638_ENABLEDMODULES));
				FlowSerialFlush();
			}

			//  SIMPLE Module count command
			if (opt == 'B') {
				FlowSerialWrite((byte)(MAX7221_ENABLEDMODULES + TM1637_ENABLEDMODULES + ENABLE_ADA_HT16K33_7SEGMENTS));
				FlowSerialFlush();
			}

			// ACQ Packet
			if (opt == 'A') {
				FlowSerialWrite(0x03);
				FlowSerialFlush();
			}

			// Buttons state
			if (opt == 'C') {
				sendButtonState();
				FlowSerialFlush();
			}

			// Device Name
			if (opt == 'N') {
				FlowSerialPrint(DEVICE_NAME);
				FlowSerialPrint("\n");
				FlowSerialFlush();
			}

			// Tachometer
			if (opt == 'T') {
#ifdef INCLUDE_TACHOMETER
				int freq = FlowSerialReadStringUntil('\n').toInt();
				if (freq > 0) {
					rpmTone.play(freq);
					//tone(pinTacho, freq);
				}
				else {
					rpmTone.stop();
					//noTone(pinTacho);
				}
#endif
			}

#ifdef INCLUDE_BOOSTGAUGE
			if (opt == 'U') {
				int level = FlowSerialReadStringUntil('\n').toInt();
				analogWrite(pinBoost, level);
			}
#endif

			// Features command
			if (opt == '0') {
				delay(10);

				// Matrix
				if (MAX7221_MATRIX_ENABLED == 1 || ENABLE_ADA_HT16K33_Matrix == 1) {
					FlowSerialPrint("M");
				}

				// LCD
				if (I2CLCD_enabled == 1) {
#ifdef INCLUDE_I2CLCD
					FlowSerialPrint("L");
#endif
				}

				if (ENABLED_NOKIALCD > 0 || ENABLED_OLEDLCD > 0) {
					FlowSerialPrint("K");
				}

				// Gear
				FlowSerialPrint("G");

				// Name
				FlowSerialPrint("N");

				// Additional buttons
#ifndef INCLUDE_TEENSY
				//FlowSerialPrint("J");
#endif
				// Custom Protocol Support
				FlowSerialPrint("P");

#ifdef INCLUDE_TACHOMETER
				if (ENABLE_TACHOMETER > 0) {
					FlowSerialPrint("T");
				}
#endif

#ifdef INCLUDE_BOOSTGAUGE
				if (ENABLE_BOOSTGAUGE > 0) {
					FlowSerialPrint("U");
				}
#endif

				FlowSerialPrint("\n");
				FlowSerialFlush();
			}

			// Write 7seg data
			if (opt == '3') {
#ifdef INCLUDE_TM1638
				// TM1638
				for (int j = 0; j < TM1638_ENABLEDMODULES; j++) {
					while (FlowSerialAvailable() < 17) {
					}

					// Wait for display data
					int newIntensity = FlowSerialRead();
					if (newIntensity != TM1638_screens[j]->Intensity) {
						TM1638_screens[j]->Screen->setupDisplay(true, newIntensity);
						TM1638_screens[j]->Intensity = newIntensity;
					}

					TM1638_SetDisplayFromSerial(TM1638_screens[j]->Screen);
				}
#endif
			}

			// No leds 7 segments displays
			if (opt == 'S') {
#ifdef INCLUDE_TM1637
				// TM1637
				for (int j = 0; j < TM1637_ENABLEDMODULES; j++) {
					while (FlowSerialAvailable() < 9) {
					}
					// Intensity
					TM1637_screens[j]->set(FlowSerialRead());
					TM1637_SetDisplayFromSerial(TM1637_screens[j]);
				}
#endif
				// MAX7221
#ifdef INCLUDE_MAX7221_MODULES
				for (int j = 0; j < MAX7221_ENABLEDMODULES; j++) {
					while (FlowSerialAvailable() < 1) {
					}
					// Wait for display data
					int newIntensity = FlowSerialRead();
					if (newIntensity != MAX7221_screens[j]->Intensity) {
						MAX7221.setIntensity(j, newIntensity * 2 + 1);
						MAX7221_screens[j]->Intensity = newIntensity;
					}

					MAX7221_SetDisplayFromSerial(j);
				}
#endif // INCLUDE_MAX7221_MODULES

#ifdef INCLUDE_LEDBACKPACK
				// Simple ADA display
				for (int j = 0; j < ENABLE_ADA_HT16K33_7SEGMENTS; j++) {
					while (FlowSerialAvailable() < 9) {
					}
					int newIntensity = FlowSerialRead();
					ADA_HT16K33_7SEGMENTS.setBrightness(newIntensity * 2 + 1);

					ADA7SEG_SetDisplayFromSerial(j);
				}
#endif
			}

			//  RGBLED count command
			if (opt == '4') {
				FlowSerialWrite((byte)(WS2812B_RGBLEDCOUNT + WS2801_RGBLEDCOUNT));
				FlowSerialFlush();
			}

			// Write RGB LEDS data
			if (opt == '6') {
#ifdef INCLUDE_WS2812B
				for (uint8_t j = 0; j < WS2812B_RGBLEDCOUNT; j++) {
					while (FlowSerialAvailable() < 3) {
					}
					uint8_t r = FlowSerialRead();
					uint8_t g = FlowSerialRead();
					uint8_t b = FlowSerialRead();
					if (WS2812B_RIGHTTOLEFT == 1) {
						WS2812B_strip.setPixelColor(WS2812B_RGBLEDCOUNT - j - 1, r, g, b);
					}
					else {
						WS2812B_strip.setPixelColor(j, r, g, b);
					}
				}
				if (WS2812B_RGBLEDCOUNT > 0) {
					WS2812B_strip.show();
				}

#endif

#ifdef INCLUDE_WS2801
				for (uint8_t j = 0; j < WS2801_RGBLEDCOUNT; j++) {
					while (FlowSerialAvailable() < 3) {
					}
					uint8_t r = FlowSerialRead();
					uint8_t g = FlowSerialRead();
					uint8_t b = FlowSerialRead();
					if (WS2801_RIGHTTOLEFT == 1) {
						WS2801_strip.setPixelColor(WS2801_RGBLEDCOUNT - j - 1, r, g, b);
					}
					else
					{
						WS2801_strip.setPixelColor(j, r, g, b);
					}
				}
				if (WS2801_RGBLEDCOUNT > 0) {
					WS2801_strip.show();
				}
#endif
				// Acq !
				FlowSerialWrite(0x15);
			}

			// MAX7221 MATRIX
			if (opt == 'M') {
#ifdef INCLUDE_MAX7221MATRIX
				if (MAX7221_MATRIX_ENABLED == 1) {
					MAX7221_MATRIX_Read();
				}
#endif // INCLUDE_MAX7221MATRIX

#ifdef INCLUDE_LEDBACKPACK
				if (ENABLE_ADA_HT16K33_Matrix == 1) {
					ADA_HT16K33_Matrix_Read();
				}
#endif
			}

			// -------------- CUSTOM PROTOCOL PART -----------------
			// GEAR
			if (opt == 'G') {
				while (FlowSerialAvailable() < 1) {
				}
				char gear = FlowSerialRead();

#ifdef INCLUDE_74HC595_GEAR_DISPLAY
				if (ENABLE_74HC595_GEAR_DISPLAY == 1) {
					RS_74HC595_SetChar(gear);
				}
#endif

#ifdef INCLUDE_6c595_GEAR_DISPLAY
				if (ENABLE_6c595_GEAR_DISPLAY == 1) {
					RS_6c595_SetChar(gear);
				}
#endif
				//
				// Do what you want with current gear here ;)
				//
			}

			if (opt == 'L') {
#ifdef INCLUDE_I2CLCD
				Read20x4LCD();
#endif
			}

			// Nokia
			if (opt == 'K')
			{
#if defined(INCLUDE_NOKIALCD) || defined(INCLUDE_OLED)
				while (FlowSerialAvailable() < 2)
				{
				}

				nokiaIndex = FlowSerialRead();
				action = FlowSerialRead();
				currentNokia = nokiaLCDs[nokiaIndex];

				if (action == 'C')
				{
					currentNokia->clearDisplay();
				}

				if (action == 'N')
				{
					FlowSerialWrite((byte)ENABLED_NOKIALCD);
					FlowSerialFlush();
				}
				if (action == 'O')
				{
					FlowSerialWrite((byte)ENABLED_OLEDLCD);
					FlowSerialFlush();
				}

				if (action == 'I')
				{
					while (FlowSerialAvailable() < 1)
					{
					}
#ifdef INCLUDE_NOKIALCD
					currentNokia->setContrast(FlowSerialRead());
#endif // INCLUDE_NOKIALCD
				}

				else if (action == 'D')
				{
					currentNokia->display();
				}
				else if (action == 'P')
				{
					while (FlowSerialAvailable() < 8)
					{
					}

					fontSize = (uint8_t)FlowSerialRead();
					fontType = (uint8_t)FlowSerialRead();
					posX = (int16_t)FlowSerialRead();
					posY = (int16_t)FlowSerialRead();
					color = FlowSerialRead();
					wrap = FlowSerialRead() > 0;
					align = FlowSerialRead();

					currentNokia->setFont();

					if (fontType == 0) {
					}
#ifdef CUSTOM_LCD_FONT_1
					else if (fontType == 1) {
						currentNokia->setFont(&CUSTOM_LCD_FONT_1);
					}
#endif
#ifdef CUSTOM_LCD_FONT_2
					else if (fontType == 2) {
						currentNokia->setFont(&CUSTOM_LCD_FONT_2);
					}
#endif
#ifdef CUSTOM_LCD_FONT_3
					else if (fontType == 3) {
						currentNokia->setFont(&CUSTOM_LCD_FONT_3);
					}
#endif

					currentNokia->setTextWrap(wrap);
					currentNokia->setTextSize(fontSize);
					currentNokia->setTextColor(color);

					String content = FlowSerialReadStringUntil('\n');
					String content2 = content + "\n ";
					if (align == 2)
					{
						currentNokia->getTextBounds((char*)content2.c_str(), 0, 0, &boundX, &boundY, &boundW, &boundH);
						posX = posX - (boundW / 2);
					}
					else if (align == 3)
					{
						currentNokia->getTextBounds((char*)content2.c_str(), 0, 0, &boundX, &boundY, &boundW, &boundH);
						posX = posX - boundW;
					}

					currentNokia->setCursor(posX, posY);
					currentNokia->print(content);
				}
				else if (action == 'L') {
					while (FlowSerialAvailable() < 5)
					{
					}
					posX = (int16_t)FlowSerialRead();
					posY = (int16_t)FlowSerialRead();
					w = (int16_t)FlowSerialRead(); // x2
					h = (int16_t)FlowSerialRead(); // y2
					color = FlowSerialRead();

					currentNokia->drawLine(posX, posY, w, h, color);
				}
				else if (action == 'T') {
					while (FlowSerialAvailable() < 6)
					{
					}
					posX = (int16_t)FlowSerialRead();
					posY = (int16_t)FlowSerialRead();
					w = (int16_t)FlowSerialRead(); // x2
					h = (int16_t)FlowSerialRead(); // y2
					int thickness = FlowSerialRead();
					color = FlowSerialRead();

					float dx = posX - w;
					float dy = posY - h;
					float d = sqrtf(dx * dx + dy * dy);
					if (!d)
						return;

					int v[4 * 2];

					/* left up */
					v[0] = posX - thickness * dy / d;
					v[1] = posY + thickness * dx / d;
					/* right up */
					v[2] = posX + thickness * dy / d;
					v[3] = posY - thickness * dx / d;
					/* right down */
					v[4] = w + thickness * dy / d;
					v[5] = h - thickness * dx / d;
					/* left down */
					v[6] = w - thickness * dy / d;
					v[7] = h + thickness * dx / d;

					currentNokia->fillTriangle(v[0], v[1], v[6], v[7], v[2], v[3], color);
					currentNokia->fillTriangle(v[2], v[3], v[4], v[5], v[6], v[7], color);
				}

				else if (action == 'F' || action == 'R')
				{
					while (FlowSerialAvailable() < 6)
					{
					}

					posX = (int16_t)FlowSerialRead();
					posY = (int16_t)FlowSerialRead();
					w = (int16_t)FlowSerialRead();
					h = (int16_t)FlowSerialRead();
					r = (int16_t)FlowSerialRead();
					color = FlowSerialRead();

					if (r == 0) {
						if (action == 'F')
							currentNokia->fillRect(posX, posY, w, h, color);
						else
							currentNokia->drawRect(posX, posY, w, h, color);
					}
					else {
						if (action == 'F')
							currentNokia->fillRoundRect(posX, posY, w, h, r, color);
						else
							currentNokia->drawRoundRect(posX, posY, w, h, r, color);
					}
				}

#endif
			}

			// Custom protocol for end users (See Wiki for more infos : https://github.com/zegreatclan/AssettoCorsaTools/wiki/Custom-Arduino-hardware-support)
			if (opt == 'P') {

				// -------------------------------------------------------
				// EXAMPLE 1 - read the whole message and sent it back to simhub
				// -------------------------------------------------------
				//String message = FlowSerialReadStringUntil('\n');
				//FlowSerialDebugPrintLn("Message received : " + message);
        String rcvBuf;
#ifdef INCLUDE_ILI9341
        //Gear
        rcvBuf = FlowSerialReadStringUntil(';');
        rcvData[dataGEAR][0] = rcvBuf;
        rcvBuf = FlowSerialReadStringUntil(';');
        rcvData[dataRPM][0] = rcvBuf;
        rcvBuf = FlowSerialReadStringUntil(';');
        rcvData[dataSPD][0] = rcvBuf;
        rcvBuf = FlowSerialReadStringUntil(';');
        rcvData[dataFUEL][0] = rcvBuf;
        rcvBuf = FlowSerialReadStringUntil(';');
        rcvData[dataTIME][0] = rcvBuf.substring(3,11);
        rcvBuf = FlowSerialReadStringUntil(';');
        rcvData[dataTIRE][dataLF] = rcvBuf;
        rcvBuf = FlowSerialReadStringUntil(';');
        rcvData[dataTIRE][dataRF] = rcvBuf;
        rcvBuf = FlowSerialReadStringUntil(';');
        rcvData[dataTIRE][dataLR] = rcvBuf;
        rcvBuf = FlowSerialReadStringUntil(';');
        rcvData[dataTIRE][dataRR] = rcvBuf; 
        rcvBuf = FlowSerialReadStringUntil(';');
        rcvData[dataPOS][0] = rcvBuf;
        rcvBuf = FlowSerialReadStringUntil(';');
        rcvData[dataTOGO][0] = rcvBuf;
        rcvBuf = FlowSerialReadStringUntil(';');
        rcvData[dataLAST][0] = rcvBuf.substring(3,11);
#endif
        rcvBuf = FlowSerialReadStringUntil('\n');
				/*
				// -------------------------------------------------------
				// EXAMPLE 2 - reads speed and gear from the message
				// Protocol formula must be set in simhub to
				// format([DataCorePlugin.GameData.NewData.SpeedKmh],'0') + ';' + isnull([DataCorePlugin.GameData.NewData.Gear],'N')
				// -------------------------------------------------------

				int speed = FlowSerialReadStringUntil(';').toInt();
				String gear = FlowSerialReadStringUntil('\n');

				FlowSerialDebugPrintLn("Speed : " + String(speed));
				FlowSerialDebugPrintLn("Gear : " + gear);
				*/

				/*
				// -------------------------------------------------------
				// EXAMPLE 3 - Driving a E36 speed gauge connected to pin D3
				// Protocol formula must be set in simhub to round([DataCorePlugin.GameData.NewData.SpeedKmh],0)
				// format([DataCorePlugin.GameData.NewData.SpeedKmh],'0')
				// -------------------------------------------------------
				CustomProtocolExample3_E36Speedo();
				*/
			}
		}
	}
#ifdef INCLUDE_ILI9341
 int lcdCnt,lcdCnt2;
 for(lcdCnt=0;lcdCnt<DATA_NUM;lcdCnt++)
   for(lcdCnt2=0;lcdCnt2<dataCount[lcdCnt];lcdCnt2++)
     lcdWriteTxt(lcdCnt,lcdCnt2,rcvData[lcdCnt][lcdCnt2]);
#endif
#ifdef INCLUDE_TEENSY
  chkJoystick();
#endif
}


#ifdef INCLUDE_TEENSY
void chkEncoder(int num) {
  //TOD: add overflow Check
  long value;
  switch (num) {
    case 0:
      value = je1.read();
      break;
    case 1:
      value = je2.read();
      break;
    case 2:
      value = je3.read();
      break;
    default:
      return;
  }
  if (value != encCurrntPos[num]) {
    // to off if before Count is still on
    Joystick.button(encJNum[ENC_CW][num], 0);
    Joystick.button(encJNum[ENC_CCW][num], 0);
    delayMicroseconds(ENC_BTN_OFF_SPAN);
    if (value > encCurrntPos[num])
      Joystick.button(encJNum[ENC_CW][num], 1);
    if (value < encCurrntPos[num])
      Joystick.button(encJNum[ENC_CCW][num], 1);
    encCurrntPos[num] = value;
    encBtnTime[num] = millis();
  }
  if (encBtnTime[num] - millis() > ENC_BTN_ON) {
    Joystick.button(encJNum[ENC_CW][num], 0);
    Joystick.button(encJNum[ENC_CCW][num], 0);
    encBtnTime[num] = millis();
  }
}

void chkBtn(int num) {
  //TODO: add Bounce Check
  int data = 0x01 & digitalRead(btnPin[num]);

  if (data == 1)
    Joystick.button(num + 1, 0);
  else
    Joystick.button(num + 1, 1);
}

void initJoystick(){
    //joystick initialize
  for (int i = 0; i < BTNNum; i++) {
    btnStatus[i] = BTN_OFF;
    btnStatusOLD[i] = BTN_OFF;
  }
  for (int i = 0; i < NBTNNum; i++) {
    pinMode(btnPin[i], INPUT_PULLUP);
  }
  for (int i = 0; i < ENCNum; i++) {
    encCurrntPos[i] = -999;
    encBtnTime[i] = millis();
  }
  for (int i = 1; i < MAXBTN + 1; i++) {
    Joystick.button(i, 0);
  }
  btnRefreshTime = 0;
  Joystick.hat(-1);
}

void chkJoystick(){
  if(btnRefreshTime <=0 ||( millis() - btnRefreshTime > BTNRefleshRate)){
    btnRefreshTime = millis();
    for (int i = 0; i < NBTNNum; i++)
      chkBtn(i);
    for (int i = 0; i < ENCNum; i++)
      chkEncoder(i);
  }
}
#endif

#ifdef INCLUDE_ILI9341
void drawFrame(word pos,int Fx,int Fy,uint16_t color,String str){
  if(pos == 0) return;
  FramePosition p = getPos(pos);
  int lf = getLABELOffset(str);
  tft.drawRoundRect(p.X, p.Y, Fx, Fy, Frame_Round, color);
  tft.fillRoundRect(p.X + LABEL_FRAME_OFFSET_X, p.Y + LABEL_FRAME_OFFSET_Y, LABEL_FRAME_WIDTH, LABEL_FRAME_HEIGHT, Label_Frame_Round , color);
  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(p.X +lf, p.Y +LABEL_OFFSET_Y);
  tft.setTextSize(2);
  tft.print(str);
}

int getLABELOffset(String str){
  if(str.length()==4)return LABEL_OFFSET4_X;
  else return LABEL_OFFSET3_X;
}

FramePosition getPos(word PosNo){
  FramePosition pos;
  pos.X = 0;pos.Y = 0;

  byte framey = (PosNo >> 4) & 0xf;
  byte framex = PosNo & 0xf;

  switch(framex){
  case 1:
    pos.X =  Frame_Hor_Left;
    break;
  case 2:
    pos.X =  Frame_Hor_Center;
    break;    
  case 3:
    pos.X =  Frame_Hor_Right;
    break;    
  }
  
  switch(framey){
  case 1:
    pos.Y =  Frame_Vert_Top;
    break;
  case 2:
    pos.Y =  Frame_Vert_TopCenter;
    break;    
  case 3:
    pos.Y =  Frame_Vert_ButtomCenter;
    break;    
  case 4:
    pos.Y =  Frame_Vert_Buttom;
    break;    
  }
  
  return pos;
}

void lcdWriteTxt(int type,int idx,String str) {
  if(FramePos[type]==0) return;
  if (str == oldData[type][idx]) return;
  
  oldData[type][idx] = str;
  
  int left = getPos(FramePos[type]).X+Cursor_Offset_X[type];
  int top = getPos(FramePos[type]).Y+Cursor_Offset_Y[type]+Cursor_Span_Y[type]*idx;

  tft.fillRect(left, top, RectSize_X[type], RectSize_Y[type], ILI9341_BLACK);
  tft.setCursor(left, top);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(FontSize[type]);
  tft.print(str);
}

void writeFrameCaption(int type) {
  //only for TireFrame yet 
  if(type == 0)return;
  if(type != TIRE_FRAME_POS)return;
  FramePosition p = getPos(type);
  tft.setCursor(p.X + 10 , p.Y + 15);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print("LeftFront");
  tft.setCursor(p.X + 10 , p.Y + 53);
  tft.setTextSize(1);
  tft.print("RightFront");
  tft.setCursor(p.X + 10 , p.Y + 91);
  tft.setTextSize(1);
  tft.print("LeftRear");
  tft.setCursor(p.X + 10 , p.Y + 129);
  tft.setTextSize(1);
  tft.print("LeftRear");  
}

void initLCD() {
  
  //initialize LCD data and Test
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  int fcount;

  for(fcount =0;fcount<DATA_NUM;fcount++)
    drawFrame(FramePos[fcount], Frame_Width, FrameSize[fcount],FrameColor[fcount],FrameCaption[fcount]); 

  writeFrameCaption(TIRE_FRAME_POS);
}
#endif //INCLUDE_ILI9341
