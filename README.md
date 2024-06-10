# Gravity Simulation

This repository contains a gravity simulation program written in C++ using the SFML (Simple and Fast Multimedia Library). The simulation allows users to create particles that interact with each other through gravitational forces. Users can manipulate particles using the mouse and keyboard.

## Warning

This program has been developed with the assistance of the GPT-4o model by OpenAI. 

## Features

- **Particle Creation**:
  - **- Key** to decrease the Gravity   
  - **= Key** to increase the Gravity  
  - **Left Click**: Hold and release to create a particle. The velocity of the particle depends on the distance the mouse is dragged.
  - **Right Click**: Hold to generate multiple particles. The number of particles created depends on the duration of the hold.
- **Particle Management**:
  - **C Key**: Press to clear all particles from the simulation.

## Prerequisites

Before running the program, ensure you have SFML installed on your system. You can download SFML from the [official website](https://www.sfml-dev.org/download.php).

### Installation on Windows

1. Download the SFML library from the [official website](https://www.sfml-dev.org/download.php).
2. Extract the contents and follow the instructions in the `README` or `Getting Started` guide provided with SFML.

### Installation on macOS

You can install SFML using Homebrew:
```bash
brew install sfml
```

### Installation on Linux

You can install SFML using your package manager. For example, on Debian-based systems:
```bash
sudo apt-get install libsfml-dev
```

## Building the Project

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/gravity-simulation.git
   cd gravity-simulation
   ```

2. Make sure you have a C++ compiler installed (e.g., `g++` or `clang`).

3. Compile the project:
   ```bash
   make
   ```

4. Run the executable:
   ```bash
   ./gravity_sim
   ```

## Contributing

Contributions are welcome! Please open an issue or submit a pull request with any improvements or bug fixes.

## Acknowledgements

- [SFML](https://www.sfml-dev.org/) - Simple and Fast Multimedia Library

Feel free to reach out if you have any questions or need further assistance!

---
