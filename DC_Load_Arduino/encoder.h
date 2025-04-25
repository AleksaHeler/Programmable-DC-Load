/**
 * @file encoder.h
 * 
 * @brief This file contains encoder handling functions
 * 
 * Encoder has two pins, A and B for rotation
 * And a push button/switch for press
 * 
 */
#ifndef ENCODER_H
#define ENCODER_H

#include "defines.h"

/* Variables to track encoder state */
int encoderPosition = 0;
bool buttonPressed = false;
int lastEncoded = 0;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

/* Prototypes for all used functions */
void encoder_setup();
void encoder_handle();

/**
 * @brief Setup
 */
void encoder_setup()
{
  pinMode(ENCODER_PIN_A, INPUT);
  pinMode(ENCODER_PIN_B, INPUT);
  pinMode(ENCODER_SWITCH, INPUT_PULLUP);

  // Initialize encoder state
  int MSB = digitalRead(ENCODER_PIN_A); // Most significant bit
  int LSB = digitalRead(ENCODER_PIN_B); // Least significant bit
  lastEncoded = (MSB << 1) | LSB;
}

/**
 * @brief Handle
 */
void encoder_handle()
{  
  // Handle encoder rotation
  int MSB = digitalRead(ENCODER_PIN_A);
  int LSB = digitalRead(ENCODER_PIN_B);
  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderPosition++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderPosition--;

  lastEncoded = encoded;

  // Print position if changed
  static int lastReportedPosition = 0;
  if (encoderPosition != lastReportedPosition) {
    lastReportedPosition = encoderPosition;
  }

  // Handle button press with debounce
  int reading = digitalRead(ENCODER_SWITCH);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && !buttonPressed) {
      buttonPressed = true;
      Serial.println("Button Pressed");
    } else if (reading == HIGH) {
      buttonPressed = false;
    }
  }

  lastButtonState = reading;
}

#endif ENCODER_H
