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

To execute the tool you have to execute the next command in the EpiSim directory

    $ python3 epiSim.py --file PATH/file.grj


# **EpiSimLanguage Sintax** #


# **License** #
Copyright (c) 2021 Saray García de la Rosa
    
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
    
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
    
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## **Author** 
Saray García de la Rosa Jiménez <saraygrj@gmail.com>

