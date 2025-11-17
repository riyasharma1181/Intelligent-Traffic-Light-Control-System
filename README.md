Intelligent Traffic Light Control System
Adaptive Traffic Management using Arduino UNO, IR Sensors, and Emergency Priority Control
Project Overview

This project implements a real-time Intelligent Traffic Light Control System that adjusts signal timing based on vehicle presence. It uses IR sensors to detect traffic density and an emergency switch to give priority to emergency vehicles. The control algorithm is non-blocking using the millis() function, ensuring smooth real-time operation.

Developed as part of the PBL–I & Digital Electronics coursework and demonstrated at the student Exhibition 2025.

Hardware Components

Arduino UNO (ATmega328P)

4 × IR Sensors

LED Indication Units

Emergency Priority Switch

5V Regulated Power Supply

220Ω Resistors

System Workflow

IR sensors detect vehicle presence in each lane.

Arduino reads sensors continuously using non-blocking logic.

Green time is increased or decreased based on detected vehicle density.

Emergency switch forces immediate green on the priority lane.

System resumes normal cycle after emergency duration.

System Architecture
IR Sensors (4 Lanes)
        |
        v
   Arduino UNO  <-- Emergency Switch
        |
        v
 LED Traffic Signal Units (4 Lanes)

Code

The complete Arduino program is available inside the /code/traffic_control.ino file.

Results

Successful adaptive lane timing

Fast emergency override

High accuracy detection

Stable non-blocking behavior

Well-received during IEEE exhibition

Documentation

Full IEEE-style paper, block diagram, schematic, and presentation files are available in the /documentation folder.

Author

Riya Sharma
Guided by: Prof. Deepanath & Prof. Ujjwala Randwale
