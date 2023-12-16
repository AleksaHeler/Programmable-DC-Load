/*
* This module will be conserned with handling analog voltage outputs,
* Based on defined logic set output voltages (controlling current load) to some value.
* Logic:
*   - TODO!
*/
#ifndef OUTPUTS_H
#define OUTPUTS_H

#include "defines.h"
#include <PCF8591.h>

/* Library object used to interface the device */
PCF8591 pcf8591(PCF8591_I2C_ADDRESS);

/* Input variables from other modules */
extern float encoder_position;
extern float temperature;

/* Scaling to be applied to convert real current value to DAC value to be written */
#define CURRENT_SET_FACTOR (67.0f)

/* At what temperatures (C) to turn on/off the fan */
#define FAN_TEMP_LOW 25
#define FAN_TEMP_HIGH 30

/* PWM values for finer control of the fan (255max) */
#define FAN_PWM_OFF 0
#define FAN_PWM_LOW 127
#define FAN_PWM_HIGH 255

/* How many cycles (each is ~10ms) to wait for the value to stabilize */
#define FAN_DEBOUNCE_COUNT_MAX 300

/* Type defines */
typedef enum fan_state_t {
  fan_off,
  fan_low,
  fan_high
};

/* Internal variables */
fan_state_t fan_state = fan_off;
fan_state_t fan_state_prev = fan_off;
int debounceCnt = FAN_DEBOUNCE_COUNT_MAX; /* Counter for debouncing timer */
int current_output = 0; /* Raw output to be written to the DAC */
float current_set = 0; /* Wanted current value (A) */

/* Prototypes for all used functions */
void outputs_setup();
void outputs_handle();
void outputs_handle_dac();
void outputs_handle_fan();

/* Called once during boot */
void outputs_setup()
{
	pcf8591.begin();
  pinMode(FAN_PIN, OUTPUT);
}

/* Called cyclically while device is running */
void outputs_handle()
{
  outputs_handle_dac();
  outputs_handle_fan();
}

/* Set value on DAC to control the current load */
void outputs_handle_dac()
{
  current_set = (encoder_position * LOAD_MAX_CURRENT)/100.0f; /* (0-100%) * MAX_CURR */
  current_output = (int)(current_set * CURRENT_SET_FACTOR);

  /* Set the current with DAC output */
  pcf8591.analogWrite(current_output);
}

/* Actuate the fan based on temperature readings to stop overheating */
void outputs_handle_fan()
{
  /* Set the fan PWM duty based on the temperature */
  if(temperature > FAN_TEMP_HIGH){
    fan_state = fan_high;
  }
  else if(temperature > FAN_TEMP_LOW){
    fan_state = fan_low;
  }
  else{
    fan_state = fan_off;
  }

  switch(fan_state){
    case fan_off:
      analogWrite(FAN_PIN, FAN_PWM_OFF);
      break;
    case fan_low:
      analogWrite(FAN_PIN, FAN_PWM_LOW);
      break;
    case fan_high:
      analogWrite(FAN_PIN, FAN_PWM_HIGH);
      break;
    default:
      break;
  }

  /* Now, if the value hasn't changed, debounce it and actuate when done */
//  if(fan_state == fan_state_prev){
//    debounceCnt--;
//
//    /* If the timer is done, this means the goal state hasn't changed for some time, so set the fan to this state */
//    if(debounceCnt == 0){
//      switch(fan_state){
//        case fan_off:
//          analogWrite(FAN_PIN, FAN_PWM_OFF);
//          break;
//        case fan_low:
//          analogWrite(FAN_PIN, FAN_PWM_LOW);
//          break;
//        case fan_high:
//          analogWrite(FAN_PIN, FAN_PWM_HIGH);
//          break;
//        default:
//          break;
//      }
//      debounceCnt = FAN_DEBOUNCE_COUNT_MAX;
//    }
//  }
//  /* If the value is changed, reset the debounce timer and wait for it to stabilize */
//  else{
//    fan_state_prev = fan_state;
//    debounceCnt = FAN_DEBOUNCE_COUNT_MAX;
//  }
}

#endif OUTPUTS_H
