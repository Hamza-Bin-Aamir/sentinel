# Welcome to CS221 Project SENTINEL
## About
Project SENTINEL is intended to be a "generalist"  hobby rocket logging system that is capable of adapting to rockets of all impulse categories (from tiny water rockets to spaceshots!)

Although this is simply a logging and telemetry system with some very basic control functionality, we aim to integrate this into a larger autopilot system, which can not only collect data but also control the rockets.

This project is intended to be the third semester projects of Azeem (2023150), Hamza Bin Aamir (2023219), and Syed Areeb Zaheer (2023672) and is part of their pursuits with GIKI Jet Propulsion Laboratory.

## System Overview
A typical SENTINEL system involves the following mandatory avionic systems:

1. The Flight Control Unit (such as an ESP32)
2. Flight Instruments (Sensors and Interfaces)
3. Flight Comms (Radio Telemetry)

The good news is that the system is designed to adapt to any type of rocket as long as the avionics stay within operating range throughout the mission.

For an easy reference to get started, we have provided schematics for "Trout" — the water rocket we used to do most of our testing — at ```schemas\Trout```.
