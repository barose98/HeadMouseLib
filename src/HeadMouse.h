/*
 * HeadMouse.h
 *
 *  Created on: Apr 13, 2020
 *      Author: Barrett Rose
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
