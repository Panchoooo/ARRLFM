
from random import seed
from random import randint
from random import *

seed(1)
import sys
filep = sys.argv[1]

data_folder = "/data/pizzachili"
path_lectura = data_folder+"/Resultados/"+filep+"/Simbolos.txt"

f = open(path_lectura, "r")
texto = f.read().split(" ")

patrones = 30000
cantidad_largo = [ 4,8,16 ]

for largo in cantidad_largo:
    print("Patron largo: "+str(largo))
    
    fo = open(data_folder+"/Resultados/"+filep+"/Patrones/Largo"+str(largo)+".txt", "w")  
    
    fo = open(data_folder+"/Resultados/"+filep+"/Patrones/Largo"+str(largo)+".txt", "a")  
    patrones_dict = {}
    contador = 0

    values_dict = {}

    limite = len(texto)
    value = 0
    while(contador < patrones and value < limite-(largo)):
        largo_patron_aux = 1
        #value = randint(0, len(texto)-largo)
        #value = value + 1
        value =randint(1, limite-(largo+10))
    
        #if(value not in values_dict.keys()):

        #values_dict[value] = 1

        patron = texto[value]
        while(largo_patron_aux < largo):
            patron = patron + " " + texto[value+largo_patron_aux]
            largo_patron_aux+=1

        #print(str(contador) + "  "+ str(value)+"  "+ patron)

        if(patron not in patrones_dict.keys()):
            patrones_dict[patron] = 1  
            fo.write(patron)
            contador+=1
            if(contador != patrones and value < limite-(largo)):
                fo.write("\n")

            print(str(contador*100/patrones)+"% | "+str(contador))
