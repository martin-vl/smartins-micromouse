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
#include <math.h>

#include <webots/device.h>
#include <webots/distance_sensor.h>
#include <webots/compass.h>
#include <webots/led.h>
#include <webots/motor.h>
#include <webots/position_sensor.h>
#include <webots/nodes.h>
#include <webots/robot.h>
#include <webots/utils/default_robot_window.h>

int time_step;

/* Motor device */
static WbDeviceTag motorL, motorR;
static WbDeviceTag sensEncL, sensEncR;
static WbDeviceTag sensL, sensLF, sensF, sensRF, sensR;
static WbDeviceTag sensMag;

/* Angular speed in rad/s */
#define MAX_SPEED 2.28

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

double get_robot_direction() {
  const double *north = wb_compass_get_values(sensMag);
  double rad = atan2(north[0], north[1]);
  double dir = (rad - 1.5708) / M_PI * 180.0;
  if (dir < 0.0) {
    dir = dir + 360.0;
  }
  return dir;
}

double get_enc_value(WbDeviceTag tag) {
  return wb_position_sensor_get_value(tag)/0.01047;
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

  sensEncL = wb_robot_get_device("sensEncL");
  sensEncR = wb_robot_get_device("sensEncL");
  wb_position_sensor_enable(sensEncL, time_step);
  wb_position_sensor_enable(sensEncR, time_step);

  // init sensors
  sensL  = wb_robot_get_device("sensorL");
  sensLF = wb_robot_get_device("sensorLF");
  sensF  = wb_robot_get_device("sensorF");
  sensRF = wb_robot_get_device("sensorRF");
  sensR  = wb_robot_get_device("sensorR");
  wb_distance_sensor_enable(sensL, time_step);
  wb_distance_sensor_enable(sensLF, time_step);
  wb_distance_sensor_enable(sensF, time_step);
  wb_distance_sensor_enable(sensRF, time_step);
  wb_distance_sensor_enable(sensR, time_step);

  sensMag  = wb_robot_get_device("magnetometer");
  wb_compass_enable(sensMag, time_step);

  sensMag  = wb_robot_get_device("magnetometer");
  wb_compass_enable(sensMag, time_step);
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

    char sensor_message[256];
    // we need to fit the sensor values in the range [0;100], hence the divisions
    snprintf(sensor_message, 256, "%.0f %.0f %.0f %.0f %.0f %.2f %.2f %.0f %.0f %.1f",
             wb_distance_sensor_get_value(sensL),
             wb_distance_sensor_get_value(sensLF),
             wb_distance_sensor_get_value(sensF),
             wb_distance_sensor_get_value(sensRF),
             wb_distance_sensor_get_value(sensR),
             wb_motor_get_velocity(motorL),
             wb_motor_get_velocity(motorR),
             get_enc_value(sensEncL),
             get_enc_value(sensEncR),
             get_robot_direction());
    wb_robot_wwi_send_text(sensor_message);
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return EXIT_SUCCESS;
}