/*
 * rotary-encoder.c
 * The implementation of the encoding for the rotary knob
 */

#include QMK_KEYBOARD_H
#include "rotary-encoder.h"
#include "layers.h"

/**
 * Global flag that tracks if <Ctrl>-<Tab> is active at the moment
 */
bool is_ctrl_tab_active = false;

/**
 * Global timer for <Ctrl>-<Tab>
 */
uint16_t ctrl_tab_timer = 0;

/**
 * Callback function that is called whenever one of the two rotary knobs was turned.
 * The two encoders control
 *   page up and down,
 *   tab scrolling (<Ctrl>-<Tab>),
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
      // Down key is pressed simultaneously --> brightness
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
      // Down key is pressed simultaneously --> <Ctrl>-<Tab>
      if (!is_ctrl_tab_active) {
        is_ctrl_tab_active = true;
        register_code(KC_LCTL);
      }
      ctrl_tab_timer = timer_read();
      if (clockwise) {
        tap_code16(KC_TAB);
      } else {
        tap_code16(LSFT(KC_TAB));
      }
    }
  }
  return false;
}

/**
 * Callback function that is called as part of the global matrix_scan_user function.
 * We check whether or not we have to switch off the possibly active <Ctrl>-<Tab> that is simulated by the right rotary
 * encoder.
 */
void matrix_scan_user_rotary_encoder(void) {
  if (is_ctrl_tab_active) {
    if (timer_elapsed(ctrl_tab_timer) > 1250) {
      // Time's up without any more action on the encoder => Release <Ctrl>.
      unregister_code(KC_LCTL);
      is_ctrl_tab_active = false;
    }
  }
}
