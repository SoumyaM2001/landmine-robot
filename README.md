BLOCK 1: RADAR SYSTEM (Arduino UNO–1)
Components
•	Ultrasonic Sensor (HC-SR04)
•	Servo Motor
•	OLED Display
•	Arduino UNO–1
Function
This block detects obstacles and measures distance using a radar-like scanning method.
Working
1.	The servo motor rotates from 0° to 180° and back.
2.	At each angle:
	Ultrasonic sensor sends a sound pulse.
	Measures echo time to calculate distance.
3.	Distance data is:
	Displayed as a radar screen on OLED
	Sent to Arduino UNO–2 via Serial communication
4.	Objects appear as dots on radar, showing:
	Angle
	Distance (0–300 cm)
This block acts as the eye of the robot
BLOCK 2: COMMUNICATION BLOCK
Function
Transfers real-time radar data between two Arduinos.
Data Format
Angle,Distance
Example: 90,45
 Ensures obstacle information reaches the robot controller instantly.
________________________________________
BLOCK 3: LANDMINE DETECTION & ROBOT CONTROL (Arduino UNO–2)
Components
•	Arduino UNO–2
•	DC Motors + Motor Driver
•	Metal Detector Sensor
•	Buzzer
•	LEDs
•	Bluetooth Module (HC-05)
________________________________________
FUNCTIONAL OPERATIONS
Robot Movement Control
•	Controlled via Bluetooth mobile app
•	Commands:
F → Forward
B → Backward
L → Left
R → Right
S → Stop
________________________________________
Obstacle Detection (Ultrasonic Data)
•	Distance data received from Arduino–1
•	If obstacle detected between 5 cm and 15 cm:
o	Robot stops automatically
o	Buzzer and LEDs turn ON
o	Prevents collision
________________________________________ 
Landmine / Metal Detection
•	Metal sensor continuously checks ground
•	If metal detected:
o	Robot stops immediately
o	Moves slightly backward
o	Ambulance siren sound
o	LEDs blink
•	Indicates possible landmine presence
This ensures human safety
________________________________________
 BLOCK 4: ALERT SYSTEM
Components
•	Buzzer
•	LEDs
Function
•	Provides audio-visual warning
•	Activated during:
o	Metal detection
o	Close obstacle detection
________________________________________
BLOCK 5: BLUETOOTH MONITORING
Function
•	Sends live data to mobile:
•	A:Angle , D:Distance
•	User can:
o	Monitor radar data
o	Control robot remotely
________________________________________
OVERALL PROJECT FUNCTION (IN ONE FLOW)
1.	Radar system scans surroundings.
2.	Distance and angle are calculated.
3.	Data sent to robot controller.
4.	Robot moves as per Bluetooth command.
5.	If obstacle detected → robot stops.
6.	If metal detected → alarm activates.
7.	OLED + Mobile app show real-time status.
