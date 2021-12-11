/*
 * leader-key.c
 * The implementation of the handling of the leader key
 */

#include QMK_KEYBOARD_H
#include "leader-key.h"
#include "layers.h"
#include "sendstring_german.h"

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

    // Ä
    SEQ_ONE_KEY(KC_A) {
      tap_code(DE_ADIA);
    }

    // €
//    SEQ_ONE_KEY(KC_E) {
  //    tap_code(DE_EURO);
    // }

    // Ö
    SEQ_ONE_KEY(KC_O) {
      tap_code(DE_ODIA);
    }

    // Ü
    SEQ_ONE_KEY(KC_U) {
      tap_code(DE_UDIA);
    }

    // ß
    SEQ_ONE_KEY(KC_S) {
      tap_code(DE_SS);
    }

    // Minimize Window in KDE
    SEQ_ONE_KEY(KC_DOT) {
      register_code(KC_LALT);
      tap_code(KC_F3);
      unregister_code(KC_LALT);
      tap_code(KC_N);
    }


    // Toggle the "Lights" layer on and off
    SEQ_ONE_KEY(KC_L) {
      layer_invert(_LIGHTS);
    }

    // Message 1
    SEQ_TWO_KEYS(KC_M, KC_T) {
      SEND_STRING("Sch");
      tap_code(DE_ODIA);
      SEND_STRING("ne Gr");
      tap_code(DE_UDIA);
      tap_code(DE_SS);
      SEND_STRING("e\nPeter\n\n");
    }

    SEQ_TWO_KEYS(KC_M, KC_S) {
      // Message 2
      SEND_STRING("Sch");
      tap_code(DE_ODIA);
      SEND_STRING("ne Gr");
      tap_code(DE_UDIA);
      tap_code(DE_SS);
      SEND_STRING("e\nPeter St");
      tap_code(DE_ODIA);
      SEND_STRING("rmer\n\n");
    }

    SEQ_TWO_KEYS(KC_M, KC_R) {
      // Message 3
      SEND_STRING("Freundliche Gr");
      tap_code(DE_UDIA);
      tap_code(DE_SS);
      SEND_STRING("e\nPeter St");
      tap_code(DE_ODIA);
      SEND_STRING("rmer\n\n");
    }

    SEQ_TWO_KEYS(KC_M, KC_W) {
      // Message 0
      SEND_STRING("\n\n"
                  "--\n\n"
                  "st");
      tap_code(DE_ODIA);
      SEND_STRING("rmer-consulting\n"
                  "Dr. Peter St");
      tap_code(DE_ODIA);
      SEND_STRING("rmer\n\n"
                  "+49 173 24 18 515\n"
                  "mail@stoermer-consulting.de\n"
                  "www.stoermer-consulting.de\n\n");
    }
  }
}
