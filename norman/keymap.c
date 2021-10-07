/* Copyright 2020  Norman Stetter <mail@normanstetter.com>
 * based on work by Thomas Baart <thomas@splitkb.com>
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

extern keymap_config_t keymap_config;

// Umlauts
// Use Layout "US international, with dead keys"

// special keys
#define SP_ATAB LALT(KC_TAB) //ALT+TAB
#define SP_CTAB LCTL(KC_TAB) //CTL+TAB
#define SP_ASPC LALT(KC_SPC) //ALT+SPC
#define SP_MID LSFT(KC_BTN3) //SHIFT+MIDDLEMOUSE

#define SP_SUENT MT(MOD_LGUI,KC_ENT)  //Enter when pressed, Super when hold
//#define SP_ESALT MT(MOD_LALT,KC_ESC)  //Escape when pressed, ALT when hold

#define SP_NAV LT(_NAV,KC_SPC) //SPACE when pressed, _NAV layer when hold
#define SP_FN LT(_FN,KC_DEL) //DEL when pressed, _FN when hold

#define SP_UMESC LT(_GER,KC_ESC) //ESC when pressed, _GER layer when hold

#define SP_SHBS LSFT_T(KC_BSPC) //Backspace when pressed, Shift when hold

#define SP_CTL TD(TD_CTL) //CTL on press/hold, CTL+SHIFT on double press/hold, CTL+ALT on triple press/hold


// MAC specific special keys
#define MC_CTLEN MT(MOD_LCTL,KC_ENT)  //Enter when pressed, CTL when hold
#define MC_CMD TD(TDM_CMD) //CMD on press/hold CMD+SHIFT on double press/hold, CMD+OPT on triple press/hold
#define MC_OPT TD(TDM_OPT) //OPT on press/hold OPT+SHIFT on double press/hold, OPT+CTL on triple press/hold

// colors
#define DEFAULT_BRIGHTNESS 130
#define HSV_MY_PURPLE 191, 255, DEFAULT_BRIGHTNESS
#define HSV_MY_MAGENTA 213, 255, DEFAULT_BRIGHTNESS
#define HSV_MY_ORANGE  28, 255, DEFAULT_BRIGHTNESS
#define HSV_MY_GREEN 90, 255, DEFAULT_BRIGHTNESS
#define HSV_MY_CYAN 187, 56, DEFAULT_BRIGHTNESS
#define HSV_MY_TURQUOISE 120, 240, DEFAULT_BRIGHTNESS

// function to send single tap without modifiers
void tap_code_nomod(int keycode) {
  uint8_t temp_mods = get_mods();
  clear_mods();
  tap_code(keycode);
  set_mods(temp_mods);
}

// function to register keycode without modifiers
void register_code_nomod(int keycode) {
  uint8_t temp_mods = get_mods();
  clear_mods();
  register_code(keycode);
  set_mods(temp_mods);
}

// function to input umlauts on Mac using ALT+U combo
void tap_umlaut_mac(int keycode) {
  uint8_t temp_mods = get_mods();
  clear_mods();
  tap_code16(LOPT(KC_U));
  set_mods(temp_mods);
  tap_code(keycode);
}

enum layer_names {
  _COLEMAK,
  _MAC,
  _GER,
  _NAV,
  _FN,
};

enum custom_keycodes {
  MOD0 = SAFE_RANGE,
  MOD1,
  MOD2,
  MOD3,
  ND_GRV,
  ND_QUOT,
  TG_DFT,
  DE_ae,
  DE_oe,
  DE_ss,
  DE_ue,
  DE_eur,
};

// variables for ALT-TABBING with encoder
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

// tap-dance struct
typedef struct {
  bool is_press_action;
  int state;
} tap;

//Define a type for as many tap dance states as you need
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};


//Tap dance enums
enum {
  TD_CTL = 0,
  TDM_CMD,
  TDM_OPT,
};

//Function associated with all tap dances
int cur_dance (qk_tap_dance_state_t *state);

//Functions associated with individual tap dances
void ctl_finished (qk_tap_dance_state_t *state, void *user_data);
void ctl_reset (qk_tap_dance_state_t *state, void *user_data);
void mac_cmd_finished (qk_tap_dance_state_t *state, void *user_data);
void mac_cmd_reset (qk_tap_dance_state_t *state, void *user_data);
void mac_opt_finished (qk_tap_dance_state_t *state, void *user_data);
void mac_opt_reset (qk_tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  //Base Layer: COLEMAK-DH
   [_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_LGUI, KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                                                 KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                            ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                                                 KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    ND_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐        ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    SP_SHBS, SP_SUENT,         SP_UMESC,SP_NAV,  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
  //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                TG(_FN), SP_FN,   SP_CTL,  SP_SHBS, SP_SUENT,         SP_UMESC,SP_NAV,  KC_LALT, KC_NO,   TG(_NAV)
                            // └────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┴────────┘
    ),

  [_MAC] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______,_______,  _______,                                              _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                            ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                                              _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐        ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______, MC_CTLEN,         _______, _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                _______, _______, MC_CMD,  _______, MC_CTLEN,         _______, _______, MC_OPT,  _______, _______
                            // └────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┴────────┘
    ),

  //German
   [_GER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,    KC_NO,                                                KC_NO,   KC_NO,   DE_ue,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                            ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   DE_ae,   KC_NO,   DE_ss,   KC_NO,   KC_NO,                                                KC_NO,   KC_NO,   DE_eur,  KC_NO,   DE_oe,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐        ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                KC_NO,   KC_NO,   KC_NO,   SP_SHBS, KC_NO,            SP_UMESC,KC_LSFT, KC_NO,   KC_NO,   KC_NO
                            // └────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┴────────┘
    ),

  //Navigation+Numbers
   [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NO,   KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_LCBR,                                              KC_RCBR, KC_7,    KC_8,    KC_9,    KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                            ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT,KC_LPRN,                                              KC_RPRN, KC_4,    KC_5,    KC_6,    KC_BSPC, KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐        ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     ND_GRV,  KC_WH_U, KC_WH_D, SP_ASPC, SP_ATAB, KC_LBRC, KC_DEL,  SP_SUENT,         KC_BSPC, SP_NAV, KC_RBRC, KC_1,    KC_2,    KC_3,    KC_0,    KC_NO,
  //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                _______, KC_NO,   SP_MID,  KC_DEL,  SP_SUENT,         KC_BSPC, SP_NAV, KC_DEL,  KC_NO,   _______
                            // └────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┴────────┘
    ),


  //Functions
   [_FN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_SLEP, KC_PWR,  KC_NO,   KC_NO,  KC_NO,    KC_NO,                                                KC_NO,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                                            ├────────┼────────┼────────┼────────┼────────┼────────┤
     TG_DFT,  KC_NO,   KC_WBAK, KC_NO,   KC_WFWD, KC_NO,                                                KC_NO,   KC_F4,   KC_F5,   KC_F6,   KC_F11,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐        ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F12,  KC_NO,
  //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
                                _______, SP_FN, KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______
                            // └────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┴────────┘
    ),

//
// Layer template
//
//  [_LAYERINDEX] = LAYOUT(
//  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                            ┌────────┬────────┬────────┬────────┬────────┬────────┐
//     KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,    KC_NO,                                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
//  //├────────┼────────┼────────┼────────┼────────┼────────┤                                            ├────────┼────────┼────────┼────────┼────────┼────────┤
//     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
//  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┬────────┐        ┌────────┬────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
//  //└────────┴────────┴────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┴────────┴────────┘
//                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
//                            // └────────┴────────┴────────┴────────┴────────┘        └────────┴────────┴────────┴────────┴────────┘
//    ),

};


/* -------------------------------------------------------------------------- */
/*                                  TAPDANCE                                  */
/* -------------------------------------------------------------------------- */


