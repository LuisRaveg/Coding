#conjuto de datos de APPLE Inc. stock prize (Abril 2020)
import csv
fn = 'D:\Coding\Python\Trading\AAPL.csv' #se abre el archivo
csv_reader=csv.DictReader(open(fn,'r')) # se crean varios diccionarios   con las filas del archivo
data=list(csv_reader) # se crea una lista de diccionarios
print(sum([float(l['CLOSE']) for  l in data])/len(data))# se calcula la media
 
