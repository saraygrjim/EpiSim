import subprocess
from matplotlib import pyplot as plt 
import csv 
import sys
import os

# añadir que si no hay argumento imprima los posibles argumentos a pasar

if(sys.argv[1] == "clean"):
    subprocess.Popen('echo "Cleaning..."', shell=True, stdout=subprocess.PIPE).stdout.read()
    subprocess.Popen('rm -rf a.out compiler.tab.c DataStrain* compiler_files/compiler', shell=True, stdout=subprocess.PIPE).stdout.read()

else:
    subprocess.Popen("cp " + sys.argv[1] + " src/compiler_files/file.grj", shell=True, stdout=subprocess.PIPE).stdout.read()
    print("Compiling...")
    subprocess.Popen("bison src/compiler_files/compiler.y", shell=True, stdout=subprocess.PIPE).stdout.read()
    subprocess.Popen("gcc compiler.tab.c -o src/compiler_files/compiler", shell=True, stdout=subprocess.PIPE).stdout.read()
    subprocess.Popen("src/compiler_files/compiler < src/compiler_files/file.grj > src/simulation/epiSim.cpp", shell=True, stdout=subprocess.PIPE).stdout.read()
    print("Executing...")
    subprocess.Popen("g++ src/simulation/main.cpp src/simulation/grid.cpp src/simulation/sim.cpp -lglut -lGLU -lGL", shell=True, stdout=subprocess.PIPE).stdout.read()
    subprocess.Popen("./a.out", shell=True, stdout=subprocess.PIPE).stdout.read()
    print("Generating results...")
    subprocess.Popen('rm -rf a.out compiler.tab.c src/compiler_files/compiler', shell=True, stdout=subprocess.PIPE).stdout.read()

    for file in os.listdir("./Data/"):
        if file.endswith(".csv"):
            fileName = file.replace('.csv','')
            with open("./Data/" + file) as f: 
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
                
                plt.savefig("./Data/" + fileName + ".png")
