/**
Pico Support
**/

/**
 * @brief pico support for reactor-c
 */

#ifndef LF_PICO_SUPPORT_H
#define LF_PICO_SUPPORT_H

#include <inttypes.h>

#define PRINTF_TIME "%" PRIu32
#define PRINTF_MICROSTEP "%" PRIu32
#define PRINTF_TAG "(" PRINTF_TIME ", " PRINTF_MICROSTEP ")"
#define _LF_TIMEOUT 1

// TODO: define interval_t and instant_t

#endif // LF_PICO_SUPPORT_H