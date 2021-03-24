import random
from colours import *

class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.alive      = True
        self.incubation = -1             # Days of incubation before the cell is infectious
        self.infected   = False          # If the cell is infected or not
        self.duration   = -1             # How many days to finish and recover or to get worse
        self.inmunity   = -1             # How inmune the cell is to infection after recovery or not
        self.medication = False          # If the cell has taken its medication or not
        self.quarantined = False         # If the cell is in quarantine
        self.color      = WHITE
        self.quaratineDays = -1 

    def __str__(self):
        out = "Cell " + str(self.x) + ", " + str(self.y) + " is: "
        if self.alive:
            if self.infected:
                out = out + "Infected" 
                if self.incubation > -1:
                    out = out + "\n\tIncubation days remaining: " + str(self.incubation) + "\n\tThe days to finish or recover are " + str(self.duration)
                if self.quarantined:
                    out = out + "\n\tThe cell is in quarantine" 
                if self.medication:
                    out = out + "\n\tThe cell has take a medication" 
                   
            else:
                if self.color == WHITE:
                    out = out + "Not Infected yet"
                if self.color == GREEN:
                    out = out + "Infected but recover \n\t The inmunity is " + str(self.inmunity)
        else:
            out = out + "Die"
        return out

    # Cell become infected  
    def infect(self, incubation, duration):
        self.infected   = True
        self.color      = YELLOW
        self.incubation = incubation
        self.duration   = duration

    # Cell become recovered
    def recover(self, inmunity):
        # print("me he recuperado")
        self.infected = False
        self.incubation = -1
        self.duration   = -1
        self.inmunity   = inmunity
        self.color      = GREEN

    def die(self):
        self.alive    = False
        self.infected = False
        self.duration   = -1
        self.color = BLACK

    def quarantine(self):
        self.quarantined = True
        self.color = BLUE
        self.quaratineDays = 10

    def medicate(self, medEfficacy):
        if random.random() < medEfficacy:
            return True # The medication works and the cell recover
        else:
            self.medication = True
            return False # The medication doesn't work and the cell stay infected

    def process(self, deadliness):
        if self.infected:
            if self.incubation > 0:
                self.incubation = self.incubation - 1
                return 0 # The cell stay incubating
            else:
                self.color = RED   # Red Ya ha incubado el virus por lo que ya es infeccioso
                if self.duration > 0:
                    self.duration = self.duration - 1
                    return 3 # The cell stay infected
                else: # If the virus has been incubated and the duration of the disease ends
                    if random.random() > deadliness:
                        return 1 # The cell recovers
                    else:
                        return 2 # The cell dies



    def processQuarantine(self, quarentEfficacy):
        if self.quaratineDays > 0:
            self.quaratineDays = self.quaratineDays -1
            return 3  # The cell stay in quarantine
        else:
            self.quaratineDays = -1
            self.quarantine = False
            if random.random() < quarentEfficacy:
                return 1 # The cell recovers
            else:
                self.color = RED
                return 2 # The cell stay infected
            
