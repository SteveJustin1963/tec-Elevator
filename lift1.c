https://gregoryalfordblog.wordpress.com/2017/05/30/pseudocoding-an-elevator/

The building is 25 stories high and will respond to only the following commands:

“open elevator door”
“close elevator door”
“go up full speed”
“go down full speed”
“slow down”
“stop”
The elevator accepts user input for:

floor buttons inside the elevator
door open and close buttons inside the elevator
up and down call buttons on each floor
Has sensors for:

if a human is in the door closing path
if it is currently at a floor (instead of in-between floors)
Has a few quirky requirements:

it must “slow down” at least 1 floor before it stops.
there is a small chance that it actually stops between floors by accident (it’s an old elevator)

write a c program to control the lift
==============================================
 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int main()
{
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
 
    // seed the random number generator
    srand(time(NULL));
 
    // loop forever
    while (1)
    {
        // if the door is open, wait for input
        if (door_open)
        {
            printf("\n");
            printf("----- Floor %d -----\n", floor);
            printf("\n");
            printf("Please select one of the following options:\n");
            printf("1 - Call elevator to this floor\n");
            printf("2 - Close door\n");
            printf("3 - Exit program\n");
            printf("\n");
            printf("Enter your selection: ");
 
            // get the user's selection
            int selection;
            scanf("%d", &selection);
 
            // if the user wants to call the elevator
            if (selection == 1)
            {
                // set the target floor
                target_floor = floor;
 
                // if the elevator is already on this floor, open the door
                if (target_floor == floor)
                {
                    door_open = 1;
                    stopped = 1;
                }
                // otherwise, set the direction and start moving
                else
                {
                    if (target_floor > floor)
                        direction = 1;
                    else
                        direction = -1;
 
                    door_open = 0;
                    stopped = 0;
                    speed = 0.1;
                }
            }
 
            // if the user wants to close the door
            else if (selection == 2)
            {
                // if there's someone in the way, don't close the door
                if (human_in_path)
                {
                    printf("You must wait until the person has left the door way before closing.\n");
                }
                else
                {
                    door_closing = 1;
                }
            }
            // if the user wants to quit
            else if (selection == 3)
            {
                return 0;
            }
            // otherwise, the user made an invalid selection
            else
            {
                printf("Invalid selection. Please try again.\n");
            }
        }
        // if the door is closing, wait for it to close
        else if (door_closing)
        {
            printf("Door is closing.\n");
 
            // wait for the door to close all the way
            door_open = 0;
            door_closing = 0;
        }
        // otherwise, the elevator is in motion
        else
        {
            if (human_in_path)
            {
                printf("There is someone in the door way. Door cannot close.\n");
            }
            // if the elevator is at the target floor, open the door
            else if (target_floor == floor)
            {
                door_open = 1;
                stopped = 1;
                speed = 0;
            }
            // otherwise, keep moving
            else
            {
                printf("Elevator is moving %s at %.2f m/s.\n",
                    (direction == 1 ? "up" : "down"),
                    speed);
 
                // move to the next floor
                floor += direction;
 
                // randomly stop between floors
                if (rand() % 10 == 0)
                {
                    printf("Elevator has stopped between floors by accident.\n");
 
                    door_open = 1;
                    stopped = 1;
                    speed = 0;
                }
 
                // randomly slow down
                if (rand() % 10 == 0)
                {
                    printf("Elevator is slowing down.\n");
 
                    speed /= 2;
                }
 
                // randomly speed up
                if (rand() % 10 == 0)
                {
                    printf("Elevator is speeding up.\n");
 
                    speed *= 2;
                }
 
                // if we're going down, stop 1 floor before the target
                if (direction == -1 && target_floor - floor == 1)
                {
                    printf("Elevator is slowing down.\n");
                    printf("Elevator is stopping at the next floor.\n");
 
                    speed /= 2;
                }
            }
        }
    }
}
