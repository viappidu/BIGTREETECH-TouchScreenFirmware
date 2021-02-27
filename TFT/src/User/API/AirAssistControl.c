#include "AirAssistControl.h"

static uint8_t setAirAssistSpeed = 0;
static uint8_t lastSetAirAssistSpeed = 0;
static uint8_t curAirAssistSpeed = 0;
static bool lastAirAssistState = true;
static bool airAssistState = true;

static bool airAssistQueryWait = false;
static bool airAssistQueryEnable = false;

static uint32_t nextAirAssistTime = 0;

#define NEXT_AIRPUMP_WAIT 500  // 1 second is 1000

bool airAssistGetState(void)
{
  return airAssistState;
}

void airAssistSetState(bool state)
{
  airAssistState = state;
}

void airAssistToggleState(void)
{
  airAssistState = !airAssistState;
}

void airAssistSetSpeed(uint8_t speed)
{
  setAirAssistSpeed = speed;
}

uint8_t airAssistGetSetSpeed(void)
{
  return setAirAssistSpeed;
}

void airAssistSetPercent(uint8_t percent)
{
  percent = NOBEYOND(0, percent, 100);
  setAirAssistSpeed = (percent * 255) / 100;
}

uint8_t airAssistGetSetPercent(void)
{
  return (setAirAssistSpeed * 100.0f) / 255 + 0.5f;
}

void airAssistSetCurSpeed(uint8_t speed)
{
  curAirAssistSpeed = speed;
}

uint8_t airAssistGetCurSpeed(void)
{
  return curAirAssistSpeed;
}

void airAssistSetCurPercent(uint8_t percent)
{
  percent = NOBEYOND(0, percent, 100);
  curAirAssistSpeed = (percent * 255) / 100;
}

uint8_t airAssistGetCurPercent(void)
{
  return (curAirAssistSpeed * 100.0f) / 255 + 0.5f;
}

void loopAirAssist(void)
{
  if ((lastSetAirAssistSpeed != setAirAssistSpeed) && (OS_GetTimeMs() > nextAirAssistTime))
  {
    if (storeCmd("M106 P%d S%d\n", (char)infoSettings.air_assist_type, setAirAssistSpeed))
        lastSetAirAssistSpeed = setAirAssistSpeed;
    nextAirAssistTime = OS_GetTimeMs() + NEXT_AIRPUMP_WAIT; // avoid rapid fire, clogging the queue
  }
}

void airAssistQuerySetWait(bool wait)
{
  airAssistQueryWait = wait;
}

