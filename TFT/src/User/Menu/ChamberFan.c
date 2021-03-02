#include "ChamberFan.h"
#include "includes.h"

//TODO: move type=1 logic to common menu

void chamberFanValueReDraw(bool skip_header)
{
  char tempstr[20];

  if (!skip_header)
  {
    setLargeFont(true);
    if (infoSettings.chamber_fan_type != 8)
    {
      if (infoSettings.fan_percentage == 1)
        GUI_DispStringCenter((exhibitRect.x0 + exhibitRect.x1)>>1, exhibitRect.y0, (uint8_t *)"%");
      else
        GUI_DispStringCenter((exhibitRect.x0 + exhibitRect.x1)>>1, exhibitRect.y0, (uint8_t *)"PWM");
    }
    setLargeFont(false);
  }

  if (infoSettings.chamber_fan_type == 8)
  {
    sprintf(tempstr, "  %s  ", (int)fanGetSetSpeed(infoSettings.chamber_fan) == (int)infoSettings.fan_max[infoSettings.chamber_fan] ? textSelect(LABEL_ON) : textSelect(LABEL_OFF));
  }
  else
  {
    if (infoSettings.fan_percentage == 1)
      sprintf(tempstr, "  %d/%d  ",  fanGetCurPercent(infoSettings.chamber_fan), fanGetSetPercent(infoSettings.chamber_fan));
    else
      sprintf(tempstr, "  %d/%d  ", (int)fanGetCurSpeed(infoSettings.chamber_fan), (int)fanGetSetSpeed(infoSettings.chamber_fan));
    setLargeFont(true);
    GUI_DispStringInPrect(&exhibitRect, (u8 *)tempstr);
    setLargeFont(false);
  }
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

  switch (infoSettings.chamber_fan_type)
  {
    case 0:
    case 1:
    case 2:
    case 8:
      fanSetSpeed(infoSettings.chamber_fan, fanGetCurSpeed(infoSettings.chamber_fan));
      break;
    case 9:
    default:
      break;
  }


  menuDrawPage(&chamberFanItems);
  chamberFanValueReDraw(false);

  #if LCD_ENCODER_SUPPORT
    encoderPosition = 0;
  #endif

  while (infoMenu.menu[infoMenu.cur] == menuChamberFan)
  {
    KEY_VALUES key_num = menuKeyGetValue();
    switch (key_num)
    {
      case KEY_ICON_0:
        if (fanGetSetSpeed(infoSettings.chamber_fan)  != 8 && (fanGetSetSpeed(infoSettings.chamber_fan) > 0))
        {
          if (infoSettings.fan_percentage == 1)
            fanSetPercent(infoSettings.chamber_fan, fanGetSetPercent(infoSettings.chamber_fan) - 1);
          else
            fanSetSpeed(infoSettings.chamber_fan, fanGetSetSpeed(infoSettings.chamber_fan) - 1);
        }
        chamberFanValueReDraw(true)
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
        if (fanGetSetSpeed(infoSettings.chamber_fan_type)  != 8 && (fanGetSetSpeed(infoSettings.chamber_fan) < infoSettings.fan_max[infoSettings.chamber_fan]))
        {
          if (infoSettings.fan_percentage == 1)
            fanSetPercent(infoSettings.chamber_fan, fanGetSetSpeed(infoSettings.chamber_fan) + 1);
          else
            fanSetSpeed(infoSettings.chamber_fan, fanGetSetSpeed(infoSettings.chamber_fan) + 1);
        }
        chamberFanValueReDraw(true);
        break;

      case KEY_ICON_4:
        if (infoSettings.chamber_fan_type != 8)
          fanSetSpeed(infoSettings.chamber_fan, infoSettings.fan_max[infoSettings.air_assist_fan] / 2);  // 50%
        else
          fanSetSpeed(infoSettings.chamber_fan, infoSettings.fan_max[infoSettings.air_assist_fan]);  // On
        chamberFanValueReDraw(true);
        break;

      case KEY_ICON_5:
        fanSetSpeed(infoSettings.chamber_fan, infoSettings.fan_max[infoSettings.chamber_fan]);
        break;

      case KEY_ICON_6:
        if (infoSettings.chamber_fan_type != 8)
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
