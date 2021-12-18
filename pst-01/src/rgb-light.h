/*
 * rgb-light.h
 * Declarations for the RGB underglow effects.
 */

#ifndef RGB_LIGHT_H
#define RGB_LIGHT_H

// Definitions for the lighting
#ifdef RGBLIGHT_ENABLE

extern void keyboard_post_init_user_rgb_light(void);  

#define RGBLIGHT_EFFECT_RAINBOW_SWIRL

// The number of LEDs in total:
#undef RGBLED_NUM
#define RGBLED_NUM 20

// define RGBLIGHT_ANIMATIONS
// define RGBLIGHT_HUE_STEP  8
// define RGBLIGHT_SAT_STEP  8
// define RGBLIGHT_VAL_STEP  8
// define RGBLIGHT_LIMIT_VAL 150

// Synchronize split keyboards
#define RGBLIGHT_SPLIT

#endif

#endif /* RGB_LIGHT_H */
