# Adaptive-Decentralised-swarm-communication
A simple, modular communication framework for decentralized multi-agent robotic swarms. This system dynamically adapts message routing, topology, and frequency based on node availability, signal quality, and mission context

# Wireless Sensor Network Using RP2350 and HC-12 Modules

This project demonstrates the design and implementation of a decentralized wireless sensor network using RP2350-based microcontrollers and HC-12 433 MHz wireless communication modules. The network is composed of three sensor nodes, each with its own sensing functionality, local display, and communication capability. All nodes operate independently while communicating with each other to create a distributed data acquisition system.

## Project Description

Each node in the network is based on a dual-core RP2350 microcontroller (e.g., Raspberry Pi Pico 2) and performs two concurrent tasks:
1. **Core 0**: Handles sensor data acquisition, HC-12 wireless transmission and reception, and serial communication.
2. **Core 1**: Manages real-time data display on an OLED screen.

The nodes are capable of both transmitting their own sensor data and receiving data broadcasted by the other nodes. This allows for fully distributed awareness across the system, where every node can locally display a snapshot of the environmental conditions being monitored by the entire network.

## System Overview

| Node | Sensor              | Function                                       |
|------|---------------------|------------------------------------------------|
| 1    | MICS5524 Gas Sensor | Measures gas concentration (air pollution)     |
| 2    | BME680              | Measures temperature, humidity, and pressure   |
| 3    | Sound Sensor (Analog)| Monitors ambient sound intensity              |

Each node uses an OLED display (128x64) to display:
- Node ID and a visual divider
- The sensor value being transmitted
- The most recent values received from the other two nodes

## File Structure

```text
.
├── Node1.ino     // Source code for Node 1 (MICS5524 Gas Sensor)
├── Node2.ino     // Source code for Node 2 (BME680 Sensor)
├── Node3.ino     // Source code for Node 3 (Analog Sound Sensor)
└── README.md     // Project documentation
