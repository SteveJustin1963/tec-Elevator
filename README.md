# tec-Elevator

aka the might Lift

TEC-1 Elevator Controller

https://gregoryalfordblog.wordpress.com/2017/05/30/pseudocoding-an-elevator/

The building is 25 stories high and will respond to only the following commands:
- open elevator door
- close elevator door
- go up full speed
- go down full speed
- slow down
- stop

The elevator accepts user input for:
- floor buttons inside the elevator
- door open and close buttons inside the elevator
- up and down call buttons on each floor

Has sensors for:
- if a human is in the door closing path
- if it is currently at a floor (instead of in-between floors)

Has a few quirky requirements:
- it must “slow down” at least 1 floor before it stops.
- there is a small chance that it actually stops between floors by accident (it’s an old elevator)

## code
- lift1.c
 

