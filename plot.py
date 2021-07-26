import sys
import csv 
from matplotlib import pyplot as plt 

file= sys.argv[1]
fileName = file.replace('.csv','')
with open(file) as f: 
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
    
    plt.savefig(fileName + ".png")