#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FLOORS 10

int main() {
    int floor = 0;
    int target_floor;
    int direction;
    int door_open = 1;
    int door_closing = 0;
    int human_in_path = 0;
    float speed = 0;
    int stopped = 0;
 
    printf("Elevator Control Program\n");
    printf("-------------------------\n");

    srand(time(NULL));

    while (1) {
        if (door_open) {
            printf("\n----- Floor %d -----\n", floor);
            printf("Please select one of the following options:\n");
            printf("1 - Call elevator to this floor\n");
            printf("2 - Close door\n");
            printf("3 - Exit program\n");
            printf("Enter your selection: ");
 
            int selection;
            scanf("%d", &selection);

            if (selection == 1) {
                printf("Enter the floor to call the elevator (0 - %d): ", MAX_FLOORS);
                scanf("%d", &target_floor);
 
                if (target_floor == floor) {
                    door_open = 1;
                    stopped = 1;
                } else {
                    if (target_floor > floor)
                        direction = 1;
                    else
                        direction = -1;
 
                    door_open = 0;
                    stopped = 0;
                    speed = 0.1;
                }
            } else if (selection == 2) {
                if (human_in_path) {
                    printf("You must wait until the person has left the doorway before closing.\n");
                } else {
                    door_closing = 1;
                }
            } else if (selection == 3) {
                return 0;
            } else {
                printf("Invalid selection. Please try again.\n");
            }
        } else if (door_closing) {
            if (human_in_path) {
                printf("There is someone in the door way. Door cannot close.\n");
                door_closing = 0;
            } else {
                printf("Door is closing.\n");
                door_open = 0;
                door_closing = 0;
            }
        } else {
            if (target_floor == floor) {
                door_open = 1;
                stopped = 1;
                speed = 0;
            } else {
                printf("Elevator is moving %s at %.2f m/s.\n", (direction == 1 ? "up" : "down"), speed);
                floor += direction;
            }
        }
    }
}
