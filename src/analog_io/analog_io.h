/**
 * @file analog_io.h
 * @author Li Putian
 * @brief Master header for analog IO library
 * @version 0.3
 * @date 2024-04-06
 *
 */

#ifndef ANALOG_IO_H
#define ANALOG_IO_H

#include <Arduino.h>

/**
 * \name Analog Read
 * @{
 */

/**
 * \name ADC single read
 * @{
 */
#define AIN0 0
#define BIN0 1
#define AIN1 2
#define BIN1 3

/**
 * @brief Read from channel ch
 *
 * @param ch ADC channel, must be either of AIN0, BIN0, AIN1, BIN1
 * @return uint16_t the ADC number of the requested channel
 *
 */
uint16_t analogio_read(uint8_t const ch);
// @}

/**
 * \name ADC pair read
 * @{
 */
#define CH0 0
#define CH1 1

// @}

// @}

/**
 * \name Analog Write
 * @{
 */

/**
 * @brief Write num to channel ch
 * 
 * @note ch has to be from {0, 1, 2, 3}
 * 
 */
extern void (&analogio_write)(uint8_t const ch, uint16_t const num);
// @}

/**
 * @name Digital Read
 *
 */
// @{
/**
 * @brief Alias of \c digitalReadFast of Teensy.
 *
 * The usage is the same as Arduino's <a href="https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/">digitalRead</a>.
 */
extern decltype(digitalReadFast)& digitalio_read;
/**
 * @brief Alias of \c digitalWriteFast of Teensy.
 *
 * The usage is the same as Arduino's <a href="https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/">digitalWrite</a>.
 */
extern decltype(digitalWriteFast)& digitalio_write;
/**
 * @brief Alias of \c pinMode of Teensy.
 *
 * The usage is the same as Arduino's <a href="https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/">pinMode</a>.
 */
extern decltype(pinMode)& digitalio_mode;
// @}

#endif