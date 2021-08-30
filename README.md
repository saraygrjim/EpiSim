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

`EpiSim` provides additional information with the command `--help`. If no more directives are given, `EpiSim` prints out an error message. 

To execute the tool you have to execute the next command in the EpiSim directory

    $ python3 epiSim.py --file PATH/file.grj


# **EpiSimLanguage Sintax** #
The language sintax has five ordered parts:

1. Header
2. Global variables
3. Cells properties
4. Rules
5. Initial state

## **Header**
In this part of the code you have to choose the following properties:


* Number of cells to represent on side of the grid(NxN cells). By default is `100`.

* Type of neighbourhood. Could be `NEWUMANN`, `MOORE` and `EXTENDED`. By default is `NEUMANN`.

* Number of ticks the simulation lasts. By default is `200`.

* Number of strains to simulate. By default is `1`.

Any of them can be omitted. In that case the default value will be taken. Example of header:

```
cells 100       // 100x100 cells represented
ngh NEUMANN     
ticks 200
strains 2
```

## **Global variables**

In this section the simulation global variables are selected. An example of global variable could be the mortality rate of the virus. A global variable could be an integer, double or boolean. Also, is possible to assign or not a value to the variable. In case you not assign a value the variable takes a default value, if it is a boolean will be a `false`, if it is a double a `0.0` and if it is an integer a `0`. The structure of a global variable is `global type nameVariable = value;` or `global type nameVariable;`. 

```
global double probability   = 0.6;
global int    daysToInfect  = 4;
global int    incubation    = 3;
global int    duration      = 10;
```

## **Cells properties**

We can determine this section like a declaration of a class in the conventional programming languages. The external strcuture is `cell() {}' and inside the brackets we are going to declare the cells atributes and it states. 

The way to declare the cell atributes is the same like in the global variables but now the structure is `type nameVariable = value;` or `type nameVariable;`. 

When the atributes are declared we have to declare the cell states. We have to determine a name state and an RGB color to represent this state on the visual simulation. The structure is `NAME_STATE (value, value, value);` where the field `value` are values between 0 and 1.

And example of this section is:
```
cell() {
    int    cincubation    = 0;
    int    cduration      = 0;
    double cinmunity      = 0;
    bool   medication     = false;  
    bool   quarantined    = false; 
    int    cquaratineDays = 0;
    
    state SINFECTED     (1.0, 0.0, 0.0)
    state NO_INFECTIOUS (1.0, 0.8, 0.6)
    state RECOVER       (0.0, 1.0, 0.0)
    state QUARANTINE    (0.6, 0.8, 1.0)
    state DIE           (0.0, 0.0, 0.0)
}

```

## **Rules**

In this section we are going to declare the strains and the behaviour of them with rules. The way to declare a strain is `strain STRAIN_NAME(intial_tick){}` and inside the brackets we are going to declare the rules with th conventional `if` statements. 

We can ommit the `initial_tick` and by default it will be 0. Also, we have some preset functions and variables, they are:
* `count(variable, value)`. Returns how many neighbours has assigned the `value` to the `variable`.

* `continue`. This statement determine that the next rules will not be checked.

* `state`. Determine the state of the cell. 

* `alive`. Determine if the cell os alive or not. Boolean.

* `infected`. Determine if the cell is infected or no. Boolean.

* `current_tick`. Determine the current tick of the simulation. Integer.

* `ngh(value).variable`. Return the value of the variable of the selected neighbour. If we need to know the state of the north neighbour: `ngh(n).state`. The neighbour identifiers are:

    * n  -> north
    * s  -> south
    * w  -> west
    * e  -> east
    * ne -> northeast
    * nw -> northwest
    * se -> southeast
    * sw -> southwest
    * np -> north plus
    * sp -> south plus
    * wp -> west plus
    * ep -> east plus

An example is:

```
strain CEPA1(){
    if(state == NO_CHANGE && count(state, SINFECTED)>0 && random < probability){
        state = NO_INFECTIOUS;
        infected = true;
        cincubation = gincubation;
        cduration = gduration;
        continue;
    } else if ( state == RECOVER && count(state, INFECTED)>0 && random < cinmunity){
        state = NO_INFECTIOUS;
        infected = true;
        cincubation = gincubation;
        cduration = gduration;
        continue;
    }
}
  
```


## **Initial state**

To determinte the initial state to the first infected cell and if you want change the initial values of some variables. The structure is `init(){}` and inside the brackets the initial state and the atributes.

An example is:
```
init() {
    state = NO_INFECTIOUS;
    cduration = gduration;
}
```










# **License** #
Copyright (c) 2021 Saray García de la Rosa
    
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
    
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
    
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## **Author** 
Saray García de la Rosa Jiménez <saraygrj@gmail.com>

