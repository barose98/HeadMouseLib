/*
 * HeadMouse.cpp
 *
 *  Created on: Apr 13, 2020
 *      Author: Barrett Rose
 */
/* ============================================
HeadMouseLib device library code is placed under the MIT license
Copyright (c) 2020 Barrett Rose

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/
#include "HeadMouse.h"
    Adafruit_DotStar HeadMouse::strip = Adafruit_DotStar(1, INTERNAL_DS_DATA, INTERNAL_DS_CLK, DOTSTAR_BGR);
    long HeadMouse::stilnessTimer;
    bool HeadMouse::pressed;
    float HeadMouse::xy_old[2];

void HeadMouse::begin(){
   pressed=false;
   stilnessTimer=0L;
   strip.begin();
   Mouse.begin();
}
void HeadMouse::process(float ypr[]){
    //Scale up the radians to mouse movements.
    ypr[0]=ypr[0]*YAWMULT;
    ypr[2]=ypr[2]*ROLLMULT;

    //Has there been movement? Compare the yawpitchroll readings this cycle to last cycle.
    if( int( (ypr[YPR_X]-xy_old[0])) >radius ||  
    int( (ypr[YPR_Y]-xy_old[1]) ) > radius ||  
    int( (ypr[YPR_X]-xy_old[0])) <(radius*-1.0) ||  
    int( (ypr[YPR_Y]-xy_old[1]) ) <(radius*-1.0) )
    {
      Mouse.move( int( (ypr[YPR_X]-xy_old[0]) ) ,  int( (ypr[YPR_Y]-xy_old[1]))  ,0  );
      stilnessTimer=millis();//reset timer

    }
    else{    //The mouse was still.

        //Has it been still for long enough?. If so, is the mouse already pressed? If not press the mouse.
        if( !pressed && (millis()-stilnessTimer)>stilnessThreshold && (millis()-stilnessTimer)<(stilnessThreshold+buttonHoldDown) )
        {
            Mouse.press();
            strip.setPixelColor(0, LED_RED, LED_GREEN, LED_BLUE); strip.show();
            pressed=true;

        }else if(pressed && (millis()-stilnessTimer)>(stilnessThreshold+buttonHoldDown)){  //Has the mouse been held still again after having been moved with the mouse down? (A drag)

         strip.setPixelColor(0, 0, 0, 0); strip.show();
         Mouse.release();
         pressed=false;
         stilnessTimer=millis();//reset timer
        }


    }
    xy_old[0]=ypr[YPR_X];
    xy_old[1]=ypr[YPR_Y];

}
