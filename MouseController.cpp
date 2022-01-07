
#include "MouseController.h"
#include "USBMouse.h"
#include <cstdio>


MouseController::MouseController(){};

void MouseController::getControlBtnState(int btnState){

    if(gMode){

          if (controlBtnState == NT && btnState == RIGHT_BTN){
              rightClick();
          }
          else if (controlBtnState == NT && btnState == LEFT_BTN){
              leftClick();
          }

    }
    else{
        if (controlBtnState == NT && btnState == UP_BTN){
            setMousePosition(0,(2 * mouseSensitK));
        }
        else if (controlBtnState == NT && btnState == RIGHT_BTN){
            setMousePosition((2 * mouseSensitK),0);
        }
        else if (controlBtnState == NT && btnState == DOWN_BTN){
            setMousePosition(0,-(2 * mouseSensitK));
        }
        else if (controlBtnState == NT && btnState == LEFT_BTN){
            setMousePosition(-(2 * mouseSensitK),0);
        }
        else if (controlBtnState == NT && btnState == CENTER_BTN) {
            btnTimer.start();
        }
        else if(controlBtnState == CENTER_BTN && btnState == NT) {
          
            btnTimer.stop();
            unsigned int timer = btnTimer.read_ms();
            

            if(timer < 200 && timer != 0){
                
                fastClickCounter++;
                if(fastClickCounter == 2){
                    rightClick();
                    fastClickCounter = 0;
                }   
                btnTimer.reset();             
            }
            else if (timer != 0) {
                leftClick();
                fastClickCounter = 0;
                btnTimer.reset();  
            }

        }
        else if(btnState == NT){
            setMousePosition(0,0);
        }
    }
  
    controlBtnState = btnState;
}

void MouseController::updateMousePosition(){

    if(gMode){
        
        gyro.GetXYZ(GyroBuffer);

        int x = 0 - ceil(mouseSensitK * GyroBuffer[2]/2000);
        int y = 0 - ceil(mouseSensitK * GyroBuffer[0]/2000);
        
        printf("%i,%i\n",int(GyroBuffer[0]),int(GyroBuffer[2]));

        setMousePosition(x,y);
    }

    zDir = GyroBuffer[1]/1500; 
    mouse.move(xDir, yDir);
   
}

void MouseController::setMousePosition(int x, int y){

    xDir = x;
    yDir = y;
}

void MouseController::gyroMode(bool isEnabled){
    gMode = isEnabled;

}

void MouseController::leftClick(){
    mouse.click(MOUSE_LEFT);
}
void MouseController::rightClick(){
    mouse.click(MOUSE_RIGHT);
}
void MouseController::inputKey(char key){
    mouse.putc(key);
}

void MouseController::setSettings(int sensK,bool isGyro){
    mouseSensitK = sensK;
    gMode = isGyro;
}
Timer btnTimer;