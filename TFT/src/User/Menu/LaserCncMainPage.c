#include "MainPage.h"
#include "includes.h"

void menuLaserCncMain(void)
{
  // 1 title, ITEM_PER_PAGE items(icon+label)
  MENUITEMS laserCncMainPageItems = {
    // title
    LABEL_LASERCNCMAINMENU,
    // icon              label
    {{ICON_AIR_CONTROL, LABEL_AIR_CONTROL},
     //TODO: CREATE LASER_CNC ICON(!) and change below
     {ICON_LASER_CNC,    LABEL_LASER_CNC},
     {ICON_HOME_MOVE,    LABEL_UNIFIEDMOVE},
     {ICON_STOP,         LABEL_EMERGENCYSTOP},
     {ICON_GCODE,        LABEL_TERMINAL},
     {ICON_CUSTOM,       LABEL_CUSTOM},
     {ICON_SETTINGS,     LABEL_SETTINGS},
     {ICON_BACK,         LABEL_BACK},}
  };

  KEY_VALUES key_num = KEY_IDLE;

  if (infoSettings.status_screen != 1)
  {
    laserCncMainPageItems.items[7].icon = ICON_PRINT;
    laserCncMainPageItems.items[7].label.index = LABEL_PRINT;
  }

  menuDrawPage(&laserCncMainPageItems);

  while (infoMenu.menu[infoMenu.cur] == menuLaserCncMain)
  {
    key_num = menuKeyGetValue();
    switch (key_num)
    {
      case KEY_ICON_0:
        infoMenu.menu[++infoMenu.cur] = menuAirControl;
        break;

      case KEY_ICON_1:
      //TODO: create menu
       // infoMenu.menu[++infoMenu.cur] = menuLaserCnc;
        break;
      case KEY_ICON_2:
        infoMenu.menu[++infoMenu.cur] = menuUnifiedMove;
        break;

      case KEY_ICON_3:
        // Emergency Stop : Used for emergency stopping, a reset is required to return to operational mode.
        // it may need to wait for a space to open up in the command queue.
        // Enable EMERGENCY_PARSER in Marlin Firmware for an instantaneous M112 command.
        Serial_Puts(SERIAL_PORT, "M112\n");
        break;

      case KEY_ICON_4:
        infoMenu.menu[++infoMenu.cur] = menuSendGcode;
        break;

      case KEY_ICON_5:
        infoMenu.menu[++infoMenu.cur] = menuCustom;
        break;

      case KEY_ICON_6:
        infoMenu.menu[++infoMenu.cur] = menuSettings;
        break;

      case KEY_ICON_7:
        if (infoSettings.status_screen != 1)
          infoMenu.menu[++infoMenu.cur] = menuPrint;
        else
          infoMenu.cur--;
        break;

      default:
        break;
    }

    loopProcess();
  }
}

