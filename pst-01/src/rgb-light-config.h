/*
 * rgb-light-config.h
 * Declarations of the constants defined for the RGB underglow effects.
 */

#ifndef RGB_LIGHT_CONFIG_H
#define RGB_LIGHT_CONFIG_H

#ifdef RGBLIGHT_ENABLE

// The only mode we have in order to save memory space:
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL

// The total number of LEDs in both keyboards:
#undef RGBLED_NUM
#define RGBLED_NUM 20

// Define the order of the LEDs such that they - synchronously on both keyboards - go in a nice circle:
#define RGBLIGHT_LED_MAP { 0, 1, 2, 9, 8, 7, 4, 3, 5, 6, 0, 1, 2, 9, 8, 7, 4, 3, 5, 6 }

// Synchronize split keyboards
#define RGBLIGHT_SPLIT

#endif /* RGBLIGHT_ENABLE */

#endif /* RGB_LIGHT_CONFIG_H */
