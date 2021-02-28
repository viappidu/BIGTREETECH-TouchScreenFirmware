#include "AirAssist.h"
#include "includes.h"


//TODO: move type=1 logic to common menu

void airAssistValueReDraw(bool skip_header)
{
  char tempstr[20];
  
  if (!skip_header)
  {
    setLargeFont(true);
    if (infoSettings.air_assist_type != 1)
    {
      if (infoSettings.fan_percentage == 1)
              GUI_DispStringCenter((exhibitRect.x0 + exhibitRect.x1)>>1, exhibitRect.y0, (uint8_t *)"%");
      else
        GUI_DispStringCenter((exhibitRect.x0 + exhibitRect.x1)>>1, exhibitRect.y0, (uint8_t *)"PWM");
    }
    setLargeFont(false);
  }

  if (infoSettings.air_assist_type == 1)
    sprintf(tempstr, "  %s  ", airAssistGetState() ? textSelect(LABEL_ON) : textSelect(LABEL_OFF));
  else if (infoSettings.fan_percentage == 1)
    sprintf(tempstr, "  %d/%d  ",  fanGetCurPercent(infoSettings.case_fan), fanGetSetPercent(infoSettings.case_fan));
  else
    sprintf(tempstr, "  %d/%d  ", (int)fanGetCurSpeed(infoSettings.case_fan), (int)fanGetSetSpeed(infoSettings.case_fan));

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
    {{ICON_DEC,                    LABEL_DEC},
    {ICON_BACKGROUND,              LABEL_BACKGROUND},
    {ICON_BACKGROUND,              LABEL_BACKGROUND},
    {ICON_INC,                     LABEL_INC},
    {ICON_FAN_HALF_SPEED ,         LABEL_HALF},
    {ICON_FAN_FULL_SPEED,          LABEL_FULL},
    {ICON_STOP,                    LABEL_STOP},
    {ICON_BACK,                    LABEL_BACK},}
  };
  
  if (infoSettings.air_assist_type == 1)
  {
    airAssistItems.items[0].icon = ICON_BACKGROUND;
    airAssistItems.items[0].label.index = LABEL_BACKGROUND;
    airAssistItems.items[3].icon = ICON_BACKGROUND;
    airAssistItems.items[3].label.index = LABEL_BACKGROUND;
    airAssistItems.items[4].icon = ICON_AIR_ASSIST;
    airAssistItems.items[4].label.index = LABEL_ON;
    airAssistItems.items[5].icon = ICON_STOP;
    airAssistItems.items[5].label.index = LABEL_STOP;
    airAssistItems.items[6].icon = ICON_BACKGROUND;
    airAssistItems.items[6].label.index = LABEL_BACKGROUND;

  }

  LASTFAN lastFan;
  switch (infoSettings.air_assist_type)
  {
    case 1:
      break;
    
    case 2:
      fanSetSpeed(infoSettings.air_assist_fan, fanGetCurSpeed(infoSettings.air_assist_fan));
      break;
    case 3:
      break;
    default:
      break;
  }

  menuDrawPage(&airAssistItems);
  airAssistValueReDraw(false);

  #if LCD_ENCODER_SUPPORT
    encoderPosition = 0;
  #endif

  while (infoMenu.menu[infoMenu.cur] == menuAirAssist)
  {
    KEY_VALUES key_num = menuKeyGetValue();
    switch (key_num)
    {
      //TODO: Fix for type 1?
      case KEY_ICON_0:
        if (fanGetSetSpeed(infoSettings.air_assist_fan) != 1)
        {
          if (infoSettings.fan_percentage == 1)
            fanSetPercent(infoSettings.air_assist_fan, fanGetSetPercent(infoSettings.air_assist_fan) - 1);
          else
            fanSetSpeed(infoSettings.air_assist_fan, fanGetSetSpeed(infoSettings.air_assist_fan) - 1);
        }
        break;

      case KEY_INFOBOX:
      {
        if (infoSettings.air_assist_type != 1)
        {
          char titlestr[30];
          if (infoSettings.fan_percentage == 1)
          {
            strcpy(titlestr, "Min:0 | Max:100");
            uint8_t val = numPadInt((u8 *) titlestr, fanGetSetPercent(infoSettings.air_assist_fan), 0, false);
            val = NOBEYOND(0, val, 100);

            if (val != fanGetSetPercent(infoSettings.air_assist_fan))
              fanSetPercent(infoSettings.air_assist_fan, val);
          }
          else
          {
            sprintf(titlestr, "Min:0 | Max:%d", infoSettings.fan_max[infoSettings.air_assist_fan]);
            uint8_t val = numPadInt((u8 *) titlestr, fanGetCurSpeed(infoSettings.air_assist_fan), 0, false);
            val = NOBEYOND(0, val,  infoSettings.fan_max[infoSettings.air_assist_fan]);

            if (val != fanGetCurSpeed(infoSettings.air_assist_fan))
              fanSetSpeed(infoSettings.air_assist_fan, val);
          }

          menuDrawPage(&airAssistItems);
          airAssistValueReDraw(true);
        }
        break;
      }

      case KEY_ICON_3:
        if (fanGetSetSpeed(infoSettings.air_assist_fan) < infoSettings.fan_max[infoSettings.air_assist_fan])
        {
          if (infoSettings.fan_percentage == 1)
            fanSetPercent(infoSettings.air_assist_fan, fanGetSetPercent(infoSettings.air_assist_fan) + 1);
          else
            fanSetSpeed(infoSettings.air_assist_fan, fanGetSetSpeed(infoSettings.air_assist_fan) + 1);
        }
        break;

      case KEY_ICON_4:
        if (infoSettings.air_assist_type != 1)
          fanSetSpeed(infoSettings.air_assist_fan, infoSettings.fan_max[infoSettings.air_assist_fan] / 2);  // 50%
        else
          airAssistSetState(true);

        airAssistValueReDraw(true);
        break;

      case KEY_ICON_5:
        if (infoSettings.air_assist_type != 1)
          fanSetSpeed(infoSettings.air_assist_fan, infoSettings.fan_max[infoSettings.air_assist_fan]);
        else
          airAssistSetState(false);
        
        airAssistValueReDraw(true);
        break;

      case KEY_ICON_6:
        if (infoSettings.air_assist_type != 1)
          fanSetSpeed(infoSettings.air_assist_fan, 0);
        break;

      case KEY_ICON_7:
        infoMenu.cur--;
        break;

      default:
        if (infoSettings.air_assist_type != 1)
        {
          #if LCD_ENCODER_SUPPORT
            if (encoderPosition)
            {
              if (fanGetSetSpeed(infoSettings.air_assist_fan) < infoSettings.fan_max[infoSettings.air_assist_fan] && encoderPosition > 0)
              {
                if (infoSettings.fan_percentage == 1)
                  fanSetPercent(infoSettings.air_assist_fan, fanGetSetPercent(infoSettings.air_assist_fan) + 1);
                else
                  fanSetSpeed(infoSettings.air_assist_fan, fanGetSetSpeed(infoSettings.air_assist_fan) + 1);
              }

              if (fanGetSetSpeed(infoSettings.air_assist_fan) > 0 && encoderPosition < 0)
              {
                if (infoSettings.fan_percentage == 1)
                  fanSetPercent(infoSettings.air_assist_fan, fanGetSetPercent(infoSettings.air_assist_fan) - 1);
                else
                  fanSetSpeed(infoSettings.air_assist_fan, fanGetSetSpeed(infoSettings.air_assist_fan) - 1);
              }
              encoderPosition = 0;
            }
          #endif
        }
        break;
    }

    if (infoSettings.air_assist_type != 1)
    {
      if ((lastFan.cur != fanGetCurSpeed(infoSettings.air_assist_fan)) || (lastFan.set != fanGetSetSpeed(infoSettings.air_assist_fan)))
      {
        lastFan = (LASTFAN) {fanGetCurSpeed(infoSettings.air_assist_fan), fanGetSetSpeed(infoSettings.air_assist_fan)};
        airAssistValueReDraw(true);
      }
    }
    loopProcess();
  }
}
