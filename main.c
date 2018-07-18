#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//*** CONSTANTES DO SISTEMA ***

#define L 30    		//Lado da malha
#define Pr 5     		//Número de casas de precisão da probabilidade
#define AM 10000		//Número de amostras
#define PS 0.01  		//Número do passo da probabilidade de 0 a 1

//Assinaturas das funções
void vertical();
int DetecaoVertical(int matriz[L][L]);
int DetecaoHorizont(int matriz[L][L]);
int DetecaoPercoAnd(int matriz[L][L]);
int DetecaoPercolOr(int matriz[L][L]);
int DetecaoPercoXor(int matriz[L][L]);
void matriz_bruta(int matriz[L][L], float p);
void hoshen_kopelman(int matriz[L][L]);
int find (int pai[] , int x);
void join (int pai[] , int x, int y);
void imprimir (int matriz[L][L]);



int main()
{
	srand(time(NULL));

	int matriz[L][L];
	matriz_bruta (matriz, 0.5);
	hoshen_kopelman(matriz);
	int a = DetecaoVertical(matriz);
	printf ("%d\n",a);
	
	vertical();


//	system("python3 grafico.py");

	return 0;
}


void vertical()
{
	int matriz[L][L];
	int a, n, p, label1, label2, label3, label4, label5, cont1, cont2, cont3, cont4, cont5;
	float probabilidade;
	
	//Abrindo arquivo
	FILE *f = fopen("DADOS.txt","w");
	
	n = round(1.0/PS);
	//Laço da variação da probabilidade
	for (p = 0; p <= n; p++)
	{
		cont1 = 0;
		cont2 = 0;
		cont3 = 0;
		cont4 = 0;
		cont5 = 0;
		//Variando o numero de amostras
		for (a = 0; a < AM; a++)
		{
			probabilidade = p/(1.0*n);
			
			matriz_bruta(matriz, probabilidade);
			hoshen_kopelman(matriz);
			
			//Detectando o rótulo dos aglomerados
			label1 = DetecaoVertical(matriz);
			label2 = DetecaoHorizont(matriz);
			label3 = DetecaoPercoAnd(matriz);
			label4 = DetecaoPercolOr(matriz);
			label5 = DetecaoPercoXor(matriz);
			
			if (label1 != 0) cont1++;
			if (label2 != 0) cont2++;
			if (label3 != 0) cont3++;
			if (label4 != 0) cont4++;
			if (label5 != 0) cont5++;
			
		}
		
		//Imprimindo no arquivo txt já normalizado
		fprintf (f,"%f %f %f %f %f %f\n",probabilidade, (cont1/(1.0*AM)), (cont2/(1.0*AM)), (cont3/(1.0*AM)), (cont4/(1.0*AM)), (cont5/(1.0*AM)) );
	
	
		//Informações de processamento
		printf ("%d%%\n",p);
	
	}
	
	
	fclose(f);
		
}

//Detecando vercolação vertical
int DetecaoVertical(int matriz[L][L])
{
	int i, j;

	//Percorrendo a malha 
	for (i = 0; i < L; i++)
		for (j = 0; j < L; j++)
			//Detectando percolação vertical e retornando o rótulo do aglomerado percolante
			if (matriz[0][i] != 0 && matriz[L-1][j] != 0 && matriz[0][i] == matriz[L-1][j])
				return matriz[0][i];				
	return 0;
}

//Detectando Percolação Horizontal
int DetecaoHorizont(int matriz[L][L])
{
	int i, j;
	
	//Percorrendo a malha
	for (i = 0; i < L; i++)
		for (j = 0; j < L; j++)
			//Detectando percolação e retornando o rótulo do aglomerado percolante
			if (matriz[i][0] != 0 && matriz[j][L-1] != 0 && matriz[i][0] == matriz[j][L-1])
				return matriz[i][0];
	return 0;
}

//Detectando percolação vertical e horizontal	
int DetecaoPercoAnd(int matriz[L][L])
{
	int i, j;
	
	//Percorrendo a malha
	for (i = 0; i < L; i++)
		for (j = 0; j < L; j++)
			if (matriz[0][i] != 0 && matriz[L-1][j] != 0 && matriz[0][i] == matriz[L-1][j])
				if (matriz[i][0] != 0 && matriz[j][L-1] != 0 && matriz[i][0] == matriz[j][L-1])
					return 1;
	return 0;
}

//Detectando percolação vertical ou horizontal
int DetecaoPercolOr(int matriz[L][L])
{
	int i, j, perc1, perc2, soma;
	
	perc1 = 0; perc2 = 0;
	for (i = 0; i < L; i++)
		for (j = 0; j < L; j++)
			//Detectando percolação vertical e retornando o rótulo do aglomerado percolante
			if (matriz[0][i] != 0 && matriz[L-1][j] != 0 && matriz[0][i] == matriz[L-1][j])
				perc1 = 1;
	
	//Percorrendo a malha
	for (i = 0; i < L; i++)
		for (j = 0; j < L; j++)
			//Detectando percolação e retornando o rótulo do aglomerado percolante
			if (matriz[i][0] != 0 && matriz[j][L-1] != 0 && matriz[i][0] == matriz[j][L-1])
				perc2 = 1;
	
	soma = perc1+perc2;
	if (soma == 1 || soma == 2) return 1;
	return 0;
	
}

