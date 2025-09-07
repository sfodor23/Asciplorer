# Asciplorer

![Asciplorer Logo](./AsciplorerLogo.png)

**A real-time ASCII world exploration simulation**

![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)
![Standard](https://img.shields.io/badge/C%2B%2B-17-green)
![Platform](https://img.shields.io/badge/Platform-Linux-orange)
[![Downloads](https://img.shields.io/github/downloads/sfodor23/National-Conquest/total.svg)](https://github.com/sfodor23/National-Conquest/releases)
[![Issues](https://img.shields.io/github/issues/sfodor23/National-Conquest.svg)](https://github.com/sfodor23/National-Conquest/issues)

## Overview

Asciplorer is a terminal Simulation/Screensaver made in C++ that focuses on the exploration of a randomly generated, realistic map by a path finding algorithm/bot. It has realistic map generation, immense customization, detailed statistic tracking, great performance, and more amazing features!

[Watch the Asciplorer Trailer](https://www.youtube.com/watch?v=lm1vumMTd2c)

## Download

### Requirements
- **C++17 compatible compiler** (GCC 7+ recommended)
- **Any operating system** (Linux preferred)
- **Terminal with 256-color support** (Black Background Preferred)

### How to Download

1. **Clone the repository**
	Open your terminal and run:
	```bash
	git clone https://github.com/sfodor23/National-Conquest.git
	cd National-Conquest
	```

2. **Build the project**
	Navigate to the `BuildAndExecutable` directory and run the build script:
	```bash
	cd Build&Executable
	bash build.sh
	```

3. **Run Asciplorer**
	After building, run ./Asciplorer in the `BuildAndExecutable` directory

For more details, see the sections below or open an issue if you encounter problems.

## Project Structure

Here is a brief description of each folder in the project:
- **MainProgram/**: Contains the Main Program which connects all parts of the project together and handles main logic
- **ProgramMethods/**: Contains the Core methods for map, input, player actions, statistics, etc.
- **Libraries/**: Contains Libraries (eg. FastNoiseLite) and Namespaces that store important variables
- **BuildAndExecutable/**: Contains the Build Script and output executable
- **RealTimeStatistics/**: Contains variables that need to be accessed across the program and altered in real time

## Contributing

To contribute:
1. Fork the repository
2. Create a new branch for your feature or fix
3. Commit your changes with clear messages
4. Open a pull request describing your changes

I appreciate changes and will try to accept most, but I might forget to check them often, so keep that in mind.

For bug reports or feature requests, please use the Issues tab.


## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Credits

- Developed by Steven Fodor
- Uses [FastNoiseLite](https://github.com/Auburn/FastNoiseLite) for noise generation
- Uses [Name-Generator](https://github.com/Mick1998/name-generator) for captain names




