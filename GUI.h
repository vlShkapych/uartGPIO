#ifndef GUI_H
#define GUI_H

#include "mbed.h"
#include <cmath>
#include "LCD_DISCO_L476VG.h"
#include <string>
#include "ThisThread.h"
#include <map>


 enum _BUTTON_STATE {
    _NT = 0,
    _UP_BTN = 1,
    _RIGHT_BTN = 2,
    _DOWN_BTN = 3,
    _LEFT_BTN = 4,
    _CENTER_BTN = 5
};
enum GUI_INTERFACE_STATE{
    CONTROL = 0,
    CHOSE_MODE = 10,
    CHOSE_MODE_BTN = 11,
    CHOSE_MODE_GYRO = 12,
    SENSITIVITY = 20,
    SET_SENSITIVITY = 21,
    KEYBOARD = 30,
    KEYBOARD_INPUT = 31
    
};





class GUI {

    public:
       
        LCD_DISCO_L476VG lcd;
       

        uint8_t displayedString[7] = {0};
        int controlBtnState = _NT;
        Timer btnTimer;
        int guiState = CONTROL;

        int sensK = 2;
        bool isGyro = false;
        int chosedKey = 0;
        
        void (*keyboard)(char);
        void (*onChangeSettingsFunc)(int,bool);

        map<int, char *> interfaceMap = {{0, (char *)"Mouse",},
                                        {10, (char *)"CHOSE",},
                                        {11, (char *)"BUTTON",},
                                        {12, (char *)"GYRO",},
                                        {20, (char *)"SENSI",},
                                        {21, (char *)"SETK",},
                                        {30, (char *)"KEYBRD",}};
        
        map<int, char> keyboardMap  =  {{0, 'A',},
                                        {1, 'B',},
                                        {2, 'C',},
                                        {3, 'D',},
                                        {4, 'E',},
                                        {5, 'F',},
                                        {6, 'G',},
                                        {7, 'H',},
                                        {8, 'I',},
                                        {9, 'J',},
                                        {10, 'K',},
                                        {11, 'L',},
                                        {12, 'M',},
                                        {13, 'N',},
                                        {14, 'O',},
                                        {15, 'P',},
                                        {16, 'Q',},
                                        {17, 'R',},
                                        {18, 'S',},
                                        {19, 'T',},
                                        {20, 'U',},
                                        {21, 'V',},
                                        {22, 'W',},
                                        {23, 'X',},
                                        {24, 'Y',},
                                        {25, 'Z',},

                                        };



        


    

    public:

        GUI();

        void getControlBtnState(int btnState);
        void updateDisplay();
        void setKeyboard(void (*func)(char));
        void onChangeSettingsSetF(void (*func)(int,bool));
        void settingsOnChange();

};


#endif