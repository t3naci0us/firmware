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
    static unsigned long upPressStarted = 0;
    static unsigned long lastButtonPress = 0;

    static bool upWasPressed = false;
    static bool upLongPressTriggered = false;

    const unsigned long now = millis();
    const unsigned long UP_HOLD_TIME = 1000;

    const bool upPressed = digitalRead(UP_BTN) == BTN_ACT;

    const bool downPressed = digitalRead(DW_BTN) == BTN_ACT;

    const bool leftPressed = digitalRead(L_BTN) == BTN_ACT;

    const bool rightPressed = digitalRead(R_BTN) == BTN_ACT;

    const bool selectPressed = digitalRead(SEL_BTN) == BTN_ACT;

    /*
     * UP button:
     *
     * Short tap = normal Up
     * Long hold = Back / Escape
     */
    if (upPressed && !upWasPressed) {
        upWasPressed = true;
        upLongPressTriggered = false;
        upPressStarted = now;
    }

    if (upPressed && upWasPressed && !upLongPressTriggered && now - upPressStarted >= UP_HOLD_TIME) {
        if (!wakeUpScreen()) {
            EscPress = true;
            AnyKeyPress = true;
        }

        upLongPressTriggered = true;
    }

    /*
     * Generate a normal Up press only when the button is
     * released before reaching the long-hold time.
     */
    if (!upPressed && upWasPressed) {
        if (!upLongPressTriggered) {
            if (!wakeUpScreen()) {
                UpPress = true;
                PrevPagePress = true;
                AnyKeyPress = true;
            }
        }

        upWasPressed = false;
        upLongPressTriggered = false;
    }

    /*
     * Debounce the remaining buttons.
     */
    if (now - lastButtonPress < 150) { return; }

    if (downPressed) {
        if (!wakeUpScreen()) {
            DownPress = true;
            NextPagePress = true;
            AnyKeyPress = true;
        }

        lastButtonPress = now;
    }

    if (leftPressed) {
        if (!wakeUpScreen()) {
            PrevPress = true;
            AnyKeyPress = true;
        }

        lastButtonPress = now;
    }

    if (rightPressed) {
        if (!wakeUpScreen()) {
            NextPress = true;
            AnyKeyPress = true;
        }

        lastButtonPress = now;
    }

    if (selectPressed) {
        if (!wakeUpScreen()) {
            SelPress = true;
            AnyKeyPress = true;
        }

        lastButtonPress = now;
    }
}

void powerOff() { esp_deep_sleep_start(); }

void checkReboot() {}
