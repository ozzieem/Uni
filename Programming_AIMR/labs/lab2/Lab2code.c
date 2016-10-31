#include <math.h>
#include "interface.h"

#define ROBOT_NUMBER "2"
#define CIRCUMFERENCE 128


float StepsPermm = 7.71;

// 1 step = 7.71 mm
void Move(double mm) {
    Steps steps;
    steps.l = mm * StepsPermm + GetSteps().l;
    steps.r = mm * StepsPermm + GetSteps().r;
    printf("Moving %lf millimeters\n", mm);
    printf("Setting steps: %d %d\n", steps.l, steps.r);
    SetTargetSteps(steps.l, steps.r);
}


// 1 step = 3.63 degrees
void Turn(double degrees) {
    float StepsPerDegree = 3.645;
    Steps targetSteps;
    targetSteps.l = -degrees * StepsPerDegree + GetSteps().l;
    targetSteps.r = degrees * StepsPerDegree + GetSteps().r;
    SetTargetSteps(targetSteps.l, targetSteps.r);
}


Posture RobPos = {0.0, 0.0, 0.0};
Steps newSteps, diffSteps, prevSteps = {0, 0};
float diffmmL, diffmmR, dist, dx, dy, ang = 0.0, thPrev = 0.0, th = 0.0;

void update_position(float D)
{
    newSteps = GetSteps();
    diffSteps.l = newSteps.l - prevSteps.l;
    diffSteps.r = newSteps.r - prevSteps.r;
    diffmmL = (diffSteps.l * 1.0) / StepsPermm;
    diffmmR = (diffSteps.r * 1.0) / StepsPermm;
	
    dist = (diffmmL + diffmmR) / 2;
    ang = (diffmmR - diffmmL) / D;

    //dx = dist * sin(ang) / ang;
    //dy = dist * (1-cos(ang)) / ang;
    // Using functions below instead because division by 0 is not possible.

    dx = dist * cos(ang/2);
    dy = dist * sin(ang/2);

    prevSteps = newSteps;
    RobPos.x += dx * cos(thPrev) - dy * sin(thPrev);
    RobPos.y += dx * sin(thPrev) + dy * cos(thPrev);

    th = ang + thPrev; 
    if (th >= 2 * PI)
        th -= 2 * PI;
    else if (th < 0)
        th += 2 * PI;
    RobPos.th = th;
    thPrev = th;

    printf("dist: %lf mm\nang : %lf rad\ndx/p: %lf\ndy/p: %lf\n\n", dist, ang, 
		dx * cos(thPrev) - dy * sin(thPrev),
		dx * sin(thPrev) + dy * cos(thPrev));
    printf("Robot position: (%lf, %lf)\nRobot Angle: %lf\n\n", RobPos.x, RobPos.y, RobPos.th);
    Sleep(10);


}

void goto_mimo(float xt, float yt){
    while (1) {
        update_position(53.92);

    }
}

//==============================================================================//
//                                  main                                        //
//==============================================================================//
int main(int argc, char *argv[])
{

//epuck connection
    epuck(ROBOT_NUMBER);

    Posture posture;     //get posture; float(x,y,th)
    Steps steps;  // get steps: int (l,r)
    Steps en_mm;    // steps to mm int (l,r)
    Steps mm_en;    // mm to encoder int (l,r)
    Speed speed;       // get speed int (l,r)
    Speed speed_mm;       // get speed in mm int (l,r)


    int i;
    printf("Starting...\n");

    int turn = 0;
    SetSpeed(400,200);
    while (1) {
        update_position(53.92);
    }

/*
  //Example 4


  for (i=0;i<10;i++)
  {
    Sleep(100);
    GetPolarSpeed(&vlin, &vrot);
    printf("(vlin,vrot)=(%.2lf,%.2lf)\n", vlin, DEG(vrot));
  }
  Stop();

*/

    printf("Done...\n");
    return (0);
}

//==============================================================================//
//                                  end main                                    //
//==============================================================================//




//void IRDetector()
//{
//    Sensors ir;       // get sensors vlotage unsigned int (sensor)
//    bool led[8] = {0,0,0,0,0,0,0,0};  // eight leds
//    SetRingLED (led);
//
//    int i, j;
//    for (i=0;i<1000;i++)
//    {
//        ir = GetIR();
//        printf("IR values: %4d, %4d, %4d, %4d, %4d, %4d, %4d, %4d\n",
//               ir.sensor[0], ir.sensor[1], ir.sensor[2], ir.sensor[3],
//               ir.sensor[4], ir.sensor[5], ir.sensor[6], ir.sensor[7]);
//        for (j=0; j<8; j++)
//        {
//            if (ir.sensor[j] > 1000)
//                led[j] = 1;
//            else
//                led[j] = 0;
//        }
//        SetRingLED(led);
//    }
//}

void Move2(double mm)
{
    int initialSteps = GetSteps().l;
    float target = GetSteps().l + mm * StepsPermm;
    SetSpeed(400, 400);
    while (GetSteps().l * 1.0 < target) {
        // "Busy wait" until target is readched...
        printf("%d steps!\n", GetSteps().l);
    }
    Stop();
    printf("Final steps: %d\n", GetSteps().l);
    float movedmm = (GetSteps().l - initialSteps) / StepsPermm;
    printf("Moved %lf mm!\n", movedmm);
}

void Move3(double mm)
{
    int initialSteps = GetSteps().l;
    float target = GetSteps().l + mm * StepsPermm;
    printf ("Speed: %d\n", SetSpeed(400, 400));
    while (GetSteps().l * 1.0 < target) {
        // "Busy wait" until target is readched...
        printf("%d steps!\n", GetSteps().l);
    }
    Stop();
    printf("Final steps: %d\n", GetSteps().l);
    float movedmm = (GetSteps().l - initialSteps) / StepsPermm;
    printf("Moved %lf mm!\n", movedmm);
}





