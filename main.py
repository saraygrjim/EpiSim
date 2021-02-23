import click
from cell import Cell

# @click.command()
# @click.option('--count', default=1, help='Number of greetings.')
# @click.option('--name', prompt='Your name',
#               help='The person to greet.')
        

cells = []

# For the simulation
width  = 0  # Size of the grid
days   = 0  # Days to simulate
output = '' # Name of the output file

# Simulation parameters
probability = 0.0 # Probability that infections happens
incubation  = 0   # Days of incubation before the cell is infectious
duration    = 0   # How many days to finish and recover or to get worse
deadliness  = 0.0 # How deadly is the disease
inmunity    = 0.0 #  How inmune the cell is to infection after recovery

# Measures
med_day          = 0   # Day when the cell take the medicine
med_efficacy     = 0   # Efficacy of the medicine
quarent_day      = 0   # Day when the cell srar quarentine
quarent_efficacy = 0   # Efficacy of the quarentine


def main():
    


if __name__ == '__main__':
    main()