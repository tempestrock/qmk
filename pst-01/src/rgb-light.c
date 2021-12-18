/*
 * rgb-light.c
 * Specialties for the RGB underglow effects.
 */

#include QMK_KEYBOARD_H
#include "rgb-light.h"

#ifdef RGBLIGHT_ENABLE

/**
 * Sets the RGB light effect right after the keyboard has been initialized.
 */
void keyboard_post_init_user_rgb_light(void) {
  rgblight_enable_noeeprom(); // Enables RGB without saving settings

  rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
  rgblight_step();
  rgblight_step();
  rgblight_step();
}

#endif
