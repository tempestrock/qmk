/*
 * leader-key.c
 * The implementation of the handling of the leader key
 */

#include QMK_KEYBOARD_H
#include "leader-key.h"
#include "layers.h"

LEADER_EXTERNS(); // Declaration of external functions

/**
 * Callback function that is called as part of the global matrix_scan_user function.
 * We check whether or not we are in the "leader key" mode and if it has just stopped so that the respective result can
 * be executed.
 */
void matrix_scan_user_leader_key(void) {

  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_L) {
      // Toggle the "Lights" layer on and off
      layer_invert(_LIGHTS);
    }

    SEQ_TWO_KEYS(KC_M, KC_T) {
      // Message 1
      SEND_STRING("Schöne Grüße\n"
                  "Peter");
    }

    SEQ_TWO_KEYS(KC_M, KC_S) {
      // Message 2
      SEND_STRING("Schöne Grüße\n"
                  "Peter Störmer");
    }

    SEQ_TWO_KEYS(KC_M, KC_R) {
      // Message 3
      SEND_STRING("Freundliche Grüße\n"
                  "Peter Störmer");
    }

    SEQ_TWO_KEYS(KC_M, KC_A) {
      // Message 0
      SEND_STRING("\n\n"
                  "--\n\n"
                  "störmer-consulting\n"
                  "Dr. Peter Störmer\n\n"
                  "+49 173 24 18 515\n"
                  "mail@stoermer-consulting.de\n"
                  "www.stoermer-consulting.de\n\n");
    }
  }
}
