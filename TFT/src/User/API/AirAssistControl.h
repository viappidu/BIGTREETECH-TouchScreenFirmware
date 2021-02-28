#ifndef _AIRPUMPCONTROL_H_
#define _AIRPUMPCONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "includes.h"

bool  airAssistGetState(void);
void  airAssistSetState(bool state);
void  airAssistToggleState(void);
void  airAssistControlInit(void);
void  loopAirAssist(void);

#ifdef __cplusplus
}
#endif

#endif
