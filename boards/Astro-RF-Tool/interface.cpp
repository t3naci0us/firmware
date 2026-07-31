#include "core/powerSave.h"

/*
 * Astro RF Tool board-specific interface
 *
 * Initial version:
 * - Five physical control buttons
 * - Backlight permanently connected to 3.3V
 * - No PMIC
 * - No battery measurement yet
 */

void _setup_gpio() {
    pinMode(UP_BTN, INPUT_PULLUP);
    pinMode(DW_BTN, INPUT_PULLUP);
    pinMode(L_BTN, INPUT_PULLUP);
    pinMode(R_BTN, INPUT_PULLUP);
    pinMode(SEL_BTN, INPUT_PULLUP);

#ifdef CC1101_SS_PIN
    pinMode(CC1101_SS_PIN, OUTPUT);
    digitalWrite(CC1101_SS_PIN, HIGH);
#endif

#ifdef NRF24_SS_PIN
    pinMode(NRF24_SS_PIN, OUTPUT);
    digitalWrite(NRF24_SS_PIN, HIGH);
#endif

#ifdef SDCARD_CS
    pinMode(SDCARD_CS, OUTPUT);
    digitalWrite(SDCARD_CS, HIGH);
#endif

    /*
     * Choose CC1101 as the initial RF module.
     * It can still be changed in Bruce configuration.
     */
#ifdef USE_CC1101_VIA_SPI
    bruceConfigPins.rfModule = CC1101_SPI_MODULE;
#endif

#ifdef RXLED
    bruceConfigPins.irRx = RXLED;
#endif

    Wire.setPins(SYS_I2C_SDA, SYS_I2C_SCL);
    Wire.begin(SYS_I2C_SDA, SYS_I2C_SCL);
}

bool isCharging() { return false; }

int getBattery() {
    /*
     * Temporary fixed value until the battery ADC
     * circuit is added.
     */
    return 100;
}

void _setBrightness(uint8_t brightval) {
    /*
     * TFT backlight is wired directly to 3.3V.
     * There is currently no GPIO brightness control.
     */
    (void)brightval;
}

void InputHandler(void) {
    static unsigned long lastInputTime = 0;

    if (millis() - lastInputTime < 150 && !LongPress) { return; }

    const bool upPressed = digitalRead(UP_BTN) == BTN_ACT;
    const bool downPressed = digitalRead(DW_BTN) == BTN_ACT;
    const bool leftPressed = digitalRead(L_BTN) == BTN_ACT;
    const bool rightPressed = digitalRead(R_BTN) == BTN_ACT;
    const bool selectPressed = digitalRead(SEL_BTN) == BTN_ACT;

    if (upPressed || downPressed || leftPressed || rightPressed || selectPressed) {
        lastInputTime = millis();

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

    /*
     * Press Left + Right together for Back/Escape.
     */
    if (leftPressed && rightPressed) {
        EscPress = true;
        NextPress = false;
        PrevPress = false;
    }
}

void powerOff() {
    /*
     * No controllable PMIC is currently fitted.
     * Put the ESP32-S3 into deep sleep instead.
     */

    esp_sleep_enable_ext0_wakeup(static_cast<gpio_num_t>(SEL_BTN), BTN_ACT);

    esp_deep_sleep_start();
}

void checkReboot() {
    /*
     * Hold Left + Right for approximately three seconds
     * to enter deep sleep.
     */

    if (digitalRead(L_BTN) != BTN_ACT || digitalRead(R_BTN) != BTN_ACT) { return; }

    const unsigned long startTime = millis();

    while (digitalRead(L_BTN) == BTN_ACT && digitalRead(R_BTN) == BTN_ACT) {
        if (millis() - startTime > 3000) { powerOff(); }

        delay(10);
    }
}
