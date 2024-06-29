# Health of 3-Phase Supply

This project monitors the health of a 3-phase electrical supply, focusing on critical electrical parameters required for the safe operation of equipment.

#Energy Efficiency Monitoring System <br>
##Project Overview
The Energy Efficiency Monitoring System is a project developed as part of an internship at Hioctane Labs. The system is designed to monitor the energy efficiency of electrical equipment by tracking key electrical parameters. The project uses the STM32F103 microcontroller to collect data from an MFM384 multi-function meter and analyze the collected data for energy efficiency assessment.

Table of Contents
Project Description
Features
Hardware Components
Software Components
Installation
Usage
Code Structure
Contributing
License
Acknowledgments
Project Description
The Energy Efficiency Monitoring System monitors the health of a 3-phase electrical supply, focusing on critical parameters such as energy consumption (kWh), voltage, and current. The system uses an MFM384 multi-function meter to collect these readings and processes the data using an STM32F103 microcontroller. The data collected from the MFM384 meter can be used for analyzing the energy efficiency of the electrical equipment.

Features
Real-time monitoring of electrical parameters (kWh, voltage, current)
Data collection from MFM384 multi-function meter
Analysis of energy efficiency of electrical equipment
Hardware Components
STM32F103 Microcontroller: Main controller for data processing.
MFM384 Multi-Function Meter: Measures electrical parameters such as kWh, voltage, and current.
RS485 to TTL Converter: Facilitates communication between the MFM384 meter and STM32F103 microcontroller.
Various Connectors and Cables: For hardware connections.
Software Components
STM32CubeIDE: Development environment for STM32 microcontroller programming.
Modscan Application: Used for reading data from the MFM384 meter.
SerialMon Application: For sniffing data packets.
Custom Firmware: Embedded code for data collection and processing. The main code is located in the main.c file.
Installation
Clone the Repository

bash
Copy code
git clone https://github.com/mohdnaser1604/energy-efficiency-monitoring.git
Open the Project

Open the project in STM32CubeIDE or another STM32-compatible IDE.

Build the Firmware

Compile the project to generate the firmware binary.

Upload to Microcontroller

Use a suitable programmer/debugger to upload the firmware to the STM32F103 microcontroller.

Connect Hardware

Connect the MFM384 meter to the STM32F103 using the RS485 to TTL converter.

Usage
Power On the System

Ensure that all hardware components are properly connected and powered.

Run the Firmware

After uploading the firmware to the microcontroller, it will start collecting data from the MFM384 meter.

Monitor Data

You can use the Modscan application or SerialMon application to view and analyze the collected data.

Code Structure
/src: Contains source code for the STM32 microcontroller firmware. The main code is located in the main.c file.
/inc: Contains header files for the firmware.
/docs: Documentation related to the project.
/scripts: Any auxiliary scripts used for setup or data processing.
Code Overview
main.c: Contains the main code for initializing hardware components, reading data from the MFM384 meter, and processing the data for analysis.
Contributing
Contributions are welcome! Please follow these steps to contribute:

Fork the repository.
Create a new branch for your feature or fix.
Make your changes and commit them.
Push your changes to your forked repository.
Create a pull request describing your changes.
License
This project is licensed under the MIT License. See the LICENSE file for details.

Acknowledgments
Hioctane Labs for providing the opportunity to work on this project.
Dr. Ayesha Naaz, Head, Department of Electronics and Communication Engineering, for the support and guidance.

