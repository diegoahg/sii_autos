import csv
import MySQLdb

db = MySQLdb.connect(host="localhost",    # tu host, usualmente localhost
                     user="r0bert01de",   # tu usuario
                     passwd="1709",       # tu password
                     db="SII_2018")       # el nombre de la base de datos
cursor = db.cursor()
mi_query = "SELECT * FROM IDEN_VEHI"
cursor.execute(mi_query)
cursor.fetchall()
i = 0
print('hdp')
with open('liv2018xls.csv') as File:  
    reader = csv.reader(File)
    for row in reader:
    	particion = str(row[0]).split(";")
		vehiculoID = int(i)
		codigo = particion[0]
		ano = int(particion[1])
		tipo = particion[2]
		marca = particion[3]
		modelo_raw = particion[4]
		modelo = str(0)
		version = str(0)
		ptas = int(particion[5])
		cilindr = int(particion[6])
		comb = particion[7]
		trans = particion[8]
		equip = particion[9]
		tas_2018 = int(particion[10])
		perm_2018 = int(particion[11])
		i = i +1
		sql = "INSERT INTO IDEN_VEHI (vehiculoID,codigo,ano,tipo,marca,modelo_raw,modelo,version,ptas,cilindr,comb,trans,equip,tas_2018,perm_2018) VALUES (%d, %s, %d, %s, %s, %s, %s, %s, %d, %d,  %s, %s, %s, %d, %d)"
		print(sql)
		registro = (vehiculoID,codigo,ano,tipo,marca,modelo_raw,modelo,version,ptas,cilindr,comb,trans,equip,tas_2018,perm_2018)
		print(registro)
		#cursor.execute(sql,registro)
		#cursor.commit()