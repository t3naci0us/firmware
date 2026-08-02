#include "core/powerSave.h"
#include <interface.h>
void _setup_gpio() {
    pinMode(UP_BTN, INPUT_PULLUP);
    pinMode(DW_BTN, INPUT_PULLUP);
    pinMode(L_BTN, INPUT_PULLUP);
    pinMode(R_BTN, INPUT_PULLUP);
    pinMode(SEL_BTN, INPUT_PULLUP);

#ifdef TFT_CS
    pinMode(TFT_CS, OUTPUT);
    digitalWrite(TFT_CS, HIGH);
#endif

#ifdef CC1101_SS_PIN
    pinMode(CC1101_SS_PIN, OUTPUT);
    digitalWrite(CC1101_SS_PIN, HIGH);
#endif

#ifdef NRF24_SS_PIN
    pinMode(NRF24_SS_PIN, OUTPUT);
    digitalWrite(NRF24_SS_PIN, HIGH);
#endif

#ifdef NRF24_CE_PIN
    pinMode(NRF24_CE_PIN, OUTPUT);
    digitalWrite(NRF24_CE_PIN, LOW);
#endif

#ifdef SDCARD_CS
    pinMode(SDCARD_CS, OUTPUT);
    digitalWrite(SDCARD_CS, HIGH);
#endif
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
    static bool rawUpState = false;
    static bool stableUpState = false;
    static bool upLongPressTriggered = false;

    static unsigned long upStateChangedAt = 0;
    static unsigned long upPressedAt = 0;
    static unsigned long lastOtherButtonPress = 0;

    const unsigned long now = millis();

    const unsigned long UP_HOLD_TIME = 1000;
    const unsigned long DEBOUNCE_TIME = 40;
    const unsigned long OTHER_BUTTON_DEBOUNCE = 150;

    const bool currentRawUp = digitalRead(UP_BTN) == BTN_ACT;

    const bool downPressed = digitalRead(DW_BTN) == BTN_ACT;

    const bool leftPressed = digitalRead(L_BTN) == BTN_ACT;

    const bool rightPressed = digitalRead(R_BTN) == BTN_ACT;

    const bool selectPressed = digitalRead(SEL_BTN) == BTN_ACT;

    /*
     * Track raw changes on the Up button.
     */
    if (currentRawUp != rawUpState) {
        rawUpState = currentRawUp;
        upStateChangedAt = now;
    }

    /*
     * Accept the new Up state only after it has remained
     * unchanged for the debounce period.
     */
    if (rawUpState != stableUpState && now - upStateChangedAt >= DEBOUNCE_TIME) {
        stableUpState = rawUpState;

        /*
         * Confirmed press.
         */
        if (stableUpState) {
            upPressedAt = now;
            upLongPressTriggered = false;
        }

        /*
         * Confirmed release.
         *
         * Generate normal Up only when no long press occurred.
         */
        else {
            if (!upLongPressTriggered) {
                if (!wakeUpScreen()) {
                    UpPress = true;
                    PrevPagePress = true;
                    AnyKeyPress = true;
                }
            }

            upLongPressTriggered = false;
        }
    }

    /*
     * Confirmed long hold:
     * issue Escape once and do not issue Up on release.
     */
    if (stableUpState && !upLongPressTriggered && now - upPressedAt >= UP_HOLD_TIME) {
        if (!wakeUpScreen()) {
            EscPress = true;
            AnyKeyPress = true;
        }

        upLongPressTriggered = true;
    }

    /*
     * Debounce remaining controls.
     */
    if (now - lastOtherButtonPress < OTHER_BUTTON_DEBOUNCE) { return; }

    if (downPressed) {
        if (!wakeUpScreen()) {
            DownPress = true;
            NextPagePress = true;
            AnyKeyPress = true;
        }

        lastOtherButtonPress = now;
        return;
    }

    if (leftPressed) {
        if (!wakeUpScreen()) {
            PrevPress = true;
            AnyKeyPress = true;
        }

        lastOtherButtonPress = now;
        return;
    }

    if (rightPressed) {
        if (!wakeUpScreen()) {
            NextPress = true;
            AnyKeyPress = true;
        }

        lastOtherButtonPress = now;
        return;
    }

    if (selectPressed) {
        if (!wakeUpScreen()) {
            SelPress = true;
            AnyKeyPress = true;
        }

        lastOtherButtonPress = now;
        return;
    }
}

void powerOff() { esp_deep_sleep_start(); }

void checkReboot() {}
