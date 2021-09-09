import subprocess
from matplotlib import pyplot as plt 
import csv 
import sys
import os
import typer
from PyInquirer import prompt
from examples import custom_style_2
import multiprocessing as mp
from time import sleep


questions = [
    {
        'type': 'confirm',
        'message': 'Do you want to generate a graph?',
        'name': 'continue',
        'default': True,
    }
]

# @app.command()
def main(file: str = typer.Option("", help="Path to Simulation file containing the rules and parameters. This file should be in .grj extension.", show_default=False)):

    if file != "":

        # Comprobaciones
        if not file.endswith('.grj'):
            typer.secho(f"ERROR: The file should be in .grj extension. Check the README file.", err=True, fg=typer.colors.RED, bold=True)
            raise typer.Exit()
         
        simulation = subprocess.Popen("cp " + file + " src/compiler_files/file.grj", shell=True, stderr=subprocess.PIPE).wait()
        if simulation != 0:
            typer.secho(f"ERROR: The file doesn't exist.", err=True, fg=typer.colors.RED, bold=True)
            raise typer.Exit()


        typer.secho(f"Compiling...", bold=True)
        subprocess.Popen("bison src/compiler_files/compiler.y", shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT).wait()
        subprocess.Popen("gcc compiler.tab.c -o src/compiler_files/compiler", shell=True, stdout=subprocess.PIPE).wait()
        compiler = subprocess.Popen("src/compiler_files/compiler < src/compiler_files/file.grj > src/simulation/epiSim.cpp", shell=True, stdout=subprocess.PIPE).wait()
        if compiler != 0:
            subprocess.Popen('rm -rf a.out compiler.tab.c src/compiler_files/compiler', shell=True, stdout=subprocess.PIPE).wait()
            raise typer.Exit()

        typer.secho(f"Executing...", bold=True)
        subprocess.Popen("g++ src/simulation/main.cpp src/simulation/grid.cpp src/simulation/sim.cpp -lglut -lGLU -lGL", shell=True, stdout=subprocess.PIPE).wait()
        simulation = subprocess.Popen("./a.out", shell=True, stdout=subprocess.PIPE).wait()
        subprocess.Popen('rm -rf a.out compiler.tab.c src/compiler_files/compiler', shell=True, stdout=subprocess.PIPE).wait()

        if simulation != 0:
            raise typer.Exit()

        answers = prompt(questions, style=custom_style_2)
        if answers['continue']:
            typer.secho(f"Generating graphs...", bold=True)
            
            for data in os.listdir("./Data/"):
                if data.endswith(".csv"):
                    dataName = data.replace('.csv','')
                    with open("./Data/" + data) as f: 
                        reader=csv.reader(f) 
                        header_row=next(reader) 

                        data = []
                        for i in range(0,len(header_row)):
                            data.append([])

                        for row in reader: 
                            for i in range(0,len(header_row)):
                                val = int(row[i])
                                data[i].append(val)

                        fig=plt.figure(dpi=128,figsize=(8,6)) 
                        
                        for i in range(1,len(header_row)):
                            plt.plot(data[0],data[i],alpha=0.6)

                        plt.title("Progress of the epidemic",fontsize=16)
                        plt.xlabel("Tick",fontsize=12)
                        plt.ylabel("Number of cells",fontsize=12)
                        plt.tick_params(axis='both',which='major',labelsize=8) 
                        plt.legend(header_row[1:len(header_row)])
                        
                        plt.savefig("./Data/" + dataName + ".png")

if __name__ == "__main__":
    typer.run(main)
