#ifndef _CASEFANCONTROL_H_
#define _CASEFANCONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "includes.h"

void    caseFanSetSpeed(uint8_t speed);
uint8_t caseFanGetSetSpeed(void);
void    caseFanSetPercent(uint8_t percent);
uint8_t caseFanGetSetPercent(void);
void    caseFanSetCurSpeed(uint8_t speed);
uint8_t caseFanGetCurSpeed(void);
void    caseFanSetCurPercent(uint8_t percent);
uint8_t caseFanGetCurPercent(void);
void    caseFanControlInit(void);
void    loopCaseFan(void);
void    caseFanQuerySetWait(bool wait);

#ifdef __cplusplus
}
#endif

#endif
