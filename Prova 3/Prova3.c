#include <stdio.h>
#include <stdlib.h>

typedef struct imagem
{
	int** matriz;
	int numerocolunas;
	int numerolinhas;
	int valormaxpixel;
}imagem;

int** leImagem(int i, int j)
{
	int** matriz; 
	matriz = (int **)malloc(sizeof(int *) * i);
	for (int i2 = 0; i2 < i; ++i2)
	{
		matriz[i2] = (int *)malloc(sizeof(int) * j);
	}

	for (int i2 = 0; i2 < i; ++i2)
	{
		for (int j2 = 0; j2 < j; ++j2)
		{
			scanf("%d", &matriz[i2][j2]);
		}
	}

	return (matriz);
}

void liberaImagem(int** matriz, int i)
{
	for (int i2 = 0; i2 < i; ++i2)
	{
		free(matriz[i2]);
	}
	free(matriz);
}

// sugestao de questao
//void questaoX(){
	
	// coloque aqui o seu codigo...
	
	// le a imagem.....
	//????? = leImagem();

	// coloque aqui o seu codigo...


	// libera a imagem
	//liberaImagem(??????);
//}

void questao1()
{
	imagem entrada;
	int limiar;
	scanf("%d", &limiar);
	scanf("%d", &entrada.numerocolunas);
	scanf("%d", &entrada.numerolinhas);

	scanf("%d", &entrada.valormaxpixel);

	entrada.matriz = leImagem(entrada.numerolinhas, entrada.numerocolunas);

	int contador = 0;
	for (int i2 = 0; i2 < entrada.numerolinhas; ++i2)
	{
		for (int j2 = 0; j2 < entrada.numerocolunas; ++j2)
		{
			if (entrada.matriz[i2][j2] >= limiar)
			{
				contador++;
			}
		}
	}

	printf("Ha %d pixels maiores ou iguais a %d\n", contador, limiar);

	liberaImagem(entrada.matriz, entrada.numerolinhas);

	return;
}

void questao2()
{
	imagem entrada;
	int qntbin;
	scanf("%d", &qntbin);
	scanf("%d", &entrada.numerocolunas);
	scanf("%d", &entrada.numerolinhas);

	scanf("%d", &entrada.valormaxpixel);

	entrada.matriz = leImagem(entrada.numerolinhas, entrada.numerocolunas);

	int tamanhovetor = entrada.valormaxpixel/qntbin;
	tamanhovetor++;

	int contador = 0;

	for(int k = 0; k < qntbin; ++k)
	{
		for (int i = 0; i < entrada.numerolinhas; ++i)
		{
			for (int j = 0; j < entrada.numerocolunas; ++j)
			{
				if (k * tamanhovetor <= entrada.matriz[i][j] && entrada.matriz[i][j] <= ((k + 1) * tamanhovetor) - 1)
				{
					contador++;
				}
			}
		}
	printf("hist[%d] = %d\n",k, contador);
	contador = 0;
	}

	liberaImagem(entrada.matriz, entrada.numerolinhas);
	return;
}

void Recursiva3(int** matriz, int x, int y, int numeroindicado, int valor)
{
	if (matriz[x - 1][y] == numeroindicado)
	{
		matriz[x - 1][y] = valor;
		Recursiva3(matriz, x - 1, y, numeroindicado, valor);
	}
	if (matriz[x + 1][y] == numeroindicado)
	{
		matriz[x + 1][y] = valor;
		Recursiva3(matriz, x + 1, y, numeroindicado, valor);
	}
	if (matriz[x][y + 1] == numeroindicado)
	{
		matriz[x][y + 1] = valor;
		Recursiva3(matriz, x, y + 1, numeroindicado, valor);
	}
	if (matriz[x][y - 1] == numeroindicado)
	{
		matriz[x][y - 1] = valor;
		Recursiva3(matriz, x, y - 1, numeroindicado, valor);
	}
	if (matriz[x - 1][y + 1] == numeroindicado)
	{
		matriz[x - 1][y + 1] = valor;
		Recursiva3(matriz, x - 1, y + 1, numeroindicado, valor);
	}
	if (matriz[x + 1][y - 1] == numeroindicado)
	{
		matriz[x + 1][y - 1] = valor;
		Recursiva3(matriz, x + 1, y - 1, numeroindicado, valor);
	}
	if (matriz[x - 1][y - 1] == numeroindicado)
	{
		matriz[x - 1][y - 1] = valor;
		Recursiva3(matriz, x - 1, y - 1, numeroindicado, valor);
	}
	if (matriz[x + 1][y + 1] == numeroindicado)
	{
		matriz[x + 1][y + 1] = valor;
		Recursiva3(matriz, x + 1, y + 1, numeroindicado, valor);
	}
	return;
}

