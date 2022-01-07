#include "PinNames.h"
#include "PinNamesTypes.h"
#include "mbed.h"
#include "GUI.h"
#include "InterruptIn.h"
#include "MouseController.h"

           



DigitalOut led_green(LED1);

Thread thread;


InterruptIn btnUp(PA_3);
InterruptIn btnDown(PA_5);
InterruptIn btnRight(PA_2);
InterruptIn btnLeft(PA_1);
InterruptIn btnCenter(PA_0);

 MouseController mouse;
//USBKeyboard keyboard;

int *sensK;
bool *isGyroMode;






int btnState = NT;




void up(){
    btnState = UP_BTN;
    led_green = !led_green;
   
}
void down(){
    btnState = DOWN_BTN;
    led_green = !led_green;
   
}
void rignt(){
    btnState = RIGHT_BTN;
    led_green = !led_green;
    
}
void left(){
    btnState = LEFT_BTN;
    led_green = !led_green;
    
}
void center(){
    btnState = CENTER_BTN;
    led_green = !led_green;
}

void state_nt(){
    btnState = NT;
    led_green = !led_green;
}



void initBtnsBtnMode(){
    
    btnUp.mode(PullDown);
    btnDown.mode(PullDown);
    btnLeft.mode(PullDown);
    btnRight.mode(PullDown);
    btnCenter.mode(PullDown);

    btnUp.rise(up);
    btnDown.rise(down);
    btnLeft.rise(left);
    btnRight.rise(rignt);    
    btnCenter.rise(center);


    btnUp.fall(state_nt);
    btnDown.fall(state_nt);
    btnLeft.fall(state_nt);
    btnRight.fall(state_nt);
    btnCenter.fall(state_nt);

    
}

// void keyInput(char key){
//     keyboard.putc(key);
// };


//USBKeyboard keyboard;


 GUI gui;

void guiThread(){
    
    
    auto putc = [](char c) 
    { 
        mouse.inputKey(c); 
    };
    auto settings = [](int sensK,bool isGyro)
    { 
        mouse.setSettings(sensK,isGyro); 
    };


    
    gui.setKeyboard(putc);

    gui.onChangeSettingsSetF(settings);
   
  
    
    while(1) {
        
        

        gui.updateDisplay();
        
        gui.getControlBtnState(btnState);

        ThisThread::sleep_for(50);
    }



}



int main()
{

    thread.start(guiThread);

    initBtnsBtnMode();

    mouse.gyroMode(false);
    
    while(true){

       if (gui.guiState != CONTROL) {
           continue;
       }

        mouse.getControlBtnState(btnState);
        mouse.updateMousePosition();
        
        ThisThread::sleep_for(10);

    }
 
}

