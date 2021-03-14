#include QMK_KEYBOARD_H
#include "print.h"

// Layer names
enum layer_names {
    _BASE,
    _KEYB
};

// Tap dance keycodes
enum {
    TD_SHAP,
};

// Custom keycodes
enum custom_keycodes {
    // Macros start with M_
    M_VIVA = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_80_with_macro(
    KC_MPLY,                 KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,     KC_F12,  KC_DEL,  KC_INS,
     M_VIVA,   KC_F2,        KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,        KC_7,   KC_NO,    KC_9,    KC_0, KC_MINS,  KC_EQL,      KC_NO, KC_BSPC, KC_HOME,
      KC_F3,   KC_F4,        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC,    KC_RBRC, KC_BSLS,  KC_END,
      KC_F5,   KC_F6, LCTL(KC_BSPC),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,    KC_QUOT,  KC_ENT, KC_PGUP,
      KC_F7,   KC_F8,       KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,TD(TD_SHAP),   KC_UP, KC_PGDN,
      KC_F9,    KC_8,       KC_LCTL, KC_LALT, KC_LGUI, KC_LALT,        KC_SPC,                  KC_SPC,   KC_NO,   KC_NO,MO(_KEYB), KC_RCTL,   KC_NO,    KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [_KEYB] = LAYOUT_80_with_macro(
    _______,                RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, _______,              _______, _______, _______, _______, _______,    _______, _______, _______,
    _______, _______,       _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,    _______, _______, _______,
    _______, _______,       _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______,    _______, _______, _______,
    _______, _______,       _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______,    _______, _______, _______,
    _______, _______,       _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______,    _______, _______, _______,
      RESET, _______,       _______, _______, _______, _______,       _______,                 _______, _______, _______, _______, _______, _______,    _______, _______, _______
  ),
  /*
  [1] = LAYOUT_80_with_macro(
    _______,                _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______,    _______, _______, _______,
    _______, _______,       _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,    _______, _______, _______,
    _______, _______,       _______, _______, _______, _______  _______, _______,              _______, _______, _______, _______, _______, _______,    _______, _______, _______,
    _______, _______,       _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______,    _______, _______, _______,
    _______, _______,       _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______,    _______, _______, _______,
    _______, _______,       _______, _______, _______, _______,       _______,                 _______, _______, _______, _______, _______, _______,    _______, _______, _______
  ),
  */
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_NO);
        } else {
            tap_code(KC_NO);
        }
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SHAP] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    #endif
    switch (keycode) {
    case M_VIVA:
        if (record->event.pressed) {
            // Open vivaldi browser
            SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(200) "vivaldi" SS_DELAY(200) SS_TAP(X_ENT));
        }
    }
    return true;
}