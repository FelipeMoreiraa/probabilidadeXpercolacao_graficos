# probabilidadeXpercolacao_graficos
O projeto consiste em algoritmos implementados em C que realiza médias estatísticas em um número muito grande de amostras, para investigação do comportamento do fenômeno de percolação em função da probabilidade de ocupação.

O modelo de percolação, consiste em uma modelagem teórica que pode ser aplicada aos mais variados problemas. Dentre
os problemas podemos destacar, propagação de incêndios florestais, movimento de fluidos em meios porosos, fluxos de 
imigração, dentre outros.

O tratamento teórico, consiste em considerar uma malha, constituída de inumeros sítios, em que existe conectividade
geométrica entre os mesmos. Por exemplo, considerando uma rede bidimensional quadrada, cada sítio possuirá 4 vizinhos,
caso a rede seja triangular, cada sítio possuiŕa 3 vizinhos.

Cada sítío da malha, poderá está ocupado com probabilidade p pi desocupado com probabilidade 1-p, computacionalmente
falando, atribuimos o valor 1 para sítios ocupados e o valor 0 para sítios desocupados em uma matriz.

Dizemos que o ocorreu percolação quando existe um caminho de sítios ocupados, que interliga uma extremidade da malha
a outra extremidade. Exemplificando com o exemplo do movimento de fluidos em meios porosos, deve existir um caminho no
quual, ao se injetar água em uma extremidade do material, a água deve sair por alguma das extremidades.

O programa desenvolvido, mostra a fração de amostras percolantes para cada probabilidade, variando de 0 100%. E o estudo
foi realizado para vários tipos de percolação.

O algoritmo foi desenvilvido na linguagem de programação C, por ser uma modelagem que exige muito processamento, uma vez
que os cálculos são realizados em cima de milhares de amostras. Temos tambem um script em python para realizar a construção
dos gráficos, a partir dos dados gerados pelo programa principal.

Compilação: gcc main.c -o main -lm
Execução  : ./main

Execuçãopy: python3 graficos.py

