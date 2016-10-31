#include <math.h>
#include <time.h>
#include "interface.h"
#include "maps.h"
#include "lists.h"

#define ROBOT_NUMBER "5"
#define CIRCUMFERENCE 128
#define CRD 53.92
#define VMAX_ 300
#define RMAX_ PI
#define MAX_COORDS 100
#define MAP_SIDE_SIZE 10000
#define ROTFACTOR 1.8
#define ROBOT_RAD 34
#define DIST_F_LEFT 1.39
#define DIST_F_RIGHT 1.55
#define DIST_F_AHEAD 1.15
#define STEPS_PER_MM 7.71

const char *MapFile_Save = "./maps/testmap1";
const char *MapFile_Empty = "./maps/testmap1empty";
const char *MapFile_Gradient = "./maps/gradientmap1";
const char *posFileName = "replanningpathmap.txt";

Map WorkMap, InitMap; // Workmap contains the planning data. InitMap contains obstacles.
List SearchList;      // Frontier for search and astar.
Sensors IR;

Cell StartCell = {2, 3, 0.0}; // Cell for the ePuck to start in.
Cell GoalCell = {5, 3, 0.0};  // Goal cell for the ePuck.
Cell CurrCell = StartCell;    // The ePuck's current cell.
Cell RefCell = StartCell;     // Reference point for translating a certain cell into coordinates.
Cell PrevCell = StartCell;    // The previous cell that the ePuck passed which was put in the path from the planning.

Cell PathCells[MAX_COORDS];                    // Contains the complete path frin planning.
Cell WaypointCells[MAX_COORDS];                // Same as PathCells, but without redundance.
Position WaypointsCoords[MAX_COORDS];          // Same as WaypointCells, but translated to coordinates.
Posture RobPos = {0.0, 0.0, 0.0};              // Robot position and orientation.
Steps newSteps, diffSteps, prevSteps = {0, 0}; // Used for odometrically updating the position.
Position prevpos;

double HValueList[MAP_SIDE_SIZE][MAP_SIDE_SIZE]; // Holds the heuristic values of each grid cell.
int ObsDetected = 0;                             // Flag used while updating map with obstacle.
int ReturningtoPrev = 0;                         // Flag used while returning to path.
int nWaypoints = 0;                              // Counting waypoints.
const double RML = 590.0;                        // Real Map Side Length.
const double CellsPerSide = 6;
double mmCell = RML / CellsPerSide;
double thPrev = 0.0, Eth, Epos;

double NormAng(double);
double heuristic(int, int, Cell);
Position TranslateCelltoCoords(Cell);
Cell TranslateCoordToCell(float, float);
void TranslateCellsToCoords(int);
void TimeMeasureAstarBFS();
void PrintWaypoints(int);
void PrintDistances();
void PrintIRValues();
void Menu();
void init();

// Labels cells with information while searching.
void MarkCell(int i, int j, int label)
{
    Cell c = {i, j, 0.0};
    int di, dj;
    switch (WorkMap.map[i][j])
    {
    case -1: // Initial position
        Push(&SearchList, c);
        break;
    case -2: // Unexplored c
    case -6:
        WorkMap.map[i][j] = label;
        c.h_value = heuristic(i, j, StartCell);
        HValueList[i][j] = heuristic(i, j, GoalCell);
        Push(&SearchList, c);
        break;
    case -3: // Obstacle
        c.h_value = 0.0;
        break;
    case -4: // Out of boundaries
        break;
    default: // Already explored
        break;
    }
}

// Breadth-First Search
void Search(Cell start, Cell goal)
{
    ClearList(&SearchList, FIFO);
    Push(&SearchList, goal);
    while (!IsListEmpty(&SearchList))
    {
        Cell current = Pop(&SearchList);
        if (current.i == start.i && current.j == start.j)
            break;
        int dist = WorkMap.map[current.i][current.j] + 1;
        MarkCell(current.i, current.j - 1, dist);
        MarkCell(current.i, current.j + 1, dist);
        MarkCell(current.i - 1, current.j, dist);
        MarkCell(current.i + 1, current.j, dist);
        PrintMap(&WorkMap);
    }
}