/* --------------------------------- GLOBAL --------------------------------- */

//Determine the current tap dance state
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//Associate our tap dance keys with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CTL] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ctl_finished, ctl_reset, 250),
  [TDM_CMD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, mac_cmd_finished, mac_cmd_reset, 250),
  [TDM_OPT] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, mac_opt_finished, mac_opt_reset, 250)
};

/* --------------------------------- TD_CTL --------------------------------- */

//Initialize tap structure associated with tap dance key
static tap ctl_tap_state = {
  .is_press_action = true,
  .state = 0
};

//Functions that control what our tap dance key does
void ctl_finished (qk_tap_dance_state_t *state, void *user_data) {
  ctl_tap_state.state = cur_dance(state);
  switch (ctl_tap_state.state) {
    case SINGLE_TAP:
        set_oneshot_mods(MOD_LCTL);
        break;
    case SINGLE_HOLD:
        register_code(KC_LCTL);
        break;
    case DOUBLE_TAP:
    case DOUBLE_HOLD:
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        break;
    case TRIPLE_TAP:
    case TRIPLE_HOLD:
        register_code(KC_LCTL);
        register_code(KC_LALT);
        break;
  }
}

void ctl_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ctl_tap_state.state) {
    case SINGLE_TAP:
        break;
    case SINGLE_HOLD:
        unregister_code(KC_LCTL);
        break;
    case DOUBLE_TAP:
    case DOUBLE_HOLD:
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        break;
    case TRIPLE_TAP:
    case TRIPLE_HOLD:
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
        break;
    }
  ctl_tap_state.state = 0;
}


