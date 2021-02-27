#include "AirAssist.h"
#include "includes.h"

void airAssistSpeedReDraw()
{
  char tempstr[20];

  if (infoSettings.air_assist_type == 1)
    sprintf(tempstr, "  %s  ", airAssistGetState() ? LABEL_ON : LABEL_OFF);
  else
  {
    if (infoSettings.fan_percentage == 1)
      sprintf(tempstr, "  %d/%d  ", airAssistGetCurPercent(), airAssistGetSetPercent());
    else
      sprintf(tempstr, "  %d/%d  ", (int)airAssistGetCurSpeed(), (int)airAssistGetSetSpeed());
  }
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

  if (infoSettings.air_assist_type != 1)
    airAssistSetSpeed(airAssistGetCurSpeed());

  menuDrawPage(&airAssistItems);
  airAssistSpeedReDraw();

  #if LCD_ENCODER_SUPPORT
    encoderPosition = 0;
  #endif

  while (infoMenu.menu[infoMenu.cur] == menuAirAssist)
  {
    KEY_VALUES key_num = menuKeyGetValue();
    switch (key_num)
    {
      case KEY_ICON_0:
        if (infoSettings.air_assist_type != 1)
        {
          if (airAssistGetSetSpeed() > 0)
          {
            if (infoSettings.fan_percentage == 1)
              airAssistSetPercent(airAssistGetSetPercent() - 1);
            else
              airAssistSetSpeed(airAssistGetSetSpeed() - 1);
          }
        }
        break;

      case KEY_INFOBOX:
      {
        char titlestr[30];
        if (infoSettings.air_assist_type != 1)
        {
          if (infoSettings.fan_percentage == 1)
          {
            strcpy(titlestr, "Min:0 | Max:100");
            uint8_t val = numPadInt((u8 *) titlestr, airAssistGetSetPercent(), 0, false);
            val = NOBEYOND(0, val, 100);

            if (val != airAssistGetSetPercent())
              airAssistSetPercent(val);
          }
          else
          {
            sprintf(titlestr, "Min:0 | Max:%d", 255);
            uint8_t val = numPadInt((u8 *) titlestr, airAssistGetCurSpeed(), 0, false);
            val = NOBEYOND(0, val,  255);

            if (val != airAssistGetCurSpeed())
              airAssistSetSpeed(val);
          }

          menuDrawPage(&airAssistItems);
          airAssistSpeedReDraw();
        }
        break;
      }

      case KEY_ICON_3:
        if (infoSettings.air_assist_type != 1)
        {
          if (airAssistGetSetSpeed() < 255)
          {
            if (infoSettings.fan_percentage == 1)
              airAssistSetPercent(airAssistGetSetPercent() + 1);
            else
              airAssistSetSpeed( airAssistGetSetSpeed() + 1);
          }
        }
        break;

      case KEY_ICON_4:
        if (infoSettings.air_assist_type != 1)
          airAssistSetSpeed(255 / 2);  // 50%
        else
          airAssistSetState(true);
        break;

      case KEY_ICON_5:
        if (infoSettings.air_assist_type != 1)
          airAssistSetSpeed(255);
        else
          airAssistSetState(false);
        break;

      case KEY_ICON_6:
        if (infoSettings.air_assist_type != 1)
          airAssistSetSpeed(0);
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
              if (airAssistGetSetSpeed() < 255 && encoderPosition > 0)
              {
                if (infoSettings.fan_percentage == 1)
                  airAssistSetPercent(airAssistGetSetPercent() + 1);
                else
                  airAssistSetSpeed(airAssistGetSetSpeed() + 1);
              }

              if (airAssistGetSetSpeed() > 0 && encoderPosition < 0)
              {
                if (infoSettings.fan_percentage == 1)
                  airAssistSetPercent(airAssistGetSetPercent() - 1);
                else
                  airAssistSetSpeed(airAssistGetSetSpeed() - 1);
              }
              encoderPosition = 0;
            }
          #endif
        }
        break;
    }

    loopProcess();
  }
}
