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
n      = 50
sizeX  = width/n  # Size of cell
sizeY  = height/n # Size of cell 
days   = 300  # Days to simulate
output = '' # Name of the output file

# Simulation parameters
probability = 0.15 # Probability that infections happens
incubation  = 3    # Days of incubation before the cell is infectious
duration    = 4    # How man days to finish and recover or to get worse
deadliness  = 0.02 # How deadly is the disease
inmunity    = 0.5  #  How inmune the cell is to infection after recovery

# Measures
medDay          = days     # Day when the cell take the medicine
medEfficacy     = 0.0   # Efficacy of the medicine
quarentDay      = days     # Day when the cell start quarentine
quarentEfficacy = 0.0  # Efficacy of the quarentine

cells = []

screen = pygame.display.set_mode((width, height))
# gameState = np.zeros((width, height))


def newPopulation():
    for i in range(0, n):
        cellsLine = []
        for j in range(0, n):
            cell = Cell(i, j)
            cellsLine.append(cell)
        cells.append(cellsLine)
    ###############
    # considerar la posibilidad de tener en cuenta una densidad y que no se cree una célula por casilla
    ###############

# Infect the middle cell
def infectOneCell():
    i = int(n/2)
    j = int(n/2)
    cells[i][j].infect(incubation, duration)
    print ("First is " + str(i) + " " + str(j))

def calculatePoly(x,y):
    poly = [(int(x     * sizeX), int(y     * sizeY)),
            (int((x+1) * sizeX), int(y     * sizeY)),
            (int((x+1) * sizeX), int((y+1) * sizeY)),
            (int(x     * sizeX), int((y+1) * sizeY))]
    return poly

def main():
    ###############
    # Configurar flags con click
    ###############

    endSimulation = False

    newPopulation()
    infectOneCell()
    
    currentTime = 0

    # Fill the screen
    for a in cells:
        for cell in a:
            pygame.draw.polygon(screen, cell.color, calculatePoly(cell.x, cell.y), 0)
            pygame.draw.polygon(screen, BG, calculatePoly(cell.x, cell.y), 1)

        
    while (not endSimulation) and currentTime < days:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                endSimulation = True
        

        for a in cells:
            for cell in a:
                print(currentTime)
                print(str(cell))
                #If the cell is not infected then we can pass to the next
                if not cell.infected: 
                    # print(str(cell.x) + ", " + str(cell.y) + " no estoy infectada o estoy muerta en " + str(currentTime) + ", paso a la siguiente")
                    pygame.draw.polygon(screen, cell.color, calculatePoly(cell.x, cell.y), 0)
                    pygame.draw.polygon(screen, BG, calculatePoly(cell.x, cell.y), 1)
                    continue

                # If the cell is infected then we have to process 
                processResult = cell.process(deadliness)

                if processResult == 0 : #If the cell is still incubating then we can pass to the next
                    # print(str(cell.x) + ", " + str(cell.y) + " sigo incubando en " + str(currentTime) + " debo tener color naranja " + str(cell.color))
                    pygame.draw.polygon(screen, cell.color, calculatePoly(cell.x, cell.y), 0)
                    pygame.draw.polygon(screen, BG, calculatePoly(cell.x, cell.y), 1)
                    continue
                elif processResult == 1 : #If the cell has recovered then we can pass to the next
                    cell.recover(inmunity)
                    # print(str(cell.x) + ", " + str(cell.y) + " me he recuperado en " + str(currentTime) + ", debo tener color verde " + str(cell.color))
                    pygame.draw.polygon(screen, cell.color, calculatePoly(cell.x, cell.y), 0)
                    pygame.draw.polygon(screen, BG, calculatePoly(cell.x, cell.y), 1)
                    continue
                elif processResult == 2: #The cell hasnt recovered so dead
                    # print(str(cell.x) + ", " + str(cell.y) + " he muerto en " + str(currentTime) + ", debo tener color negro " + str(cell.color))
                    cell.die()
                else: #The cell stay infected
                    pygame.draw.polygon(screen, cell.color, calculatePoly(cell.x, cell.y), 0)
                    pygame.draw.polygon(screen, BG, calculatePoly(cell.x, cell.y), 1)

                # Medicine aplication when its time
                if not cell.medication and (currentTime > medDay):
                    medicationResult = cell.medicate(medEfficacy) 
                    if medicationResult: # If medicine is successful then the cell recover and pass to the next
                        cell.recover(inmunity)
                        print(str(cell.x) + ", " + str(cell.y) + " me han medicado y me he recuperado en " + str(currentTime) + ", debo tener color verde " + str(cell.color))
                        pygame.draw.polygon(screen, cell.color, calculatePoly(cell.x, cell.y), 0)
                        pygame.draw.polygon(screen, BG, calculatePoly(cell.x, cell.y), 1)
                        continue
                    # print(str(cell.x) + ", " + str(cell.y) + " me han medicado y no ha funcionado " + str(currentTime) + ", debo tener color rojo " + str(cell.color))

                if not cell.quarantined and (currentTime > quarentDay) and random.random() < quarentEfficacy : 
                   cell.quarantine()
                #    print(str(cell.x) + ", " + str(cell.y) + " estoy en cuarentena en " + str(currentTime) + ", debo tener color azul " + str(cell.color))

                # unless quarantined, look for neighbours and infect them
                if not cell.quarantined:
                    print("ENTRO AQUIIIIIIIIIII")
                    print(str(cell.x) + ", " + str(cell.y) + " no estoy en cuarentena y chequeo a mis vecinos en " + str(currentTime) + ", debo tener un color diferente a azul, verde o blanco " + str(cell.color))
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
                                    pygame.draw.polygon(screen, cells[x][y].color, calculatePoly(cells[x][y].x, cells[x][y].y), 0)
                                    pygame.draw.polygon(screen, BG, calculatePoly(cells[x][y].x, cells[x][y].y), 1)

                pygame.draw.polygon(screen, cell.color, calculatePoly(cell.x, cell.y), 0)
                pygame.draw.polygon(screen, BG, calculatePoly(cell.x, cell.y), 1)


        
        time.sleep(0.1)
        pygame.display.flip() 
        currentTime = currentTime + 1  

    pygame.quit()

if __name__ == '__main__':
    main()