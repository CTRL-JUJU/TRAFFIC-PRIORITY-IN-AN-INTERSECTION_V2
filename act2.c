#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define LINE_SIZE 100

typedef struct {
    char movement[MAX];
    int time;
} Traffic;

Traffic createTraffic(char *movement, int time);
void displayTraffic(Traffic t);
int calculateTimeBeforePedestrianCross(Traffic *list, int size);

int main() {
    FILE *fpInput, *fpOutput;
    int result = 0;

    fpInput = fopen("traffic.csv", "r");
    if (fpInput != NULL) {
        fpOutput = fopen("traffic_result.dat", "w");
        if (fpOutput != NULL) {
            char line[LINE_SIZE];
            while (fgets(line, sizeof(line), fpInput)) {
                Traffic list[10];
                int count = 0;
                char *token = strtok(line, ",");
                while (token != NULL && count < 10) {
                    char movement[MAX];
                    int time;
                    sscanf(token, "%[^:]:%d", movement, &time);
                    list[count++] = createTraffic(movement, time);
                    token = strtok(NULL, ",");
                }
                int totalTime = calculateTimeBeforePedestrianCross(list, count);
                fprintf(fpOutput, "Total time before main pedestrian can cross: %d\n", totalTime);
            }
            fclose(fpOutput);
        } else {
            result = 1;
        }
        fclose(fpInput);
    } else {
        result = 1;
    }

    if (result != 0) {
        printf("Error opening file.\n");
    } else {
        printf("Results have been written to traffic_result.dat\n");
    }
    
    return result;
}

Traffic createTraffic(char *movement, int time) {
    Traffic T;
    strncpy(T.movement, movement, MAX);
    T.time = time;
    return T;
}

int calculateTimeBeforePedestrianCross(Traffic *list, int size) {
    int time = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(list[i].movement, "pedestrian_main") != 0) {
            time += list[i].time;
        }
    }
    return time;
}

void displayTraffic(Traffic t) {
    printf("Movement: %s, Time: %d\n", t.movement, t.time);
}
