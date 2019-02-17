#include "Robot.h"

void Robot::armContinue() {
    if (arm_started_front) {
        if (arm_potentiometer_current<arm_potentiometer_mid) { //arm has reached halfway point
            arm_moving=false; //stop arm from moving
            arm.Set(0);
        }
        else {
            arm.Set(arm_speed_getting); //continue moving to the other side
        }
    }
    else {
        if (arm_potentiometer_current>arm_potentiometer_mid) { //arm has readed halfway point
            arm_moving=false;
            arm.Set(0);
        }
        else {
            arm.Set(-arm_speed_putting);
        }
    }
}