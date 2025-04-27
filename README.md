# Car Black-Box System

### **Overview**
This project implements a car black-box system using a **PIC microcontroller** for continuous event logging and monitoring. Inspired by black-box systems in airplanes, it records events like over-speeding to EEPROM for post-event analysis. The goal is to enhance safety and understand root causes in transportation-related incidents.

### **Features**
- Continuous monitoring and logging of critical events.
- Event storage in **EEPROM** for post-event analysis.
- Support for peripherals like potentiometers for data collection and control.
- Easily extendable to other types of vehicles.

### **How It Works**
1. **Event Detection**: The microcontroller continuously monitors parameters like speed, system status, etc.
2. **Data Logging**: Critical events are recorded in EEPROM for secure storage.
3. **Peripheral Integration**: Rich peripherals are leveraged to gather additional input and improve functionality.
4. **Interrupt Handling**: Efficient processing ensures no event is missed during operation.

### **Prerequisites**
Before working on this project, familiarity with the following concepts is recommended:
- **PIC Microcontroller & Schematics**: Understanding how to program and interface with PIC microcontrollers.
- **Peripheral Handling**: Learn to use devices like potentiometers by interpreting datasheets.
- **Interrupt Handling**: Manage asynchronous events effectively using interrupts.

### **Getting Started**
1. Clone the repository:  
   ```bash
   git clone https://github.com/your-username/Car-Black-Box.git
   cd Car-Black-Box
