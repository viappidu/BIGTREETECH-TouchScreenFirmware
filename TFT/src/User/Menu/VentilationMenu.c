#include "VentilationMenu.h"
#include "includes.h"

//TODO: Refine menu items with check if we need submenus. eg. chamber_fan=0 or air_assist=1

/*
//TODO: DRAW CURRENT VALUE on top of backgroud icon. Maybe using
// getIconStartPoint(2)

void valuesReDraw(void)
{
  char tempstr[20];

  if (infoSettings.chamber_fan_type != 8)
  {
    if (infoSettings.fan_percentage == 1)
      GUI_DispStringCenter((exhibitRect.x0 + exhibitRect.x1)>>1, exhibitRect.y0, (uint8_t *)"%");
    else
      GUI_DispStringCenter((exhibitRect.x0 + exhibitRect.x1)>>1, exhibitRect.y0, (uint8_t *)"PWM");
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
*/
void menuVentilationMenu(void)
{
  MENUITEMS VentilationMenuItems = {
    // title
    LABEL_VENTILATIONMENU,
    // icon                         label
    {{ICON_AIR_ASSIST,             LABEL_AIR_ASSIST},
    {ICON_BACKGROUND,              LABEL_BACKGROUND},
    {ICON_BACKGROUND,              LABEL_BACKGROUND},
    {ICON_BACKGROUND,              LABEL_BACKGROUND},
    {ICON_CHAMBER_FAN,             LABEL_CHAMBER_FAN},
    {ICON_BACKGROUND,              LABEL_BACKGROUND},
    {ICON_BACKGROUND,              LABEL_BACKGROUND},
    {ICON_BACK,                    LABEL_BACK},}
  };

  if (infoSettings.air_assist_type == 1)
  {
    VentilationMenuItems.items[0].label.index = LABEL_ON;
    VentilationMenuItems.items[1].icon = ICON_AIR_ASSIST;
    VentilationMenuItems.items[1].label.index = LABEL_STOP;
  }
  if (infoSettings.chamber_fan_type == 3)
  {
    VentilationMenuItems.items[4].label.index = LABEL_ON;
    VentilationMenuItems.items[5].icon = ICON_CHAMBER_FAN;
    VentilationMenuItems.items[5].label.index = LABEL_STOP;
  }

  menuDrawPage(&VentilationMenuItems);

  while(infoMenu.menu[infoMenu.cur] == menuVentilationMenu)
  {
    KEY_VALUES key_num = menuKeyGetValue();
    switch (key_num)
    {
      case KEY_ICON_0:
        if (infoSettings.air_assist_type == 1)
          fanSetSpeed(infoSettings.air_assist_fan, infoSettings.fan_max[infoSettings.air_assist_fan]);
        else
          infoMenu.menu[++infoMenu.cur] = menuAirAssist;
        break;

      case KEY_ICON_1:
        fanSetSpeed(infoSettings.air_assist_fan, 0]);
        break;

      case KEY_ICON_4:
        if (infoSettings.air_assist_type == 1)
          fanSetSpeed(infoSettings.chamber_fan, infoSettings.fan_max[infoSettings.chamber_fan]);
        else
        infoMenu.menu[++infoMenu.cur] = menuChamberFan;
        break;

      case KEY_ICON_5:
        fanSetSpeed(infoSettings.chamber_fan, 0);
        break;

      case KEY_ICON_7:
        infoMenu.cur--;
        break;

      default:
        break;
    }
    loopProcess();
  }
}
