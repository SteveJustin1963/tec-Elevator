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

## MINT program

```
// TEC-1 Elevator Controller
// Variables:
// c - current floor (1-25)
// t - target floor
// s - state (0=stop, 1=up fast, 2=down fast, 3=slow up, 4=slow down, 5=door open)
// d - door state (0=closed, 1=opening, 2=open, 3=closing)
// q - queue of floors to visit [array]
// h - human detected flag
// f - at floor sensor
// r - random number for quirky behavior

// Initialize all variables
:I 1 c!                    // Start at floor 1
  0 s!                     // Initially stopped
  0 d!                     // Door closed
  \[0 0 0 0 0] q!         // Empty queue
  0 h!                     // No human detected
  1 f!                     // At floor sensor true
;

// Display current status
:D `Floor: ` c . /N
   `State: `
   s 0 = (`Stopped` /N) /E
   s 1 = (`Going Up Fast` /N) /E
   s 2 = (`Going Down Fast` /N) /E
   s 3 = (`Slowing Up` /N) /E
   s 4 = (`Slowing Down` /N) /E
   s 5 = (`Door Operating` /N)
   `Door: `
   d 0 = (`Closed` /N) /E
   d 1 = (`Opening` /N) /E
   d 2 = (`Open` /N) /E
   d 3 = (`Closing` /N)
;

// Open door routine
:O d 0 = (               // If door closed
     1 d!                // Start opening
     100()              // Wait
     2 d!                // Door fully open
     200()              // Keep open
     h 0 = (            // If no human
        3 d!             // Start closing
        100()           // Wait
        0 d!             // Door closed
     )
  )
;

// Check if need to slow down
:S t c - " * 2 < (      // If within 2 floors of target
     s 1 = (3 s!)       // If going up, slow up
     s 2 = (4 s!)       // If going down, slow down
  )
;

// Move one floor up or down
:M s 1 = s 3 = +(       // If going up (fast or slow)
     c 1 + c!
  ) /E (
     c 1 - c!           // Else going down
  )
  // Random chance of stopping between floors
  25 /K 24 = (0 f!) /E (1 f!)
;

// Process floor request
:R t c = (              // If at target floor
     0 s!               // Stop
     5 s!               // Door operation state
     O                  // Open door
     0 s!               // Back to stopped
  ) /E (
     f 1 = (            // If at a floor
        t c > (         // Target above us
           s 0 = (1 s!) // Start going up
        ) /E (          // Target below us
           s 0 = (2 s!) // Start going down
        )
        S               // Check if need to slow
        M               // Move one floor
     )
  )
;

// Main control loop
:C `Elevator Controller` /N
   `Enter target floor (1-25): `
   /K 48 - t!           // Get floor number (ASCII to number)
   t 1 < (1 t!)         // Validate minimum floor
   t 25 > (25 t!)       // Validate maximum floor
   /U (                 // Infinite control loop
      D                 // Display status
      R                 // Process floor request
      t c = f 1 = * (   // If at target and at floor
         0 /W           // Break loop
      )
      50()              // Small delay
   )
;

// Simulate human detection (toggles h flag)
:H h 0 = (1 h!) /E (0 h!) ;

// Run system with I then C

```


Key Components:

1. State Variables:
   - c: Current floor (1-25)
   - t: Target floor
   - s: State (0=stop, 1=up fast, 2=down fast, 3=slow up, 4=slow down, 5=door)
   - d: Door state (0=closed, 1=opening, 2=open, 3=closing)
   - h: Human detection flag
   - f: At floor sensor

2. Main Functions:
   - I: Initialize system
   - D: Display status
   - O: Door operation routine
   - S: Slow down check
   - M: Move one floor
   - R: Process floor request
   - C: Main control loop
   - H: Toggle human detection

Safety Features:
1. Door won't close if human detected
2. Elevator slows down before target floor
3. Floor number validation
4. Random chance of stopping between floors
5. State-based movement control

To use the system:

1. Run `I` to initialize
2. Run `C` to start control loop
3. Enter target floor when prompted
4. Use `H` to simulate human detection

The system will:
1. Display current status
2. Control speed based on distance to target
3. Handle door operations safely
4. Stop when target reached

 
 

