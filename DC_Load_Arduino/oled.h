/**
 * @file oled.h
 * 
 * @brief This file contains OLED display handling functions
 * 
 * Connected via I2C
 * 
 */
#ifndef OLED_H
#define OLED_H

#include "defines.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* Prototypes for all used functions */
void oled_setup();
void oled_handle();

/**
 * @brief Setup
 */
void oled_setup()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    /* Maybe even set an error flag */
    return;
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Hello wrld");
  display.display();
}

/**
 * @brief Handle
 */
void oled_handle()
{
  
}



#endif OLED_H