void AStarSearch(Cell start, Cell goal)
{
    ClearList(&SearchList, SORTED);
    Push(&SearchList, goal);
    while (!IsListEmpty(&SearchList))
    {
        Cell current = Pop(&SearchList);
        if (current.i == start.i && current.j == start.j)
            break;
        int dist = WorkMap.map[current.i][current.j] + 1;
        MarkCell(current.i, current.j - 1, dist);
        MarkCell(current.i, current.j + 1, dist);
        MarkCell(current.i - 1, current.j, dist);
        MarkCell(current.i + 1, current.j, dist);
        PrintMap(&WorkMap);
    }
}

// Small time measuring program for comparing A* with BFS.
void TimeMeasureAstarBFS()
{
    int size;
    int algChoice;

    printf("Choose algorithm:\n1. A*\n2. BFS\n");
    scanf("%d", &algChoice);
    printf("Enter map side size:\n");
    scanf("%d", &size);

    StartCell = {1, 1, 0.0};
    GoalCell = {size - 2, size - 2, 0.0};

    WorkMap = *CreateBorderedMap(size, size, DEFAULT_MAX_VALUE);
    WorkMap.map[StartCell.i][StartCell.j] = MAP_START;
    WorkMap.map[GoalCell.i][GoalCell.j] = MAP_GOAL;

    clock_t start;
    switch (algChoice)
    {
    case 1:
        printf("Running A* on map side size %d...\n", size);
        start = clock();
        AStarSearch(StartCell, GoalCell);
        break;
    case 2:
        printf("Running BFS on map side size %d...\n", size);
        start = clock();
        Search(StartCell, GoalCell);
        break;
    default:
        break;
    }
    clock_t end = clock();
    float ms = (float)(end - start) / CLOCKS_PER_SEC * 1000;
    printf("Measured milliseconds: %lf\n", ms);
}

// Checks the four neigbours of a cell to plan a path.
Cell GetNextNeighbour(Cell c)
{
    int next_nr = 99999;
    Cell next_c;
    if (WorkMap.map[c.i - 1][c.j] < next_nr && WorkMap.map[c.i - 1][c.j] >= 0)
    {
        next_nr = WorkMap.map[c.i - 1][c.j];
        next_c.i = c.i - 1;
        next_c.j = c.j;
    }
    if (WorkMap.map[c.i + 1][c.j] < next_nr && WorkMap.map[c.i + 1][c.j] >= 0)
    {
        next_nr = WorkMap.map[c.i + 1][c.j];
        next_c.i = c.i + 1;
        next_c.j = c.j;
    }
    if (WorkMap.map[c.i][c.j - 1] < next_nr && WorkMap.map[c.i][c.j - 1] >= 0)
    {
        next_nr = WorkMap.map[c.i][c.j - 1];
        next_c.i = c.i;
        next_c.j = c.j - 1;
    }
    if (WorkMap.map[c.i][c.j + 1] < next_nr && WorkMap.map[c.i][c.j + 1] >= 0)
    {
        next_nr = WorkMap.map[c.i][c.j + 1];
        next_c.i = c.i;
        next_c.j = c.j + 1;
    }
    return next_c;
}

// Generates the final waypoints by removing all redundant waypoints in the path.
int GenerateRoute()
{
    int i_change = 0, j_change = 0, route_index = 0;
    WaypointCells[route_index++] = PathCells[0];
    for (int i = 1; i < nWaypoints; ++i)
    {
        if (!i_change)
            if (PathCells[i].i - PathCells[i - 1].i != 0)
            {
                i_change++;
            }
        if (!j_change)
            if (PathCells[i].j - PathCells[i - 1].j != 0)
            {
                j_change++;
            }
        if (abs(i_change) && abs(j_change)) // Did both i and j values change? (Did the ePuck turn?)
        {
            WaypointCells[route_index++] = PathCells[i-- - 1]; // If the ePuck turned, add waypoint.
            i_change = 0;
            j_change = 0;
        }
    }
    WaypointCells[route_index++] = PathCells[nWaypoints - 1]; // The goal has to be the last waypoint.
    return route_index;
}

