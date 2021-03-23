import pygame
import time

pygame.init()

WIDTH  = 800
HEIGHT = 600
ROJO = (255,0,0)
ventana = pygame.display.set_mode((WIDTH,HEIGHT))
jugando = True

while jugando:
    # Registramos eventos de teclado y raton
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == pygame.KEYDOWN:
            pauseExect = not pauseExect

    ventana.fill(ROJO)

    

    time.sleep(0.1)
    pygame.display.flip()

pygame.quit()