void questao3()
{
	imagem entrada;
	int x, y;
	int valor;
	scanf("%d", &x);
	scanf("%d", &y);
	scanf("%d", &valor);
	scanf("%d", &entrada.numerocolunas);
	scanf("%d", &entrada.numerolinhas);

	scanf("%d", &entrada.valormaxpixel);

	entrada.matriz = leImagem(entrada.numerolinhas, entrada.numerocolunas);

	int matrizsalva[entrada.numerolinhas][entrada.numerocolunas];
	for (int i = 0; i < entrada.numerolinhas; ++i)
	{
		for (int j = 0; j < entrada.numerocolunas; ++j)
		{
			matrizsalva[i][j] = entrada.matriz[i][j];
		}
	}

	Recursiva3(entrada.matriz, x, y, entrada.matriz[x][y], valor);
	int contador = 0;

	for (int i = 0; i < entrada.numerolinhas; ++i)
	{
		for (int j = 0; j < entrada.numerocolunas; ++j)
		{
			if (matrizsalva[i][j] != entrada.matriz[i][j])
			{
				contador++;
			}
		}
	}

	printf("%d %d\n", entrada.numerocolunas, entrada.numerolinhas);
	printf("%d\n", entrada.valormaxpixel);
	for (int i = 0; i < entrada.numerolinhas; ++i)
	{
		for (int j = 0; j < entrada.numerocolunas; ++j)
		{
			printf("%4d", entrada.matriz[i][j]);
		}
		printf("\n");
	}
	printf("Quantidade de pixels trocados = %d\n", contador);

	liberaImagem(entrada.matriz, entrada.numerolinhas);
	return;
}

float Media4(int **matriz, int x, int y)
{
	float media = 0.0;
	media += matriz[x][y] + matriz[x + 1][y] + matriz[x - 1][y] + matriz[x][y + 1] + matriz[x][y - 1] + matriz[x + 1][y + 1] + matriz[x + 1][y - 1] + matriz[x - 1][y + 1] + matriz[x - 1][y - 1];
	media = media/9.0;
	return (media);
}

void questao4()
{
	imagem entrada;
	scanf("%d", &entrada.numerocolunas);
	scanf("%d", &entrada.numerolinhas);

	scanf("%d", &entrada.valormaxpixel);

	entrada.matriz = leImagem(entrada.numerolinhas, entrada.numerocolunas);

	float contador = 0.0;
	float matrizfloat[entrada.numerolinhas][entrada.numerocolunas];

	for (int i = 0; i < entrada.numerolinhas; ++i)
	{
		for (int j = 0; j < entrada.numerocolunas; ++j)
		{
			if (i == 0 || j == 0 || i == entrada.numerolinhas - 1 || j == entrada.numerocolunas - 1)
			{
				matrizfloat[i][j] = 0.0;
			}
			else
			{
				matrizfloat[i][j] = Media4(entrada.matriz, i, j);
				contador += matrizfloat[i][j];
			}
		}
	}
	contador = contador/((entrada.numerolinhas - 2) * (entrada.numerocolunas - 2));

	printf("%d %d\n", entrada.numerocolunas, entrada.numerolinhas);
	printf("%d\n", entrada.valormaxpixel);

	for (int i = 0; i < entrada.numerolinhas; ++i)
	{
		for (int j = 0; j < entrada.numerocolunas; ++j)
		{
			printf("%5.1f", matrizfloat[i][j]);
		}
		printf("\n");
	}
	printf("Media = %.1f\n", contador);

	liberaImagem(entrada.matriz, entrada.numerolinhas);
}

int main(int argc, char const *argv[])
{
	int opcao;

	// le a primeira linha do caso de teste que contem a questao a ser resolvida
	scanf("%d", &opcao);

	switch (opcao){
		case 1: 
			// chama a questao 1
			questao1();
		break;
		case 2:
			// Chama a questao 2
			questao2();
		break;
		case 3:
			// Chama a questao 3
			questao3();
		break;
		case 4:
			// Chama a questao 4
			questao4();
		break;
	}
	return(1);
}