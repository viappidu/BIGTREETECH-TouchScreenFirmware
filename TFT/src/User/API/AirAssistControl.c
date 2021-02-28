#include "AirAssistControl.h"

static bool lastAirAssistState = true;
static bool airAssistState = false;

static bool airAssist_send_waiting = false;

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

void airAssistSendWaiting(bool isWaiting)
{
  airAssist_send_waiting = isWaiting;
}

void loopAirAssist(void)
{
  if (lastAirAssistState != airAssistState)
  {
    lastAirAssistState = airAssistState;
    if (airAssist_send_waiting == false)
    {
      if (airAssistState == false)
        airAssist_send_waiting = storeCmd("M7\n");
      else
        airAssist_send_waiting = storeCmd("M9\n");
    }
  }
}
