/*
 * tapdance.c
 * The implementation of the tap dance
 */

#include QMK_KEYBOARD_H
#include "tapdance.h"
#include "layers.h"
#include <keymap_german.h>

/**
 * Possible states a tap dance can be in
 */
typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD,
  TD_DOUBLE_TAP,
  TD_DOUBLE_HOLD,
  TD_DOUBLE_SINGLE_TAP, // Send two single taps
  TD_TRIPLE_TAP,
  TD_TRIPLE_HOLD
} td_state_t;

/**
 * Tap type
 */
typedef struct {
  bool is_press_action;
  td_state_t state;
} td_tap_t;

/**
 * Functions that are to be defined later and just declared here
 */
void td_spacedown_finished(qk_tap_dance_state_t *state, void *user_data);
void td_spacedown_reset(qk_tap_dance_state_t *state, void *user_data);

/**
 * The array of all tap dance actions.
 */
qk_tap_dance_action_t tap_dance_actions[] = {
    [A_TO_AE] = ACTION_TAP_DANCE_DOUBLE(KC_A, DE_ADIA),
    [E_TO_EUR] = ACTION_TAP_DANCE_DOUBLE(KC_E, DE_EURO),
    [O_TO_OE] = ACTION_TAP_DANCE_DOUBLE(KC_O, DE_ODIA),
    [U_TO_UE] = ACTION_TAP_DANCE_DOUBLE(KC_U, DE_UDIA),
    [V_TO_SZ] = ACTION_TAP_DANCE_DOUBLE(KC_V, DE_SS),
    [SPACE_DOWN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_spacedown_finished, td_spacedown_reset)};

// TODO: Unclear: What happens with capital umlauts like Ä, Ö, Ü, and capital ß?

/**
 * Provide the current tap dance state depending on what has happened so far.
 * Interrupted state: If the state of a tap dance is "interrupted", that means that another key has been hit under the
 * tapping term. This is typically an indication that you are trying to "tap" the key.
 * Pressed state: Whether or not the key is still being pressed. If this value is true, that means the tapping term has
 * ended, but the key is still being pressed down. This generally means the key is being "held".
 * @param state the current tap dance state
 * @returns an integer that corresponds to what kind of tap dance should be executed.
 */
td_state_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) {
      return TD_SINGLE_TAP;
    } else {
      // Key has not been interrupted, but the key is still held. Means we want to send a 'HOLD'.
      return TD_SINGLE_HOLD;
    }
  }

  if (state->count == 2) {
    if (state->interrupted) {
      // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
      // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
      // keystrokes of the key, and not the 'double tap' action/macro.
      return TD_DOUBLE_SINGLE_TAP;
    } else {
      if (state->pressed) {
        return TD_DOUBLE_HOLD;
      } else {
        return TD_DOUBLE_TAP;
      }
    }
  }

  // Assumes no one is trying to type the same letter three times (at least not quickly).
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)
      return TD_TRIPLE_TAP;
    else
      return TD_TRIPLE_HOLD;
  }

  // If we are still here, then there were too many key strokes of the same key.
  return TD_UNKNOWN;
}

/* -------------------------------------------------------------------------- */
/*                        TAP DANCE FOR SPACE-DOWN                            */
/* -------------------------------------------------------------------------- */

/**
 * A global instance of type 'td_tap_t' for the 'space-down' tap dance.
 */
static td_tap_t space_tap_state = {.is_press_action = true, .state = TD_NONE};

/**
 * Callback function that is called when the space-down tap dance is over.
 * Handles the respective keystroke depending on the current tap state.
 * @param state the current state of the tap dance
 * @param user_data unused
 **/
void td_spacedown_finished(qk_tap_dance_state_t *state, void *user_data) {
  space_tap_state.state = cur_dance(state);
  switch (space_tap_state.state) {
  case TD_SINGLE_TAP:
    register_code(KC_SPACE);
    break;
  case TD_SINGLE_HOLD:
    layer_on(_DOWN);
    break;
  case TD_DOUBLE_TAP:
    tap_code(KC_SPACE);
    register_code(KC_SPACE);
    break;
  case TD_DOUBLE_HOLD:
    register_code(KC_LALT);
    layer_on(_DOWN);
    break;
  case TD_DOUBLE_SINGLE_TAP:
    tap_code(KC_SPACE);
    register_code(KC_SPACE);
    break;

  default:
    break;
  }
}

/**
 * Callback function that is called to reset everything after the space-down tap dance.
 * @param state the current state of the tap dance
 * @param user_data unused
 **/
void td_spacedown_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (space_tap_state.state) {
  case TD_SINGLE_TAP:
    unregister_code(KC_SPACE);
    break;
  case TD_SINGLE_HOLD:
    layer_off(_DOWN);
    break;
  case TD_DOUBLE_TAP:
    unregister_code(KC_SPACE);
    break;
  case TD_DOUBLE_HOLD:
    layer_off(_DOWN);
    unregister_code(KC_LALT);
  case TD_DOUBLE_SINGLE_TAP:
    unregister_code(KC_SPACE);
  default:
    break;
  }
  space_tap_state.state = TD_NONE;
}
