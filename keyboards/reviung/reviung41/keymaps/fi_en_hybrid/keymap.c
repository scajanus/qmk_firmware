/* Copyright 2020 gtips
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
#define TAPPING_TERM 200

#include QMK_KEYBOARD_H
#include "keymap_finnish.h"
//#include "sendstring_finnish.h"
//#include "features/custom_shift_keys.h"

// const custom_shift_key_t custom_shift_keys[] = {
//  {FI_SCLN, FI_COLN}, // Shift : is ;
//   {FI_QUOT, FI_DQUO}, // Shift : is ;
//   {FI_COMM, KC_GRV}, // Shift : is ;
//   {FI_DOT, S(KC_GRV)}, // Shift : is ;
//   {FI_SLSH, FI_QUES}, // Shift : is ;
// };
//
// uint8_t NUM_CUSTOM_SHIFT_KEYS =
//     sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);
//

enum my_keycodes {
  SS_TILDE = SAFE_RANGE
};

enum layer_names {
    _BASE_FI,
    _BASE_EN,
    _LOWER,
    _RAISE,
    _ADJUST
};

const key_override_t backspace_question_override =
    ko_make_with_layers_negmods_and_options(
        MOD_MASK_SHIFT,       // Trigger modifiers: shift
        KC_BSPC,             // Trigger key: backspace
        FI_QUES,             // Replacement key
        ~0,                  // Activate on all layers
        MOD_MASK_CAG,         // Do not activate when ctrl, alt or gui are pressed
        ko_option_no_reregister_trigger); // Specifies that the key is not registered again after lifting shift

const key_override_t semicolon_colon_override =
    ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, FI_SCLN, FI_COLN, ~_BASE_EN, MOD_MASK_CAG, ko_option_no_reregister_trigger);
const key_override_t quote_doublequote_override =
    ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, FI_QUOT, FI_DQUO, ~_BASE_EN, MOD_MASK_CAG, ko_option_no_reregister_trigger);
const key_override_t comma_lt_override =
    ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, FI_COMM, KC_GRV, ~_BASE_EN, MOD_MASK_CAG, ko_option_no_reregister_trigger);
const key_override_t dot_gt_override =
    ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, FI_DOT, S(KC_GRV), ~_BASE_EN, MOD_MASK_CAG, ko_option_no_reregister_trigger);
const key_override_t slash_question_override =
    ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, FI_SLSH, FI_QUES, ~_BASE_EN, MOD_MASK_CAG, ko_option_no_reregister_trigger);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &backspace_question_override,
    &semicolon_colon_override,
    &quote_doublequote_override,
    &comma_lt_override,
    &dot_gt_override,
    &slash_question_override,
    NULL
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

enum custom_keycodes {
  RAPIDF
};
bool rapid_fire = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE_FI] = LAYOUT(
    LGUI_T(KC_TAB),          KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    LCTL_T(KC_ESC),  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     FI_ODIA,  FI_ADIA,
    SC_LSPO,         KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     FI_COMM,  FI_DOT,   FI_MINS,  SC_RSPC,
                                       KC_LALT,   LT(LOWER, KC_ENT),   KC_SPC,    LT(RAISE, KC_BSPC),    KC_RCTL
  ),

  [_BASE_EN] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  FI_SCLN,  FI_QUOT,
    _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  FI_COMM,  FI_DOT,   FI_SLSH,  _______,
                                            _______,  _______,  _______,  _______,  _______
  ),

//  [_LOWER] = LAYOUT(
//    _______,  KC_1,     KC_2,     KC_3,     KC_4,      KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
//    _______,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,   KC_PIPE,            KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_GRV,   KC_TILD,
//    _______,  KC_ESC,   KC_LGUI,  KC_LALT,  KC_CAPS,   KC_DQUO,            KC_HOME,  KC_END,   KC_PGUP,  KC_PGDN,  KC_PSCR,  RSFT_T(KC_SPC),
//                                            _______,   _______,  KC_ENT,   _______,  _______
//  ),
  [_LOWER] = LAYOUT(
    _______,  KC_1,     KC_2,     KC_3,     KC_4,      KC_5,            S(FI_LBRC),S(FI_RBRC),FI_LPRN,FI_RPRN,  KC_0,    _______,
    _______,  KC_4,     KC_5,     KC_6,  KC_RCBR,   KC_PIPE,            KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  FI_DQUO,   FI_ASTR,
    _______,  KC_7,     KC_8,     KC_9,  KC_CAPS,   KC_DQUO,            KC_HOME,  KC_END,   KC_PGUP,  KC_PGDN,  KC_PSCR,  RSFT_T(KC_SPC),
                                            _______,   _______,  KC_ENT,   _______,  _______
  ),

  [_RAISE] = LAYOUT(
    _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,    KC_PERC,            KC_CIRC,  KC_AMPR,  FI_LPRN,  FI_RPRN,  KC_RPRN,  _______,
    _______,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,   KC_BSLS,            KC_F1,    KC_F2,    RALT(KC_8),    RALT(KC_9),    KC_F5,    KC_F6,
    _______,  RAPIDF,   KC_RGUI,  KC_RALT,  KC_CAPS,   KC_QUOT,            KC_F7,    KC_F8,    RALT(FI_LPRN),    RALT(FI_RPRN),   KC_F11,   KC_F12,
                                            _______,   _______,  KC_BSPC,  _______,  _______
  ),

  [_ADJUST] = LAYOUT(
    DF(_BASE_FI),   DF(_BASE_EN), RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_DEL,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            QK_BOOT,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                            _______,   _______,  XXXXXXX,  _______,  _______
  ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// bool process_record_user(uint16_t keycode, keyrecord_t* record) {
//   if (get_highest_layer(default_layer_state) == _BASE_EN) {
//       if (!process_custom_shift_keys(keycode, record)) { return false; };
//   };
//
//   return true;
// }
//
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QUOT:
        case KC_TAB:
            if (record->event.pressed && (get_mods() & MOD_MASK_ALT)) {
                del_mods(MOD_MASK_ALT);
                SEND_STRING("~");
                register_code16(KC_LALT);
                return false;
            }
            return true;
            break;
        case RAPIDF:
            if (record->event.pressed) {
                rapid_fire = true;
            } else {
                rapid_fire = false;
            }
            return true;
            break;
    }

    return true;
}
void matrix_scan_user(void) {
  if (rapid_fire) {
    tap_code(KC_MS_BTN1);
  } else {
  }
}
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case FI_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}
