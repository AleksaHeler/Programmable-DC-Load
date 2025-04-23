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

/* NTC lookup */
#define NTC_LOOKUP_TABLE_SIZE 148
float ntc_lookup_table[NTC_LOOKUP_TABLE_SIZE][2] = {
  /* ADC    °C */
  {  75,   -23 },
  {  79,   -22 },
  {  84,   -21 },
  {  89,   -20 },
  {  94,   -19 },
  {  99,   -18 },
  { 105,   -17 },
  { 110,   -16 },
  { 116,   -15 },
  { 123,   -14 },
  { 129,   -13 },
  { 136,   -12 },
  { 143,   -11 },
  { 150,   -10 },
  { 157,   -9  },
  { 165,   -8  },
  { 173,   -7  },
  { 181,   -6  },
  { 189,   -5  },
  { 198,   -4  },
  { 207,   -3  },
  { 216,   -2  },
  { 225,   -1  },
  { 235,    0  },
  { 244,    1  },
  { 254,    2  },
  { 264,    3  },
  { 274,    4  },
  { 285,    5  },
  { 295,    6  },
  { 306,    7  },
  { 317,    8  },
  { 328,    9  },
  { 339,   10  },
  { 350,   11  },
  { 362,   12  },
  { 373,   13  },
  { 384,   14  },
  { 396,   15  },
  { 408,   16  },
  { 419,   17  },
  { 431,   18  },
  { 442,   19  },
  { 454,   20  },
  { 466,   21  },
  { 477,   22  },
  { 489,   23  },
  { 500,   24  },
  { 512,   25  },
  { 523,   26  },
  { 534,   27  },
  { 545,   28  },
  { 556,   29  },
  { 567,   30  },
  { 578,   31  },
  { 589,   32  },
  { 599,   33  },
  { 610,   34  },
  { 620,   35  },
  { 630,   36  },
  { 640,   37  },
  { 650,   38  },
  { 659,   39  },
  { 669,   40  },
  { 678,   41  },
  { 687,   42  },
  { 696,   43  },
  { 704,   44  },
  { 713,   45  },
  { 729,   46  },
  { 737,   47  },
  { 737,   48  },
  { 745,   49  },
  { 753,   50  },
  { 760,   51  },
  { 768,   52  },
  { 775,   53  },
  { 782,   54  },
  { 788,   55  },
  { 795,   56  },
  { 801,   57  },
  { 807,   58  },
  { 813,   59  },
  { 819,   60  },
  { 825,   61  },
  { 831,   62  },
  { 836,   63  },
  { 841,   64  },
  { 846,   65  },
  { 851,   66  },
  { 856,   67  },
  { 861,   68  },
  { 865,   69  },
  { 870,   70  },
  { 874,   71  },
  { 878,   72  },
  { 882,   73  },
  { 886,   74  },
  { 890,   75  },
  { 894,   76  },
  { 898,   77  },
  { 901,   78  },
  { 904,   79  },
  { 908,   80  },
  { 911,   81  },
  { 914,   82  },
  { 917,   83  },
  { 920,   84  },
  { 923,   85  },
  { 925,   86  },
  { 928,   87  },
  { 931,   88  },
  { 933,   89  },
  { 936,   90  },
  { 938,   91  },
  { 940,   92  },
  { 943,   93  },
  { 945,   94  },
  { 947,   95  },
  { 949,   96  },
  { 951,   97  },
  { 953,   98  },
  { 954,   99  },
  { 956,  100  },
  { 958,  101  },
  { 960,  102  },
  { 961,  103  },
  { 963,  104  },
  { 965,  105  },
  { 966,  106  },
  { 967,  107  },
  { 969,  108  },
  { 970,  109  },
  { 972,  110  },
  { 973,  111  },
  { 974,  112  },
  { 975,  113  },
  { 977,  114  },
  { 978,  115  },
  { 979,  116  },
  { 980,  117  },
  { 981,  118  },
  { 982,  119  },
  { 983,  120  },
  { 984,  121  },
  { 985,  122  },
  { 986,  123  },
  { 987,  124  }
};

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
    if(adc_value < ntc_lookup_table[0][0]){
      ntc_temperatures[i] = ntc_lookup_table[0][1];
    } 
    /* Value above the highest raw ADC? */
    else if(adc_value > ntc_lookup_table[(NTC_LOOKUP_TABLE_SIZE-1)][0]){
      ntc_temperatures[i] = ntc_lookup_table[(NTC_LOOKUP_TABLE_SIZE-1)][1];
    } 
    else {
      /* Interpolate the temperature */
      for(uint8_t j = 0; j < (NTC_LOOKUP_TABLE_SIZE-1); j++){
        if(adc_value >= ntc_lookup_table[j][0] && adc_value <= ntc_lookup_table[j+1][0]){
          float slope = (ntc_lookup_table[j+1][1] - ntc_lookup_table[j][1]) / (ntc_lookup_table[j+1][0] - ntc_lookup_table[j][0]);
          ntc_temperatures[i] = slope * (adc_value - ntc_lookup_table[j][0]) + ntc_lookup_table[j][1];
          break;
        }
      }
    }
  }
}



#endif NTC_H
