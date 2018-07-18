import numpy as np
import pylab as pl

#Salvando os dados
dadosp = np.loadtxt("DADOS.txt",float)

#Realizando fatiamento dos dados
probabilidade = dadosp[:,0]
fracaopercol1 = dadosp[:,1]
fracaopercol2 = dadosp[:,2]
fracaopercol3 = dadosp[:,3]
fracaopercol4 = dadosp[:,4]
fracaopercol5 = dadosp[:,5]

pl.plot(probabilidade, fracaopercol1, 'r-', label = "Vertical")
pl.plot(probabilidade, fracaopercol2, 'b-', label = "Horizontal")
pl.plot(probabilidade, fracaopercol3, 'g-', label = "And")
pl.plot(probabilidade, fracaopercol4, 'k-', label = "Or")
pl.plot(probabilidade, fracaopercol5, 'y-', label = "Xor")

pl.legend(loc='best')
pl.grid(True)
pl.title("Rede 30x30")
pl.xlabel("Probabilidade de ocupação")
pl.ylabel("Fração de amostras percolantes")
pl.show()