//Determinando percolação "OU EXCLUSIVO"
int DetecaoPercoXor(int matriz[L][L])
{
	int i, j, perc1, perc2, soma;
	
	perc1 = 0; perc2 = 0;
	for (i = 0; i < L; i++)
		for (j = 0; j < L; j++)
			//Detectando percolação vertical e retornando o rótulo do aglomerado percolante
			if (matriz[0][i] != 0 && matriz[L-1][j] != 0 && matriz[0][i] == matriz[L-1][j])
				perc1 = 1;
	
	//Percorrendo a malha
	for (i = 0; i < L; i++)
		for (j = 0; j < L; j++)
			//Detectando percolação e retornando o rótulo do aglomerado percolante
			if (matriz[i][0] != 0 && matriz[j][L-1] != 0 && matriz[i][0] == matriz[j][L-1])
				perc2 = 1;
	
	soma = perc1+perc2;
	if (soma == 1) return 1;
	return 0;
	
}



void matriz_bruta(int matriz[L][L], float p)
{
	int i, j, precisao;
	float num;
	
	//Percorrendo toda a malha
	for (i = 0; i < L; i++)
	{
		for (j = 0; j < L; j++)
		{
			//Gerando o numero aleatório
			precisao = pow(10,Pr);
			num = (rand() % precisao)+1;
			num = num/precisao;
			
			//Condição de ocupação
			if (num <= p)
				matriz[i][j] = 1;
			else
				matriz[i][j] = 0;
			
		}
	}
}


//Implementação do método de Hoshen-Kopelman
void hoshen_kopelman(int matriz[L][L])
{
	int i, j, novo;
	
	//Inicializando
	novo = 1;
	
	//Laço que percorrerá a malha
	for (i = 0; i < L; i++)
	{
		for (j = 0; j < L; j++)
		{
			//Visitando apenas sítios ocupados
			if (matriz[i][j] != 0)
			{
				
				//Rotulando o primeiro sítio
				if (i == 0 && j == 0)
				{
					matriz[i][j] = novo;
					novo++;
				}
				
				//Rotulando primeira linha
				if (i == 0 && j != 0)
				{
					if (matriz[i][j-1] != 0)
					{
						matriz[i][j] = matriz[i][j-1];
					}else
					{
						matriz[i][j] = novo;
						novo++;
					}
				}
				
				//Rotulando primeira coluna
				if (i != 0 && j == 0)
				{
					if (matriz[i-1][j] != 0)
					{
						matriz[i][j] = matriz[i-1][j];
					}else
					{
						matriz[i][j] = novo;
						novo++;
					}
				}
				
				//Rotulando a parte central da matriz
				if (i != 0 && j != 0)
				{
										
					//Possui apenas vizinho anterior
					if (matriz[i][j-1] != 0 && matriz[i-1][j] == 0)
					{
						matriz[i][j] = matriz[i][j-1];
					}
					
					//Possui apenas vizinho superior
					if (matriz[i][j-1] == 0 && matriz[i-1][j] != 0)
					{
						matriz[i][j] = matriz[i-1][j];
					}

					
					//Não possui vizinhos superiores nem anteriores
					if (matriz[i][j-1] == 0 && matriz[i-1][j] == 0)
					{
						matriz[i][j] = novo;
						novo++;
					}
					
					//Possui vizinhos superiores e anteriores
					if (matriz[i][j-1] != 0 && matriz[i-1][j] != 0)
					{
						if (matriz[i][j-1] < matriz[i-1][j])
						{
							matriz[i][j] = matriz[i][j-1];
						}else
						{
							matriz[i][j] = matriz[i-1][j];
						}
						
						if (matriz[i][j-1] == matriz[i-1][j])
						{
							matriz[i][j] = matriz[i][j-1];
						}
					}
					
					
				}
				
			}
		}
	}
		
	
	//Tratamento de conflitos
	int raiz, menor, maior;
	int pai[(L*L)/2]; for (i = 0; i < (L*L)/2; i++) pai[i] = i;
	
	
	//Percorrendo a malha
	for (i = 0; i < L; i++)
	{
		for (j = 0; j < L; j++)
		{
			//Condição de conflito
			if (i > 0 && j > 0 && matriz[i][j] != 0 && matriz[i][j-1] != 0 && matriz[i-1][j] != 0 && matriz[i][j-1] != matriz[i-1][j])
			{
				//Descobrir quem é o maior
				if (matriz[i][j-1] < matriz[i-1][j])
				{
					maior = matriz[i-1][j];
					menor = matriz[i][j-1];
					
					raiz = find (pai , maior);
					join (pai , raiz , menor);
				}else
				{
					maior = matriz[i][j-1];
					menor = matriz[i-1][j];
					
					raiz = find (pai , maior);
					join (pai , raiz , menor);
				}
			}
		}
	}
	
	//Rerotulando
	for (i = 0; i < L; i++)
		for (j = 0; j < L; j++)
			matriz[i][j] = find (pai , matriz[i][j]);
					
}

//Algoritmo UNION-FIND
int find (int pai[] , int x)
{
	if (pai[x] == x)
	{
		return x;
	}else
	{
		return (find(pai , pai[x]));
	}
}

void join (int pai[] , int x, int y)
{
	
	pai[find(pai , x)] = find (pai , y);
	
}

void imprimir (int matriz[L][L])
{
	int i, j;
	
	printf("\n");
	for (i = 0; i < L; i++)
	{
		for (j = 0; j < L; j++)
			printf ("%5d",matriz[i][j]);
			printf ("\n");
			printf ("\n");
	}
	printf("\n");
	
}
