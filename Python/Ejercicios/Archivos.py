
from random import randint as rnd
memReg = 'D:/Coding/Python/Ejercicios/members.txt'
exReg = 'D:/Coding/Python/Ejercicios/inactive.txt'
fee =('yes','no')
def crearArchivos(current,old):
    with open(current,'w+') as writefile: 
        writefile.write('Membership No  Date Joined  Active  \n')
        data = "{:^13}  {:<11}  {:<6}\n"

        for rowno in range(20):
            date = str(rnd(2015,2020))+ '-' + str(rnd(1,12))+'-'+str(rnd(1,25))
            writefile.write(data.format(rnd(10000,99999),date,fee[rnd(0,1)]))


    with open(old,'w+') as writefile: 
        writefile.write('Membership No  Date Joined  Active  \n')
        data = "{:^13}  {:<11}  {:<6}\n"
        for rowno in range(3):
            date = str(rnd(2015,2020))+ '-' + str(rnd(1,12))+'-'+str(rnd(1,25))
            writefile.write(data.format(rnd(10000,99999),date,fee[1]))
crearArchivos(memReg,exReg)
def eliminardatos(memReg,exReg):
    inactive=[]
    with open(memReg,'r+') as file1:
        with open(exReg,'a+')as file2:
            lineas1=file1.readlines()
            header=lineas1[0]
            lineas1.pop(0)
            for n in lineas1:
                if('no ' in n):
                    inactive.append(n)
            file1.seek(0)
            file1.write(header)
            for n in lineas1:
                if(n in inactive):
                    file2.write(n)
                else:
                    file1.write(n)
            file1.truncate()

eliminardatos(memReg, exReg)
