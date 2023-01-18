/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include <math.h>

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {
  int power;
  int turn;
  int speed;
  int strafe;
  int belt;
  int roter;
  int pitch;
    while (1) {
      bool up = joystickGetDigital(1, 5, JOY_UP);
      bool down = joystickGetDigital(1, 5, JOY_DOWN);
      bool drop = joystickGetDigital(1, 6, JOY_UP);
      if(up)
      {
        belt = 127;
      }
      else if(down)
      {
        belt = -100;
      }
      else
      {
        belt = 0;
      }
      if(drop)
      {
        roter = 127; 
      }
      else
      {
        roter = 0;
      }
        //strafe = joystickGetAnalog(1, 4);
        const int deadbanda = 20;  //(you would want to calibrate this to the right value for your robot)
        power = joystickGetAnalog(1, 3);
        if (power < deadbanda && power > (deadbanda * -1)){
        power = 0;
        }// vertical axis on left joystick
        const int deadbandb = 20;  //(you would want to calibrate this to the right value for your robot)
        turn = joystickGetAnalog(1, 1);
        if (turn < deadbandb && turn > (deadbandb * -1)){
        turn = 0;
        }// vertical axis on left joystick // horizontal axis on left joystick
        const int deadbandc = 20;  //(you would want to calibrate this to the right value for your robot)
        strafe = joystickGetAnalog(1, 4);
        if (strafe < deadbandc && strafe > (deadbandc * -1)){
        strafe = 0;
        }
        speed = abs(power) + abs(strafe);
    //motorSet(9, -power-turn);
    motorSet(10, turn);
    //motorSet(2, -power+turn);
    motorSet(1, speed);
    //motorSet(6, roter);
    //motorSet(8, belt*-1);
    //wmotorSet(7, belt);
        delay(20);
    }
}
