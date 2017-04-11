# Mobile_Gateway
wi-fi sensors, lcd,... for Smart Home

i2c lcd: 0x3F

encoder:
  taste 7
  a     8
  b     9
  
24x NeoPixel:
    Pin   2
  
add backfunction in ultimul tab
luat exemplu de LCDM_back_function

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_back)
// *********************************************************************
{
  // setup
  // is called only if it is started
}
   
void LCDML_DISP_loop(LCDML_FUNC_back)
{
  // loop
  // is called when it is triggert
  LCDML_DISP_resetIsTimer(); // reset the initscreen timer
  LCDML.goBack();            // go back
  LCDML_DISP_funcend();      // LCDML_DISP_funcend calls the loop_end function
}
   
void LCDML_DISP_loop_end(LCDML_FUNC_back)
{
  // loop end
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing 
}


si meniu pt fiecare level

 LCDML_DISP_add      (15 , _LCDML_G1  , LCDML_root_4_1_2  , 4  , "Back"               , LCDML_FUNC_back);


--------------------------------------------------------------------------------------------------------------
// Descripton:     
// This examples thows how the static menu text can be dynamical
// update. For example for a clock as text.
// In this Tab is a backend function added. In this function is 
// the refresh call for the menu. In the FUNC_DISP tab is the 
// content switch for the menu. 

dynamic menuitem
schimba primul meniu cu un counter si clipeste cand se schimba cifra
addd code to LCDM_DISP tab:

				case 0:
				lcd.print("Sec counter: "); // or datetime or other things
				lcd.print(g_sec_counter);
				break;


addd code to LCDM_FUNC_BACKEND tab:



/* ******************************************************************** */  
void LCDML_BACK_setup(LCDML_BACKEND_sec_counter)
/* ******************************************************************** */
{
  // setup
  // is called only if it is started or restartet (reset+start)
}

boolean LCDML_BACK_loop(LCDML_BACKEND_sec_counter)
{    
  // runs in loop
  g_sec_counter++; 
      
  // Update menu if no function is running (the check is in LCDML_DISP_update_menu_direct())
  // the update function check if the parameter id is realy displayed on the screen only then 
  // the display is realy updated.  
  LCDML_DISP_update_menu_direct(0);
 
  return false;  
}

void LCDML_BACK_stable(LCDML_BACKEND_sec_counter)
{
  // stable stop
  // is called when a backend function is stopped with stopStable  
}




addd code to first tab:


  #define _LCDML_BACK_cnt    2  // last backend function id


  LCDML_BACK_new_timebased_dynamic (2  , ( 1000UL )       , _LCDML_start  , LCDML_BACKEND_sec_counter);

// ********************************************************************* 
// INIT SOME GLOBAL VARS
// *********************************************************************
	unsigned int g_sec_counter = 0;  
----------------------------------------------------------------------------------------------------
// Descripton:     
// In this example menu elements are in different groups. 
// Groups can be enabled (displayed) and disabled (not displayed).
// You can change under "Settings" the status from "Program" Menu.


in void setup:

LCDML_DISP_groupEnable(_LCDML_G2); // enable group 2

de pus in LCMD_FUNC_DISP:



// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_program_enable)
// *********************************************************************
{
  // setup function 
  LCDML_DISP_groupDisable(_LCDML_G2); // enable group 2
  LCDML_DISP_groupEnable(_LCDML_G3); // enable group 2
  LCDML.goRoot(); // go to root element (first element of this menu with id=0) 
}

void LCDML_DISP_loop(LCDML_FUNC_program_enable) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
}

void LCDML_DISP_loop_end(LCDML_FUNC_program_enable)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing   
}  



// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_program_disable)
// *********************************************************************
{
  // setup function 
  LCDML_DISP_groupDisable(_LCDML_G3); // enable group 2
  LCDML_DISP_groupEnable(_LCDML_G2); // enable group 2
  LCDML.goRoot(); // go to root element (first element of this menu with id=0) 
}

void LCDML_DISP_loop(LCDML_FUNC_program_disable) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
}

void LCDML_DISP_loop_end(LCDML_FUNC_program_disable)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing 
   
}


Asta se pune in primul tab:

LCDML_DISP_add      (1  , _LCDML_G2  , LCDML_root_1      , 1  , "En Program"         , LCDML_FUNC_program_enable);
LCDML_DISP_add      (2  , _LCDML_G3  , LCDML_root_1      , 2  , "Dis Program"        , LCDML_FUNC_program_disable);

------------------------------------------------------------------------------------------------------