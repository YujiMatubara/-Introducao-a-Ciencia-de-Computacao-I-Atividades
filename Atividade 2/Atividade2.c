#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char const *argv[])
{
	//declarando variaveis
	int n, i;
	scanf("%d %d", &n, &i);
	int matriz[n][i];
	float t;
	scanf("%f", &t);
	float matrizsimilaridade[n][n];
	//variaveis do calculo da similaridade
	int num = 0;
	float den1 = 0.0;
	float den2 = 0.0;

	//vamos escrever a matriz
	for (int i2 = 0; i2 < n; ++i2)
	{
		for (int j2 = 0; j2 < i; ++j2)
		{
			scanf("%d", &matriz[i2][j2]);
		}
	}

	//zerar matriz para nao conter lixo
	for (int i2 = 0; i2 < n; ++i2)
	{
		for (int j2 = 0; j2 < n; ++j2)
		{
			matrizsimilaridade[i2][j2] = 0.0;
		}
	}

	//agora vamos identificar o 0 
	for (int linha = 0; linha < n; linha++)
	{
		for (int coluna = 0; coluna < i; coluna++)
		{
			if (matriz[linha][coluna] == 0)
			{
					//agora vamos calcular a similaridade
					//utilizaremos o a para comparar as linhas
					for (int a = 0; a < n; a++)
					{	
						if (a != linha)
						{
							//calcular o numerador
							for (int j = 0; j < i; j++)
							{	
								num += matriz[linha][j] * matriz [a][j];
							}
							//calcular os denominadores
							for (int j = 0; j < i; j++)
							{
								den1 += pow(matriz[linha][j],2);
								den2 += pow(matriz[a][j],2);
							}

							//escrever a matriz de todas as similaridades
							matrizsimilaridade[linha][a] = (float)num/(sqrt(den1)*sqrt(den2));		
						}

						//dei um valor invalido para a linha de comparacao do cara com ele mesmo
						//o motivo de ser 0 esta no calculo da nota final no numerador
						else
						{	
							matrizsimilaridade[linha][a] = 0.0;
						}
						//zerar os valores do calculo para o looping do for
						num = 0;
						den1 = 0.0;
						den2 = 0.0;
					}
				break;	
			}
		}
	}

	//calcular a media das notas dos usuarios
	//o vetor medianotas esta com Media1[0], Media2[1]... Median[n-1]

	float medianotas[n];
	int count;
	for (int linha = 0; linha < n; linha++)
	{
		medianotas[linha] = 0;
		count = 0;
		for (int coluna = 0; coluna < i; ++coluna)
		{
			medianotas[linha] += matriz [linha][coluna];
			//o denominador deve contar somente o numero de filmes com notas dadas (!=0)
			if(matriz[linha][coluna] != 0)
				count += 1;
		}
		medianotas[linha] = medianotas[linha]/count;
	}


	//vamos criar a diferenca entre a nota dada e a media das notas da pessoa (s)
	float s[n][i];
	for (int linha = 0; linha < n; ++linha)
	{
		for (int coluna = 0; coluna < i; coluna++)
		{
			if (matriz[linha][coluna] != 0)
			{
				s[linha][coluna] = matriz[linha][coluna] - medianotas[linha];
			}
			else
			{
				s[linha][coluna] = 0;	
			}
		}
	}

	//valores para calcular a nota suposta
	float numnotasuposta = 0.0;
	float dennotasuposta = 0.0;
	float notasuposta = 0.0;
	//utilizaremos o flag apenas para pular (\n) de linha apos calcular as notas para uma pessoa
	int flag = 0;
	//devemos encontrar 0 para calcular a nota
	for (int linha = 0; linha < n; ++linha)
	{
		for (int coluna = 0; coluna < i; ++coluna)
		{
			if (matriz[linha][coluna] == 0)
			{
				flag = 1;
				for (int k = 0; k < n; ++k)
				{
					if (matrizsimilaridade[linha][k] >= t && matriz[k][coluna] != 0)
					{
						dennotasuposta += matrizsimilaridade[linha][k];
						numnotasuposta += matrizsimilaridade[linha][k] * s[k][coluna];
					}
				}
				//printar o DI quando nao houver similaridade suficiente para o calculo
				if (dennotasuposta == 0.0)
				{
					printf("DI ");
				}
				else
				{
					notasuposta = (float)medianotas[linha] + (numnotasuposta/dennotasuposta);
					printf("%.2f ", notasuposta);
				}
			}
			//zerar os valores para o looping
			numnotasuposta = 0.0;
			dennotasuposta = 0.0;
			notasuposta = 0.0;
		}
		if (flag == 1)
		{
			printf("\n");
			flag = 0;
		}
	}
	return 0;
}