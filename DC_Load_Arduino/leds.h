/**
 * @file leds.h
 * 
 * @brief This file contains the LED handling functions.
 * 
 * Each LED has it's defined pin in defines.h
 * LEDs have states: on, off, blink_slow, blink_fast
 * 
 */
#ifndef LEDS_H
#define LEDS_H

#include "defines.h"

/* Define how many ms to wait between toggling LEDs */
#define LED_BLINK_SLOW_TIME 1000
#define LED_BLINK_FAST_TIME 250

/* Define enum of all possible LED states */
typedef enum led_state_t {
  led_off = 0,
  led_on = 1,
  led_blink_slow,
  led_blink_fast
} led_state_t;

/* Define arrays to store runtime data */
led_state_t led_states[LED_NUM];
uint32_t led_blink_time[LED_NUM] = { 0 };

/* Prototypes for all used functions */
void leds_setup();
void leds_handle();
void leds_set_led(uint8_t led, led_state_t state);

/**
 * @brief Setup the LED pins and initial states
 */
void leds_setup()
{
  for(uint16_t i = 0; i < LED_NUM; i++){
    led_states[i] = led_off;
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
}

/**
 * @brief Handle LED states and blinking
 */
void leds_handle()
{
  for(uint16_t i = 0; i < LED_NUM; i++){
    switch(led_states[i]){
      case led_off:
        digitalWrite(LED_PINS[i], LOW);
        break;
      case led_on:
        digitalWrite(LED_PINS[i], HIGH);
        break;
      case led_blink_slow:
        if(millis() - led_blink_time[i] > 1000){
          digitalWrite(LED_PINS[i], !digitalRead(LED_PINS[i]));
          led_blink_time[i] = millis();
        }
        break;
      case led_blink_fast:
        if(millis() - led_blink_time[i] > 250){
          digitalWrite(LED_PINS[i], !digitalRead(LED_PINS[i]));
          led_blink_time[i] = millis();
        }
        break;
      default:
        break;
    }
  }
}

/**
 * @brief Set the state of a specific LED
 */
void leds_set_led(uint8_t led, led_state_t state)
{
  if(led < LED_NUM){
    led_states[led] = state;
  }
}


#endif LEDS_H
