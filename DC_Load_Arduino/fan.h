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
  /* If fan set to 0% or 100%, set as digital output, else set duty cycle */
  if(duty_cycle == 0){
    digitalWrite(FAN_PIN, LOW);
  } 
  else if(duty_cycle == 100) {
    digitalWrite(FAN_PIN, HIGH);
  } 
  else {
    /* Scale PWM so it actually goes from 90 to 100%*/
    uint8_t pwm_value = (90.0 + duty_cycle/10.0);
    analogWrite(FAN_PIN, map(pwm_value, 0, 100, 0, 255));
  }
}


#endif FAN_H