// Plans the shortest waypoint path between start and goal.
void Plan(Cell start, Cell goal)
{
    // Comment out the algorithm below which will not be used.
    Search(start, goal);
    // AStarSearch(start, goal);    
    Cell curr = start;
    Cell next;
    nWaypoints = 0;
    printf("C:(%d, %d) (Start)\n", curr.i, curr.j);
    do
    {
        next = GetNextNeighbour(curr);
        if (nWaypoints)
            WorkMap.map[curr.i][curr.j] = MAP_TRACE;
        PathCells[nWaypoints] = next;
        nWaypoints++;
        printf("C:(%d, %d) (MVal: %d)\n", next.i, next.j, WorkMap.map[next.i][next.j]);
        if (curr.i == next.i && curr.j == next.j)
        {
            printf("PATH NOT FOUND\n");
            exit(0);
        }
        curr = next;
    } while (WorkMap.map[curr.i][curr.j] != MAP_GOAL);
}

// Calculates and updates the estimated position of the ePuck by approximation.
void UpdatePosition()
{
    newSteps = GetSteps();
    diffSteps.l = newSteps.l - prevSteps.l;
    diffSteps.r = newSteps.r - prevSteps.r;
    double diffmmL = (diffSteps.l) / STEPS_PER_MM;
    double diffmmR = (diffSteps.r) / STEPS_PER_MM;

    double dist = (diffmmL + diffmmR) / 2;
    double ang = (diffmmR - diffmmL) / CRD;

    double dx = dist * cos(ang / 2);
    double dy = dist * sin(ang / 2);

    prevSteps = newSteps;
    RobPos.x += dx * cos(thPrev) - dy * sin(thPrev);
    RobPos.y += dx * sin(thPrev) + dy * cos(thPrev);

    double th = NormAng(ang + thPrev);
    RobPos.th = th;
    thPrev = th;

    CurrCell = TranslateCoordToCell(RobPos.x, RobPos.y);

    // Keeps track of the last visited cell that was part of the calculated path.
    for (int i = 1; i < nWaypoints; ++i)
    {
        if (PathCells[i].i == CurrCell.i && PathCells[i].j == CurrCell.j)
        {
            PrevCell.i = PathCells[i - 1].i;
            PrevCell.j = PathCells[i - 1].j;
        }
    }
}

int ResponseToVel(float response)
{
    // If the response is 0.33, the linear speed should be 0.
    const double limit = 0.33;
    return -(limit - response) * VMAX_;
}

double ResponseToRot(float response)
{
    // If the response is 0.5, the rotation speed should be 0.
    const double limit = 0.5;
    double factor = (limit - response);
    return factor * PI * ROTFACTOR;
}

void GotoAvoidRules(double xt, double yt)
{
    // GoTo -----------------------------------------------------------
    double dx, dy;
    FPred Pos_Left, Pos_Right, Pos_Ahead, Pos_Here;

    // Compute Eth and Epos
    dx = xt - RobPos.x;
    dy = yt - RobPos.y;
    Epos = sqrt(pow(dx, 2) + pow(dy, 2));
    Eth = NormAng(atan2(dy, dx) - RobPos.th);

    Pos_Left = RampUp(Eth, 0, PI / 3.0);
    Pos_Right = RampDown(Eth, PI / -3.0, 0);
    Pos_Ahead = min(RampUp(Eth, PI / -7.0, 0), RampDown(Eth, 0, PI / 7.0));
    Pos_Here = RampDown(Epos, 5, 50);

    // Avoid -----------------------------------------------------------
    FPred Obs_Left, Obs_Right, Obs_Ahead, Obs_Back;

    IR = GetIR();
    Obs_Left = RampUp(max(IR.sensor[5], IR.sensor[6]), 300, 1000);
    Obs_Right = RampUp(max(IR.sensor[1], IR.sensor[2]), 300, 1000);
    Obs_Ahead = RampUp(max(IR.sensor[0], IR.sensor[7]), 200, 800);

    RULESET;
    // Rotation rules
    IF(AND(Pos_Left, NOT(Obs_Left)));
    ROT(LEFT);
    IF(AND(AND(Obs_Right, NOT(Obs_Left)), NOT(Pos_Ahead)));
    ROT(LEFT);
    IF(AND(Pos_Ahead, Obs_Right));
    ROT(LEFT);

    IF(AND(Pos_Right, NOT(Obs_Right)));
    ROT(RIGHT);
    IF(AND(AND(Obs_Left, NOT(Obs_Right)), NOT(Pos_Ahead)));
    ROT(RIGHT);
    IF(AND(Pos_Ahead, Obs_Left));
    ROT(RIGHT);

    IF(AND(Pos_Ahead, NOT(Obs_Ahead)));
    ROT(AHEAD);

    // Velocity rules
    IF(AND(AND(AND(Pos_Ahead, NOT(Pos_Here)), AND(NOT(Obs_Left), NOT(Obs_Right))), NOT(Obs_Ahead)));
    VEL(FAST);

    IF(OR(Pos_Here, NOT(Pos_Ahead)));
    VEL(NONE);
    IF(Obs_Ahead);
    VEL(NONE);

    IF(AND(OR(Obs_Right, Obs_Left), NOT(Obs_Ahead)));
    VEL(SLOW);

    RULEEND;
}

