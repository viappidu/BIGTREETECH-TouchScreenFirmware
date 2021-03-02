#include "AirControl.h"
#include "includes.h"

const MENUITEMS AirControlItems = {
  // title
  LABEL_UNIFIEDHEAT,
  // icon                         label
  {{ICON_AIR_ASSIST,              LABEL_AIR_ASSIST},
   {ICON_BACKGROUND,              LABEL_BACKGROUND},
   {ICON_BACKGROUND,              LABEL_BACKGROUND},
   {ICON_BACKGROUND,              LABEL_BACKGROUND},
   {ICON_CHAMBER_FAN,             LABEL_CHAMBER_FAN},
   {ICON_BACKGROUND,              LABEL_BACKGROUND},
   {ICON_BACKGROUND,              LABEL_BACKGROUND},
   {ICON_BACK,                    LABEL_BACK},}
};
//TODO: Refine menu items with check if we need submenus. eg. chamber_fan=0 or air_assist=1
void menuAirControl(void)
{
  KEY_VALUES key_num = KEY_IDLE;
  menuDrawPage(&AirControlItems);

  while(infoMenu.menu[infoMenu.cur] == menuAirControl)
  {
    key_num = menuKeyGetValue();
    switch (key_num)
    {
      case KEY_ICON_0:
        infoMenu.menu[++infoMenu.cur] = menuAirAssist;
        break;

      case KEY_ICON_4:
        infoMenu.menu[++infoMenu.cur] = menuChamberFan;
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
