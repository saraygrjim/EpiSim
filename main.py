import click
import sys
import os.path
import random
import pygame
import numpy as np
import time

sys.path.append(".")
from colours import *
from cell    import Cell
from grid    import *

# @click.command()
# @click.option('--count', default=1, help='Number of greetings.')
# @click.option('--name', prompt='Your name',
#               help='The person to greet.')

pygame.init()


# For the simulation
width  = 700  # Size of the grid
height = 800  # Size of the grid
n      = 50
sizeX  = width/n  # Size of cell
sizeY  = height/n # Size of cell 
days   = 700  # Days to simulate
output = '' # Name of the output file

# Simulation parameters
probability = 0.15  # Probability that infections happens
incubation  = 3     # Days of incubation before the cell is infectious
duration    = 10    # How man days to finish and recover or to get worse
deadliness  = 0.02  # How deadly is the disease
inmunity    = 0.5   # How inmune the cell is to infection after recovery

# Measures
medDay          = 150    # Day when the cell take the medicine
medEfficacy     = 0.5    # Efficacy of the medicine
quarentDay      = 100     # Day when the cell start quarentine
quarentEfficacy = 0.3    # Efficacy of the quarentine
quarentProb     = 0.7

cells = []
state = []

screen = pygame.display.set_mode((width, height))

def newPopulation():
    for i in range(0, n):
        cellsLine = []
        stateLine = []
        for j in range(0, n):
            cell = Cell(i, j)
            cellsLine.append(cell)
            stateLine.append(0)
        cells.append(cellsLine)
        state.append(stateLine)
    ###############
    # considerar la posibilidad de tener en cuenta una densidad y que no se cree una célula por casilla
    ###############

# Infect the middle cell
def infectOneCell():
    i = int(n/2)
    j = int(n/2)
    cells[i][j].infect(incubation, duration)
    state[i][j] = cells[i][j].state
    print(cells[i][j].state)
    print ("First is " + str(i) + " " + str(j))


def main():
    endSimulation = False
    currentTime = 0
    
    newPopulation()
    infectOneCell()

    while (not endSimulation) and currentTime < days:
        print("---------------------------DIA " + str(currentTime) + "---------------------------") 
        screen.fill(BG)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                endSimulation = True

        ######################
        #  PARTE DE CÓMPUTO  #
        ######################

        for a in cells:
            for cell in a:
                
                if not cell.infected : 
                    continue
                
                #If the cell is in quarantine we can pass to the next
                if cell.quarantined: 
                    print("entro")
                    processQResult = cell.processQuarantine(quarentEfficacy)
                    if processQResult == 1:
                        cell.recover(inmunity)
                        state[cell.x][cell.y] = cell.state
                    

                # If the cell is infected then we have to process 
                processResult = cell.process(deadliness)

                if processResult == 0 : #If the cell is still incubating then we can pass to the next
                    continue
                elif processResult == 1 : #If the cell has recovered then we can pass to the next
                    cell.recover(inmunity)
                    state[cell.x][cell.y] = cell.state
                    continue
                elif processResult == 2: #The cell hasnt recovered so dead
                    cell.die()
                    state[cell.x][cell.y] = cell.state

                # Medicine aplication when its time
                if not cell.medication and (currentTime > medDay):
                    medicationResult = cell.medicate(medEfficacy) 
                    if medicationResult: # If medicine is successful then the cell recover and pass to the next
                        cell.recover(inmunity)
                        state[cell.x][cell.y] = cell.state
                        continue

                if not cell.quarantined and (currentTime > quarentDay) and random.random() > quarentProb and cell.alive: 
                   cell.quarantine()
                   state[cell.x][cell.y] = cell.state

                # unless quarantined, look for neighbours and infect them
                if not cell.quarantined:
                    # find all the cell's neighbours
                    neighbours = searchNeighbours(n, cells, cell.x, cell.y)

                    for neighbour in neighbours:
                        x = neighbour[0]
                        y = neighbour[1]
                        if cells[x][y].alive:
                            if cells[x][y].infected:
                                continue
                            
                            # probability of re-infection
                            if random.random() > cells[x][y].inmunity:
                                # if probability less than infection rate then cell gets infected
                                if random.random() < probability:
                                    cells[x][y].infect(incubation, duration)
                                    state[x][y] = cells[x][y].state
                state[cell.x][cell.y] = cell.state
                
                
        ##############################
        #  PARTE DE REPRESENTACIÓN   #
        ##############################
        for i in range(0,n):
            for j in range(0,n):
                poly = [(int(i     * sizeX), int(j     * sizeY)),
                        (int((i+1) * sizeX), int(j     * sizeY)),
                        (int((i+1) * sizeX), int((j+1) * sizeY)),
                        (int(i     * sizeX), int((j+1) * sizeY))]

                colors = {
                    0: white(),
                    1: yellow(),
                    2: red(),
                    3: green(),
                    4: blue(),
                    5: black(),
                }
                # print(state[i][j])
                if (colors.get(state[i][j], default()) == yellow()):
                    print(type(colors.get(state[i][j], default())))
                pygame.draw.polygon(screen, colors.get(state[i][j], default()), poly, 0)
                pygame.draw.polygon(screen, BG, poly, 1)

        time.sleep(0.3)
        pygame.display.flip() 
        currentTime = currentTime + 1  

    pygame.quit()



if __name__ == '__main__':
    main()