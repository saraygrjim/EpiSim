import sys 

sys.path.append(".")
from cell import Cell

def c1(x, y): return (x-1, y-1)
def c2(x, y): return (x  , y-1)
def c3(x, y): return (x+1, y-1)
def c4(x, y): return (x+1, y  )
def c5(x, y): return (x+1, y+1)
def c6(x, y): return (x  , y+1)
def c7(x, y): return (x-1, y+1)
def c8(x, y): return (x-1, y  )

def searchNeighbours(width, heigh, cells, x, y):
    neighbours = []
    c
    # Case 1: Top left corner
    if x == 0 and y == 0:
        neighbours.append(c4(x, y)) 
        neighbours.append(c5(x, y))
        neighbours.append(c6(x, y))

    # Case 2: Top right corner
    elif x == width-1 and y == 0:
        neighbours.append(c6(x, y))
        neighbours.append(c7(x, y))
        neighbours.append(c8(x, y)) 

    #Case 3: Bottom right corner
    elif x == width-1 and y == heigh-1:
        neighbours.append(c1(x, y))
        neighbours.append(c2(x, y))
        neighbours.append(c8(x, y))

    #Case 4: Bottom left corner
    elif x == 0 and y == heigh-1:
        neighbours.append(c2(x, y))
        neighbours.append(c3(x, y))
        neighbours.append(c4(x, y))

    #Case 5: Top wall
    elif x > 0 and x < width and y == 0:
        neighbours.append(c4(x, y))
        neighbours.append(c5(x, y))
        neighbours.append(c6(x, y))
        neighbours.append(c7(x, y))
        neighbours.append(c8(x, y))

    #Case 6: Right wall
    elif x == width-1 and y > 0 and y < heigh:
        neighbours.append(c1(x, y))
        neighbours.append(c2(x, y))
        neighbours.append(c6(x, y))
        neighbours.append(c7(x, y))
        neighbours.append(c8(x, y))

    #Case 7: Bottom wall
    elif x > 0 and x < width and y == heigh-1:
        neighbours.append(c1(x, y))
        neighbours.append(c2(x, y))
        neighbours.append(c3(x, y))
        neighbours.append(c4(x, y))
        neighbours.append(c8(x, y))

    #Case 9: Left wall
    elif x == 0 and y > 0 and y < heigh:
        neighbours.append(c2(x, y))
        neighbours.append(c3(x, y))
        neighbours.append(c4(x, y))
        neighbours.append(c5(x, y))
        neighbours.append(c6(x, y))

    else:
        neighbours.append(c1(x, y))
        neighbours.append(c2(x, y))
        neighbours.append(c3(x, y))
        neighbours.append(c4(x, y))
        neighbours.append(c5(x, y))
        neighbours.append(c6(x, y))
        neighbours.append(c7(x, y))
        neighbours.append(c8(x, y))


    return neighbours
