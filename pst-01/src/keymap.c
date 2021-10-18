/* Copyright 2021 Peter Störmer <mail@peter.stoermer.de>
 * based on the original work of Thomas Baart <thomas@splitkb.com> 2019.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "shift-handling.h"

/* -------------------------------------------------------------------------- */
/*                              KEYMAP DEFINITION                             */
/* -------------------------------------------------------------------------- */

// --------------- Constants ---------------
enum layers {
  _COLEMAK_PST = 0,
  _DOWN,
  _FUNCTION,
  _ADJUST
};

// Aliases for readability
#define COLEMAK  DF(_COLEMAK_PST)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)

#define SPC_DOWN LT(_DOWN, KC_SPC)       // Space when pressed,     _DOWN layer when held down
#define ESC_CTL  MT(MOD_LCTL, KC_ESC)    // ESC when pressed,       Ctrl when held down
#define ENT_CTL  MT(MOD_LCTL, KC_ENT)    // Enter when pressed,     Ctrl when held down
#define BSP_SHFT RSFT_T(KC_BSPC)         // Backspace when pressed, right Shift when held down

#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

#define TD_A_AE  TD(TD_A_TO_AE)
#define TD_E_EUR TD(TD_E_TO_EUR)
#define TD_O_OE  TD(TD_O_TO_OE)
#define TD_U_UE  TD(TD_U_TO_UE)
#define TD_S_SZ  TD(TD_S_TO_SZ)

// Umlauts:
#define DE_ae UC(0x00E4)
#define DE_eur UC(0x20AC)
#define DE_oe UC(0x00F6)
#define DE_ue UC(0x00FC)
#define DE_sz UC(0x00DF)

// My own custom key codes:
enum custom_keycodes {
  // Special symbol keys:
  S_ATPIPE = SAFE_RANGE,   // @ --> |
  S_ANGLEB,                // < --> >
  S_CBRCKT,                // { --> }
  S_PARNTH,                // ( --> )
  S_BRCKET,                // [ --> ]
  S_DOTCOL,                // . --> :
  S_COMSEM,                // , --> ;
  S_SLSTIL,                // / --> ~
  S_PRCAMP,                // % --> &
  S_CIRGRV,                // ^ --> `
  S_EQUAST,                // = --> *
  S_USCHAS                 // _ --> #
};

// --------------- Tap Dance definitions ---------------

enum {
    TD_A_TO_AE,
    TD_E_TO_EUR,
    TD_O_TO_OE,
    TD_U_TO_UE,
    TD_S_TO_SZ
};

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_A_TO_AE] = ACTION_TAP_DANCE_DOUBLE(KC_A, DE_ae),
    [TD_E_TO_EUR] = ACTION_TAP_DANCE_DOUBLE(KC_E, DE_eur),
    [TD_O_TO_OE] = ACTION_TAP_DANCE_DOUBLE(KC_O, DE_oe),
    [TD_U_TO_UE] = ACTION_TAP_DANCE_DOUBLE(KC_U, DE_ue),
    [TD_S_TO_SZ] = ACTION_TAP_DANCE_DOUBLE(KC_S, DE_sz)
};

// TODO: Unclear: What happens with capital umlauts like Ä, Ö, Ü, and capital ß?

