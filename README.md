# **EpiSim**

This tool allows the simulation of epidemics using cellular automata. It is necessary to write a program in designed language called EpiSimLanguage and its path will be indicated in the source of execution, then a compiler will check for syntax errors, if there are none, the simulation will proceed. Finally, results obtained from the simulation are stored. 

# **Install** #

The dependencies that must be previously installed for the correct execution of the tool are detailed below. The listed commands are for the Debian operating system 


#### **mathplotlib** 
    $ pip3 install mathplotlib

#### **GLUT**
    $ sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev

#### **Flex/Bison** 

    $ sudo apt-get install flex bison

#### **Typer**

    $ pip3 install Typer
  
#### **PyInquirer**

    $ pip3 install PyInquirer


Finally, clone the repository with:

    $ git clone https://github.com/saraygrjim/EpiSim.git


# **Usage** # 
`EpiSim`  has a mandatory argument that shall be given with `--file` and shall consist of a path to a `.grj` file. 

EpiSim provides additional information with the command `--help`. If no more directives are given, pgnparser prints out an error message. 
