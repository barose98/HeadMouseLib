/*
 * HeadMouse.h
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
#ifndef SRC_HEADMOUSE_H_
#define SRC_HEADMOUSE_H_
#include <Mouse.h>
#include <Adafruit_DotStar.h>

#define INTERNAL_DS_DATA     7
#define INTERNAL_DS_CLK      8

#define LED_RED 40
#define LED_GREEN 0
#define LED_BLUE 0
#define LEDPIN 13
#define YPR_X 0
#define YPR_Y 2
#define YAWMULT 4000
#define ROLLMULT 4000
#define HEADMOUSE

#define stilnessThreshold 1250
#define buttonHoldDown 190
#define radius 1.0

class HeadMouse {
public:
//    HeadMouse();
    static Adafruit_DotStar strip;
    static long stilnessTimer;
    static bool pressed;
    static float xy_old[2];
    static void begin();
    static void process(float ypr[]);
};

#endif /* SRC_HEADMOUSE_H_ */
