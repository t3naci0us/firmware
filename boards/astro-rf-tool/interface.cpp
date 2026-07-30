#include "core/powerSave.h"
#include <interface.h>
void _setup_gpio() {
    pinMode(UP_BTN, INPUT_PULLUP);
    pinMode(DW_BTN, INPUT_PULLUP);
    pinMode(L_BTN, INPUT_PULLUP);
    pinMode(R_BTN, INPUT_PULLUP);
    pinMode(SEL_BTN, INPUT_PULLUP);
}

bool isCharging() { return false; }

int getBattery() { return 100; }

void _setBrightness(uint8_t value) {
    /*
     * Backlight is currently connected directly to power.
     */
    (void)value;
}

void InputHandler() {
    static unsigned long lastPress = 0;

    if (millis() - lastPress < 150 && !LongPress) { return; }

    const bool upPressed = digitalRead(UP_BTN) == BTN_ACT;

    const bool downPressed = digitalRead(DW_BTN) == BTN_ACT;

    const bool leftPressed = digitalRead(L_BTN) == BTN_ACT;

    const bool rightPressed = digitalRead(R_BTN) == BTN_ACT;

    const bool selectPressed = digitalRead(SEL_BTN) == BTN_ACT;

    if (upPressed || downPressed || leftPressed || rightPressed || selectPressed) {
        lastPress = millis();

        if (!wakeUpScreen()) {
            AnyKeyPress = true;
        } else {
            return;
        }
    }

    if (leftPressed) { PrevPress = true; }

    if (rightPressed) { NextPress = true; }

    if (upPressed) {
        UpPress = true;
        PrevPagePress = true;
    }

    if (downPressed) {
        DownPress = true;
        NextPagePress = true;
    }

    if (selectPressed) { SelPress = true; }

    // Left + Right together acts as Back/Escape
    if (leftPressed && rightPressed) {
        EscPress = true;
        PrevPress = false;
        NextPress = false;
    }
}

void powerOff() { esp_deep_sleep_start(); }

void checkReboot() {}
