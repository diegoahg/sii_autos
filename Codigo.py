import csv

with open('liv2018xls.csv') as File:  
    reader = csv.reader(File)
    for row in reader:
    	particion = str(row[0]).split(";")
    print(particion)
    