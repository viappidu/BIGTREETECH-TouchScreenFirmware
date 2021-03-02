#include "ChamberFanControl.h"

static uint8_t setChamberFanSpeed = 0;
static uint8_t lastSetChamberFanSpeed = 0;
static uint8_t curChamberFanSpeed = 0;

static bool chamberFanQueryWait = false;
static bool chamberFanQueryEnable = false;

static uint32_t nextChamberFanTime = 0;

#define NEXT_FAN_WAIT 500  // 1 second is 1000

void chamberFanSetSpeed(uint8_t speed)
{
  setChamberFanSpeed = speed;
}

uint8_t chamberFanGetSetSpeed(void)
{
  return setChamberFanSpeed;
}

void chamberFanSetPercent(uint8_t percent)
{
  percent = NOBEYOND(0, percent, 100);
  setChamberFanSpeed = (percent * 255) / 100;
}

uint8_t chamberFanGetSetPercent(void)
{
  return (setChamberFanSpeed * 100.0f) / 255 + 0.5f;
}

void chamberFanSetCurSpeed(uint8_t speed)
{
  curChamberFanSpeed = speed;
}

uint8_t chamberFanGetCurSpeed(void)
{
  return curChamberFanSpeed;
}

void chamberFanSetCurPercent(uint8_t percent)
{
  percent = NOBEYOND(0, percent, 100);
  curChamberFanSpeed = (percent * 255) / 100;
}

uint8_t chamberFanGetCurPercent(void)
{
  return (curChamberFanSpeed * 100.0f) / 255 + 0.5f;
}

void loopChamberFan(void)
{
  if ((lastSetChamberFanSpeed != setChamberFanSpeed) && (OS_GetTimeMs() > nextChamberFanTime))
  {
    if (storeCmd("M106 P%d S%d\n", infoSettings.chamber_fan, setChamberFanSpeed))
        lastSetChamberFanSpeed = setChamberFanSpeed;
    nextChamberFanTime = OS_GetTimeMs() + NEXT_FAN_WAIT; // avoid rapid fire, clogging the queue
  }
}

void chamberFanQuerySetWait(bool wait)
{
  chamberFanQueryWait = wait;
}

