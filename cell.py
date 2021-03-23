import random

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
        self.quarantined = False          # If the cell is in quarantine
        self.color      = (255,255,255)  # White

    # Cell become infected  
    def infect(self, incubation, duration):
        self.infected   = True
        self.color      = (255, 128, 0)  #Orange Infectado pero aún no infeccioso
        self.incubation = incubation
        self.duration   = duration

    # Cell become recovered
    def recover(self, inmunity):
        self.infected = False
        self.incubation = -1
        self.duration   = -1
        self.inmunity   = inmunity
        self.color      = (51, 204, 51) # Green

    def die(self):
        self.alive    = False
        self.infected = False
        self.duration   = -1
        self.color = (0,0,0)  # Black

    def quarantine(self):
        self.quarantined = True
        self.color = (102, 204, 255) # Blue

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
                self.color = (255,0,0)   # Red Ya ha incubado el virus por lo que ya es infeccioso
                if self.duration > 0:
                    self.duration = self.duration - 1
                else: # If the viris has been incubated and the duration of the disease ends
                    if random.random() < deadliness:
                        return 1 # The cell recovers
                    else:
                        return 2 # The cell dies




