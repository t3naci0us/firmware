#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include "soc/soc_caps.h"
#include <stdint.h>

/*
 * Astro RF Tool
 * ESP32-S3-N16R8
 *
 * TFT wiring:
 * MOSI = GPIO11
 * SCK  = GPIO12
 * CS   = GPIO10
 * DC   = GPIO9
 * RST  = GPIO14
 * BL   = permanently connected to 3.3V
 */

/* ---------------------------------------------------------
   Default serial / UART
   --------------------------------------------------------- */

static const uint8_t TX = 18;
static const uint8_t RX = 17;

// Default ESP32-S3 SPI pins
static const uint8_t SS = 5;
static const uint8_t MOSI = 11;
static const uint8_t MISO = 13;
static const uint8_t SCK = 12;

#define SERIAL_RX 17
#define SERIAL_TX 18

#define BAD_RX SERIAL_RX
#define BAD_TX SERIAL_TX

#define GPS_SERIAL_RX 17
#define GPS_SERIAL_TX 18

#define USB_as_HID 1

/* ---------------------------------------------------------
   I2C — PN532
   --------------------------------------------------------- */

static const uint8_t SDA = 1;
static const uint8_t SCL = 2;

#define GROVE_SDA 1
#define GROVE_SCL 2

#define SYS_I2C_SDA 1
#define SYS_I2C_SCL 2

/* ---------------------------------------------------------
   Five-way controls
   --------------------------------------------------------- */

#define BTN_ALIAS "\"OK\""
#define HAS_5_BUTTONS

#define UP_BTN 39
#define DW_BTN 40
#define L_BTN 42
#define R_BTN 41
#define SEL_BTN 47

#define BTN_ACT LOW

/* ---------------------------------------------------------
   IR
   --------------------------------------------------------- */

#define TXLED 8
#define RXLED 21

#define LED_ON HIGH
#define LED_OFF LOW

/* ---------------------------------------------------------
   TFT display
   --------------------------------------------------------- */

#define HAS_SCREEN 1
#define ROTATION 1
#define MINBRIGHT (uint8_t)1

#define USER_SETUP_LOADED 1

#define ILI9341_DRIVER

#define TFT_WIDTH 240
#define TFT_HEIGHT 320

#define TFT_MOSI 11
#define TFT_MISO 13
#define TFT_SCLK 12
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 14

#define TOUCH_CS -1

#define SMOOTH_FONT 1

#define SPI_FREQUENCY 10000000
#define SPI_READ_FREQUENCY 5000000
#define SPI_TOUCH_FREQUENCY 2500000

/* ---------------------------------------------------------
   MicroSD
   --------------------------------------------------------- */

#define SDCARD_CS 4
#define SDCARD_SCK 12
#define SDCARD_MOSI 11
#define SDCARD_MISO 13

/* ---------------------------------------------------------
   Shared RF SPI bus
   --------------------------------------------------------- */

#define SPI_SCK_PIN 12
#define SPI_MOSI_PIN 11
#define SPI_MISO_PIN 13
#define SPI_SS_PIN 5

/* ---------------------------------------------------------
   CC1101
   --------------------------------------------------------- */

#define USE_CC1101_VIA_SPI

#define CC1101_SS_PIN 5
#define CC1101_GDO0_PIN 6
#define CC1101_GDO2_PIN 7

#define CC1101_MOSI_PIN SPI_MOSI_PIN
#define CC1101_SCK_PIN SPI_SCK_PIN
#define CC1101_MISO_PIN SPI_MISO_PIN

/* ---------------------------------------------------------
   NRF24L01
   --------------------------------------------------------- */

#define USE_NRF24_VIA_SPI

#define NRF24_SS_PIN 15
#define NRF24_CE_PIN 16

#define NRF24_MOSI_PIN SPI_MOSI_PIN
#define NRF24_SCK_PIN SPI_SCK_PIN
#define NRF24_MISO_PIN SPI_MISO_PIN

/* ---------------------------------------------------------
   Buzzer
   --------------------------------------------------------- */

#define BUZZ_PIN 38

/* ---------------------------------------------------------
   Bruce frequency presets
   --------------------------------------------------------- */

#define FP 1
#define FM 2
#define FG 3

#endif /* Pins_Arduino_h */
