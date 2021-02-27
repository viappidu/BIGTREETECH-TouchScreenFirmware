#include "CaseFan.h"
#include "includes.h"

void caseFanSpeedReDraw()
{
  char tempstr[20];

  if (infoSettings.fan_percentage == 1)
    sprintf(tempstr, "  %d/%d  ", caseFanGetCurPercent(), caseFanGetSetPercent());
  else
    sprintf(tempstr, "  %d/%d  ", (int)caseFanGetCurSpeed(), (int)caseFanGetSetSpeed());

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
     {ICON_FAN_HALF_SPEED ,         LABEL_HALF},
     {ICON_FAN_FULL_SPEED,          LABEL_FULL},
     {ICON_STOP,                    LABEL_STOP},
     {ICON_BACK,                    LABEL_BACK},}
  };

  caseFanSetSpeed(caseFanGetCurSpeed());

  menuDrawPage(&caseFanItems);
  caseFanSpeedReDraw();

  #if LCD_ENCODER_SUPPORT
    encoderPosition = 0;
  #endif

  while (infoMenu.menu[infoMenu.cur] == menuCaseFan)
  {
    KEY_VALUES key_num = menuKeyGetValue();
    switch (key_num)
    {
      case KEY_ICON_0:
        if (caseFanGetSetSpeed() > 0)
        {
          if (infoSettings.fan_percentage == 1)
            caseFanSetPercent(caseFanGetSetPercent() - 1);
          else
            caseFanSetSpeed(caseFanGetSetSpeed() - 1);
        }
        break;

      case KEY_INFOBOX:
      {
        char titlestr[30];
        if (infoSettings.fan_percentage == 1)
        {
          strcpy(titlestr, "Min:0 | Max:100");
          uint8_t val = numPadInt((u8 *) titlestr, caseFanGetSetPercent(), 0, false);
          val = NOBEYOND(0, val, 100);

          if (val != caseFanGetSetPercent())
            caseFanSetPercent(val);
        }
        else
        {
          sprintf(titlestr, "Min:0 | Max:%d", 255);
          uint8_t val = numPadInt((u8 *) titlestr, caseFanGetCurSpeed(), 0, false);
          val = NOBEYOND(0, val,  255);

          if (val != caseFanGetCurSpeed())
            caseFanSetSpeed(val);
        }

        menuDrawPage(&caseFanItems);
        caseFanSpeedReDraw();
        break;
      }

      case KEY_ICON_3:
        if (caseFanGetSetSpeed() < 255)
        {
          if (infoSettings.fan_percentage == 1)
            caseFanSetPercent(caseFanGetSetPercent() + 1);
          else
            caseFanSetSpeed( caseFanGetSetSpeed() + 1);
        }
        break;

      case KEY_ICON_4:
        caseFanSetSpeed(255 / 2);  // 50%
        break;

      case KEY_ICON_5:
        caseFanSetSpeed(255);
        break;

      case KEY_ICON_6:
        caseFanSetSpeed(0);
        break;

      case KEY_ICON_7:
        infoMenu.cur--;
        break;

      default:
        #if LCD_ENCODER_SUPPORT
          if (encoderPosition)
          {
            if (caseFanGetSetSpeed() < 255 && encoderPosition > 0)
            {
              if (infoSettings.fan_percentage == 1)
                caseFanSetPercent(caseFanGetSetPercent() + 1);
              else
                caseFanSetSpeed(caseFanGetSetSpeed() + 1);
            }

            if (caseFanGetSetSpeed() > 0 && encoderPosition < 0)
            {
              if (infoSettings.fan_percentage == 1)
                caseFanSetPercent(caseFanGetSetPercent() - 1);
              else
                caseFanSetSpeed(caseFanGetSetSpeed() - 1);
            }
            encoderPosition = 0;
          }
        #endif
        break;
    }

    loopProcess();
  }
}
