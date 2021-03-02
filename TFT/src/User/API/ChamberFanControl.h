#ifndef _CHAMBERFANCONTROL_H_
#define _CHAMBERFANCONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "includes.h"

void    chamberFanSetSpeed(uint8_t speed);
uint8_t chamberFanGetSetSpeed(void);
void    chamberFanSetPercent(uint8_t percent);
uint8_t chamberFanGetSetPercent(void);
void    chamberFanSetCurSpeed(uint8_t speed);
uint8_t chamberFanGetCurSpeed(void);
void    chamberFanSetCurPercent(uint8_t percent);
uint8_t chamberFanGetCurPercent(void);
void    chamberFanControlInit(void);
void    loopChamberFan(void);
void    chamberFanQuerySetWait(bool wait);

#ifdef __cplusplus
}
#endif

#endif
