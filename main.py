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
quarentDay      = days     # Day when the cell start quarentine
quarentEfficacy = 0.3    # Efficacy of the quarentine
quarentProb     = 0.7

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
    i = random.randint(0, n-1)
    j = random.randint(0, n-1)
    cells[i][j].infect(incubation, duration)
    print ("First is " + str(i) + " " + str(j))

def drawCircle(color, x, y):
    poly = (int((x*sizeX) + (sizeX/2)), int((y*sizeY) + (sizeY/2)))
    pygame.draw.circle(screen, color, poly, (sizeX/2.5), 0)

def drawPoly(color, x, y):
    poly = [(int(x     * sizeX), int(y     * sizeY)),
            (int((x+1) * sizeX), int(y     * sizeY)),
            (int((x+1) * sizeX), int((y+1) * sizeY)),
            (int(x     * sizeX), int((y+1) * sizeY))]
    pygame.draw.polygon(screen, color, poly, 0)
    pygame.draw.polygon(screen, BG, poly, 1)

def main():
    ###############
    # Configurar flags con click
    ###############

    endSimulation = False

    newPopulation()
    infectOneCell()
    
    currentTime = 0
    screen.fill(BG)
    # Fill the screen
    for a in cells:
        for cell in a:
            drawPoly(cell.color, cell.x, cell.y)
        

        
    while (not endSimulation) and currentTime < days:
        screen.fill(BG)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                endSimulation = True
        
        print(currentTime)

        for a in cells:
            for cell in a:
                if cell.color == BLUE:
                    print(str(cell))
                # print(str(cell))
                #If the cell is not infected then we can pass to the next
                if not cell.infected : 
                    drawPoly(cell.color, cell.x, cell.y)
                    continue
                
                #If the cell is in quarantine we can pass to the next
                if cell.quarantined: 
                    processQResult = cell.processQuarantine(quarentEfficacy)
                    if processQResult == 1:
                        cell.recover(inmunity)
                        # drawPoly(cell.color, cell.x, cell.y)
                    

                # If the cell is infected then we have to process 
                processResult = cell.process(deadliness)

                if processResult == 0 : #If the cell is still incubating then we can pass to the next
                    drawPoly(cell.color, cell.x, cell.y)
                    continue
                elif processResult == 1 : #If the cell has recovered then we can pass to the next
                    cell.recover(inmunity)
                    drawPoly(cell.color, cell.x, cell.y)
                    continue
                elif processResult == 2: #The cell hasnt recovered so dead
                    cell.die()
                    # drawPoly(cell.color, cell.x, cell.y)
                # else: #The cell stay infected
                #     drawPoly(cell.color, cell.x, cell.y)

                # Medicine aplication when its time
                if not cell.medication and (currentTime > medDay):
                    medicationResult = cell.medicate(medEfficacy) 
                    if medicationResult: # If medicine is successful then the cell recover and pass to the next
                        cell.recover(inmunity)
                        # print(str(cell.x) + ", " + str(cell.y) + " me han medicado y me he recuperado en " + str(currentTime) + ", debo tener color verde " + str(cell.color))
                        drawPoly(cell.color, cell.x, cell.y)
                        continue

                if not cell.quarantined and (currentTime > quarentDay) and random.random() > quarentProb and cell.alive: 
                   cell.quarantine()

                # unless quarantined, look for neighbours and infect them
                if not cell.quarantined:
                    # print("ENTRO AQUIIIIIIIIIII")
                    # print(str(cell.x) + ", " + str(cell.y) + " no estoy en cuarentena y chequeo a mis vecinos en " + str(currentTime) + ", debo tener un color diferente a azul, verde o blanco " + str(cell.color))
                    
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
                                    drawPoly(cells[x][y].color, cells[x][y].x, cells[x][y].y)
                
                drawPoly(cell.color, cell.x, cell.y)


        
        time.sleep(0.1)
        pygame.display.flip() 
        currentTime = currentTime + 1  

    pygame.quit()

if __name__ == '__main__':
    main()