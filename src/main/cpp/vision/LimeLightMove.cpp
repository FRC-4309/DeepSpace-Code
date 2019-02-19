#include "Robot.h"

#include <iostream>

void Robot::limelightMove() {
    limelightUpdate();
    //center rotationaly and horizontaly
    if (limelight_stage==0) {
        if ((!limelightCentered(limelight_value_enum::HORZ) ||
            !limelightCentered(limelight_value_enum::SKEW)) ||
            limelight_stage_0_calibrating < limelight_stage_0_calibrating_wait
            ) {
            Move(
                limelight_offset_horz*limelight_offset_horz_mult,
                0,
                limelight_skew*limelight_skew_mult
            );
            limelight_stage_0_centered=0;
            std::cout << "TIMER: " << limelight_stage_0_calibrating << "\n";
            limelight_stage_0_calibrating++;
        }
        else if (limelight_stage_0_calibrating>=limelight_stage_0_calibrating_wait) {
            limelight_stage_0_calibrating=0;
            limelight_stage_0_centered=0;
            limelight_stage=1;
        }
        else {
            limelight_stage_0_calibrating=0;
            limelight_stage_0_centered++;
            if (limelight_stage_0_centered>=limelight_stage_0_centered_wait) {
                limelight_stage_0_calibrating=0;
                limelight_stage_0_centered=0;
                limelight_stage=1;
            }
        }
    }
    //keep driving until time has passed
    else if (limelight_stage==1) {
        if (limelight_area<3)
            Move(0, -limelight_put_speed, 0); //continue moving
        else limelight_stage=2;
    }
    else if (limelight_stage==2) {
        armConfirm(); //wait for arm to flip
        limelight_stage=3;
    }
    //release hatch and reset vals
    else if (limelight_stage==3) {
        Move(0, -limelight_put_speed, 0, 1.8);
        ToggleSolenoid(phenumatic_grabber, phenumatic_grabber_grabbing);
        Move(0, limelight_put_speed, 0, 1);
        armToggle();
        limelight_stage=-1; //reset stage
        limelight->PutNumber("ledMode", 1); //turn off limelight lights
    }
}