// MATLAB generated function which calculates distance from the ePuck to an obstacle.
double ObsDistance(int IRvalue, float F)
{
    return (8.7 * pow(10, -7) * pow(IRvalue, 2) - 0.0087 * IRvalue + 23) * F;
}

// Update a cell with a detected object.
void SetObstacle(float offsetAngle, float distance)
{
    // Check in which cell the IR sensor detected something.
    Cell c = TranslateCoordToCell(cos(RobPos.th + offsetAngle) * (distance + ROBOT_RAD) + RobPos.x,
                                  sin(RobPos.th + offsetAngle) * (distance + ROBOT_RAD) + RobPos.y);

    int cVal = WorkMap.map[c.i][c.j];
    if (cVal != MAP_OBSTACLE && cVal != MAP_BORDER)
    {
        // printf("Obstacle not in map!\n");
        InitMap.map[c.i][c.j] = MAP_OBSTACLE;
        if (cVal == MAP_TRACE)
        {
            ObsDetected = 1;
        }
    }
}

// Scans for nearby obstacles.
int DetectObstacle()
{
    IR = GetIR();
    int obsAheadVal = 500;
    int obsLeftVal = 700;
    int obsRightVal = 700;
    double distOffset = 15.0;

    if (IR.sensor[0] > obsAheadVal || IR.sensor[7] > obsAheadVal)
    {
        double distAvg = ObsDistance(max(IR.sensor[0], IR.sensor[7]), DIST_F_AHEAD);
        SetObstacle(0.0, distAvg + distOffset);
    }

    if (IR.sensor[2] > obsRightVal)
    {
        double distance = (ObsDistance(IR.sensor[2], DIST_F_RIGHT));
        SetObstacle(-PI / 2, distance + distOffset);
    }

    if (IR.sensor[5] > obsLeftVal)
    {
        double distance = (ObsDistance(IR.sensor[5], DIST_F_LEFT));
        SetObstacle(PI / 2, distance + distOffset);
    }

    return ObsDetected;
}

void GoToAvoid_fuzzy(double xt, double yt)
{
    double vlin, vrot;
    do
    {
        // New detected obstacle in the current planned path? Abort and replan.
        if (DetectObstacle() && !ReturningtoPrev)
        {
            Stop();
            return;
        }

        UpdatePosition();
        ClearFSet(f_set_vlin);
        ClearFSet(f_set_vrot);
        GotoAvoidRules(xt, yt);

        DeFuzzify(f_set_vrot, 3, &f_vrot);
        DeFuzzify(f_set_vlin, 4, &f_vlin);

        vlin = ResponseToVel(f_vlin);
        vrot = ResponseToRot(f_vrot);

        SetPolarSpeed(vlin, vrot);
        Sleep(10);
    } while (Epos > 30);
    Stop();
}

