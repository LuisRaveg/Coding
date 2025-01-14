import pandas as pd
csv_path='D:/Coding/Python/Ejercicios/Datos.csv'
df=pd.read_csv(csv_path)
#print(df)
#print(df.iloc[0,0]) #el elemento fila 1 columna 1 (no se incluye el header)
#print(df.loc[0,'nombre'])#el elemento fila 1 columna 1 (no se incluye el header)
#df.index=['a','b','c','d'] #cambiamos los indices (no cambia el archivo)
#print(df.loc['a','nombre'])
#print(df.loc[0:2,'nombre':'dinero'])
df1=df[df['edad']>20]      #data frame con las personas mayores a 20
#df1.to_csv('nuevos_datos.csv')
print(df.loc[1:4,'edad'])
