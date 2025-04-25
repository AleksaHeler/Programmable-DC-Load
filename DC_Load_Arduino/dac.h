/**
 * @file dac.h
 * 
 * @brief This file contains functions regarding DAC output to set current
 * 
 */
#ifndef DAC_H
#define DAC_H

#include "defines.h"
#include <Wire.h>

/* Global variable to store the output value (read only) */
float dac_set_current = 0.0f; /* Measured voltage */

/* Prototypes for all used functions */
void dac_setup();
void dac_handle();
void dac_set_output(float voltage);

/**
 * @brief Setup
 */
void dac_setup()
{
  // Join I2C bus as master
  Wire.begin();
}

/**
 * @brief Handle
 */
void dac_handle()
{
  /* Nothing for now */
  dac_set_output(0.3);  // Set to x amps
}

/**
 * @brief Set the DAC current
 * 
 * @param amps Current to set (0-5A)
 */
void dac_set_output(float amps)
{
  /* First check if given current is in valid range */
  if (amps < 0.0) amps = 0.0;  // Limit to 0A
  if (amps > 5.0) amps = 5.0;  // Limit to 5A

  /* Store the set output values */
  dac_set_current = amps;

  /* Now apply scaling value, which is calibrated */
  amps = amps * DAC_OUTPUT_FACTOR;  // Scale to amps

  /* Now onto calculating the register values */
  uint16_t dacVal = (amps / DAC_VREF) * 1023;
  if (dacVal > 1023) dacVal = 1023;

  // Command byte structure:
  // C2:C1:C0 = 010 (Write to DAC register), PD1:PD0 = 00 (Normal mode), VREF = external, GAIN = 1x
  uint8_t cmd = 0b01000000;  // 0x40 = write to DAC register, normal mode
  // DAC value is 10 bits: MSB = upper 8 bits, LSB = lower 2 bits in upper nibble
  uint8_t msb = dacVal >> 2;               // Upper 8 bits
  uint8_t lsb = (dacVal & 0x03) << 6;      // Lower 2 bits in upper nibble of byte

  /* And finally transmit the data */
  Wire.beginTransmission(DAC_MCP4716_I2C_ADDRESS);
  Wire.write(cmd);
  Wire.write(msb);
  Wire.write(lsb);
  Wire.endTransmission();
}

#endif DAC_H