// --------------- The actual keymap ---------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * Base Layer: Peter's Colemak
   */
  [_COLEMAK_PST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
      FKEYS  ,  KC_Q  ,  KC_W  ,  KC_F  ,  KC_P  ,  KC_B  ,                                               KC_J  ,  KC_L  ,TD_U_UE ,  KC_Y  ,S_PRCAMP,S_CIRGRV,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                            ├────────┼────────┼────────┼────────┼────────┼────────┤
     S_ATPIPE,TD_A_AE ,  KC_R  ,TD_S_SZ ,  KC_T  ,  KC_G  ,                                               KC_M  ,  KC_N  ,TD_E_EUR,  KC_I  ,  KC_H  ,S_EQUAST,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐        ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
      KC_APP ,  KC_Z  ,  KC_X  ,  KC_C  ,  KC_V  ,  KC_D  ,SPC_DOWN,ESC_CTL ,         ENT_CTL ,BSP_SHFT,  KC_K  ,TD_O_OE ,S_DOTCOL,S_COMSEM,S_SLSTIL, KC_DLR ,
  //└────────┴────────┴────────┼────────┼────────┼────────┤        |        |        |        |        ├────────┼────────┼────────┼────────┴────────┴────────┘
                                 KC_SPC , KC_TAB ,KC_LALT ,SPC_DOWN,ESC_CTL ,         ENT_CTL ,BSP_SHFT,KC_RCTRL,S_USCHAS, KC_SPC
  //                           └────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┴────────┘
  ),

  /*
   * Down: All necessary other keys
   */
  [_DOWN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,  KC_9  ,  KC_8  ,  KC_7  ,S_CBRCKT,                                             KC_DQUO ,KC_HOME , KC_UP  , KC_END , KC_NO  , KC_GRV ,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                            ├────────┼────────┼────────┼────────┼────────┼────────┤
     S_ANGLEB,  KC_0  ,  KC_3  ,  KC_2  ,  KC_1  ,S_PARNTH,                                             KC_QUOTE,KC_LEFT ,KC_DOWN ,KC_RGHT , KC_NO  , KC_DLR ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐        ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,  KC_6  ,  KC_5  ,  KC_4  ,S_BRCKET,_______ ,_______ ,         _______ , KC_DEL ,KC_QUES ,KC_MINUS,KC_PLUS ,KC_EXLM , KC_NO  , KC_NO  ,
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
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |Colmak|      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                    _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, _______, _______, _______,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
      _______, _______, _______, COLEMAK, _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),
};


/* -------------------------------------------------------------------------- */
/*                                 USER INPUT                                 */
/* -------------------------------------------------------------------------- */

//
// Callback function that is called whenever a key is pressed.
// @param keycode the code of the key that was pressed
// @param record contains information about the actual press
// @return true if QMK shall continue to process the key event, false otherwise.
//
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case S_ATPIPE: // @ --> |
      NSHIFT_SSHIFT(PK_AT, PK_PIPE);

    case S_ANGLEB: // < --> >
      NSHIFT_SSHIFT(PK_LANGLEBR, PK_RANGLEBR);

    case S_CBRCKT: // { --> }
      NSHIFT_SSHIFT(PK_LCURLBRKT, PK_RCURLBRKT);

    case S_PARNTH: // ( --> )
      NSHIFT_SSHIFT(PK_LPAREN, PK_RPAREN);

    case S_BRCKET: // [ --> ]
      NNOSHIFT_SNOSHIFT(KC_LBRACKET, KC_RBRACKET);
      
    case S_DOTCOL: // . --> :
      NNOSHIFT_SSHIFT(KC_DOT, PK_COLON);

    case S_COMSEM: // , --> ;
      NNOSHIFT_SNOSHIFT(KC_COMMA, KC_SCOLON);

    case S_SLSTIL: // / --> ~
      NNOSHIFT_SSHIFT(KC_SLASH, PK_TILDA);

    case S_PRCAMP: // % --> &
      NSHIFT_SSHIFT(PK_PERCENT, PK_AMPERSAND);

    case S_CIRGRV: // ^ --> `
      NSHIFT_SNOSHIFT(PK_CIRCUMFLEX, KC_GRAVE);

    case S_EQUAST: // = --> *
      NNOSHIFT_SSHIFT(KC_EQUAL, PK_ASTERISK);

    case S_USCHAS: // _ --> #
      NSHIFT_SSHIFT(PK_UNDERSCORE, PK_HASH)

    // TODO: Probably also those keys that only have a symbol but no <Shift>-<symbol> will need to get an NNOSHIFT_SNOOP
    //       NSHIFT_SNOOP, respectively.

    default:
      return true;
  }
}


/* -------------------------------------------------------------------------- */
/*                                OLED OUTPUT                                 */
/* -------------------------------------------------------------------------- */

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

/* DELETE THIS LINE TO UNCOMMENT (1/2)
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

void oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _QWERTY:
                oled_write_P(PSTR("QWERTY\n"), false);
                break;
            case _DVORAK:
                oled_write_P(PSTR("Dvorak\n"), false);
                break;
            case _COLEMAK_PST:
                oled_write_P(PSTR("Colemak-DH\n"), false);
                break;
            case _DOWN:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case _SYM:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR("Function\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif
DELETE THIS LINE TO UNCOMMENT (2/2) */
