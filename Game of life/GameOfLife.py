import pygame
import numpy as np
import time

width, height = 700, 700
nX, nY = 80, 80
# Dimensiones de cada celda
sizeX = width/nX
sizeY = height/nY

pygame.init()

screen = pygame.display.set_mode((height, width))

bg   = (25, 25, 25) # Color de fondo
live = (255,255,255)
dead = (128, 128, 128)
# Estado de las celdas. Vivas = 1; Muertas = 0
gameState = np.zeros((nX, nY)) #Inicializamos a 0 el tablero


# Autómata palo
gameState[5, 2] = 1
gameState[5, 3] = 1
gameState[5, 4] = 1
gameState[5, 5] = 1
gameState[5, 6] = 1


# Automata movil
# gameState[21, 21] = 1
# gameState[22, 22] = 1
# gameState[22, 23] = 1
# gameState[21, 23] = 1
# gameState[20, 23] = 1

# Controlar el flujo de ejecucion de nuestro juego
pauseExect = False

running = True
# Bucle de ejecucion
while running:
    newGameState = np.copy(gameState)

    #Registramos eventos de teclado y raton
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == pygame.KEYDOWN:
            pauseExect = not pauseExect

        # Detectamos si se presiona el raton
        mouseClick = pygame.mouse.get_pressed()
        if sum(mouseClick)>0:
            posX, posY = pygame.mouse.get_pos()
            celX, celY = int(np.floor(posX/sizeX)), int(np.floor(posY/sizeY))
            newGameState[celX, celY] = not mouseClick[2]

    screen.fill(bg) # Clean background

    for y in range(0, nX):
        for x in range(0, nY):

            if not pauseExect:
                # Calculamos el número de vecinos cercanos
                nNeigh =  gameState[(x-1) % nX, (y-1) % nY] + \
                          gameState[(x)   % nX, (y-1) % nY] + \
                          gameState[(x+1) % nX, (y-1) % nY] + \
                          gameState[(x-1) % nX, (y)   % nY] + \
                          gameState[(x+1) % nX, (y)   % nY] + \
                          gameState[(x-1) % nX, (y+1) % nY] + \
                          gameState[(x)   % nX, (y+1) % nY] + \
                          gameState[(x+1) % nX, (y+1) % nY] 

                # Rule 1: Una celula muerta con exactamente 3 vecinas vivas, revive
                if gameState[x, y] == 0 and nNeigh == 3:
                    newGameState[x, y] = 1

                # Rule 1: Una ceula viva con menos de 2 o mas de 3 vecinas vivas muere (por soledad o por superpoblacion)
                elif gameState[x, y] == 1 and (nNeigh < 2 or nNeigh > 3):
                    newGameState[x, y] = 0

                # Puntos que definen al poligono que estamos dibujando
                poly = [((x)   * sizeX, y     * sizeY),
                        ((x+1) * sizeX, y     * sizeY),
                        ((x+1) * sizeX, (y+1) * sizeY),
                        ((x)   * sizeX, (y+1) * sizeY)]

                # Dibujamos la celda para cada par de x e y
                if newGameState[x, y] == 1:
                    pygame.draw.polygon(screen, live, poly, 1)
                else:
                    pygame.draw.polygon(screen, dead, poly, 0)

            
    gameState = np.copy(newGameState)
    time.sleep(0.1)
    pygame.display.flip()


pygame.quit()

