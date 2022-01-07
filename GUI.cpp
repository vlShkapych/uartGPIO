
#include "GUI.h"

GUI::GUI(){};


void GUI::updateDisplay(){

    lcd.Clear();

    if(guiState == SET_SENSITIVITY){
        sprintf((char *)displayedString, "%s %i",interfaceMap.find(guiState)->second,sensK);
        lcd.DisplayString(displayedString);
        lcd.BarLevelConfig(sensK);
    }
    else if (guiState == KEYBOARD_INPUT) {
        sprintf((char *)displayedString, "  -%c- ",keyboardMap.find(chosedKey)->second);
        lcd.DisplayString(displayedString);
    }

    else{
     
        sprintf((char *)displayedString, "%s",interfaceMap.find(guiState)->second);
        lcd.DisplayString(displayedString);
  
    }

    

}


void GUI::getControlBtnState(int btnState){

    if (controlBtnState == _NT && btnState == _CENTER_BTN && guiState == CONTROL) {
        btnTimer.start();
    }
    else if(controlBtnState == _CENTER_BTN && btnState == _NT && guiState == CONTROL){

        btnTimer.stop();

        unsigned int timer = btnTimer.read_ms();

        if(timer >= 1000){
            guiState = CHOSE_MODE;
        }
        btnTimer.reset();
    }

    

    if(guiState == SET_SENSITIVITY){
        if(btnState == _NT && controlBtnState == _UP_BTN){
             if(sensK < 4){
                  sensK +=1;
             }
              
        }
        else if(btnState == _NT && controlBtnState == _DOWN_BTN){
           
              if(sensK > 1){
                  sensK -=1;
             }
           
           

        }
    }
    if(guiState == KEYBOARD_INPUT){
        if(btnState == _NT && controlBtnState == _DOWN_BTN){
             if(chosedKey > 0){
                  chosedKey -=1;
             }
              
            
        }
        else if(btnState == _NT && controlBtnState == _UP_BTN){
           
              if(chosedKey < 25){
                  chosedKey +=1;
             }
        }
        else if(btnState == _NT && controlBtnState == _CENTER_BTN){
            
            keyboard(keyboardMap.find(chosedKey)->second);
            chosedKey = 0;
        }
    }

    

    if(guiState >= CHOSE_MODE){
        
        if(btnState == _NT && controlBtnState == _UP_BTN){
            if(guiState % 10 == 0 ){
                if(guiState != 30){
                    guiState += 10;
                }
              
            }
            else if ((floor((guiState/10)) * 10) == CHOSE_MODE) {
                if(guiState < CHOSE_MODE_GYRO){ guiState += 1; }
               
            }

        }
        else if(btnState == _NT && controlBtnState == _DOWN_BTN){
            if(guiState % 10 == 0 ){
                if(guiState > 10){
                    guiState -= 10;
                }
              
            }
            else if ((floor((guiState/10)) * 10) == CHOSE_MODE) {
                if(guiState > CHOSE_MODE_BTN){ guiState -= 1; }
            }

        }
        else if(btnState == _NT && controlBtnState == _CENTER_BTN){
             if(guiState % 10 == 0 ){
                
                    guiState += 1;
                           
            }
            else {
                if(guiState == SET_SENSITIVITY){
                    guiState = 0;
                    settingsOnChange();
                }
                if((floor((guiState/10)) * 10) == CHOSE_MODE){
                    if(guiState == CHOSE_MODE_GYRO){
                        isGyro = true;
                        guiState = 0;
                        settingsOnChange();
                    }
                    else {
                        isGyro = false;
                        guiState = 0;
                        settingsOnChange();
                    }
                }
            }

        }
        else if(btnState == _NT && controlBtnState == _LEFT_BTN){

            guiState = floor((guiState/10)) * 10;
        }
    }

    controlBtnState = btnState;
}
void GUI::onChangeSettingsSetF(void (*func)(int,bool)){
    
    onChangeSettingsFunc = func;

}

void GUI::settingsOnChange(){
    onChangeSettingsFunc(sensK,isGyro);
}

void GUI::setKeyboard(void (*func)(char)){
    keyboard = func;
};