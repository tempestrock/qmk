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
#include "shift-handling.h"
#include "tapdance.h"
#include <keymap_german.h>

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
  S_DOTCOL,              // . --> :
  S_COMSEM,              // , --> ;
  S_SLSTIL,              // / --> ~
  S_AMPPRC,              // & --> %
  S_CIRGRV,              // ^ --> `
  S_EQUAST,              // = --> *
  S_USCHAS,              // _ --> #
  S_DOLPAR               // $ --> §
};

// clang-format off

// --------------- Aliases for readability ---------------

#define FKEYS    MO(_FUNCTION)        // activate the function keys only as long the FN key is pressed
#define LIGHTS   TG(_LIGHTS)          // toggle the lights layer on and off
#define ESC_CTL  MT(MOD_LCTL, KC_ESC) // ESC when pressed,       Ctrl when held down
#define ENT_CTL  MT(MOD_LCTL, KC_ENT) // Enter when pressed,     Ctrl when held down
#define BSP_SHFT RSFT_T(KC_BSPC)      // Backspace when pressed, right Shift when held down

// --------------- The actual keymap ---------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * Base Layer: Peter's Colemak
   */
  [_COLEMAK_PST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
      FKEYS  ,  DE_Q  ,  DE_W  ,  DE_F  ,  DE_P  ,  DE_B  ,                                               DE_J  ,  DE_L  ,TD_U_UE ,  DE_Z  ,S_AMPPRC,S_CIRGRV,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                            ├────────┼────────┼────────┼────────┼────────┼────────┤
     S_ATPIPE,TD_A_AE ,  DE_R  ,  DE_S  ,  DE_T  ,  DE_D  ,                                               DE_M  ,  DE_N  ,TD_E_EUR,  DE_I  ,  DE_H  ,S_EQUAST,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐        ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_APP ,  DE_Y  ,  DE_X  ,  DE_C  ,TD_V_SZ ,  DE_G  ,TD_SPDWN,ESC_CTL ,         ENT_CTL ,BSP_SHFT,  DE_K  ,TD_O_OE ,S_DOTCOL,S_COMSEM,S_SLSTIL, LIGHTS ,
  //└────────┴────────┴────────┼────────┼────────┼────────┤        |        |        |        |        ├────────┼────────┼────────┼────────┴────────┴────────┘
                                KC_MUTE , KC_TAB ,KC_LALT ,TD_SPDWN,ESC_CTL ,         ENT_CTL ,BSP_SHFT,KC_RCTRL,S_USCHAS, KC_SPC
  //                           └────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┴────────┘
  ),

  /*
   * Down: All necessary other keys
   */
  [_DOWN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,  DE_9  ,  DE_8  ,  DE_7  ,S_CBRCKT,                                             DE_DQUO ,KC_HOME , KC_UP  , KC_END ,XXXXXXX ,S_ACUNON,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                            ├────────┼────────┼────────┼────────┼────────┼────────┤
     DE_LABK ,  DE_0  ,  DE_3  ,  DE_2  ,  DE_1  ,S_PARNTH,                                             DE_QUOT ,KC_LEFT ,KC_DOWN ,KC_RGHT ,XXXXXXX ,S_DOLPAR,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐        ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,  DE_6  ,  DE_5  ,  DE_4  ,S_BRCKET,_______ ,_______ ,         _______ , KC_DEL ,DE_QUES ,DE_MINS, DE_PLUS ,DE_EXLM ,XXXXXXX ,XXXXXXX ,
  //└────────┴────────┴────────┼────────┼────────┼────────┤        |        |        |        |        ├────────┼────────┼────────┼────────┴────────┴────────┘
                                _______ ,_______ ,_______ ,_______ ,_______ ,         _______ , KC_DEL ,_______ ,_______ ,_______
  //                           └────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┴────────┘
  ),

  /*
   * Function Layer: Function keys
   */
  [_FUNCTION] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ , KC_F9  , KC_F8  , KC_F7  , KC_F10,                                              _______, _______, _______, _______, _______, _______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                            ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ , KC_F3  , KC_F2  , KC_F1  , KC_F11 ,                                             _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐        ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ , KC_F6  , KC_F5  , KC_F4  , KC_F12 ,_______ ,_______,          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //└────────┴────────┴────────┼────────┼────────┼────────┤        |        |        |        |        ├────────┼────────┼────────┼────────┴────────┴────────┘
                                _______ ,_______ ,_______ ,_______ ,_______ ,         _______ ,_______ ,_______ ,_______ ,_______
  //                           └────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┴────────┘
  ),

  /*
   * Lights Layer: Set RGB lighting
   */
  [_LIGHTS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                             _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                            ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                             RGB_TOG ,RGB_SAI ,RGB_HUI ,RGB_VAI ,RGB_MOD ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐        ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,         _______ ,_______ ,_______ ,RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______ ,
  //└────────┴────────┴────────┼────────┼────────┼────────┤        |        |        |        |        ├────────┼────────┼────────┼────────┴────────┴────────┘
                                _______ ,_______ ,_______ ,_______ ,_______ ,         _______ ,_______ ,_______ ,_______ ,_______
  //                           └────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┴────────┘
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

    // TODO: Probably also those keys that only have a symbol but no <Shift>-<symbol> will need to get an NNOSHIFT_SNOOP
    //       NSHIFT_SNOOP, respectively.

  default:
    return true;
  }
}
