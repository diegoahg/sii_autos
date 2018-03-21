import csv
import MySQLdb

db = MySQLdb.connect(host="localhost",user="r0bert01de",passwd="1709",db="SII_2018")
cursor = db.cursor()
i = 0
j = 0
#print('hdp')
with open('liv2018xls.csv') as File:
	reader = csv.reader(File)
	for row in reader:
		particion = str(row[0]).split(";")
		print(particion[2])
		if particion[2]!="MOTO":
            vehiculoID = i
            codigo = particion[0]
            ano = int(particion[1])
            tipo = particion[2]
            marca = particion[3]
            modelo_raw = particion[4]
            modelo = str(0)
            version = str(0)
            ptas = particion[5]
            cilindr = particion[6]
            comb = particion[7]
            trans = particion[8]
            equip = particion[9]
            tas_2018 = particion[10]
            perm_2018 = particion[11]
            i = i +1
            sql = """INSERT INTO IDEN_VEHI (vehiculoID,codigo,ano,tipo,marca,modelo_raw,modelo,version,ptas,cilindr,comb,trans,equip,tas_2018,perm_2018) VALUES
                                            (%d, %s, %d, %s, %s, %s, %s, %s, %d, %d,  %s, %s, %s, %d, %d)"""
            #print(sql)
            registro = (vehiculoID,codigo,ano,tipo,marca,modelo_raw,modelo,version,ptas,cilindr,comb,trans,equip,tas_2018,perm_2018)
            print(sql,registro)
            #cursor.execute(sql,registro)
            #cursor.commit()
            #sql = """SELECT * FROM IDEN_VEHI"""
            #cursor.execute(sql)
            #for row in cursor.fetchall():
            #print row[0]
            #print('Se ingresaron ' + str(i) + ' registros')
		j=j+1
		print('Se omitieron ' ,j, ' motos')
