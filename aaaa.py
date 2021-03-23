import click
import sys
import os.path
import random
import pygame
import numpy as np
import time

sys.path.append(".")
from cell import Cell
from grid import *

# @click.command()
# @click.option('--count', default=1, help='Number of greetings.')
# @click.option('--name', prompt='Your name',
#               help='The person to greet.')

pygame.init()
# Colours
WHITE  = (255,255,255)
RED    = (255, 0, 0)     # Infected and infectious
ORANGE = (255, 128, 0)   # Infected but not infectious
GREEN  = (51, 204, 51)   # Recover
BLACK  = (0, 0, 0)       # Dead
BLUE   = (102, 204, 255) # Quarantine
BG     = (128, 128, 128) # Background color

# For the simulation
width  = 700  # Size of the grid
height = 800  # Size of the grid
nX     = 50
nY     = 50
sizeX  = width/nX  # Size of cell
sizeY  = height/nY # Size of cell 
days   = 100  # Days to simulate
output = '' # Name of the output file

# Simulation parameters
probability = 0.3 # Probability that infections happens
incubation  = 3   # Days of incubation before the cell is infectious
duration    = 7   # How many days to finish and recover or to get worse
deadliness  = 0.6 # How deadly is the disease
inmunity    = 0.5 #  How inmune the cell is to infection after recovery

# Measures
medDay          = 5   # Day when the cell take the medicine
medEfficacy     = 0.9   # Efficacy of the medicine
quarentDay      = 3   # Day when the cell srar quarentine
quarentEfficacy = 0.7   # Efficacy of the quarentine

cells = []

screen = pygame.display.set_mode((width, height))
# gameState = np.zeros((width, height))


def newPopulation():
    for i in range(0, nX):
        cellsLine = []
        for j in range(0, nY):
            cell = Cell(i, j)
            cellsLine.append(cell)
        cells.append(cellsLine)
    ###############
    # considerar la posibilidad de tener en cuenta una densidad y que no se cree una célula por casilla
    ###############

# Infect the middle cell
def infectOneCell():
    i = int(nX/2)
    j = int(nY/2)
    cells[i][j].color = (255,0,0)
    cells[i][j].infected = True
    cells[i][j].duration = duration


def main():
    ###############
    # Configurar flags con click
    ###############

    endSimulation = False

    newPopulation()
    infectOneCell()
    
    currentTime = 0
    screen.fill(BG) # Clean background

    for a in cells:
        for cell in a:
            poly = [((cell.x)   * sizeX, cell.y     * sizeY),
                    ((cell.x+1) * sizeX, cell.y     * sizeY),
                    ((cell.x+1) * sizeX, (cell.y+1) * sizeY),
                    ((cell.x)   * sizeX, (cell.y+1) * sizeY)]
            pygame.draw.polygon(screen, cell.color, poly, 0)
        
    while (not endSimulation) and currentTime < days:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                endSimulation = True
        

        for a in cells:
            for cell in a:

                #If the cell is not infected then we can pass to the next
                if not cell.infected: 
                    poly = [((cell.x)   * sizeX, cell.y     * sizeY),
                            ((cell.x+1) * sizeX, cell.y     * sizeY),
                            ((cell.x+1) * sizeX, (cell.y+1) * sizeY),
                            ((cell.x)   * sizeX, (cell.y+1) * sizeY)]
                    pygame.draw.polygon(screen, cell.color, poly, 0)
                    continue

                # If the cell is infected then we have to process 
                processResult = cell.process(deadliness)

                if processResult == 0 : #If the cell is still incubating then we can pass to the next
                    poly = [((cell.x)   * sizeX, cell.y     * sizeY),
                        ((cell.x+1) * sizeX, cell.y     * sizeY),
                        ((cell.x+1) * sizeX, (cell.y+1) * sizeY),
                        ((cell.x)   * sizeX, (cell.y+1) * sizeY)]
                    pygame.draw.polygon(screen, cell.color, poly, 0)
                    continue
                elif processResult == 1 : #If the cell has recovered then we can pass to the next
                    cell.recover(inmunity)
                    poly = [((cell.x)   * sizeX, cell.y     * sizeY),
                        ((cell.x+1) * sizeX, cell.y     * sizeY),
                        ((cell.x+1) * sizeX, (cell.y+1) * sizeY),
                        ((cell.x)   * sizeX, (cell.y+1) * sizeY)]
                    pygame.draw.polygon(screen, cell.color, poly, 0)
                    continue
                else:
                    cell.die()

                # Medicine aplication when its time
                if not cell.medication and (currentTime > medDay):
                    medicationResult = cell.medicate(medEfficacy) 
                    if medicationResult: # If medicine is successful then the cell recover and pass to the next
                        cell.recover(inmunity)
                        poly = [((cell.x)   * sizeX, cell.y     * sizeY),
                                ((cell.x+1) * sizeX, cell.y     * sizeY),
                                ((cell.x+1) * sizeX, (cell.y+1) * sizeY),
                                ((cell.x)   * sizeX, (cell.y+1) * sizeY)]
                        pygame.draw.polygon(screen, cell.color, poly, 0)
                        continue
               
                if not cell.quarantined and (currentTime > quarentDay) and random.random() < quarentEfficacy:
                   cell.quarantine()

                # unless quarantined, look for neighbours and infect them
                if not cell.quarantined:
                    # find all the cell's neighbours
                    neighbours = searchNeighbours(nX, nY, cells, cell.x, cell.y)

                    for neighbour in neighbours:
                        x = neighbour[0]
                        y = neighbour[1]

                        if cells[x][y].infected:
                            continue
                        
                        # probability of re-infection
                        if random.random() > cells[x][y].inmunity:
                            # if probability less than infection rate then cell gets infected
                            if random.random() < probability:
                                cells[x][y].infect(incubation, duration)

                poly = [((cell.x)   * sizeX, cell.y     * sizeY),
                        ((cell.x+1) * sizeX, cell.y     * sizeY),
                        ((cell.x+1) * sizeX, (cell.y+1) * sizeY),
                        ((cell.x)   * sizeX, (cell.y+1) * sizeY)]
                # print(poly)
                pygame.draw.polygon(screen, cell.color, poly, 0)

        time.sleep(0.1)
        pygame.display.flip() 
        currentTime = currentTime + 1  

    pygame.quit()

if __name__ == '__main__':
    main()