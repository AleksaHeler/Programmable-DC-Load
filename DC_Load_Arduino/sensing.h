/**
 * @file sensing.h
 * 
 * @brief This file contains functions regarding sensing and measurements of input current/voltage and power.
 * 
 * Voltage measured via voltage divider (47k, 10k)
 * Current measured via ADC (INA219)
 * Power/resistance calculated from voltage and current
 * 
 * @note: using adafruit library for Adafruit_INA219
 */
#ifndef SENSING_H
#define SENSING_H

#include "defines.h"
#include <Wire.h>
#include <Adafruit_INA219.h>

// ADC_INA219_I2C_ADDRESS
Adafruit_INA219 ina219;

/* Measured voltage and current */
float input_voltage = 0.0f; /* Measured voltage */
float input_current = 0.0f; /* Measured current */
float input_power = 0.0f;   /* Calculated power */

/* Prototypes for all used functions */
void sensing_setup();
void sensing_handle();

/**
 * @brief Setup pins, and initialize everything
 */
void sensing_setup()
{
  /* Initialize INA219 ADC IC */
  if (! ina219.begin())
  {
    Serial.println("Failed to find INA219 chip!");
  }
}

/**
 * @brief Handle all sensing and measurements
 */
void sensing_handle()
{
  uint16_t input_raw_adc = analogRead(INPUT_VOLTAGE_PIN); /* Raw ADC value */
  float input_voltage_divider = input_raw_adc * ( 5.0 / 1024.0); /* Scaled to voltage */
  input_voltage = ( input_voltage_divider * (INPUT_VOLTAGE_R1 + INPUT_VOLTAGE_R2) ) / INPUT_VOLTAGE_R2; /* Scale to actual input voltage */
  input_current = ina219.getCurrent_mA() / 1000.0; /* By default, this library expects 0.1 Ohm shunt, as is our case */
  input_power = input_voltage * input_current;
}

#endif SENSING_H
