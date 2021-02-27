#include "CaseFanControl.h"

static uint8_t setCaseFanSpeed = 0;
static uint8_t lastSetCaseFanSpeed = 0;
static uint8_t curCaseFanSpeed = 0;

static bool caseFanQueryWait = false;
static bool caseFanQueryEnable = false;

static uint32_t nextCaseFanTime = 0;

#define NEXT_FAN_WAIT 500  // 1 second is 1000

void caseFanSetSpeed(uint8_t speed)
{
  setCaseFanSpeed = speed;
}

uint8_t caseFanGetSetSpeed(void)
{
  return setCaseFanSpeed;
}

void caseFanSetPercent(uint8_t percent)
{
  percent = NOBEYOND(0, percent, 100);
  setCaseFanSpeed = (percent * 255) / 100;
}

uint8_t caseFanGetSetPercent(void)
{
  return (setCaseFanSpeed * 100.0f) / 255 + 0.5f;
}

void caseFanSetCurSpeed(uint8_t speed)
{
  curCaseFanSpeed = speed;
}

uint8_t caseFanGetCurSpeed(void)
{
  return curCaseFanSpeed;
}

void caseFanSetCurPercent(uint8_t percent)
{
  percent = NOBEYOND(0, percent, 100);
  curCaseFanSpeed = (percent * 255) / 100;
}

uint8_t caseFanGetCurPercent(void)
{
  return (curCaseFanSpeed * 100.0f) / 255 + 0.5f;
}

void loopCaseFan(void)
{
  if ((lastSetCaseFanSpeed != setCaseFanSpeed) && (OS_GetTimeMs() > nextCaseFanTime))
  {
    if (storeCmd("M106 P%d S%d\n", infoSettings.case_fan, setCaseFanSpeed))
        lastSetCaseFanSpeed = setCaseFanSpeed;
    nextCaseFanTime = OS_GetTimeMs() + NEXT_FAN_WAIT; // avoid rapid fire, clogging the queue
  }
}

void caseFanQuerySetWait(bool wait)
{
  caseFanQueryWait = wait;
}