// New obstacle aborted current run. Plan a new route.
void Replan()
{
    printf("Added obstacle to cell ahead. Replanning!\n");

    // Updating Map with new obstacles
    SaveMapToFile(&InitMap, SYM, MapFile_Save);
    WorkMap = *CreateMapFromFile(SYM, MapFile_Save);

    ObsDetected = 0;

    // Sets the new position to start from
    Cell RobCell = TranslateCoordToCell(RobPos.x, RobPos.y);
    if (WorkMap.map[RobCell.i][RobCell.j] == MAP_OBSTACLE)
    {
        // Obstacle detected in same cell as ePuck. Return to last visited path cell.
        ReturningtoPrev = 1;
        prevpos = TranslateCelltoCoords(PrevCell);
        printf("Going back to prev cell\n");
        GoToAvoid_fuzzy(prevpos.x, prevpos.y);
        ReturningtoPrev = 0;

        if (WorkMap.map[PrevCell.i][PrevCell.j] != MAP_OBSTACLE)
        {
            StartCell.i = PrevCell.i;
            StartCell.j = PrevCell.j;
        }
    }
    else
    {
        StartCell.i = RobCell.i;
        StartCell.j = RobCell.j;
    }

    // Resets used lists
    memset(PathCells, 0, sizeof(PathCells));
    memset(WaypointCells, 0, sizeof(WaypointCells));
    memset(WaypointsCoords, 0, sizeof(WaypointsCoords));
}

// Goes through a list of waypoints to instruct the ePuck where to go.
void Track(Position positions[], int size)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        printf("Track position coords: (%.2lf, %.2lf)\n", positions[i].x, positions[i].y);
        GoToAvoid_fuzzy(positions[i].x, positions[i].y);
        if (ObsDetected)
        {
            // Abort the track to replan
            return;
        }
    }
}

// Evaluates the four neighbours of a cell while gradient following. Returns the current best choice.
Cell GetBestGradient(Cell robc)
{
    double next_nr = 99999.99;
    Cell next_c;
    Cell neighbours[4] = {{robc.i, robc.j - 1},
                          {robc.i - 1, robc.j},
                          {robc.i + 1, robc.j},
                          {robc.i, robc.j + 1}};
    for (int i = 0; i < 4; ++i)
    {
        neighbours[i].h_value = HValueList[neighbours[i].i][neighbours[i].j];

        double cellVal = WorkMap.map[neighbours[i].i][neighbours[i].j];
        double cellH = HValueList[neighbours[i].i][neighbours[i].j] + cellVal;

        if (cellH < next_nr && cellH > 0.0 &&
            cellVal != MAP_BORDER &&
            cellVal != MAP_OBSTACLE)
        {
            next_c.i = neighbours[i].i;
            next_c.j = neighbours[i].j;
            next_c.h_value = next_nr = neighbours[i].h_value = cellH;
        }
        else if (WorkMap.map[neighbours[i].i][neighbours[i].j] == MAP_GOAL)
        {
            next_c = GoalCell;
            break;
        }
    }
    return next_c;
}

// Function for making the ePuck follow the gradient.
void FollowGradient()
{
    InitMap = *CreateMapFromFile(SYM, MapFile_Gradient);
    WorkMap = *CreateMapFromFile(SYM, MapFile_Gradient);

    WorkMap.map[StartCell.i][StartCell.j] = MAP_START;
    WorkMap.map[GoalCell.i][GoalCell.j] = MAP_GOAL;
    do
    {
        Search(StartCell, GoalCell);
        PrintMap(&WorkMap);
        Cell newCell = GetBestGradient(CurrCell);
        Position coords = TranslateCelltoCoords(newCell);
        GoToAvoid_fuzzy(coords.x, coords.y);
        StartCell = CurrCell;

    } while (!(CurrCell.i == GoalCell.i && CurrCell.j == GoalCell.j));
    printf("End of FollowGradient\n");
}

// Wrapper function for being able to use Track() again after a run is done.
void FollowPath()
{
    InitMap = *CreateMapFromFile(SYM, MapFile_Save);
    WorkMap = *CreateMapFromFile(SYM, MapFile_Save);
    int run = 1;

    while (run)
    {
        WorkMap.map[StartCell.i][StartCell.j] = MAP_START;
        WorkMap.map[GoalCell.i][GoalCell.j] = MAP_GOAL;

        Plan(StartCell, GoalCell);
        PrintMap(&WorkMap);

        int nRoutes = GenerateRoute();
        TranslateCellsToCoords(nRoutes);
        PrintWaypoints(nRoutes);
        Track(WaypointsCoords, nRoutes);
        if (ObsDetected)
            Replan();
        else
            run = 0;
    }
    printf("End of FollowPath\n");
    SaveMapToFile(&InitMap, SYM, MapFile_Save);
}

