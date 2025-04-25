/**
 * @file fan.h
 * 
 * @brief This file contains fan handling functions
 * 
 * Fan is controlled via PWM signal on power pin, via duty cycle
 * 
 */
#ifndef FAN_H
#define FAN_H

#include "defines.h"

#define FAN_PWM_MIN 180
#define FAN_PWM_MAX 255

/* Global variable to store current fan PWM (read only) */
uint8_t fan_duty_cycle = 0;

/* Prototypes for all used functions */
void fan_setup();
void fan_handle();
void fan_set_pwm(uint8_t duty_cycle);

/**
 * @brief Setup fan pins
 */
void fan_setup()
{
  /* set fan pin to output, and pwm duty cycle to 0 */
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
}

/**
 * @brief Handle fan driver
 */
void fan_handle()
{
  /* Nothing to do here now */
}

/**
 * @brief Set the fan PWM duty cycle
 * @param duty_cycle Duty cycle in percent (0-100%)
 */
void fan_set_pwm(uint8_t duty_cycle)
{
  /* Check if duty cycle is in range */
  if(duty_cycle > 100) duty_cycle = 100; /* Limit to 100% */
  if(duty_cycle < 0) duty_cycle = 0; /* Limit to 0% */

  /* Store the duty cycle value */
  fan_duty_cycle = duty_cycle; 

  /* If fan set to 0% or 100%, set as digital output, else set duty cycle */
  if(duty_cycle == 0){
    digitalWrite(FAN_PIN, LOW);
  } 
  else if(duty_cycle == 100) {
    digitalWrite(FAN_PIN, HIGH);
  }
  else {
    uint8_t pwm_value = map(fan_duty_cycle, 0, 100, FAN_PWM_MIN, FAN_PWM_MAX);
    analogWrite(FAN_PIN, pwm_value);
  }
}


#endif FAN_H
