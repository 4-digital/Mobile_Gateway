

// ============================================================                                                            
// Example:     LCDML: display with liquidcrystal and i2c                          
// ============================================================
// Autor:       Nils Feldkämper
// Last update: 08.01.2017
// License:     MIT                                     
// ============================================================ 
// Descripton:  
// This example is like the liquidcrystal example with another 
// lcd object.
// ============================================================ 

  // include libs
  #include <Wire.h> 
  #include <LiquidCrystal_I2C.h>
  #include <LCDMenuLib.h>
//---------------------------------------------------------------------------------------
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>
#include <dht.h>
dht DHT;
#define DHT11_PIN 5

//--------------------------------------------------------------------------------------
  
  // lib config
  #define _LCDML_DISP_cfg_button_press_time          200    // button press time in ms
  #define _LCDML_DISP_cfg_scrollbar                  1      // enable a scrollbar
  #define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol 
  #define _LCDML_DISP_cfg_initscreen_time            10000  // enable initscreen time



//--------------------------------------------------------------------------------------
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN_STRIP 2
#define PIN_RING  3

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS_STRIP 24
#define NUMPIXELS_RING 24

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS_STRIP, PIN_STRIP, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUMPIXELS_RING, PIN_RING, NEO_GRB + NEO_KHZ800);

//-----------------------------------------------------------------------------------------



