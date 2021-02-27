#include "AirACaseFan.h"
#include "includes.h"

const MENUITEMS AirACaseFanItems = {
  // title
  LABEL_UNIFIEDHEAT,
  // icon                         label
  {{ICON_AIR_ASSIST,              LABEL_AIR_ASSIST},
   {ICON_BACKGROUND,              LABEL_BACKGROUND},
   {ICON_BACKGROUND,              LABEL_BACKGROUND},
   {ICON_BACKGROUND,              LABEL_BACKGROUND},
   {ICON_CASE_FAN,                LABEL_CASE_FAN},
   {ICON_BACKGROUND,              LABEL_BACKGROUND},
   {ICON_BACKGROUND,              LABEL_BACKGROUND},
   {ICON_BACK,                    LABEL_BACK},}
};
//TODO: Refine menu items with check if we need submenus. eg. case_fan=0 or air_assist=1
void menuAirACaseFan(void)
{
  KEY_VALUES key_num = KEY_IDLE;
  menuDrawPage(&AirACaseFanItems);

  while(infoMenu.menu[infoMenu.cur] == menuAirACaseFan)
  {
    key_num = menuKeyGetValue();
    switch (key_num)
    {
      case KEY_ICON_0:
        //TODO: Create menu
        //infoMenu.menu[++infoMenu.cur] = menuAirAssist;
        break;

      case KEY_ICON_4:
        //TODO: Create menu
        //infoMenu.menu[++infoMenu.cur] = menuCaseFan;
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
