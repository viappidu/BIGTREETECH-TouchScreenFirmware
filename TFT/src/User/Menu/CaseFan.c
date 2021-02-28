#include "CaseFan.h"
#include "includes.h"

void caseFanSpeedReDraw(bool skip_header)
{
  char tempstr[20];

  if (!skip_header)
  {
    setLargeFont(true);
    if (infoSettings.fan_percentage == 1)
    {
      GUI_DispStringCenter((exhibitRect.x0 + exhibitRect.x1)>>1, exhibitRect.y0, (uint8_t *)"%");
    }
    else
    {
      GUI_DispStringCenter((exhibitRect.x0 + exhibitRect.x1)>>1, exhibitRect.y0, (uint8_t *)"PWM");
    }
    setLargeFont(false);
  }

  if (infoSettings.fan_percentage == 1)
    sprintf(tempstr, "  %d/%d  ",  fanGetCurPercent(infoSettings.case_fan), fanGetSetPercent(infoSettings.case_fan));
  else
    sprintf(tempstr, "  %d/%d  ", (int)fanGetCurSpeed(infoSettings.case_fan), (int)fanGetSetSpeed(infoSettings.case_fan));

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

  LASTFAN lastFan;
  fanSetSpeed(infoSettings.case_fan, fanGetCurSpeed(infoSettings.case_fan));

  menuDrawPage(&caseFanItems);
  caseFanSpeedReDraw(false);

  #if LCD_ENCODER_SUPPORT
    encoderPosition = 0;
  #endif

  while (infoMenu.menu[infoMenu.cur] == menuCaseFan)
  {
    KEY_VALUES key_num = menuKeyGetValue();
    switch (key_num)
    {
      case KEY_ICON_0:
        if (fanGetSetSpeed(infoSettings.case_fan) > 0)
        {
          if (infoSettings.fan_percentage == 1)
            fanSetPercent(infoSettings.case_fan, fanGetSetPercent(infoSettings.case_fan) - 1);
          else
            fanSetSpeed(infoSettings.case_fan, fanGetSetSpeed(infoSettings.case_fan) - 1);
        }
        break;

      case KEY_INFOBOX:
      {
        char titlestr[30];
        if (infoSettings.fan_percentage == 1)
        {
          strcpy(titlestr, "Min:0 | Max:100");
          uint8_t val = numPadInt((u8 *) titlestr, fanGetSetPercent(infoSettings.case_fan), 0, false);
          val = NOBEYOND(0, val, 100);

          if (val != fanGetSetPercent(infoSettings.case_fan))
            fanSetPercent(infoSettings.case_fan, val);
        }
        else
        {
          sprintf(titlestr, "Min:0 | Max:%d", infoSettings.fan_max[infoSettings.case_fan]);
          uint8_t val = numPadInt((u8 *) titlestr, fanGetCurSpeed(infoSettings.case_fan), 0, false);
          val = NOBEYOND(0, val,  infoSettings.fan_max[infoSettings.case_fan]);

          if (val != fanGetCurSpeed(infoSettings.case_fan))
            fanSetSpeed(infoSettings.case_fan, val);
        }

        menuDrawPage(&caseFanItems);
        caseFanSpeedReDraw(true);
        break;
      }

      case KEY_ICON_3:
        if (fanGetSetSpeed(infoSettings.case_fan) < infoSettings.fan_max[infoSettings.case_fan])
        {
          if (infoSettings.fan_percentage == 1)
            fanSetPercent(infoSettings.case_fan, fanGetSetPercent(infoSettings.case_fan) + 1);
          else
            fanSetSpeed(infoSettings.case_fan, fanGetSetSpeed(infoSettings.case_fan) + 1);
        }
        break;

      case KEY_ICON_4:
        fanSetSpeed(infoSettings.case_fan, infoSettings.fan_max[infoSettings.case_fan] / 2);  // 50%
        caseFanSpeedReDraw(true);
        break;

      case KEY_ICON_5:
        fanSetSpeed(infoSettings.case_fan, infoSettings.fan_max[infoSettings.case_fan]);
        break;

      case KEY_ICON_6:
        fanSetSpeed(infoSettings.case_fan, 0);
        break;

      case KEY_ICON_7:
        infoMenu.cur--;
        break;

      default:
        #if LCD_ENCODER_SUPPORT
          if (encoderPosition)
          {
            if (fanGetSetSpeed(infoSettings.case_fan) < infoSettings.fan_max[infoSettings.case_fan] && encoderPosition > 0)
            {
              if (infoSettings.fan_percentage == 1)
                fanSetPercent(infoSettings.case_fan, fanGetSetPercent(infoSettings.case_fan) + 1);
              else
                fanSetSpeed(infoSettings.case_fan, fanGetSetSpeed(infoSettings.case_fan) + 1);
            }

            if (fanGetSetSpeed(infoSettings.case_fan) > 0 && encoderPosition < 0)
            {
              if (infoSettings.fan_percentage == 1)
                fanSetPercent(infoSettings.case_fan, fanGetSetPercent(infoSettings.case_fan) - 1);
              else
                fanSetSpeed(infoSettings.case_fan, fanGetSetSpeed(infoSettings.case_fan) - 1);
            }
            encoderPosition = 0;
          }
        #endif
        break;
    }

    if ((lastFan.cur != fanGetCurSpeed(infoSettings.case_fan)) || (lastFan.set != fanGetSetSpeed(infoSettings.case_fan)))
    {
      lastFan = (LASTFAN) {fanGetCurSpeed(infoSettings.case_fan), fanGetSetSpeed(infoSettings.case_fan)};
      caseFanSpeedReDraw(true);
    }
    loopProcess();
  }
}
