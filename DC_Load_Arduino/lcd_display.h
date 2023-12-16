/*
* This module will be conserned with handling the 16x2 LCD display.
* Based on defined logic write all data needed to the LCD.
* Logic:
*   - TODO!
*/
#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include "defines.h"
#include <LiquidCrystal.h>

/* Input variables from other modules */
extern float current_set;
extern float current;
extern float voltage;
extern float power;
extern float temperature;

/* Library object used to interface the device */
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/* Prototypes for all used functions */
void lcd_setup();
void lcd_handle();
void lcdPrintWelcomeMessage();

/* Called once during boot */
void lcd_setup()
{
  /* Set up the LCD's number of columns and rows */
  lcd.begin(16, 2);

  lcdPrintWelcomeMessage();
  delay(1500);
}

/* Called cyclically while device is running */
void lcd_handle()
{
  /* Print frist line */
  lcd.setCursor(0, 0);
  lcd.print("SET=");
  lcd.print(current_set);
  lcd.print(" ");
  lcd.print("C=");
  lcd.print(current);
  lcd.print("     ");

  /* Print second line */
  lcd.setCursor(0, 1);
  lcd.print("  V=");
  lcd.print(voltage);
  
  //lcd.print(" P=");
  //lcd.print(power);
  //lcd.print("        ");
  
  lcd.print(" T=");
  lcd.print(temperature);
  lcd.print("        ");
}

/* A little helper to just write some text */
void lcdPrintWelcomeMessage()
{
  lcd.setCursor(0, 0);
  lcd.print("CC/CP LOAD");
  lcd.setCursor(0, 1);
  lcd.print("-Aleksa Heler-");
}

#endif /* LCD_DISPLAY_H */
