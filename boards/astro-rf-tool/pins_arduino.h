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

static const uint8_t TX = 43;
static const uint8_t RX = 44;

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

#define SERIAL_TX 43
#define SERIAL_RX 44

#define BAD_TX SERIAL_TX
#define BAD_RX SERIAL_RX

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

#define UP_BTN 41
#define DW_BTN 42
#define L_BTN 40
#define R_BTN 39
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
#define TFT_RGB_ORDER TFT_BGR
#define TFT_INVERSION_OFF
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 14

#define TFT_BL 8
#define TFT_BACKLIGHT_ON HIGH

#define TOUCH_CS -1

#define ROTATION 1
#define MINBRIGHT ((uint8_t)1)

#define SMOOTH_FONT 1

#define SPI_FREQUENCY 40000000
#define SPI_READ_FREQUENCY 5000000
#define SPI_TOUCH_FREQUENCY 2500000

/* --------------------------------------------------
   Default SPI module bus - TFT - CC1101 - NRF24
   -------------------------------------------------- */

#define SPI_SCK_PIN 12
#define SPI_MOSI_PIN 11
#define SPI_MISO_PIN 13
#define SPI_SS_PIN 5

/* --------------------------------------------------
   Passive buzzer
   -------------------------------------------------- */

#define BUZZ_PIN 38

/* --------------------------------------------------
   CC1101 sub-GHz radio
   Shared SPI bus with TFT
   -------------------------------------------------- */

#define USE_CC1101_VIA_SPI

#define CC1101_SS_PIN 5
#define CC1101_GDO0_PIN 6
#define CC1101_GDO2_PIN 7

#define CC1101_SCK_PIN SPI_SCK_PIN
#define CC1101_MOSI_PIN SPI_MOSI_PIN
#define CC1101_MISO_PIN SPI_MISO_PIN

/* --------------------------------------------------
   NRF24L01 2.4 GHz radio
   Shared SPI bus
   -------------------------------------------------- */

#define USE_NRF24_VIA_SPI

#define NRF24_CE_PIN 16
#define NRF24_SS_PIN 15

#define NRF24_MOSI_PIN SPI_MOSI_PIN
#define NRF24_SCK_PIN SPI_SCK_PIN
#define NRF24_MISO_PIN SPI_MISO_PIN

/* --------------------------------------------------
   MicroSD card
   Shared SPI bus
   -------------------------------------------------- */

#define SDCARD_CS 4
#define SDCARD_SCK SPI_SCK_PIN
#define SDCARD_MOSI SPI_MOSI_PIN
#define SDCARD_MISO SPI_MISO_PIN

/* --------------------------------------------------
   NEO-6M GPS — dedicated UART
   -------------------------------------------------- */

#define GPS_SERIAL_RX 17 // Receives data from GPS TX
#define GPS_SERIAL_TX 18 // Sends data to GPS RX

/* --------------------------------------------------
   Feature defaults
   -------------------------------------------------- */

#define FP 1
#define FM 2
#define FG 3

#endif
