#include <math.h>
#include "interface.h"

#define ROBOT_NUMBER "2"
#define CIRCUMFERENCE 128
#define CRD 53.92

float StepsPermm = 7.71;
Posture RobPos = {0.0, 0.0, 0.0};

// 1 step = 7.71 mm
void Move(double mm) {
    Steps steps;
    steps.l = mm * StepsPermm + GetSteps().l;
    steps.r = mm * StepsPermm + GetSteps().r;
    printf("Moving %lf millimeters\n", mm);
    printf("Setting steps: %d %d\n", steps.l, steps.r);
    SetTargetSteps(steps.l, steps.r);
}

void writeToFile() {
    FILE *f = fopen("RobPos.txt", "a");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "%.2f,%.2f\n", RobPos.x, RobPos.y);
    fclose(f);
}

// 1 degree = 3.63 steps
void Turn(double degrees) {
    float StepsPerDegree = 3.645;
    Steps targetSteps;
    targetSteps.l = -degrees * StepsPerDegree + GetSteps().l;
    targetSteps.r = degrees * StepsPerDegree + GetSteps().r;
    SetTargetSteps(targetSteps.l, targetSteps.r);
}

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

    dx = dist * cos(ang/2);
    dy = dist * sin(ang/2);

    prevSteps = newSteps;
    RobPos.x += dx * cos(thPrev) - dy * sin(thPrev);
    RobPos.y += dx * sin(thPrev) + dy * cos(thPrev);

    th = ang + thPrev;
    if (th > PI)
        th -= 2 * PI;
    else if (th < -PI)
        th += 2 * PI;
    RobPos.th = th;
    thPrev = th;
    printf("Robot position: (%lf, %lf)\nRobot Angle: %lf\n\n", RobPos.x, RobPos.y, RobPos.th);
//    writeToFile();
}

void normalize_speeds(int* vR, int* vL){
	const int minSpeed = 200;
    const int maxSpeed = 800;
	
    if (*vL > maxSpeed)
        *vL = maxSpeed;
    if (*vR > maxSpeed)
        *vR = maxSpeed;
    if (*vL < -maxSpeed)
        *vL = -maxSpeed;
    if (*vR < -maxSpeed)
        *vR = -maxSpeed;
    if ((*vL < minSpeed && *vL >= 0))
        *vL = minSpeed;
    if (*vL > -minSpeed && *vL <= 0)
        *vL = -minSpeed;
    if ((*vR < minSpeed && *vR >= 0))
        *vR = minSpeed;
    if (*vR > -minSpeed && *vR <= 0)
        *vR = -minSpeed;
}

// MIMO-controller
void goto_mimo(float xt, float yt){
    float dx, dy, Eth, Epos, vt, w, D = CRD;
	int vR, vL;
	
	float Kp_pos = 8, Kp_th = 60, delta_pos = 10.0;  // double instead of float?
    
    do {
        update_position(CRD);
        dx = xt - RobPos.x;
        dy = yt - RobPos.y;
        Epos = sqrt(pow(dx, 2) + pow(dy, 2));	// abs() does not work properly, so sqrt(pow()) is used instead
        Eth = atan2(dy, dx) - RobPos.th;
        if (Eth > PI)
            Eth -= 2 * PI;
        else if (Eth < -PI)
            Eth += 2 * PI;
		
        vt = Kp_pos * Epos;
        w = Kp_th * Eth;
        vR = vt + D/2 * w;
        vL = vt - D/2 * w;
		
        printf("Speed before normalization: %d %d\n", vL, vR);
        normalize_speeds(&vL, &vR);
		
        printf("Epos: %lf\n", Epos);
        printf("Speed: %d %d\n", vL, vR);
        printf("Eth: %lf\n", Eth);
        SetSpeed(vL, vR);
        Sleep(10);
    } while (Epos > delta_pos);
    Stop();
}

// Divide et Impera
void goto_dei(double xt, double yt){
    double dx, dy, Eth, Epos, D = CRD;
    int vR, vL;
	
	double Kp_pos = 3.0, Kp_th = 150.0, delta_pos = 10.0, delta_th = 0.25;
	
    do {
        update_position(CRD);
        dx = xt - RobPos.x;
        dy = yt - RobPos.y;
        Epos = sqrt(pow(dx, 2) + pow(dy, 2));
        Eth = RobPos.th - atan2(dy, dx);
        printf("dx & dy: %lf %lf\n", dx, dy);
        if (sqrt(pow(Eth, 2)) >= delta_th){
            vR = -(Kp_th * Eth);
            vL = - vR;
            printf("Speeds before normalizing: %d %d\n", vL, vR);
            printf("Turned!\n\n\n");
        }
        else {
            vR = (Kp_pos * Epos);
            vL = vR;
            printf("No turn!\n\n\n");
        }
        while (abs(vL) > 1000 || abs(vR) > 1000) {
            vL /= 2;
            vR /= 2;
            printf("Divided vL or vR!\n");
        }
        while (abs(vL) < 200 || abs(vR) < 200) {
            vL *= 1.2;
            vR *= 1.2;
            printf("Doubled vL or vR!\n");
        }
//        normalize_speeds(&vL, &vR);
        printf("Epos: %lf\n", Epos);
        printf("Speed: %d %d\n", vL, vR);
        printf("Eth: %lf\n", Eth);
        SetSpeed(vL, vR);
        Sleep(100);
    } while (Epos > delta_pos);
    Stop();
}


void track(Position positions[], int size) {
    int i;
    printf("size: %d\n", sizeof(positions) / sizeof(positions[0]));

    for (i = 0; i < size; ++i) {
        goto_mimo(positions[i].x, positions[i].y);
        Sleep(2000);
    }
}


//==============================================================================//
//                                  main                                        //
//==============================================================================//
int main(int argc, char *argv[])
{

//epuck connection
    epuck(ROBOT_NUMBER);

    Position positions[] = {{150.0, 150.0}, {0.0, 0.0}, {150.0, 150.0}};

    printf("Starting...\n");
    printf("size: %d\n", sizeof(positions) / sizeof(positions[0]));
    track(positions, 3);

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
