#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <stdint.h>

/*
 * Astro RF Tool
 * ESP32-S3-N16R8
 * ILI9341 240x320
 */

/* --------------------------------------------------
   Standard Arduino pins
   -------------------------------------------------- */

static const uint8_t TX = 18;
static const uint8_t RX = 17;

static const uint8_t SDA = 1;
static const uint8_t SCL = 2;

static const uint8_t SS = 5;
static const uint8_t MOSI = 11;
static const uint8_t MISO = 13;
static const uint8_t SCK = 12;

/* --------------------------------------------------
   USB / serial
   -------------------------------------------------- */

#define USB_as_HID 1

#define SERIAL_TX 18
#define SERIAL_RX 17

#define BAD_TX SERIAL_TX
#define BAD_RX SERIAL_RX

#define GPS_SERIAL_TX SERIAL_TX
#define GPS_SERIAL_RX SERIAL_RX

/* --------------------------------------------------
   I2C
   -------------------------------------------------- */

#define GROVE_SDA SDA
#define GROVE_SCL SCL

#define SYS_I2C_SDA SDA
#define SYS_I2C_SCL SCL

/* --------------------------------------------------
   Buttons
   -------------------------------------------------- */

#define HAS_5_BUTTONS

#define UP_BTN 39
#define DW_BTN 40
#define L_BTN 41
#define R_BTN 42
#define SEL_BTN 47

#define BTN_ACT LOW
#define BTN_ALIAS "\"OK\""

/* --------------------------------------------------
   Display
   -------------------------------------------------- */

#define HAS_SCREEN 1

#define USER_SETUP_LOADED 1
#define ILI9341_DRIVER 1

#define TFT_WIDTH 240
#define TFT_HEIGHT 320

#define TFT_MOSI 11
#define TFT_MISO 13
#define TFT_SCLK 12

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 14

#define TFT_BL 8
#define TFT_BACKLIGHT_ON HIGH

#define TOUCH_CS -1

#define ROTATION 1
#define MINBRIGHT ((uint8_t)1)

#define SMOOTH_FONT 1

#define SPI_FREQUENCY 10000000
#define SPI_READ_FREQUENCY 5000000
#define SPI_TOUCH_FREQUENCY 2500000

/* --------------------------------------------------
   Default SPI module bus
   -------------------------------------------------- */

#define SPI_SCK_PIN 12
#define SPI_MOSI_PIN 11
#define SPI_MISO_PIN 13
#define SPI_SS_PIN 5

/* --------------------------------------------------
   Storage disabled for first boot
   -------------------------------------------------- */

/*#define SDCARD_CS -1

/* --------------------------------------------------
   Feature defaults
   -------------------------------------------------- */

#define FP 1
#define FM 2
#define FG 3

#endif
