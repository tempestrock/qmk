/* Copyright 2021 Peter Störmer <mail@peter.stoermer.de> based on the work of Thomas Baart <thomas@splitkb.com> 2019.
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If you have not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "layers.h"
#include "leader-key.h"
#include "rgb-light.h"
#include "rotary-encoder.h"
#include "shift-handling.h"
#include "typing.h"
#include <keymap_german.h>

#ifdef CONSOLE_ENABLE
#include "print.h" // Debug output
#endif

const char layer_name[NUM_LAYERS][MAX_STRING_SIZE] = {"Standard", "Down", "Function"};

/*
 * My own custom key codes. 'S_' stands for symbol.
 */
enum custom_keycodes {
  S_ATPIPE = SAFE_RANGE, // @ --> |
  S_ANGLEB,              // < --> >
  S_ACUNON,              // ´
  S_CBRCKT,              // { --> }
  S_PARNTH,              // ( --> )
  S_BRCKET,              // [ --> ]
  S_SLSTIL,              // / --> ~
  S_AMPPRC,              // & --> %
  S_CIRGRV,              // ^ --> `
  S_EQUAST,              // = --> *
  S_USCHAS,              // _ --> #
  S_DOLPAR               // $ --> §
};

// --------------- Aliases for readability ---------------

#define ALT_DOWN LM(_DOWN, MOD_LALT) // Alt-Down
#define BSP_SHFT RSFT_T(KC_BSPC)     // Backspace when pressed, right Shift when held down
#define DEL_SHFT RSFT_T(KC_DEL)      // Delete when pressed, right Shift when held down
#define ENT_CTL  CTL_T(KC_ENT)       // Enter when pressed,     Ctrl when held down
#define FKEYS    OSL(_FUNCTION)      // activate the function keys as one shot or while the Fn key is held down
#define LIGHTS   TG(_LIGHTS)         // toggle the lights layer on and off
#define SFT_ENT  LSFT(KC_ENTER)      // <Shift>-<Enter>
#define SPC_DOWN LT(_DOWN, KC_SPACE) // Space when pressed, layer 'down' when held down
#define TAB_CTL  CTL_T(KC_TAB)       // TAB when pressed,       Ctrl when held down

// clang-format off

// --------------- The actual keymap ---------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * Base Layer: Peter's Colemak
   */
  [_COLEMAK_PST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                        ┌────────┬────────┬────────┬────────┬────────┬────────┐
      FKEYS  ,  DE_Q  ,  DE_W  ,  DE_F  ,  DE_P  ,  DE_B  ,                                           DE_J  ,  DE_L  ,  DE_U  ,  DE_Z  ,S_AMPPRC,S_CIRGRV,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                        ├────────┼────────┼────────┼────────┼────────┼────────┤
     S_ATPIPE,  DE_A  ,  DE_R  ,  DE_S  ,  DE_T  ,  DE_D  ,                                           DE_M  ,  DE_N  ,  DE_E  ,  DE_I  ,  DE_H  ,S_EQUAST,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐    ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LWIN ,  DE_Y  ,  DE_X  ,  DE_C  ,  DE_V  ,  DE_G  ,ALT_DOWN,KC_LSFT ,     SFT_ENT ,KC_BSPC ,  DE_K  ,  DE_O  , KC_DOT ,KC_COMM ,S_SLSTIL,KC_LEAD ,
  //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤    ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                KC_MUTE , KC_ESC ,KC_LALT ,SPC_DOWN,TAB_CTL ,     ENT_CTL ,KC_RSFT ,KC_RCTRL,S_USCHAS,RGB_TOG
  //                           └────────┴────────┴────────┴────────┴────────┘    └────────┴────────┴────────┴────────┴────────┘
  ),

  /*
   * Down: All necessary other keys
   */
  [_DOWN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                        ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,  DE_9  ,  DE_8  ,  DE_7  ,S_CBRCKT,                                         DE_DQUO ,KC_HOME , KC_UP  , KC_END ,XXXXXXX ,S_ACUNON,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                        ├────────┼────────┼────────┼────────┼────────┼────────┤
     DE_LABK ,  DE_0  ,  DE_3  ,  DE_2  ,  DE_1  ,S_PARNTH,                                         DE_QUOT ,KC_LEFT ,KC_DOWN ,KC_RGHT ,XXXXXXX ,S_DOLPAR,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐    ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,  DE_6  ,  DE_5  ,  DE_4  ,S_BRCKET,_______ ,_______ ,     _______ ,_______ ,DE_QUES ,DE_MINS, DE_PLUS ,DE_EXLM ,DE_BSLS ,_______ ,
  //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤    ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                _______ ,_______ ,_______ ,_______ ,_______ ,     _______ ,DEL_SHFT,_______ ,_______ ,RGB_VAI
  //                           └────────┴────────┴────────┴────────┴────────┘    └────────┴────────┴────────┴────────┴────────┘
  ),

  /*
   * Function Layer: Function keys
   */
  [_FUNCTION] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                        ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ , KC_F9  , KC_F8  , KC_F7  , KC_F10,                                          _______, _______, DE_UDIA , _______, _______, _______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                        ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ , KC_F3  , KC_F2  , KC_F1  , KC_F11 ,                                         _______ ,DE_ADIA ,DE_EURO ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐    ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ , KC_F6  , KC_F5  , KC_F4  , KC_F12 ,_______ ,_______ ,     _______ ,_______ ,_______ ,DE_ODIA , DE_SS  ,_______ ,_______ ,_______ ,
  //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤    ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                _______ ,_______ ,_______ ,_______ ,_______ ,     _______ ,_______ ,_______ ,_______ ,_______
  //                           └────────┴────────┴────────┴────────┴────────┘    └────────┴────────┴────────┴────────┴────────┘
  )
};

