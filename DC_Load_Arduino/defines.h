/*
* Here we mostly define pins and global configurations, for module-specific
* configurations see the module .h files
*/
#ifndef DEFINES_H
#define DEFINES_H

/****************************************************************************************/
/* Logic defines                                                                        */
/****************************************************************************************/

/* Define maximum values */
#define LOAD_MAX_VOLTAGE (28.5f)   /* V */
#define LOAD_MAX_CURRENT (2.0f)    /* A */
#define LOAD_MAX_POWER 20          /* W */

/****************************************************************************************/
/* Hardware/pin defines                                                                 */
/****************************************************************************************/

/* I2C: ADC/DAC, OLED display  */
#define DAC_MCP4716_I2C_ADDRESS 0x60  /* Set current via precise DAC */
#define ADC_INA219_I2C_ADDRESS 0x40   /* Measure current via shunt resistor (A0 and A1 pin of IC are connected to GND)*/
#define OLED_I2C_ADDRESS 0x3C         /* Typical 64x128 OLED display */
#define OLED_RESET -1                 /* Reset pin # (or -1 if sharing Arduino reset pin) */

/* Encoder pins */
#define ENCODER_PIN_A 7
#define ENCODER_PIN_B 6
#define ENCODER_SWITCH 5

/* Analog inputs */
#define INPUT_VOLTAGE_PIN A0
#define NTC_NUM 2                    /* How many status NTCs we have */
const int NTC_PINS[NTC_NUM] = {      /* NTC pins */
  A2,  /* NTC_PCB_TEMP_PIN */
  A1   /* NTC_EXT_TEMP_PIN */
};

/* Digital outputs */
#define FAN_PIN 3
#define LED_NUM 1                      /* How many status LEDs we have */
const int LED_PINS[LED_NUM] = { 2 };   /* Status LED pins */

/* Define encoder positive direction: right = 1, left = -1 */
#define ENCODER_DIRECTION (-1)
/* Define encoder step value (0-100%) */
#define ENCODER_STEP (1)

/* Input voltage divider values */
#define INPUT_VOLTAGE_R1 47 /* Resistor from Vin to midpoint (kOhm) */
#define INPUT_VOLTAGE_R2 10 /* Resistor from midpoint to ground (kOhm) */
#define INPUT_VOLTAGE_FACTOR 1.015 /* Voltage is multiplied by this number to offset any resitor deviations */

/* Output DAC scaling factor, used to convert it's output voltage to amps */
#define DAC_OUTPUT_FACTOR 1.13f /* DAC output voltage is multiplied by this number to offset any resitor deviations */
#define DAC_VREF 5.0f /* DAC reference voltage, 5V bus */
#define INPUT_CURRENT_FACTOR 1.034f /* Current is multiplied by this number to offset any resitor deviations */

/****************************************************************************************/
/* Other defines                                                                        */
/****************************************************************************************/


#endif /* DEFINES_H */