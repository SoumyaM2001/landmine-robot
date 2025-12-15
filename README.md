System Overview

The Landmine Detection Robot is designed with a modular block architecture to ensure accurate sensing, safe navigation, and reliable user control. Block 1 (Radar System – Arduino UNO-1) functions as the eye of the robot. It uses an HC-SR04 ultrasonic sensor mounted on a servo motor that continuously scans from 0° to 180° and back. At each angle, the ultrasonic sensor emits a sound pulse and measures the echo time to calculate distance. This real-time distance and angle data is visualized as a radar-like display on an OLED screen, where obstacles appear as dots representing their position within a range of 0–300 cm. The same data is simultaneously transmitted to the second Arduino through serial communication.

Block 2 (Communication Block) ensures fast and reliable transfer of radar data between the two Arduino boards. The data is sent in a simple and efficient format as Angle,Distance (for example, 90,45), allowing the robot controller to instantly receive obstacle information without delay.

Block 3 (Landmine Detection and Robot Control – Arduino UNO-2) is responsible for motion control, safety logic, and metal detection. The robot is driven using DC motors controlled via a motor driver, and movement commands are received through a Bluetooth module (HC-05) from a mobile application. The robot responds to standard commands such as Forward, Backward, Left, Right, and Stop. Ultrasonic data received from Arduino UNO-1 is continuously monitored, and if an obstacle is detected within 5 cm to 15 cm, the robot automatically stops and activates warning indicators to prevent collision. Additionally, a metal detector sensor continuously scans the ground, and upon detecting metal, the robot immediately stops, moves slightly backward, triggers an ambulance-style siren sound, and blinks LEDs to indicate a potential landmine, ensuring human safety.

Block 4 (Alert System) provides critical audio-visual feedback using a buzzer and LEDs. This system is activated during close obstacle detection or metal detection events, ensuring clear and immediate warnings in hazardous situations.

Block 5 (Bluetooth Monitoring) enables real-time data monitoring on a mobile device. Live radar information in the format A:Angle, D:Distance is sent to the mobile app, allowing users to visually track obstacle positions while remotely controlling the robot.

Overall, the system operates in a seamless flow where the radar scans the environment, calculates distance and angle, transmits data to the robot controller, and allows user-controlled movement through Bluetooth. Automatic safety mechanisms stop the robot during obstacle detection or metal detection, while the OLED display and mobile application continuously provide real-time status updates, making the system reliable, intelligent, and suitable for landmine detection applications.

Project Repository

All project-related resources, including the block diagram, circuit diagram, and complete Arduino source code for all modules, are available in the public GitHub repository. The repository is well-organized into separate folders for hardware diagrams and software programs, making it easy to understand and replicate the system.

🔗 GitHub Repository:
👉 https://github.com/SoumyaM2001/landmine-robot

Contents of the Repository:
Block Diagram – Overall system architecture and module interconnections
Circuit Diagram – Detailed wiring of Arduino UNO, sensors, motors, and modules

Source Code –
Radar System (Arduino UNO–1)
Robot Control & Landmine Detection (Arduino UNO–2)

This repository serves as a complete reference for understanding, building, and further enhancing the Landmine Detection Robot system.