// clang-format on

/* -------------------------------------------------------------------------- */
/*                                 USER INPUT                                 */
/* -------------------------------------------------------------------------- */

/**
 * Callback function that is called whenever a key is pressed or released.
 * @param keycode the code of the key that was pressed or released.
 * @param record contains information about the actual press
 * @return true if QMK shall continue to process the key event, false otherwise. *
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

#ifdef CONSOLE_ENABLE
  // Debug
  // uprintf("key event: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode,
  //         record->event.key.col, record->event.key.row, record->event.pressed, record->event.time,
  //         record->tap.interrupted, record->tap.count);
#endif

  if (record->event.pressed) {
    notifyTyping();
  }

  switch (keycode) {
  case S_ATPIPE: // @ --> |
    NALTGR_SALTGR(PK_AT, PK_PIPE);

  case S_CBRCKT: // { --> }
    NALTGR_SALTGR(PK_LCURLBRKT, PK_RCURLBRKT);

  case S_PARNTH: // ( --> )
    NSHIFT_SSHIFT(PK_LPAREN, PK_RPAREN);

  case S_BRCKET: // [ --> ]
    NALTGR_SALTGR(PK_LBRACKET, PK_RBRACKET);

  case S_SLSTIL: // / --> ~
    NSHIFT_SALTGR(PK_SLASH, PK_TILDA);

  case S_AMPPRC: // & --> %
    NSHIFT_SSHIFT(PK_AMPERSAND, PK_PERCENT);

  case S_CIRGRV: // ^ --> `
    NNOSHIFTDEAD_SSHIFTDEAD(DE_CIRC, PK_GRAVE);

  case S_ACUNON: // ´
    NNOSHIFTDEAD_SNONE(DE_ACUT);

  case S_EQUAST: // = --> *
    NSHIFT_SSHIFT(PK_EQUAL, PK_ASTERISK);

  case S_DOLPAR: // $ --> §
    NSHIFT_SSHIFT(PK_DOLLAR, PK_PARAGRAPH);

  case S_USCHAS: // _ --> #
    NSHIFT_SNOSHIFT(PK_UNDERSCORE, DE_HASH);

  default:
    return true;
  }
}

/**
 * Callback function that is called veeeery often in order to scan the key matrix.
 * Calls the matrix scan functions of the sub areas.
 */
void matrix_scan_user(void) {
  matrix_scan_user_rotary_encoder();
  matrix_scan_user_leader_key();
}

/**
 * The very last task in the keyboard initialization process.
 *
 */
void keyboard_post_init_user(void) {

#ifdef RGBLIGHT_ENABLE
  keyboard_post_init_user_rgb_light();
#endif
}
