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

#ifndef CONFIG_H
#define CONFIG_H

#include "rgb-light-config.h"

// Definitions for tap dance
#define TAPPING_TERM 175

// Definitions for the leader key
#define LEADER_NO_TIMEOUT     // Define an infinite time between pressing the leader key and the first key of the sequence
#define LEADER_PER_KEY_TIMING // Define that the leader key timing is measured per key, not for the whole sequence.
#define LEADER_TIMEOUT        400

// Lets you roll mod-tap keys
#define IGNORE_MOD_TAP_INTERRUPT

#define SPLIT_USB_DETECT

#endif /* CONFIG_H */