int main(int argc, char *argv[])
{
    epuck(ROBOT_NUMBER);
    printf("Starting...\n");
    init();
    Menu();
    printf("Done...\n");
    return (0);
}

// Reseting map to empty
void init()
{
    InitMap = *CreateMapFromFile(SYM, MapFile_Empty);
    WorkMap = *CreateMapFromFile(SYM, MapFile_Empty);
    SaveMapToFile(&InitMap, SYM, MapFile_Save);
}

// A simple console interface menu to simplify the use.
void Menu()
{
    int run = 1;
    char c;
    while (run)
    {
        do
        {
            if (c != '\n')
            {
                printf("\n---------------Menu---------------\n");
                printf("1. Enter destination (Follow Path)\n");
                printf("2. Follow Path (S: (%d, %d), G: (%d, %d))\n",
                       StartCell.i, StartCell.j, GoalCell.i, GoalCell.j);
                printf("3. Follow Gradient (S: (%d, %d), G: (%d, %d))\n",
                       StartCell.i, StartCell.j, GoalCell.i, GoalCell.j);
                printf("4. Measure search algorithm time\n");
            }
            c = getchar();
            switch (c)
            {
            case '1':
            {
                StartCell = PrevCell = CurrCell;
                printf("Destination: ");
                scanf("%d %d", &GoalCell.i, &GoalCell.j);
                FollowPath();
            }
            break;
            case '2':
                FollowPath();
                break;
            case '3':
                FollowGradient();
                break;
            case '4':
                TimeMeasureAstarBFS();
                break;
            case 'q':
                run = 0;
                break;
            default:
                break;
            }
        } while (c != '\n');
    }
}

// Print the onboard IR-sensors output values.
void PrintIRValues()
{
    IR = GetIR();
    printf("IR values:\n %4d  %4d\n%4d    %4d\n%4d    %4d\n\n",
           IR.sensor[7], IR.sensor[0], IR.sensor[6], IR.sensor[1],
           IR.sensor[5], IR.sensor[2]);
}

// Prints the calculated distances from IR sensors to objects.
void PrintDistances()
{
    IR = GetIR();
    printf("Distances:\nAhead: %.2lf\nLeft: %.2lf\nRight: %.2lf\n\n",
           (ObsDistance(IR.sensor[0], 0) + ObsDistance(IR.sensor[7], 0)) / 2,
           ObsDistance(IR.sensor[5], 0), ObsDistance(IR.sensor[2], 0));
}

// Translates the position of each waypoint cell into real coordinates.
void TranslateCellsToCoords(int nCoords)
{
    for (int i = 0; i < nCoords; ++i)
    {
        Position coords = TranslateCelltoCoords(WaypointCells[i]);
        WaypointsCoords[i].x = coords.x;
        WaypointsCoords[i].y = coords.y;
    }
}

// Translate a map cell into coordinates.
Position TranslateCelltoCoords(Cell c)
{
    double x = (c.j - RefCell.j) * mmCell;
    double y = (RefCell.i - c.i) * mmCell;
    Position coords = {x, y};
    return coords;
}

// Translate coordinates into a map cell.
Cell TranslateCoordToCell(float x, float y)
{
    Cell result;
    result.j = round(x / mmCell + RefCell.j);
    result.i = round(RefCell.i - y / mmCell);
    return result;
}

// Calculates heuristic value with the Pythagorean theorem.
double heuristic(int i, int j, Cell c)
{
    int di = i - c.i;
    int dj = c.j - j;
    return sqrt(pow(di, 2) + pow(dj, 2));
}

// Translates an angle to a value between -PI and PI.
double NormAng(double a)
{
    double norm_a = a;
    if (a > PI)
        norm_a -= 2 * PI;
    else if (a < -PI)
        norm_a += 2 * PI;
    return norm_a;
}

// Prints the waypoint cells to visit in the current run.
void PrintWaypoints(int nCoords)
{
    printf("Generated:   Translated:\n");
    for (int i = 0; i < nCoords; ++i)
    {
        printf("(%d, %d)    (%.1lf, %.1lf)\n",
               WaypointCells[i].i, WaypointCells[i].j, WaypointsCoords[i].x, WaypointsCoords[i].y);
    }
}