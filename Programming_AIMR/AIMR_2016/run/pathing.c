#include "ourlibs/pathing.h"


char convertMapSymbol(char input) {
    switch (input){
        case 0:
            return 'G';
        case -1:
            return 'W';
        case -2:
            return ' ';
        case -3:
            return '#';
        case -4:
            return 'R';
        default:
            return input;
    }
}

void printGrid(){
    printf("\n");
    for (int i=0; i < 15; i++) {
        for (int j=0; j < 15; j++) {

            if (Grid[i][j] <= 0){
                printf("%c  ", convertMapSymbol(Grid[i][j]));
            }
            else {
                printf("%d ", Grid[i][j]);
                if (Grid[i][j] <= 9)
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("Width: %3d  Height: %3d\n", 15, 15);
}

void MarkCell(int i, int j, int value){
    Cell cell = {i, j, 0.0};
    switch (Grid[i][j]){
        case -1:    // Out of boundaries
            break;
        case -2:    // Unexplored cell
            Grid[i][j] = value;
            Push(&Queuea, cell);
            break;
        case -3:    // Obstacle
            break;
        case -4:    // Initial position
            Push(&Queuea, cell);
            break;
        default:    // Already explored
            break;
    }
}


void Search(Cell target, Cell robot){
    ClearList(&Queuea, FIFO);
    Push(&Queuea, target);
    while (!IsListEmpty(&Queuea)){
        Cell current = Pop(&Queuea);
        if (current.i == robot.i && current.j == robot.j)
            break;
        int dist = Grid[current.i][current.j] + 1;
        MarkCell(current.i, current.j - 1, dist);
        MarkCell(current.i, current.j + 1, dist);
        MarkCell(current.i - 1, current.j, dist);
        MarkCell(current.i + 1, current.j, dist);
    }
    printGrid();
}