/* -------------------------------- TDM_CMD --------------------------------- */

//Initialize tap structure associated with tap dance key
static tap mac_cmd_tap_state = {
  .is_press_action = true,
  .state = 0
};

//Functions that control what our tap dance key does
void mac_cmd_finished (qk_tap_dance_state_t *state, void *user_data) {
  mac_cmd_tap_state.state = cur_dance(state);
  switch (mac_cmd_tap_state.state) {
    case SINGLE_TAP:
    case SINGLE_HOLD:
        register_code(KC_LCMD);
        break;
    case DOUBLE_TAP:
    case DOUBLE_HOLD:
        register_code(KC_LSFT);
        register_code(KC_LCMD);
        break;
    case TRIPLE_TAP:
    case TRIPLE_HOLD:
         register_code(KC_LOPT);
         register_code(KC_LCMD);
         break;
  }
}

void mac_cmd_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (mac_cmd_tap_state.state) {
    case SINGLE_TAP:
    case SINGLE_HOLD:
        unregister_code(KC_LCMD);
        break;
    case DOUBLE_TAP:
    case DOUBLE_HOLD:
        unregister_code(KC_LSFT);
        unregister_code(KC_LCMD);
        break;
    case TRIPLE_TAP:
    case TRIPLE_HOLD:
        unregister_code(KC_LOPT);
        unregister_code(KC_LCMD);
        break;
    }
  mac_cmd_tap_state.state = 0;
}

/* -------------------------------- TDM_OPT -------------------------------- */

//Initialize tap structure associated with tap dance key
static tap mac_opt_tap_state = {
  .is_press_action = true,
  .state = 0
};

//Functions that control what our tap dance key does
void mac_opt_finished (qk_tap_dance_state_t *state, void *user_data) {
  mac_opt_tap_state.state = cur_dance(state);
  switch (mac_opt_tap_state.state) {
    case SINGLE_TAP:
    case SINGLE_HOLD:
        register_code(KC_ROPT);
        break;
    case DOUBLE_TAP:
    case DOUBLE_HOLD:
        register_code(KC_LSFT);
        register_code(KC_ROPT);
        break;
    case TRIPLE_TAP:
    case TRIPLE_HOLD:
        register_code(KC_ROPT);
        register_code(KC_LCTL);
        break;
  }
}

void mac_opt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (mac_opt_tap_state.state) {
    case SINGLE_TAP:
    case SINGLE_HOLD:
        unregister_code(KC_ROPT);
        break;
    case DOUBLE_TAP:
    case DOUBLE_HOLD:
        unregister_code(KC_LSFT);
        unregister_code(KC_ROPT);
        break;
    case TRIPLE_TAP:
    case TRIPLE_HOLD:
         unregister_code(KC_ROPT);
         unregister_code(KC_LCTL);
         break;
    }
  mac_opt_tap_state.state = 0;
}


