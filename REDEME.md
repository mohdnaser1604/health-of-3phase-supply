<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Energy Efficiency Monitoring System/ health of 3phase supply</title>
</head>
<body>

<h1>Energy Efficiency Monitoring System</h1>

<h2>Project Overview</h2>
<p>
    The <strong>Energy Efficiency Monitoring System</strong> is a project developed as part of an internship at Hioctane Labs. The system is designed to monitor the energy efficiency of electrical equipment by tracking key electrical parameters. The project uses the STM32F103 microcontroller to collect data from an MFM384 multi-function meter and analyze the collected data for energy efficiency assessment.
</p>

<h2>Table of Contents</h2>
<ul>
    <li><a href="#project-description">Project Description</a></li>
    <li><a href="#features">Features</a></li>
    <li><a href="#hardware-components">Hardware Components</a></li>
    <li><a href="#software-components">Software Components</a></li>
    <li><a href="#installation">Installation</a></li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#code-structure">Code Structure</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
</ul>

<h2 id="project-description">Project Description</h2>
<p>
    The Energy Efficiency Monitoring System monitors the health of a 3-phase electrical supply, focusing on critical parameters such as energy consumption (kWh), voltage, and current. The system uses an MFM384 multi-function meter to collect these readings and processes the data using an STM32F103 microcontroller. The data collected from the MFM384 meter can be used for analyzing the energy efficiency of the electrical equipment.
</p>

<h2 id="features">Features</h2>
<ul>
    <li>Real-time monitoring of electrical parameters (kWh, voltage, current)</li>
    <li>Data collection from MFM384 multi-function meter</li>
    <li>Analysis of energy efficiency of electrical equipment</li>
</ul>

<h2 id="hardware-components">Hardware Components</h2>
<ul>
    <li><strong>STM32F103 Microcontroller</strong>: Main controller for data processing.</li>
    <li><strong>MFM384 Multi-Function Meter</strong>: Measures electrical parameters such as kWh, voltage, and current.</li>
    <li><strong>RS485 to TTL Converter</strong>: Facilitates communication between the MFM384 meter and STM32F103 microcontroller.</li>
    <li><strong>Various Connectors and Cables</strong>: For hardware connections.</li>
</ul>

<h2 id="software-components">Software Components</h2>
<ul>
    <li><strong>STM32CubeIDE</strong>: Development environment for STM32 microcontroller programming.</li>
    <li><strong>Modscan Application</strong>: Used for reading data from the MFM384 meter.</li>
    <li><strong>SerialMon Application</strong>: For sniffing data packets.</li>
    <li><strong>Custom Firmware</strong>: Embedded code for data collection and processing. The main code is located in the <code>main.c</code> file.</li>
</ul>

<h2 id="installation">Installation</h2>
<ol>
    <li>
        <strong>Clone the Repository</strong>
        <pre><code>git clone [(https://github.com/mohdnaser1604/health-of-3phase-supply.git)]</code></pre>
    </li>
    <li><strong>Open the Project</strong>: Open the project in STM32CubeIDE or another STM32-compatible IDE.</li>
    <li><strong>Build the Firmware</strong>: Compile the project to generate the firmware binary.</li>
    <li><strong>Upload to Microcontroller</strong>: Use a suitable programmer/debugger to upload the firmware to the STM32F103 microcontroller.</li>
    <li><strong>Connect Hardware</strong>: Connect the MFM384 meter to the STM32F103 using the RS485 to TTL converter.</li>
</ol>

<h2 id="usage">Usage</h2>
<ol>
    <li><strong>Power On the System</strong>: Ensure that all hardware components are properly connected and powered.</li>
    <li><strong>Run the Firmware</strong>: After uploading the firmware to the microcontroller, it will start collecting data from the MFM384 meter.</li>
    <li><strong>Monitor Data</strong>: You can use the Modscan application or SerialMon application to view and analyze the collected data.</li>
</ol>

<h2 id="code-structure">Code Structure</h2>
<ul>
    <li><strong>/src</strong>: Contains source code for the STM32 microcontroller firmware. The main code is located in the <code>main.c</code> file.</li>
    <li><strong>/inc</strong>: Contains header files for the firmware.</li>
    <li><strong>/docs</strong>: Documentation related to the project.</li>
    <li><strong>/scripts</strong>: Any auxiliary scripts used for setup or data processing.</li>
</ul>

<h2 id="code-overview">Code Overview</h2>
<p>
    <code>main.c</code>: Contains the main code for initializing hardware components, reading data from the MFM384 meter, and processing the data for analysis.
</p>

<h2 id="contributing">Contributing</h2>
<p>
    Contributions are welcome! Please follow these steps to contribute:
</p>
<ol>
    <li>Fork the repository.</li>
    <li>Create a new branch for your feature or fix.</li>
    <li>Make your changes and commit them.</li>
    <li>Push your changes to your forked repository.</li>
    <li>Create a pull request describing your changes.</li>
</ol>

<h2 id="license">License</h2>
<p>
    This project is licensed under the MIT License. See the <a href="LICENSE">LICENSE</a> file for details.
</p>

<h2 id="acknowledgments">Acknowledgments</h2>
<p>
    <strong>Hioctane Labs</strong> for providing the opportunity to work on this project.<br>
    <strong>Dr. Ayesha Naaz</strong>, Head, Department of Electronics and Communication Engineering, for the support and guidance.
</p>

</body>
</html>
