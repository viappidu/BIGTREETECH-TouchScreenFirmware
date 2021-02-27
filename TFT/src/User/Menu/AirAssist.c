#include "AirAssist.h"
#include "includes.h"

const ITEM itemAirAssist[2] = {
  // icon                        label
  {ICON_AIR_ASSIST,                LABEL_OFF},
  {ICON_AIR_ASSIST,                LABEL_ON},
};

static inline void updateCaseFanIcon(MENUITEMS * curmenu, bool state)
{
  curmenu->items[KEY_ICON_4] = itemAirAssist[state ? 1 : 0];
}

void airAssistReDraw()
{
  char tempstr[20];
  sprintf(tempstr, "  %d%%  ", airAssistSetSpeedPercent());
  setLargeFont(true);
  GUI_DispStringInPrect(&exhibitRect, (u8 *)tempstr);
  setLargeFont(false);
}

void menuAirAssist(void)
{
  // 1 title, ITEM_PER_PAGE items (icon + label)
  MENUITEMS airAssistItems = {
    // title
    LABEL_AIR_ASSIST,
    // icon                         label
    {{ICON_DEC,                     LABEL_DEC},
     {ICON_BACKGROUND,              LABEL_BACKGROUND},
     {ICON_BACKGROUND,              LABEL_BACKGROUND},
     {ICON_INC,                     LABEL_INC},
     {ICON_RGB_WHITE,               LABEL_ON},
     {ICON_BACKGROUND,              LABEL_BACKGROUND},
     {ICON_BACKGROUND,              LABEL_BACKGROUND},
     {ICON_BACK,                    LABEL_BACK},}
  };

  KEY_VALUES key_num = KEY_IDLE;

  // Initiate query. Value will be compared in while loop
  airAssistValueQuery();

  bool currentAirAssistState = airAssistGetState();
  bool previousAirAssistState = currentAirAssistState;
  uint8_t currentAirAssistSpeed = airAssistGetSpeed();
  uint8_t previousAirAssistSpeed = currentAirAssistSpeed;

  updateAirAssistIcon(&airAssistItems, currentAirAssistState);
  menuDrawPage(&airAssistItems);
  airAssistSpeedReDraw();

  while (infoMenu.menu[infoMenu.cur] == menuAirAssist)
  {
    key_num = menuKeyGetValue();

    switch (key_num)
    {
      case KEY_ICON_0:
        airAssistChangeSpeedPrecent(-10);
        airAssistSpeedReDraw();
        break;

      case KEY_ICON_3:
        airAssistChangeSpeedPrecent(10);
        airAssistSpeedReDraw();
        break;

      case KEY_ICON_4:
        airAssistToggleState();
        menuDrawPage(&airAssistItems);
        airAssistSpeedReDraw();
        break;

      case KEY_ICON_7:
        infoMenu.cur--;
        break;

      default:
        #if LCD_ENCODER_SUPPORT
          if (encoderPosition)
          {
            airAssistChangeSpeedPrecent(encoderPosition);
            airAssistSpeedReDraw();
            encoderPosition = 0;
          }
        #endif
        break;
    }

    currentAirAssistState = airAssistGetState();
    if (previousAirAssistState != currentAirAssistState)
    {
      // Dynamically change the pump on/off icon based on the current state
      previousAirAssistState = currentAirAssistState;
      updateAirAssistIcon(&airAssistItems, currentAirAssistState);
      menuDrawItem(&airAssistItems.items[KEY_ICON_4], KEY_ICON_4);
      airAssistSpeedReDraw();
    }

    currentAirAssistSpeed = airAssistGetSpeed();
    if (previousAirAssistSpeed != currentAirAssistSpeed)
    {
      previousAirAssistSpeed = currentAirAssistSpeed;
      airAssistSpeedReDraw();
    }

    loopProcess();
  }
}
