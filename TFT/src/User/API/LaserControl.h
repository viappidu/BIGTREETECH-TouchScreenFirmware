#ifndef _LASERCONTROL_H_
#define _LASERCONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "includes.h"

#define FAN_TYPE_F        0  // Default cooling laser
#define FAN_TYPE_CTRL_S   1  // Controller FAN on Stepper/Bed On  (Check - Marlin M710)
#define FAN_TYPE_CTRL_I   2  // Controller FAN on Idle            (Check - Marlin M710)
#define FAN_TYPE_UNKNOWN  8  // Unknown / Not defined!

extern char*   laserCmd;
extern uint8_t laserType;

bool    setLaserOff(bool is_off);
/*
bool    laserIsType(uint8_t i, uint8_t type);
uint8_t laserGetTypID(uint8_t startIndex, uint8_t type);
void    laserSetSpeed(uint8_t i, uint8_t speed);
uint8_t laserGetSetSpeed(uint8_t i);
void    laserSetPercent(uint8_t i, uint8_t percent);
uint8_t laserGetSetPercent(uint8_t i);
void    laserSetCurSpeed(uint8_t i, uint8_t speed);
uint8_t laserGetCurSpeed(uint8_t i);
void    laserSetCurPercent(uint8_t i, uint8_t percent);
uint8_t laserGetCurPercent(uint8_t i);
void    laserControlInit(void);
void    loopLaser(void);
bool    LaserChanged(uint8_t i);
void    laserSpeedQuery(void);
void    laserQuerySetWait(bool wait);
*/

#ifdef __cplusplus
}
#endif

#endif
