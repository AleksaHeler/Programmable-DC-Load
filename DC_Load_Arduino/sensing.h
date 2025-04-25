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
float input_shunt_voltage_mv = 0.0f; /* Measured shunt voltage */
float input_current_ma = 0.0f; /* Measured current */
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
  /* Input voltage */
  uint16_t input_raw_adc = analogRead(INPUT_VOLTAGE_PIN); /* Raw ADC value */
  float input_voltage_divider = input_raw_adc * ( 5.0 / 1024.0); /* Scaled to voltage */
  input_voltage = INPUT_VOLTAGE_FACTOR * ( ( input_voltage_divider * (INPUT_VOLTAGE_R1 + INPUT_VOLTAGE_R2) ) / INPUT_VOLTAGE_R2 ); /* Scale to actual input voltage */

  /* Input current */
  /* 0.1 Ohm shunt, with 11x gain opamp stage. I(mA) = (v / 11.0) / 0.1 = (v / 11.0) * 10.0 = (v * 10.0) / 11.0 */
  input_shunt_voltage_mv = ina219.getShuntVoltage_mV();
  input_current_ma = INPUT_CURRENT_FACTOR * ( (input_shunt_voltage_mv * 10.0) / 11.0 );

  /* Input power (U * I) */
  input_power = input_voltage * (input_current_ma / 1000.0);
}

#endif SENSING_H
