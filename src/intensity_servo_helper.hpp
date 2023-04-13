/**
 * @file intensity_servo_helper.hpp
 * @brief Helper functions for intensity servo 
 * @date 2023-04-14
 * 
 * 
 */
#ifndef INTENSITY_SERVO_HELPER
#define INTENSITY_SERVO_HELPER

#include <stdint.h>
#include "servo_system.hpp"
#include "trigger.h"

struct PowerReading {
    uint16_t vmin, vmax, pmin, pmax;
    PowerReading() : vmin(0), vmax(1500), pmin(65535), pmax(0) {}
};

PowerReading get_best_power(PIServoSystem* const sys);

void servo_loop(uint8_t const mask);
#endif