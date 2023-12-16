/*
* This program is intended to be used to control a programmable electronic DC load.
* Interfacing is possible with a rotary encoder and a 16x2 LCD display, to set mode (CC, CR, CP)
* and to configure it and track the state of the whole device.
*
* TODO: develop and implement calibration feature (without reprogramming the device, EEPROM)
* TODO: adapt for variant with other external ADCs and DACs
* TODO: update LCD screen to have more info and cycle between some things
* TODO: add timer so that we have precise 10ms cycles (and measure execution time just for reference)
*/

/* Include our helper files */
#include "defines.h"
#include "inputs.h"
#include "rotary_encoder.h"
#include "outputs.h"
#include "lcd_display.h"

/* First setup all used helper modules */
void setup() 
{
  inputs_setup(); /* analog inputs: current, voltage, temperature */
  rotary_encoder_setup(); /* well, rotary encoder input */
  lcd_setup(); /* 16x2 LCD */
  outputs_setup(); /* DAC current setting output */
}

/* During loop, just call helper function to handle all the functionality every 10ms */
void loop() 
{
  inputs_handle();
  rotary_encoder_handle();
  lcd_handle();
  outputs_handle();

  /* No need to be super precise here, but we can just wait for some time for stability */
  delay(10);
}
