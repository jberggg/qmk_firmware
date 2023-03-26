/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"

enum preonic_layers {
  _QWERTZ_UMLAUTE,
  _QWERTZ,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTZ_UMLAUTE = SAFE_RANGE,
  QWERTZ,
  COLEMAK,
  LOWER,
  RAISE,
  BACKLIT,
};

void send_unicode_a_or_ae(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code(KC_A);
  } else {
      if(get_mods() & MOD_MASK_SHIFT){
        send_unicode_string("Ä");
      } else {
        send_unicode_string("ä");
      }
  }
}

void send_unicode_o_or_oe(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code(KC_O);
  } else {
      if(get_mods() & MOD_MASK_SHIFT){
        send_unicode_string("Ö");
      } else {
        send_unicode_string("ö");
      }
  }
}

void send_unicode_u_or_ue(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_code(KC_U);
  } else {
      if(get_mods() & MOD_MASK_SHIFT){
        send_unicode_string("Ü");
      } else {
        send_unicode_string("ü");
      }
  }
}

enum tap {
    TD_AÄ,
    TD_OÖ,
    TD_UÜ,
    TD_LSFT,
    TD_SLSH,
    TD_LEFT,
    TD_RIGHT
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_AÄ]   = ACTION_TAP_DANCE_FN(send_unicode_a_or_ae),
    [TD_OÖ]   = ACTION_TAP_DANCE_FN(send_unicode_o_or_oe),
    [TD_UÜ]   = ACTION_TAP_DANCE_FN(send_unicode_u_or_ue),
    [TD_LSFT] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_SLSH] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH,KC_BSLS),
    [TD_LEFT]   = ACTION_TAP_DANCE_DOUBLE(KC_LEFT,S(KC_COMMA)),
    [TD_RIGHT]   = ACTION_TAP_DANCE_DOUBLE(KC_RGHT,S(KC_DOT))
};

// Aliases for tab dance actions
#define TDK_AÄ    TD(TD_AÄ)
#define TDK_OÖ    TD(TD_OÖ)
#define TDK_UÜ    TD(TD_UÜ)
#define TDK_LSFT  TD(TD_LSFT)
#define TDK_SLSH  TD(TD_SLSH)
#define TDK_LEFT  TD(TD_LEFT)
#define TDK_RGHT  TD(TD_RIGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwertz w. double tab Umlaute
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down | Up   |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTZ_UMLAUTE] = LAYOUT_preonic_grid(
    KC_ESC,    KC_1,    KC_2,    KC_3,  KC_4,   KC_5,   KC_6,   KC_7,      KC_8,    KC_9,     KC_0, KC_DEL,
    KC_ESC,    KC_Q,    KC_W,    KC_E,  KC_R,   KC_T,   KC_Z, TDK_UÜ,      KC_I,  TDK_OÖ,     KC_P, KC_BSPC,
    KC_TAB,  TDK_AÄ,    KC_S,    KC_D,  KC_F,   KC_G,   KC_H,   KC_J,      KC_K,    KC_L,  KC_SCLN, KC_QUOT,
  TDK_LSFT,    KC_Y,    KC_X,    KC_C,  KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,  KC_DOT, TDK_SLSH, KC_ENT,
   RGB_TOG, KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC, KC_SPC,   RAISE, TDK_LEFT, KC_DOWN,    KC_UP, TDK_RGHT
),

/* Qwertz
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down | Up   |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTZ] = LAYOUT_preonic_grid(
    KC_ESC,    KC_1,    KC_2,    KC_3,  KC_4,   KC_5,   KC_6,  KC_7,     KC_8,    KC_9,     KC_0,  KC_DEL,
    KC_ESC,    KC_Q,    KC_W,    KC_E,  KC_R,   KC_T,   KC_Z,  KC_U,     KC_I,    KC_O,     KC_P, KC_BSPC,
    KC_TAB,    KC_A,    KC_S,    KC_D,  KC_F,   KC_G,   KC_H,  KC_J,     KC_K,    KC_L,  KC_SCLN, KC_QUOT,
  TDK_LSFT,    KC_Y,    KC_X,    KC_C,  KC_V,   KC_B,   KC_N,  KC_M,  KC_COMM,  KC_DOT, TDK_SLSH,  KC_ENT,
   RGB_TOG, KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC, KC_SPC, RAISE, TDK_LEFT, KC_DOWN,    KC_UP, TDK_RGHT
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down | Up   |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_preonic_grid(
    KC_ESC,    KC_1,    KC_2,    KC_3,  KC_4,   KC_5,   KC_6,  KC_7,     KC_8,    KC_9,     KC_0,  KC_DEL,
    KC_ESC,    KC_Q,    KC_W,    KC_F,  KC_P,   KC_G,   KC_J,  KC_L,   TDK_UÜ,    KC_Y,  KC_SCLN, KC_BSPC,
    KC_TAB,  TDK_AÄ,    KC_R,    KC_S,  KC_T,   KC_D,   KC_H,  KC_N,     KC_E,    KC_I,   TDK_OÖ, KC_QUOT,
  TDK_LSFT,    KC_Z,    KC_X,    KC_C,  KC_V,   KC_B,   KC_K,  KC_M,  KC_COMM,  KC_DOT, TDK_SLSH,  KC_ENT,
   RGB_TOG, KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC, KC_SPC, RAISE, TDK_LEFT, KC_DOWN,    KC_UP, TDK_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |      |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | F12  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
  KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, _______, _______, KC_BSPC,
  _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
  KC_F12,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  `   |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   +  |   -  |   [  |   ]  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   _  |   =  |   {  |   }  |  ~   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid(
  KC_GRV,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8, _______, _______, KC_BSPC,
  KC_GRV,  KC_EXLM,   KC_AT, KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, S(KC_9), S(KC_0),  KC_DEL,
  _______, _______, _______, _______, _______, _______, _______, KC_PLUS, KC_MINS, KC_LBRC, KC_RBRC, KC_PIPE,
  _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_EQL , KC_LCBR, KC_RCBR, KC_TILD,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- | OSX  |QwrtzU|BRGTH+|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Aud cy|Aud on|AudOff|AGnorm|AGswap|      |      | LNX  | Qwrz |BRGTH-|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      | Clmk |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
  KC_F1  ,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,         KC_F11,  KC_F12,
  _______, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  UC_MAC, QWERTZ_UMLAUTE, RGB_VAI,
  _______, _______, MU_NEXT,   AU_ON,  AU_OFF, AG_NORM, AG_SWAP, _______, _______, UC_LINX,         QWERTZ, RGB_VAD,
  _______, AU_PREV, AU_NEXT,   MU_ON,  MU_OFF,   MI_ON,  MI_OFF, _______, _______, _______,        COLEMAK, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTZ_UMLAUTE:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTZ_UMLAUTE);
          }
          return false;
          break;
        case QWERTZ:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTZ);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:            
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef __AVR__
            writePinLow(E6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            writePinHigh(E6);
            #endif
          }
          return false;
          break;
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
  return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}


void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}