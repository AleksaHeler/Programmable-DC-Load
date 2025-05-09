/*
 * This program is intended to be used to control a programmable electronic DC load.
 * Interfacing is possible with a rotary encoder and a 16x2 LCD display, to set mode (CC, CR, CP)
 * and to configure it and track the state of the whole device.
 *
 * TODO: develop and implement calibration feature (without reprogramming the device, EEPROM)
 * TODO: adapt for variant with other external ADCs and DACs
 * TODO: update LCD screen to have more info and cycle between some things
 * TODO: add timer so that we have precise 10ms cycles (and measure execution time just for reference)
 * TODO: add a mode for batteries, to set the cut-off voltage when to stop current
 * 
 * 
 * From INA219 datasheet, chapter 9.2:
 *  Current_LSB = Max expected current / 2^15
 *  Cal = trunc ( 0.04096 / Current_LSB * Rshunt ) // trunc = floor, round the value down
 * So for our case, max current is 5A, and Rshunt is 0.1 Ohm
 *  Current_LSB = 5A / 32768 = 0.000152587890625 A = 0.1526 mA
 *  Cal = trunc ( 0.04096 / 0.000152587890625 * 0.1 ) = trunc(2672.0) = 2672
 * This value is then programmed into the Calibration register
 * 
 */

/* Include our helper files */
#include "defines.h"   /* Global defines */
#include "sensing.h"   /* Handle sensing of current and voltage */
#include "ntc.h"       /* Handle NTC temperature sensors */
#include "encoder.h"   /* Handle rotary encoder */
#include "dac.h"       /* Handle DAC output */
#include "leds.h"      /* Handle status LEDs */
#include "fan.h"       /* Handle fan */
#include "oled.h"      /* Handle OLED display */
#include "logger.h"    /* Handle logging */


/* First setup all used helper modules */
void setup() 
{
  Serial.begin(9600); /* Start serial communication for debugging */
  Serial.println("Starting DC Load program...");

  sensing_setup(); /* Sensing of current and voltage */
  ntc_setup();     /* NTC temperature input */
  encoder_setup(); /* Encoder input */
  dac_setup();     /* DAC output for current */
  leds_setup();    /* LED status output */
  fan_setup();     /* Fan driver output */
  oled_setup();    /* OLED display output */
  logger_setup();  /* Logger output */

  leds_set_led(0, led_blink_slow); /* Set LED to blink slowly */
  Serial.println("Setup complete!");
}

/* During loop, just call helper function to handle all the functionality every 10ms */
void loop() 
{
  sensing_handle(); /* Read voltage and current */
  ntc_handle();     /* Read NTC temperatures */
  encoder_handle(); /* Read encoder input */
  dac_handle();     /* Handle DAC output */
  leds_handle();    /* Handle LED states and blinking */
  fan_handle();     /* Handle fan driver */
  oled_handle();    /* Handle OLED display */
  logger_handle();  /* Handle logging */

  // dac_set_output(0.2); // Set DAC to x volts
  // fan_set_pwm(90); // Set fan to x%
  // ntc_temperatures[0]  // PCB temperature
  // ntc_temperatures[1]  // External temperature

  fan_set_pwm(encoderPosition);
  
  delay(1);
}
