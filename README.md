Team number: XIL-82078

Project name: OXiGen

Date:  

Version of uploaded archive: 0.1

University name: Politecnico di Milano

Supervisor name: Marco Domenico Santambrogio

Supervisor e-mail: marco.santambrogio@polimi.it

Participant(s): Marco Siracusa, Francesco Peverelli, Enrico Reggiani

Email: marco.siracusa@mail.polimi.it

Email: francesco1.peverelli@mail.polimi.it

Email: enrico2.reggiani@mail.polimi.it

Board used: Virtex-5, Virtex-7

Vivado Version:

Brief description of project:

In the field of High Performance Computing (HPC), a considerable effort has been put into the exploration of different solutions which address the ever-increasing need for high performance and power efficiency.
Field Programmable Gate Arrays (FPGAs) are reconfigurable hardware devices that allow the developer to create circuits with specific and dedicated functions. They have risen in popularity in the HPC environment due to their ability to provide faster and more energy efficient solutions than CPUs and GPUs. On the other hand, programming FPGAs by means of hardware-description languages (HDLs), like VHDL or Verilog, is a time-consuming and error-prone task. In order to ease and speed-up the development process, different companies have developed tools to allow FPGA programming by means of high-level languages, as well as tools to aid the developer through all the stages of the circuit design. However, acquiring the experience needed to develop correct and efficient programs by means of High Level Synthesis tools requires a considerable amount of time, and a more accessible way to develop for FPGAs would be extremely valuable to increase their usability even further. Hence, the aim of our work is to develop a tool which realizes a fully automatic translation from a control-flow oriented program written in C/C++ into a bitstream suitable as an input for a Xilinx FPGA, and automates all the intermediate stages of circuit design. This tool will both directly rely on the tools offered by Xilinx, as well as support other technologies which in turn target the Xilinx boards.

Description of archive:

/

|----bin/          #contains binaries
|----build/        #contains autogenerated CMake files
|
|----include/      # contains header files
|    |----DFG/     
|    |    |----DFGManager.h
|    |    |----Nodes.h
|    |
|    |----OXiGen/
|    |    |----OXiGenPass.h
|    |    
|    |----Utils/
|         |----IOStreams.h
|
|----resources/   #contains .ll files and the .c example
|    |----grav.c
|    |----grav.ll
|    |----loop_1.ll
|    |----loop_2.ll
|
|----src/          # contains the source .cpp files
     |
     |----CMakeLists.txt   #used to build the project with CMake
     |----main.cpp         
     |----OXiGenPass.cpp
     |----Nodes.cpp
     |----DFGManager.cpp


Instructions to build and test project

Step 1:

1.1 download llvm 4.0 from http://releases.llvm.org/download.html

1.2 install the LLVM libraries (recommended location: /usr/local/) and Clang

Step 2:

Install CMake (3.5.1 or later)

Step 3:

Clone this repository

Step 4:

4.1 Create the /build directory in this repository
4.2 Move to the /build directory and run:
        cmake -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++
4.3 Build the project

Step 5:

To test the project on the example, run the main executable (/bin/main)
with the following arguments:

    grav.ll                    #name of the .ll file
    <project_dir>/resources/   #file path
    gravitational_force        #function name

Link to YouTube Video(s):