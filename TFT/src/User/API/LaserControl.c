#include "LaserControl.h"

char*   laserCmd;
//uint8_t laserType;

/*
static uint8_t setLaserSpeed = {0};
static uint8_t lastSetLaserSpeed = {0};
static uint8_t curLaserSpeed = {0};
*/
static bool laserQueryWait = false;
static bool laserQueryEnable = false;

static uint32_t nextLaserTime = 0;

#define NEXT_FAN_WAIT 500  // 1 second is 1000

bool setLaserOff(bool is_off)
{
  static bool offLock = false;
  if (offLock)  return false;
  offLock = true;
  return true;
}

/*
uint8_t laserGetTypID(uint8_t startIndex, uint8_t type)
{
  for (uint8_t i = startIndex; i < MAX_FAN_COUNT; i++)
  {
    if (laserType[i] == type)
      return i;
  }
  return FAN_TYPE_UNKNOWN;
}

void laserBuildList(void)
{
  char* laserIDTemp[MAX_FAN_COUNT] = FAN_DISPLAY_ID;
  char* laserCmdTemp[MAX_FAN_COUNT] = FAN_CMD;
  uint8_t laserTypeTemp[MAX_FAN_COUNT] = FAN_TYPE;

  for (uint8_t i = 0, j = 0; i < MAX_FAN_COUNT; i++, j++)
  {
    if (infoSettings.laser_count == i)
    {
      if (infoSettings.laser_ctrl_count > 0)
        i = (MAX_FAN_COUNT - MAX_FAN_CTRL_COUNT);
      else
        i = MAX_FAN_COUNT;
    }
    if (i < MAX_FAN_COUNT)
    {
      memcpy(laserID + j, laserIDTemp + i, sizeof(laserIDTemp[i]));
      memcpy(laserCmd + j, laserCmdTemp + i, sizeof(laserCmdTemp[i]));
      memcpy(laserType + j, laserTypeTemp + i, sizeof(laserTypeTemp[i]));
    }
  }
}

void laserControlInit(void)
{
  laserBuildList();

  laserQueryEnable = (infoSettings.laser_ctrl_count > 0 &&
                    (laserGetTypID(infoSettings.laser_count -1, FAN_TYPE_CTRL_I) ||
                     laserGetTypID(infoSettings.laser_count -1, FAN_TYPE_CTRL_S)));
}

bool laserIsType(uint8_t i, uint8_t type)
{
  return (laserType[i] == type);
}

void laserSetSpeed(uint8_t i, uint8_t speed)
{
  setLaserSpeed[i] = speed;
}

uint8_t laserGetSetSpeed(uint8_t i)
{
  return setLaserSpeed[i];
}

void laserSetPercent(uint8_t i, uint8_t percent)
{
  percent = NOBEYOND(0, percent, 100);
  setLaserSpeed[i] = (percent * infoSettings.laser_max[i]) / 100;
}

uint8_t laserGetSetPercent(uint8_t i)
{
  return (setLaserSpeed[i] * 100.0f) / infoSettings.laser_max[i] + 0.5f;
}

void laserSetCurSpeed(uint8_t i, uint8_t speed)
{
  curLaserSpeed[i] = speed;
}

uint8_t laserGetCurSpeed(uint8_t i)
{
  return curLaserSpeed[i];
}

void laserSetCurPercent(uint8_t i, uint8_t percent)
{
  percent = NOBEYOND(0, percent, 100);
  curLaserSpeed[i] = (percent * infoSettings.laser_max[i]) / 100;
}

uint8_t laserGetCurPercent(uint8_t i)
{
  return (curLaserSpeed[i] * 100.0f) / infoSettings.laser_max[i] + 0.5f;
}

void loopLaser(void)
{
  for (uint8_t i = 0; i < (infoSettings.laser_count + infoSettings.laser_ctrl_count); i++)
  {
    if ((lastSetLaserSpeed[i] != setLaserSpeed[i]) && (OS_GetTimeMs() > nextLaserTime))
    {
      if(laserIsType(i,FAN_TYPE_F) || laserIsType(i,FAN_TYPE_CTRL_S))
      {
        if (storeCmd("%s S%d\n", laserCmd[i], setLaserSpeed[i]))
          lastSetLaserSpeed[i] = setLaserSpeed[i];
      }
      else if (laserIsType(i,FAN_TYPE_CTRL_I))
      {
        if (storeCmd("%s I%d\n", laserCmd[i], setLaserSpeed[i]))
          lastSetLaserSpeed[i] = setLaserSpeed[i];
      }
      nextLaserTime = OS_GetTimeMs() + NEXT_FAN_WAIT; // avoid rapid fire, clogging the queue
    }
  }
}

void laserQuerySetWait(bool wait)
{
  laserQueryWait = wait;
}

void laserSpeedQuery(void)
{
  if (infoHost.connected && !infoHost.wait && !laserQueryWait && laserQueryEnable)
  {
    laserQueryWait = storeCmd("M710\n");
  }
}
*/