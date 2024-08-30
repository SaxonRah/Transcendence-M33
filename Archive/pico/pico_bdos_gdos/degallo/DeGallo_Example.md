### Simple DeGallo OS and App Example
Simple operating system structure similar to CP/M or DOS, which includes a BIOS (Basic Input/Output System) and BDOS (Basic Disk Operating System) to handle hardware communication and provide system services.

This structure sets up a basic operating system environment where the BIOS handles direct hardware interactions and the BDOS provides higher-level services to the application. The application can use BDOS calls to interact with the system, such as displaying text on the screen or reading files from the SD card.

1. **BIOS (Basic Input/Output System)**:
    - Handles direct interaction with the hardware.
    - Provides low-level functions for I/O operations, such as reading from and writing to the display, accessing the SD card, handling the RTC, etc.

2. **BDOS (Basic Disk Operating System)**:
    - Provides higher-level OS services that applications can call.
    - Handles file system operations, memory management, and other system services.

3. **Application**:
    - Uses BDOS calls to interact with the system without needing to know the hardware details.

#### Compilation and Setup
0. **Requirements**:
	- Windows 
		- Chocolatey : Download and Install Chocolatey for Windows 
			- Cmake : `choco install cmake`
				- Generally locates to `C:\Program Files\CMake\bin`
				- Add this path to PATH in system enviroment variables on Windows.
			- Make : `choco install make`
				- Generally locates to `C:\ProgramData\chocolatey\bin`
				- Chocolatey should automatically add it's bin path to PATH in system enviroment variables on Windows.
				- If it doesn't add `C:\ProgramData\chocolatey\bin` to PATH in system enviroment variables on Windows.
		- PicoSDK : Download and Install `Raspberry Pi Pico Windows Installer`
			- https://github.com/raspberrypi/pico-setup-windows/releases/latest/download/pico-setup-windows-x64-standalone.exe
			- Add `PICO_SDK_PATH` to system enviroment variables on Windows.
			- The Pico SDK path is generally something like `C:\Program Files\Raspberry Pi\Pico SDK v1.5.1\pico-sdk`
				- Note the version number might be different.
			- Or Modify `DeGallo_BUILD_ALL.sh` and add `export PICO_SDK_PATH=/path/to/pico-sdk` and changing the path to the SDK path.

	- Linux
		- You probably already know what to do. ;)

1. **Clean/Build the Project**:
- Clean Build Folders:
	- Run `CLEAN_BUILD_FILES.sh`
		- Removes Build folders and files.
- Individually:
    - Run `DeGallo_Build.sh`
		- Produces DeGallo OS uf2 file.
    - Run `degallo_app/DeGallo_APP_Build.sh`
		- Produces DeGallo APP elf file.
    - Run `degallo_app/APP_to_BIN.sh`
		- Converts DeGallo APP elf file to DeGallo APP BIN file.
- Batch Job:
	- Run the `DeGallo_BUILD_ALL.sh`
		- Builds both degallo_os and degallo_app.
- Issues:
	- make: *** No targets specified and no makefile found.  Stop.
		- Failed to build DeGallo OS
		- Failed to build DeGallo App
	- u...uuh yeah build with Pico - Visual Studio Code?

2. **Load the Application**:
    - Place the `degallo_app.bin` file on the SD card.
    - Upload the compiled firmware (`degallo_os.uf2`) to the Raspberry Pi Pico.

### Running the OS

1. **Insert the SD card** with the `degallo_app.bin` file into the SD card slot.
2. **Power up the Raspberry Pi Pico** and it will load and execute the application.
