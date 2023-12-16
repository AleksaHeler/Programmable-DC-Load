/*
* Here we mostly define pins and global configurations, for module-specific
* configurations see the module .h files
*/
#ifndef DEFINES_H
#define DEFINES_H

/* Define maximum values */
#define LOAD_MAX_CURRENT (3.0f) /* A */
#define LOAD_MAX_POWER 40 /* W */

/* ADC/DAC */
#define PCF8591_I2C_ADDRESS 0x48

/* Encoder */
#define ENCOD_PIN_IN1 9
#define ENCOD_PIN_IN2 10

/* Analog inputs */
#define CURR_READ_PIN A0
#define VOLT_READ_PIN A1
#define TEMP_READ_PIN A2

/* Digital outputs */
#define FAN_PIN 13

/* Define encoder positive direction: right = 1, left = -1 */
#define ENCODER_DIRECTION (-1)
/* Define encoder step value (0-100%) */
#define ENCODER_STEP (1)


/* LCD pins (not using the I2C) */
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

#endif /* DEFINES_H */