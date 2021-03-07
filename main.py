import click
import sys
import os.path
import random

sys.path.append(".")
from cell import Cell
from grid import *

# @click.command()
# @click.option('--count', default=1, help='Number of greetings.')
# @click.option('--name', prompt='Your name',
#               help='The person to greet.')

WHITE  = (255,255,255)
RED    = (255, 0, 0)     # Infected and infectious
ORANGE = (255, 128, 0)   # Infected but not infectious
GREEN  = (51, 204, 51)   # Recover
BLACK  = (0, 0, 0)       # Dead
BLUE   = (102, 204, 255) # Quarantine

# For the simulation
width  = 12  # Size of the grid
heigh  = 12
days   = 0  # Days to simulate
output = '' # Name of the output file

# Simulation parameters
probability = 0.0 # Probability that infections happens
incubation  = 0   # Days of incubation before the cell is infectious
duration    = 0   # How many days to finish and recover or to get worse
deadliness  = 0.0 # How deadly is the disease
inmunity    = 0.0 #  How inmune the cell is to infection after recovery

# Measures
medDay          = 0   # Day when the cell take the medicine
medEfficacy     = 0   # Efficacy of the medicine
quarentDay      = 0   # Day when the cell srar quarentine
quarentEfficacy = 0   # Efficacy of the quarentine

cells = []

def newPopulation():
    for i in range(0, heigh):
        cellsLine = []
        for j in range(0, width):
            cell = Cell(i, j)
            cellsLine.append(cell)
        cells.append(cellsLine)
    ###############
    # considerar la posibilidad de tener en cuenta una densidad y que no se cree una célula por casilla
    ###############

# Infect the middle cell
def infectOneCell():
    i = width/2
    j = heigh/2
    cells[i][j].color = (255,0,0)
    cells[i][j].infected = True
    cells[i][j].duration = duration



def main():
    ###############
    # Configurar flags con click
    ###############

    endSimulation = False

    print(cells)
    newPopulation()
    infectOneCell()
    
    currentTime = object
    while (not endSimulation) and currentTime < days:
        ###############
        # capturar señales de teclado para terminar
        ###############

        for a in cells:
            for cell in a:

                #If the cell is not infected then we can pass to the next
                if not cell.infected: 
                    continue

                # If the cell is infected then we have to process 
                processResult = cell.process(deadliness)

                if processResult == 0 : #If the cell is still incubating then we can pass to the next
                    continue
                elif processResult == 1 : #If the cell has recovered then we can pass to the next
                    cell.recover(inmunity)
                    continue
                else:
                    cell.die()

                # Medicine aplication when its time
                if not cell.medication and (currentTime > medDay):
                    medicationResult = cell.medicate() 
                    if medicationResult: # If medicine is successful then the cell recover and pass to the next
                        cell.recover(inmunity)
                        continue
               
                if not cell.quaratined and (currentTime > quarentDay) and random.random() < quarentEfficacy:
                   cell.quarantine()

                # unless quarantined, look for neighbours and infect them
                if not cell.quarantined:
                    # find all the cell's neighbours
                    neighbours = searchNeighbours(width, heigh, cells, cell.x, cell.y)

                    for neighbour in neighbours:
                        x = neighbour[0]
                        y = neighbour[1]

                        if cells[x][y].infected:
                            continue
                        
                        # probability of re-infection
                        if random.random() > cells[x][y].inmunity:
                            # if probability less than infection rate then cell gets infected
                            if random.random() < probability:
                                cells[x][y].infected()
            

if __name__ == '__main__':
    main()