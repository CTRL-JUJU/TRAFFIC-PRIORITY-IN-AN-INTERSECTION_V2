#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct {
    char movement[MAX];
    int time;
} Traffic;

Traffic createTraffic(char *movement, int time);
void displayTraffic(Traffic t);

int main() {
    FILE *fp;

    Traffic list[10];
    list[0] = createTraffic("main_lane", 15);
    list[1] = createTraffic("diversion_lane", 25);
    list[2] = createTraffic("left_main", 25);
    list[3] = createTraffic("right_main", 30);
    list[4] = createTraffic("left_diversion", 30);
    list[5] = createTraffic("right_diversion", 35);
    list[6] = createTraffic("pedestrian_main", 40);
    list[7] = createTraffic("pedestrian_diversion", 45);
    list[8] = createTraffic("main_lane", 50);
    list[9] = createTraffic("diversion_lane", 50);

    // create file
    fp = fopen("traffic.dat", "wb");
    if (fp != NULL) {
        fwrite(list, sizeof(Traffic), 10, fp);
        fclose(fp);
    }

    // read file
    fp = fopen("traffic.dat", "rb");
    int time = 0;
    if (fp != NULL) {
        Traffic T;
        while (fread(&T, sizeof(Traffic), 1, fp)) {
            if (strcmp(T.movement, "pedestrian_main") != 0) {
                time += T.time;
            }
        }
        fclose(fp);
    }

    printf("Total time before a main pedestrian can cross: %d\n", time);
    return 0;
}

void displayTraffic(Traffic t) {
    printf("\nMovement: %s, Time: %d", t.movement, t.time);
}

Traffic createTraffic(char *movement, int time) {
    Traffic T;
    strcpy(T.movement, movement);
    T.time = time;
    return T;
}
