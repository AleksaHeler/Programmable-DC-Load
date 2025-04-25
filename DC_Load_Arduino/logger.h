/**
 * @file logger.h
 * 
 * @brief This file contains functions for logging data via UART/Serial
 * 
 */
#ifndef LOGGER_H
#define LOGGER_H

#include "defines.h"

/* Driver include files, for gathering data to log */
#include "sensing.h"
#include "fan.h"
#include "ntc.h"
#include "encoder.h"
#include "dac.h"

#define LOGGER_DELAY 2000 /* Delay between log writes (ms) */

/* Keep track of time passed since last log write */
unsigned long last_log_time = 0;

/* Prototypes for all used functions */
void logger_setup();
void logger_handle();

/**
 * @brief Setup
 */
void logger_setup()
{
  Serial.println("Logger is working!");
}

/**
 * @brief Handle
 */
void logger_handle()
{
  /* Only write to serial if certain time has passed */
  unsigned long current_time = millis();
  if(current_time - last_log_time > LOGGER_DELAY)
  {
    last_log_time = current_time; /* Update the time */
    
    Serial.print("Input voltage:        "); Serial.print(input_voltage);          Serial.println("V");
    Serial.print("Input shunt voltage:  "); Serial.print(input_shunt_voltage_mv); Serial.println("mV");
    Serial.print("Input current:        "); Serial.print(input_current_ma);       Serial.println("mA");
    Serial.print("Input power:          "); Serial.print(input_power);            Serial.println("W");
    Serial.print("PCB temperature:      "); Serial.print(ntc_temperatures[0]);    Serial.println("*C");
    Serial.print("External temperature: "); Serial.print(ntc_temperatures[1]);    Serial.println("*C");
    Serial.print("DAC set current:      "); Serial.print(dac_set_current);        Serial.println("A");
    Serial.print("Fan duty cycle:       "); Serial.print(fan_duty_cycle);         Serial.println("%");
    Serial.print("Encoder position:     "); Serial.print(encoderPosition);        Serial.println("");
    Serial.println("");
  }
}

#endif LOGGER_H
