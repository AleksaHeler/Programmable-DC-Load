/**
 * @file ntc.h
 * 
 * @brief This file contains the Negative Thermal Coefficient (NTC) handling functions.
 * 
 * Each NTC has it's defined pin in defines.h
 * NTC will use a lookup table and linear interpolation to determine the temperature
 * 
 */
#ifndef NTC_H
#define NTC_H

#include "defines.h"

/* Measured NTC temperatures */
float ntc_temperatures[NTC_NUM] = { 0.0f, 0.0f };

/* NTC lookup stored in program memory (not dynamic) */
#define NTC_LOOKUP_TABLE_SIZE 148
const PROGMEM uint16_t ntc_lookup_table_adc[NTC_LOOKUP_TABLE_SIZE] = {
  75, 79, 84, 89, 94, 99, 105, 110, 116, 123, 129, 136, 143, 150, 157, 165, 173, 181, 189, 198, 207, 216, 225, 
  235, 244, 254, 264, 274, 285, 295, 306, 317, 328, 339, 350, 362, 373, 384, 396, 408, 419, 431, 442, 454, 466, 
  477, 489, 500, 512, 523, 534, 545, 556, 567, 578, 589, 599, 610, 620, 630, 640, 650, 659, 669, 678, 687, 696, 
  704, 713, 729, 737, 737, 745, 753, 760, 768, 775, 782, 788, 795, 801, 807, 813, 819, 825, 831, 836, 841, 846, 
  851, 856, 861, 865, 870, 874, 878, 882, 886, 890, 894, 898, 901, 904, 908, 911, 914, 917, 920, 923, 925, 928, 
  931, 933, 936, 938, 940, 943, 945, 947, 949, 951, 953, 954, 956, 958, 960, 961, 963, 965, 966, 967, 969, 970, 
  972, 973, 974, 975, 977, 978, 979, 980, 981, 982, 983, 984, 985, 986, 987
};

const PROGMEM int16_t ntc_lookup_table_temp[NTC_LOOKUP_TABLE_SIZE] = {
  -23, -22, -21, -20, -19, -18, -17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1,  0,  
  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 
  29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 
  57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 
  85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 
  110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124
};

/* Accessing the lookup table from program memory with memory offset calculation */
#define GET_LOOKUP_TABLE_ADC(i)   uint16_t(pgm_read_word_near(ntc_lookup_table_adc + (i)))
#define GET_LOOKUP_TABLE_TEMP(i)  int16_t(pgm_read_word_near(ntc_lookup_table_temp + (i)))

/* Prototypes for all used functions */
void ntc_setup();
void ntc_handle();

/**
 * @brief Setup the NTC
 */
void ntc_setup()
{
  /* No need to setup NTC pins, they are ADC input by default */
}

/**
 * @brief Read the NTC input, compare to lookup table and note down the temperature
 */
void ntc_handle()
{
  for(uint8_t i = 0; i < NTC_NUM; i++){
    /* Read the NTC pin */
    uint16_t adc_value = analogRead(NTC_PINS[i]);
    
    /* Check if we are in the range of the lookup table */
    /* Value below the lowest raw ADC? */
    if(adc_value < GET_LOOKUP_TABLE_ADC(0)){
      ntc_temperatures[i] = float(GET_LOOKUP_TABLE_TEMP(0));
    } 
    /* Value above the highest raw ADC? */
    else if(adc_value > GET_LOOKUP_TABLE_ADC(NTC_LOOKUP_TABLE_SIZE - 1)){
      ntc_temperatures[i] = float(GET_LOOKUP_TABLE_TEMP(NTC_LOOKUP_TABLE_SIZE - 1));
    } 
    else {
      /* Interpolate the temperature */
      for(uint8_t j = 0; j < (NTC_LOOKUP_TABLE_SIZE-1); j++){
        if(adc_value >= GET_LOOKUP_TABLE_ADC(j) && adc_value <= GET_LOOKUP_TABLE_ADC(j + 1)){
          float slope = float( GET_LOOKUP_TABLE_TEMP(j + 1) - GET_LOOKUP_TABLE_TEMP(j) ) / ( float( GET_LOOKUP_TABLE_ADC(j + 1) - GET_LOOKUP_TABLE_ADC(j) ) );
          ntc_temperatures[i] = slope * (adc_value - GET_LOOKUP_TABLE_ADC(j)) + float(GET_LOOKUP_TABLE_TEMP(j));
          break;
        }
      }
    }
  }
}



#endif NTC_H
