#ifndef _AIRPUMPCONTROL_H_
#define _AIRPUMPCONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "includes.h"

bool    airAssistGetState(void);
void    airAssistSetState(bool state);
void    airAssistToggleState(void);
void    airAssistSetSpeed(uint8_t speed);
uint8_t airAssistGetSetSpeed(void);
void    airAssistSetPercent(uint8_t percent);
uint8_t airAssistGetSetPercent(void);
void    airAssistSetCurSpeed(uint8_t speed);
uint8_t airAssistGetCurSpeed(void);
void    airAssistSetCurPercent(uint8_t percent);
uint8_t airAssistGetCurPercent(void);
void    airAssistControlInit(void);
void    loopAirAssist(void);
void    airAssistQuerySetWait(bool wait);

#ifdef __cplusplus
}
#endif

#endif
