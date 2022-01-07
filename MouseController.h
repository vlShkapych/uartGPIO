#ifndef MouseController_H
#define MouseController_H

#include "mbed.h"
#include "USBMouse.h"
#include "GYRO_DISCO_L476VG.h"
#include "USBMouseKeyboard.h"
#include <cmath>


enum BUTTON_STATE {
    NT = 0,
    UP_BTN = 1,
    RIGHT_BTN = 2,
    DOWN_BTN = 3,
    LEFT_BTN = 4,
    CENTER_BTN = 5
};


class MouseController {

    public:
       
        GYRO_DISCO_L476VG gyro;
       
        USBMouseKeyboard mouse;
        float GyroBuffer[3];

        int xDir= 0;
        int yDir= 0;
        int zDir = 0;
        bool gMode = true;
        int controlBtnState = 0;
        Timer btnTimer;
        int fastClickCounter = 0;
        int mouseSensitK = 2;



    public:

        MouseController();

        
        void updateMousePosition();
        void leftClick();
        void rightClick();
        void setMousePosition(int x, int y);
        void gyroMode(bool isEnabled);
        void getControlBtnState(int state);
        void inputKey(char key);
        void setSettings(int sensK,bool isGyro);


};


#endif