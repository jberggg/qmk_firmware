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


enum planck_layers {
  _QWERTZ_UMLAUTE,
  _QWERTZ,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _PLOVER,
  _ADJUST
};

enum planck_keycodes {
  QWERTZ_UMLAUTE = SAFE_RANGE,
  QWERTZ,
  COLEMAK,
  PLOVER,
  BACKLIT,
  EXT_PLV,
  LINUX_MODE,
  OSX_MODE
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

void send_unicode_a_or_ae(qk_tap_dance_state_t *state, void *user_data) {
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

void send_unicode_o_or_oe(qk_tap_dance_state_t *state, void *user_data) {
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

void send_unicode_u_or_ue(qk_tap_dance_state_t *state, void *user_data) {
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
    TD_RIGHT,
    TD_QUOTE
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_AÄ]    = ACTION_TAP_DANCE_FN(send_unicode_a_or_ae),
    [TD_OÖ]    = ACTION_TAP_DANCE_FN(send_unicode_o_or_oe),
    [TD_UÜ]    = ACTION_TAP_DANCE_FN(send_unicode_u_or_ue),
    [TD_LSFT]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_SLSH]  = ACTION_TAP_DANCE_DOUBLE(KC_SLSH,KC_BSLS),
    [TD_LEFT]  = ACTION_TAP_DANCE_DOUBLE(KC_LEFT,S(KC_COMMA)),
    [TD_RIGHT] = ACTION_TAP_DANCE_DOUBLE(KC_RGHT,S(KC_DOT)),
    [TD_QUOTE] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT,KC_GRV)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwertz w. double tabs and umlaute
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Z  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Y  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Up   | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTZ_UMLAUTE] = LAYOUT_planck_grid(
    KC_ESC,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Z,TD(TD_UÜ),       KC_I,TD(TD_OÖ),       KC_P, KC_BSPC,
    KC_TAB,TD(TD_AÄ),    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,     KC_J,       KC_K,     KC_L,    KC_SCLN, TD(TD_QUOTE),
TD(TD_LSFT),    KC_Y,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,     KC_M,    KC_COMM,   KC_DOT,TD(TD_SLSH),  KC_ENT,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI,   LOWER,  KC_SPC,  KC_SPC,    RAISE,TD(TD_LEFT),    KC_UP,    KC_DOWN, TD(TD_RIGHT)
),

/* Qwertz w. double tabs
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Z  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Y  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Up   | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTZ] = LAYOUT_planck_grid(
     KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Z,    KC_U,       KC_I,    KC_O,       KC_P, KC_BSPC,
     KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,       KC_K,    KC_L,    KC_SCLN, TD(TD_QUOTE),
TD(TD_LSFT),    KC_Y,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,TD(TD_SLSH),  KC_ENT,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI,   LOWER,  KC_SPC,  KC_SPC,   RAISE,TD(TD_LEFT),   KC_UP,  KC_DOWN  , TD(TD_RIGHT)
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Up   | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_UP,   KC_DOWN,   KC_RGHT
),

/* Lower - NEW
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | F12  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home | PgUp | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
     KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
),

/* Raise - NEW
 * ,-----------------------------------------------------------------------------------.
 * |  `   |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |      |      |      |      |      |      |   +  |   -  |   [  |   ]  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   _  |   =  |   {  |   }  |  ~   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_EXLM,   KC_AT, KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, S(KC_9), S(KC_0), KC_DEL,
    KC_DEL,  _______, _______, _______, _______, _______, _______, KC_PLUS, KC_MINS, KC_LBRC, KC_RBRC, KC_PIPE,
    _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_EQL , KC_LCBR, KC_RCBR, KC_TILD,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL------v      v-------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- | OSX  |QwrtzU|BRGTH+|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|      |Colemk| Linux|Qwertz|BRGTH-|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |Plover|      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______,   RESET,   DEBUG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  OSX_MODE, QWERTZ_UMLAUTE, RGB_VAI,
    _______, _______,  MU_MOD,   AU_ON,  AU_OFF, AG_NORM, AG_SWAP, _______, _______,LINUX_MODE, QWERTZ, RGB_VAD,
    _______,  MUV_DE,  MUV_IN,   MU_ON,  MU_OFF,   MI_ON,  MI_OFF, _______, _______,   _______, COLEMAK, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,  PLOVER, _______
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

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
        print("mode just switched to qwertz and this is a huge string\n");
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
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
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
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
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