// ********************************************************************* 
// LCDML TYPE SELECT
// *********************************************************************
  // settings for lcd 
  #define _LCDML_DISP_cols             20
  #define _LCDML_DISP_rows             4  

  // lcd object
  //LiquidCrystal_I2C lcd(0x27);  // Set the LCD I2C address
  //LiquidCrystal_I2C lcd(0x27, BACKLIGHT_PIN, POSITIVE);  // Set the LCD I2C address
  LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

  
  
  const uint8_t scroll_bar[5][8] = {
    {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
    {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1 
    {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
    {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
    {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
  }; 

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // create menu
  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    42
  
  // LCDML_root        => layer 0 
  // LCDML_root_X      => layer 1 
  // LCDML_root_X_X    => layer 2 
  // LCDML_root_X_X_X  => layer 3 
  // LCDML_root_... 	 => layer ... 
  
  // LCDMenuLib_add(id, group, prev_layer_element, new_element_num, lang_char_array, callback_function)
  LCDML_DISP_init(_LCDML_DISP_cnt);
  
  
  
  

   LCDML_DISP_add      (0   , _LCDML_G1  , LCDML_root          , 1   , "Scene Select"           , LCDML_FUNC);
   LCDML_DISP_add      (1   , _LCDML_G1  , LCDML_root_1        , 1   , "Eco Mode"               , LCDML_FUNC);
   LCDML_DISP_add      (2   , _LCDML_G1  , LCDML_root_1        , 2   , "sleep mode"             , LCDML_FUNC);
   LCDML_DISP_add      (3   , _LCDML_G1  , LCDML_root_1        , 3   , "movie"                  , LCDML_FUNC);
   LCDML_DISP_add      (4   , _LCDML_G1  , LCDML_root_1        , 4   , "party"                  , LCDML_FUNC);
   LCDML_DISP_add      (5   , _LCDML_G1  , LCDML_root_1        , 5   , "dinner"                 , LCDML_FUNC);
   LCDML_DISP_add      (6   , _LCDML_G1  , LCDML_root_1        , 6   , "cooking"                , LCDML_FUNC);
   LCDML_DISP_add      (7   , _LCDML_G1  , LCDML_root_1        , 7   , "reading"                , LCDML_FUNC);
   LCDML_DISP_add      (8   , _LCDML_G1  , LCDML_root_1        , 8   , "evening"                , LCDML_FUNC);
   LCDML_DISP_add      (9   , _LCDML_G1  , LCDML_root_1        , 9   , "away"                   , LCDML_FUNC);
   LCDML_DISP_add      (10  , _LCDML_G1  , LCDML_root_1        , 10  , "good morning"           , LCDML_FUNC);
   LCDML_DISP_add      (11  , _LCDML_G1  , LCDML_root_1        , 11  , "good night"             , LCDML_FUNC);
   LCDML_DISP_add      (12  , _LCDML_G1  , LCDML_root_1        , 12  , "studio"                 , LCDML_FUNC);
   LCDML_DISP_add      (13  , _LCDML_G1  , LCDML_root_1        , 13  , "back"                   , LCDML_FUNC_back);

   LCDML_DISP_add      (14  , _LCDML_G1  , LCDML_root          , 2   , "Functions"              , LCDML_FUNC);
   LCDML_DISP_add      (15  , _LCDML_G1  , LCDML_root_2        , 1   , "speakers"               , LCDML_FUNC);
   LCDML_DISP_add      (16  , _LCDML_G1  , LCDML_root_2        , 2   , "electronic labor"       , LCDML_FUNC);
   LCDML_DISP_add      (17  , _LCDML_G1  , LCDML_root_2        , 3   , "dock station"           , LCDML_FUNC);
   LCDML_DISP_add      (18  , _LCDML_G1  , LCDML_root_2        , 4   , "foto studio"            , LCDML_FUNC);
   LCDML_DISP_add      (19  , _LCDML_G1  , LCDML_root_2        , 5   , "foam cutting"           , LCDML_FUNC);
   LCDML_DISP_add      (20  , _LCDML_G1  , LCDML_root_2        , 6   , "back"                   , LCDML_FUNC_back);
 
   LCDML_DISP_add      (21  , _LCDML_G1  , LCDML_root          , 3   , "Learn"                  , LCDML_FUNC);
   LCDML_DISP_add      (22  , _LCDML_G1  , LCDML_root_3        , 1   , "Music"                  , LCDML_FUNC);
   LCDML_DISP_add      (23  , _LCDML_G1  , LCDML_root_3        , 2   , "Math"                   , LCDML_FUNC);
   LCDML_DISP_add      (24  , _LCDML_G1  , LCDML_root_3        , 3   , "English"                , LCDML_FUNC);
   LCDML_DISP_add      (25  , _LCDML_G1  , LCDML_root_3        , 4   , "German"                 , LCDML_FUNC);  
   LCDML_DISP_add      (26  , _LCDML_G1  , LCDML_root_3        , 5   , "back"                   , LCDML_FUNC_back);

  
   LCDML_DISP_add      (27  , _LCDML_G1  , LCDML_root          , 4   , "Games"                  , LCDML_FUNC);
   LCDML_DISP_add      (28  , _LCDML_G1  , LCDML_root_4        , 1   , "fade efect"             , LCDML_FUNC_NeoPixel);
   LCDML_DISP_add      (29  , _LCDML_G1  , LCDML_root_4        , 2   , "vu meter"               , LCDML_FUNC);
   LCDML_DISP_add      (30  , _LCDML_G1  , LCDML_root_4        , 3   , "proximity"              , LCDML_FUNC);
   LCDML_DISP_add      (31  , _LCDML_G1  , LCDML_root_4        , 4   , "back"                   , LCDML_FUNC_back);

  
  
   LCDML_DISP_add      (32  , _LCDML_G1  , LCDML_root          , 5   , "Mode"                   , LCDML_FUNC);
   LCDML_DISP_add      (33  , _LCDML_G1  , LCDML_root_5        , 1   , "kids"                   , LCDML_FUNC);
   LCDML_DISP_add      (34  , _LCDML_G1  , LCDML_root_5        , 2   , "parents"                , LCDML_FUNC);
   LCDML_DISP_add      (35  , _LCDML_G1  , LCDML_root_5        , 3   , "back"                   , LCDML_FUNC_back);

  
  
   LCDML_DISP_add      (36  , _LCDML_G1  , LCDML_root          , 6   , "Setings"                , LCDML_FUNC);
   LCDML_DISP_add      (37  , _LCDML_G1  , LCDML_root_6        , 1   , "disabled"               , LCDML_FUNC);
   LCDML_DISP_add      (38  , _LCDML_G1  , LCDML_root_6        , 2   , "basic"                  , LCDML_FUNC);
   LCDML_DISP_add      (39  , _LCDML_G1  , LCDML_root_6        , 3   , "advanced"               , LCDML_FUNC);
   LCDML_DISP_add      (40  , _LCDML_G1  , LCDML_root_6        , 4   , "back"                   , LCDML_FUNC_back);

   LCDML_DISP_add      (41  , _LCDML_G1  , LCDML_root          , 7  , "Information"             , LCDML_FUNC_information);
   
   
   LCDML_DISP_add      (42  , _LCDML_G7  , LCDML_root          , 8  , "Program 2"               , LCDML_FUNC_initscreen); // in g7 => hidden
  
  /*
  LCDML_DISP_add      (1  , _LCDML_G1  , LCDML_root        , 2  , "Time info"          , LCDML_FUNC_timer_info);
  LCDML_DISP_add      (2  , _LCDML_G1  , LCDML_root        , 3  , "Settings"           , LCDML_FUNC);
  LCDML_DISP_add      (3  , _LCDML_G1  , LCDML_root_3      , 1  , "Neo Pixel"          , LCDML_FUNC_NeoPixel);
  LCDML_DISP_add      (4  , _LCDML_G1  , LCDML_root_3      , 2  , "Something"          , LCDML_FUNC);
  LCDML_DISP_add      (5  , _LCDML_G1  , LCDML_root        , 4  , "Program"            , LCDML_FUNC);
  LCDML_DISP_add      (6  , _LCDML_G1  , LCDML_root_4      , 1  , "Program 1"          , LCDML_FUNC);
  LCDML_DISP_add      (7  , _LCDML_G1  , LCDML_root_4_1    , 1  , "P1 start"           , LCDML_FUNC);
  LCDML_DISP_add      (8  , _LCDML_G1  , LCDML_root_4_1    , 2  , "Settings"           , LCDML_FUNC);
  LCDML_DISP_add      (9  , _LCDML_G1  , LCDML_root_4_1_2  , 1  , "Warm"               , LCDML_FUNC);
  LCDML_DISP_add      (10 , _LCDML_G1  , LCDML_root_4_1_2  , 2  , "Long"               , LCDML_FUNC);
  LCDML_DISP_add      (11 , _LCDML_G1  , LCDML_root_4      , 2  , "Program 2"          , LCDML_FUNC_p2);
  LCDML_DISP_add      (12 , _LCDML_G1  , LCDML_root        , 5  , "Last Point"         , LCDML_FUNC);
  LCDML_DISP_add      (13 , _LCDML_G1  , LCDML_root_4_1_2  , 3  , "Exit"               , LCDML_FUNC);
  LCDML_DISP_add      (14 , _LCDML_G7  , LCDML_root        , 6  , "Program 2"          , LCDML_FUNC_initscreen); // in g7 => hidden
  LCDML_DISP_add      (15 , _LCDML_G1  , LCDML_root_4_1_2  , 4  , "Back"               , LCDML_FUNC_back);
  */
  
  LCDML_DISP_createMenu(_LCDML_DISP_cnt);



// ********************************************************************* 
// LCDML BACKEND (core of the menu, do not change here anything yet)
// ********************************************************************* 
  // define backend function  
  #define _LCDML_BACK_cnt    1  // last backend function id
  
  LCDML_BACK_init(_LCDML_BACK_cnt);
  LCDML_BACK_new_timebased_dynamic (0  , ( 20UL )         , _LCDML_start  , LCDML_BACKEND_control);
  LCDML_BACK_new_timebased_dynamic (1  , ( 1000UL )       , _LCDML_stop   , LCDML_BACKEND_menu);
 
  LCDML_BACK_create();
// ********************************************************************* 
// INIT SOME GLOBAL VARS
// *********************************************************************
  unsigned int g_sec_counter = 0;  

// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  {  
    // serial init; only be needed if serial control is used 
    while(!Serial);                    // wait until serial ready
    Serial.begin(9600);                // start serial    
    Serial.println(F(_LCDML_VERSION)); // only for examples
    
    // LCD Begin
    lcd.begin(_LCDML_DISP_cols,_LCDML_DISP_rows);  

    //----------------------------------------------------------------
     pixels.begin(); // This initializes the NeoPixel library.
     pixels.show(); // Initialize all pixels to 'off'
    //--------------------------------------------------------------
    
    lcd.home ();                   // go home       
    // set special chars for scrollbar
    lcd.createChar(0, (uint8_t*)scroll_bar[0]);
    lcd.createChar(1, (uint8_t*)scroll_bar[1]);
    lcd.createChar(2, (uint8_t*)scroll_bar[2]);
    lcd.createChar(3, (uint8_t*)scroll_bar[3]);
    lcd.createChar(4, (uint8_t*)scroll_bar[4]);
    lcd.setCursor(0,0);
    lcd.print(F("booting"));
  
    // Enable all items with _LCDML_G1
    LCDML_DISP_groupEnable(_LCDML_G1); // enable group 1
  
    // LCDMenu Setup
    LCDML_setup(_LCDML_BACK_cnt);  
  }

// *********************************************************************
// LOOP
// *********************************************************************
  void loop()

  { 

// example for init screen   
    if((millis() - g_lcdml_initscreen) >= _LCDML_DISP_cfg_initscreen_time) {
      g_lcdml_initscreen = millis(); // reset init screen time
      LCDML_DISP_jumpToFunc(LCDML_FUNC_initscreen); // jump to initscreen     
    }  
    
    // this function must called here, do not delete it
    LCDML_run(_LCDML_priority); 
  }




// *********************************************************************
// check some errors - do not change here anything
// *********************************************************************
# if(_LCDML_DISP_rows > _LCDML_DISP_cfg_max_rows)
# error change value of _LCDML_DISP_cfg_max_rows in LCDMenuLib.h
# endif
# if(_LCDML_DISP_cols > _LCDML_DISP_cfg_max_string_length)
# error change value of _LCDML_DISP_cfg_max_string_length in LCDMenuLib.h
# endif
