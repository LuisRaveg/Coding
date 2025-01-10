#conjuto de datos de APPLE Inc. stock prize (Abril 2020)
import csv
import pandas as pd
fn=n = r'C:\Users\Administrator\Documents\Coding\Python\Trading\AAPL.csv'
#fn = 'D:\Coding\Python\Trading\AAPL.csv' #se abre el archivo
csv_reader=csv.DictReader(open(fn,'r')) # se crean varios diccionarios   con las filas del archivo
data=list(csv_reader) # se crea una lista de diccionarios
print(sum([float(l['CLOSE']) for  l in data])/len(data))# se calcula la media
#Con pandas:
data=pd.read_csv(fn,index_col=0,parse_dates=True)
print(data['CLOSE'].mean())

data.to_excel(r'C:\Users\Administrator\Documents\Coding\Python\Trading\AAPL.xlsx','AAPL')
data_copy=pd.read_excel(r'C:\Users\Administrator\Documents\Coding\Python\Trading\AAPL.xlsx','AAPL')