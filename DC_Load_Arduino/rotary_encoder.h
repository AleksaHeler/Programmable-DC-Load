/*
* This module will be conserned with handling rotary encoder input.
* Store internal (float) value which goes from 0% to 100%.
* Store internal (boolean) status of the integrated button.
*/
#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include "defines.h"
#include <RotaryEncoder.h>

/* A pointer to the dynamic created rotary encoder instance */
RotaryEncoder *encoder = nullptr;

/* Variables */
float encoder_position = 0; /* Variable other modules can use to get the position (0-100%) */

/* Prototypes for all used functions */
void rotary_encoder_setup();
void rotary_encoder_handle();
void checkPosition();

/* Called once during boot */
void rotary_encoder_setup()
{
  // setup the rotary encoder functionality
  encoder = new RotaryEncoder(ENCOD_PIN_IN1, ENCOD_PIN_IN2, RotaryEncoder::LatchMode::TWO03);

  // register interrupt routine
  attachInterrupt(digitalPinToInterrupt(ENCOD_PIN_IN1), checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCOD_PIN_IN2), checkPosition, CHANGE);
}

/* Called cyclically while device is running */
void rotary_encoder_handle()
{
  static int encoder_curr_position = 0;
  static int encoder_prev_position = 0;

  /* Handle encoder - just call tick() to check the state */
  encoder->tick();
  encoder_curr_position = encoder->getPosition();
  
  /* If encoder value has increased */
  if(encoder_curr_position > encoder_prev_position){
    if(ENCODER_DIRECTION > 0){
      encoder_position += ENCODER_STEP;
    }
    else{
      encoder_position -= ENCODER_STEP;
    }
  }
  
  /* If encoder value has decreased */
  if(encoder_curr_position < encoder_prev_position){
    if(ENCODER_DIRECTION > 0){
      encoder_position -= ENCODER_STEP;
    }
    else{
      encoder_position += ENCODER_STEP;
    }
  }

  /* Clamp the output variable to 0-100% */
  if(encoder_position > 100){
    encoder_position = 100;
  }
  else if(encoder_position < 0){
    encoder_position = 0;
  }

  /* Remember previous position */
  encoder_prev_position = encoder_curr_position;
}

/* This interrupt routine will be called on any change of one of the input signals */
void checkPosition()
{
  encoder->tick(); // just call tick() to check the state.
}

#endif ROTARY_ENCODER_H
