#include "ChamberFan.h"
#include "includes.h"

void chamberFanSpeedReDraw()
{
  char tempstr[20];

  if (infoSettings.fan_percentage == 1)
    sprintf(tempstr, "  %d/%d  ", chamberFanGetCurPercent(), chamberFanGetSetPercent());
  else
    sprintf(tempstr, "  %d/%d  ", (int)chamberFanGetCurSpeed(), (int)chamberFanGetSetSpeed());

  setLargeFont(true);
  GUI_DispStringInPrect(&exhibitRect, (u8 *)tempstr);
  setLargeFont(false);
}

void menuChamberFan(void)
{
  // 1 title, ITEM_PER_PAGE items (icon + label)
  MENUITEMS chamberFanItems = {
    // title
    LABEL_CHAMBER_FAN,
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

  chamberFanSetSpeed(chamberFanGetCurSpeed());

  menuDrawPage(&chamberFanItems);
  chamberFanSpeedReDraw();

  #if LCD_ENCODER_SUPPORT
    encoderPosition = 0;
  #endif

  while (infoMenu.menu[infoMenu.cur] == menuChamberFan)
  {
    KEY_VALUES key_num = menuKeyGetValue();
    switch (key_num)
    {
      case KEY_ICON_0:
        if (chamberFanGetSetSpeed() > 0)
        {
          if (infoSettings.fan_percentage == 1)
            chamberFanSetPercent(chamberFanGetSetPercent() - 1);
          else
            chamberFanSetSpeed(chamberFanGetSetSpeed() - 1);
        }
        break;

      case KEY_INFOBOX:
      {
        char titlestr[30];
        if (infoSettings.fan_percentage == 1)
        {
          strcpy(titlestr, "Min:0 | Max:100");
          uint8_t val = numPadInt((u8 *) titlestr, chamberFanGetSetPercent(), 0, false);
          val = NOBEYOND(0, val, 100);

          if (val != chamberFanGetSetPercent())
            chamberFanSetPercent(val);
        }
        else
        {
          sprintf(titlestr, "Min:0 | Max:%d", 255);
          uint8_t val = numPadInt((u8 *) titlestr, chamberFanGetCurSpeed(), 0, false);
          val = NOBEYOND(0, val,  255);

          if (val != chamberFanGetCurSpeed())
            chamberFanSetSpeed(val);
        }

        menuDrawPage(&chamberFanItems);
        chamberFanSpeedReDraw();
        break;
      }

      case KEY_ICON_3:
        if (chamberFanGetSetSpeed() < 255)
        {
          if (infoSettings.fan_percentage == 1)
            chamberFanSetPercent(chamberFanGetSetPercent() + 1);
          else
            chamberFanSetSpeed( chamberFanGetSetSpeed() + 1);
        }
        break;

      case KEY_ICON_4:
        chamberFanSetSpeed(255 / 2);  // 50%
        break;

      case KEY_ICON_5:
        chamberFanSetSpeed(255);
        break;

      case KEY_ICON_6:
        chamberFanSetSpeed(0);
        break;

      case KEY_ICON_7:
        infoMenu.cur--;
        break;

      default:
        #if LCD_ENCODER_SUPPORT
          if (encoderPosition)
          {
            if (chamberFanGetSetSpeed() < 255 && encoderPosition > 0)
            {
              if (infoSettings.fan_percentage == 1)
                chamberFanSetPercent(chamberFanGetSetPercent() + 1);
              else
                chamberFanSetSpeed(chamberFanGetSetSpeed() + 1);
            }

            if (chamberFanGetSetSpeed() > 0 && encoderPosition < 0)
            {
              if (infoSettings.fan_percentage == 1)
                chamberFanSetPercent(chamberFanGetSetPercent() - 1);
              else
                chamberFanSetSpeed(chamberFanGetSetSpeed() - 1);
            }
            encoderPosition = 0;
          }
        #endif
        break;
    }

    loopProcess();
  }
}
