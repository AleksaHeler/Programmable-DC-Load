/*
* This module will be conserned with handling analog inputs.
* Based on defined logic process incoming data and store in internal variables.
* Logic:
*   - TODO!
*/
#ifndef INPUTS_H
#define INPUTS_H

#include "defines.h"

/* Factors used to mutliply the raw ADC value to get the calibrated physical value */
#define CURRENT_SCALING_FACTOR (0.04795383256f)
#define VOLTAGE_SCALING_FACTOR (0.028330424f)
#define TEMPERATURE_SCALING_FACTOR (0.1f)
#define TEMPERATURE_OFFSET_FACTOR (-23.0f)

/* External variables - that can be used by other modules */
float current = 0;
float voltage = 0;
float power = 0;
float temperature = 0;

/* Internal variables */
int currAnaIn = 0;
int voltAnaIn = 0;
int tempAnaIn = 0;

/* Prototypes for all used functions */
void inputs_setup();
void inputs_handle();

/* Called once during boot */
void inputs_setup()
{
  /* No setup needed for analog input pins for now! */
}

/* Called cyclically while device is running */
void inputs_handle()
{
  /* Read all the analog inputs */
  currAnaIn = analogRead(CURR_READ_PIN);
  voltAnaIn = analogRead(VOLT_READ_PIN);
  tempAnaIn = analogRead(TEMP_READ_PIN);
  
  /* Calculate actual physical values */
  current = currAnaIn * CURRENT_SCALING_FACTOR;
  voltage = voltAnaIn * VOLTAGE_SCALING_FACTOR;
  temperature = tempAnaIn * TEMPERATURE_SCALING_FACTOR + TEMPERATURE_OFFSET_FACTOR;
  power = voltage * current;
}

#endif /* INPUTS_H */
