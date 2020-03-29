/*
 * File:          micromouse_controller.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <webots/device.h>
#include <webots/distance_sensor.h>
#include <webots/led.h>
#include <webots/motor.h>
#include <webots/nodes.h>
#include <webots/robot.h>

int time_step;

/* Motor device */
static WbDeviceTag motorL, motorR;

/* Angular speed in rad/s */
#define MAX_SPEED 6.28

/* function to get simulator time step */
static int get_time_step() {
  static int time_step = -1;
  if (time_step == -1)
    time_step = (int)wb_robot_get_basic_time_step();
  return time_step;
}


/* function to set motor velocity to move forward */
static void move_forward() {
  wb_motor_set_velocity(motorL, MAX_SPEED);
  wb_motor_set_velocity(motorR, MAX_SPEED);
}

/* function to init robot stuff */
static void init_robot() {
  // get simulator time step
  time_step = get_time_step();
	
  // get a handler to the motors and set target position to infinity (speed control)
  motorL = wb_robot_get_device("motorL");
  motorR = wb_robot_get_device("motorR");
  wb_motor_set_position(motorL, INFINITY);
  wb_motor_set_position(motorR, INFINITY);
  wb_motor_set_velocity(motorL, 0.0);
  wb_motor_set_velocity(motorR, 0.0);
}

/* main function */
int main(int argc, char **argv) {
  /* necessary to initialize webots stuff */
  wb_robot_init();

  init_robot();

  /* main loop
   * Perform simulation steps of TIME_STEP milliseconds
   * and leave the loop when the simulation is over
   */
  while (wb_robot_step(get_time_step()) != -1) {
    /*
     * move the robot forward
     * */
    move_forward();
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return EXIT_SUCCESS;
}