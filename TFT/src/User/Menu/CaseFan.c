#include "CaseFan.h"
#include "includes.h"

const ITEM itemCaseFan[2] = {
  // icon                        label
  {ICON_CASE_FAN,                LABEL_OFF},
  {ICON_CASE_FAN,                LABEL_ON},
};

static inline void updateCaseFanIcon(MENUITEMS * curmenu, bool state)
{
  curmenu->items[KEY_ICON_4] = itemCaseFan[state ? 1 : 0];
}

void caseFanReDraw()
{
  char tempstr[20];
  sprintf(tempstr, "  %d%%  ", caseFanGetSpeedPercent());
  setLargeFont(true);
  GUI_DispStringInPrect(&exhibitRect, (u8 *)tempstr);
  setLargeFont(false);
}

void menuCaseFan(void)
{
  // 1 title, ITEM_PER_PAGE items (icon + label)
  MENUITEMS caseFanItems = {
    // title
    LABEL_CASE_FAN,
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
  caseFanValueQuery();

  bool currentCaseFanState = caseFanGetState();
  bool previousCaseFanState = currentCaseFanState;
  uint8_t currentCaseFanSpeed = caseFanGetSpeed();
  uint8_t previousCaseFanSpeed = currentCaseFanSpeed;

  updateCaseFanIcon(&caseFanItems, currentCaseFanState);
  menuDrawPage(&caseFanItems);
  caseFanSpeedReDraw();

  while (infoMenu.menu[infoMenu.cur] == menuCaseFan)
  {
    key_num = menuKeyGetValue();

    switch (key_num)
    {
      case KEY_ICON_0:
        caseFanChangeSpeedPrecent(-10);
        caseFanSpeedReDraw();
        break;

      case KEY_ICON_3:
        caseFanChangeSpeedPrecent(10);
        caseFanSpeedReDraw();
        break;

      case KEY_ICON_4:
        caseFanToggleState();
        menuDrawPage(&caseFanItems);
        caseFanSpeedReDraw();
        break;

      case KEY_ICON_7:
        infoMenu.cur--;
        break;

      default:
        #if LCD_ENCODER_SUPPORT
          if (encoderPosition)
          {
            caseFanChangeSpeedPrecent(encoderPosition);
            caseFanSpeedReDraw();
            encoderPosition = 0;
          }
        #endif
        break;
    }

    currentCaseFanState = caseFanGetState();
    if (previousCaseFanState != currentCaseFanState)
    {
      // Dynamically change the case fan on/off icon based on the current state
      previousCaseFanState = currentCaseFanState;
      updateCaseFanIcon(&caseFanItems, currentCaseFanState);
      menuDrawItem(&caseFanItems.items[KEY_ICON_4], KEY_ICON_4);
      caseFanSpeedReDraw();
    }

    currentCaseFanSpeed = caseFanGetSpeed();
    if (previousCaseFanSpeed != currentCaseFanSpeed)
    {
      previousCaseFanSpeed = currentCaseFanSpeed;
      caseFanSpeedReDraw();
    }

    loopProcess();
  }
}
