import csv
import MySQLdb

db = MySQLdb.connect(host="localhost",    # tu host, usualmente localhost
                     user="r0bert01de",   # tu usuario
                     passwd="1709",       # tu password
                     db="SII_2018")       # el nombre de la base de datos

with open('liv2018xls.csv') as File:  
    reader = csv.reader(File)
    for row in reader:
    	particion = str(row[0]).split(";")
    print(particion)
    