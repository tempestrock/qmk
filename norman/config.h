/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#pragma once

// stuff for QMK DFU
// outer thumb key as bootloader escape
#define QMK_ESC_OUTPUT B6 // COL0
#define QMK_ESC_INPUT D4 // ROW3
#define QMK_LED B0
//#define QMK_SPEAKER C6

// bootmagic lite key (top-left key)
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 7

#define USE_SERIAL
#define EE_HANDS

//number of times a modifier has to be pressed to toggle a layer
#define TAPPING_TOGGLE 2

//timeout for tap dance
#define TAPPING_TERM 150

//Time (in ms) before the one shot key is released
#define ONESHOT_TIMEOUT 2000
//Tapping this number of times holds the key until tapped once again
#define ONESHOT_TAP_TOGGLE 3

//encoder settings (EC11K has different resolution than EC11)
#define ENCODER_DIRECTION_FLIP
#define ENCODER_RESOLUTION 2

//faster scrolling
# define MOUSEKEY_WHEEL_INTERVAL 50

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
  #define OLED_DISABLE_TIMEOUT
  #define OLED_SCROLL_TIMEOUT_RIGHT 60000
#endif

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_SLEEP
  #define RGBLIGHT_LIMIT_VAL 200
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_SPLIT
#endif

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK
