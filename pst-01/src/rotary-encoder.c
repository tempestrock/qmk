/*
 * rotary-encoder.c
 * The implementation of the encoding for the rotary knob
 */

#include QMK_KEYBOARD_H
#include "layers.h"

/**
 * Callback function that is called whenever one of the two rotary knobs was turned.
 * The two encoders control
 *   page up and down,
 *   horizontal scrolling, (tbd)
 *   volume up and down, and
 *   brightness up and down.
 * @param index tells us which encoder was turned. May be 0 (left knob) or 1 (right knob).
 * @param clockwise true if the encoder was turned clockwise, false otherwise.
 * @returns true if the keyboard level code shall be allowed to run afterwards, too. Returns false if the keyboard level
 * code shall be overriden.
 */
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    // Left encoder
    if (IS_LAYER_OFF(_DOWN)) {
      // Normal turn --> volume
      if (clockwise) {
        tap_code(KC_AUDIO_VOL_UP);
      } else {
        tap_code(KC_AUDIO_VOL_DOWN);
      }
    } else {
      // Down is pressed --> brightness
      if (clockwise) {
        tap_code(KC_BRIGHTNESS_UP);
      } else {
        tap_code(KC_BRIGHTNESS_DOWN);
      }
    }
  } else {
    // Right encoder
    if (IS_LAYER_OFF(_DOWN)) {
      // Normal turn --> page up/down
      if (clockwise) {
        tap_code(KC_PGDN);
      } else {
        tap_code(KC_PGUP);
      }
    } else {
      // Down is pressed --> horizontal scrolling
      // TODO: implement this
      if (clockwise) {
        tap_code(KC_PGDN);
      } else {
        tap_code(KC_PGUP);
      }
    }
  }
  return false;
}