/* -------------------------------------------------------------------------- */
/*                                 USER INPUT                                 */
/* -------------------------------------------------------------------------- */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_NO:
      /* Always cancel one-shot layer when another key gets pressed */
      if (record->event.pressed && is_oneshot_layer_active())
      clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      return true;
    case MOD0:
      if (record->event.pressed) {
        set_single_persistent_default_layer(0);
      }
      return false;
      break;

    // Toggle default layers between _COLEMAK and _MAC
    case TG_DFT:
      if (record->event.pressed) {
        if (! IS_LAYER_ON(_MAC)) {
          layer_on(_MAC);
          set_single_persistent_default_layer(_MAC);
        }
        else if (IS_LAYER_ON(_MAC)) {
          layer_off(_MAC);
          set_single_persistent_default_layer(0);
        }
      }
      return false;
      break;

    // Tap Space after international layout dead keys, to use them like regular keys
    case ND_GRV:
      if (record->event.pressed) {
        tap_code(KC_GRV);
        tap_code_nomod(KC_SPC);
      } else {
        //
      }
      return false;
      break;
    case ND_QUOT:
      if (record->event.pressed) {
        tap_code(KC_QUOT);
        tap_code_nomod(KC_SPC);
      } else {
        //
      }
      return false;
      break;
    case KC_6:
      if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) { //send space after keycode if SHIFT is pressed, to avoid dead key for ^
            tap_code(KC_6);
            tap_code_nomod(KC_SPC);
        } else {
            tap_code(KC_6);
        }
      } else {
        //
      }
      return false;
      break;
    case DE_ae:
      if (record->event.pressed) {
        if (IS_LAYER_ON(_MAC)) {
          tap_umlaut_mac(KC_A);
        } else {
          tap_code16(RALT(KC_Q));
        }
      }
      return false;
      break;
    case DE_oe:
      if (record->event.pressed) {
        if (IS_LAYER_ON(_MAC)) {
          tap_umlaut_mac(KC_O);
        } else {
          tap_code16(RALT(KC_P));
        }
      }
      return false;
      break;
    case DE_ue:
      if (record->event.pressed) {
        if (IS_LAYER_ON(_MAC)) {
          tap_umlaut_mac(KC_U);
        } else {
          tap_code16(RALT(KC_Y));
        }
      }
      return false;
      break;
    case DE_ss:
      if (record->event.pressed) {
        tap_code16(RALT(KC_S));
      }
      return false;
      break;
    case DE_eur:
      if (record->event.pressed) {
        if (IS_LAYER_ON(_MAC)) {
          tap_code16(LSFT(RALT(KC_2)));
        } else {
        tap_code16(RALT(KC_5));
        }
      }
      return false;
      break;
    }
  return true;
}

void matrix_scan_user(void) {
    // helper for ALT-TABBING with encoder
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}


/* -------------------------------------------------------------------------- */
/*                                    OLED                                    */
/* -------------------------------------------------------------------------- */
#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
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
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
            oled_write_P(PSTR("Colemak\n"), false);
            break;
        case _MAC:
            oled_write_P(PSTR("Mac\n"), false);
            break;
        case _GER:
            oled_write_P(PSTR("German\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("Function\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}
#endif


/* -------------------------------------------------------------------------- */
/*                                   ENCODER                                  */
/* -------------------------------------------------------------------------- */
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    // LEFT ENCODER
    if (index == 0) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_WH_D);
            tap_code(KC_WH_D);
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
            tap_code(KC_WH_U);
            tap_code(KC_WH_U);
        }
    }
    // RIGHT ENCODER
    else if (index == 1) {
        // ALT-TABBING through windows
        if (!is_alt_tab_active) {
            is_alt_tab_active = true;
            register_code(KC_LALT);
        }
        if (clockwise) {
            alt_tab_timer = timer_read();
            tap_code16(KC_TAB);
        } else {
            alt_tab_timer = timer_read();
            tap_code16(LSFT(KC_TAB));
        }
    }
    return true;
}
#endif

/* -------------------------------------------------------------------------- */
/*                                  UNDERGLOW                                 */
/* -------------------------------------------------------------------------- */
//run at the end of the firmware's startup process
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_MY_TURQUOISE);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
