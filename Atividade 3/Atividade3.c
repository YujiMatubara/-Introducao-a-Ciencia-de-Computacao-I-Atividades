#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//flag sera necessaria na recursao
bool flag;
void Limpausarmap(int **map, int **usarmap)
{
	flag = false;
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			usarmap[i][j] = map[i][j];
		}
	}
}

int floodfill(int LinhaAndador, int ColunaAndador, int **map, int LinhaRec, int ColunaRec)
{
	//restar o count
	int count = 0;
	count++;
	//preencher 1 onde ja passei com o Andador.
	map[LinhaAndador][ColunaAndador] = 1;

	if (LinhaAndador == LinhaRec && ColunaAndador == ColunaRec)
	{
		flag = true;
	}

    //Sul
	if (LinhaAndador + 1 < 9)
	{
		if(map[LinhaAndador + 1][ColunaAndador] == 0 && flag == false)
		{
			count+= floodfill(LinhaAndador + 1, ColunaAndador, map, LinhaRec, ColunaRec);
		}
	}

	//Norte
	if (LinhaAndador - 1 >= 0)
	{
		if (map[LinhaAndador - 1][ColunaAndador] == 0 && flag == false)
		{
			count+= floodfill(LinhaAndador - 1, ColunaAndador, map, LinhaRec, ColunaRec);
		}
	}

	//Oeste
	if (ColunaAndador - 1 >= 0)
	{
		if (map[LinhaAndador][ColunaAndador - 1] == 0 && flag == false)
		{
		count+= floodfill(LinhaAndador, ColunaAndador - 1, map, LinhaRec, ColunaRec);
		}
	}

	//Leste
	if (ColunaAndador + 1 < 9)
	{
		if (map[LinhaAndador][ColunaAndador + 1] == 0 && flag == false)
		{
		count+= floodfill(LinhaAndador, ColunaAndador + 1, map, LinhaRec, ColunaRec);
		}
	}
	return count;
}

int main(int argc, char const *argv[])
{
	//alocar dinamicamente o mapa de referencia
	int **map;
	map = (int **) malloc(sizeof(int *) * 9);
	for (int i = 0; i < 9; ++i)
	{
		map[i] = (int *) malloc(sizeof(int) * 9);
	}

	//alocar dinamicamente o mapa que sera usado
	int **usarmap;
	usarmap = (int **) malloc(sizeof(int *) * 9);
	for (int i = 0; i < 9; ++i)
	{
		usarmap[i] = (int *) malloc(sizeof(int) * 9);
	}

	//vamos escanear o mapa
	int P = 0;
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			scanf ("%d", &map[i][j]);
			//ler o numero de zeros e colocar em P para o calculo do somatorio
			P += 1 - map[i][j];
		}
	}

	//escanear posicao jogador 1
	int LinhaJogador1;
	scanf ("%d", &LinhaJogador1);
	int ColunaJogador1;
	scanf ("%d", &ColunaJogador1);
	//escanear posicao jogador 2
	int LinhaJogador2;
	scanf ("%d", &LinhaJogador2);
	int ColunaJogador2;
	scanf ("%d", &ColunaJogador2);

	//escanear numero de recursos
	int numrecursos;
	scanf ("%d", &numrecursos);

	//alocar estaticamente os recursos
	int posicaorec[numrecursos][2];
	
	//escanear posicao dos recursos
	for (int i = 0; i < numrecursos; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			scanf ("%d", &posicaorec[i][j]);
		}
	}

	//floadfill Eij
	//Temos (2 * numrecursos)Eijs
	Limpausarmap(map, usarmap);

	int Eij[2][numrecursos];
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < numrecursos; ++j)
		{
			Eij[i][j] = 0;
		}
	}

	//como as variaveis da posicao dos jogadores nao esta em vetor sera necessario de dois for.
	for (int j = 0; j < numrecursos; ++j)
	{
		//note Eij: jogador1 -->(countrec1, countrec2, countrecn)
		//			jogador2 -->(countrec1, countrec2, countrecn)
		Eij[0][j] = floodfill(LinhaJogador1, ColunaJogador1, usarmap, posicaorec[j][0], posicaorec[j][1]);
		Limpausarmap(map, usarmap);
	}

		
	for (int j = 0; j < numrecursos; ++j)
	{
		//note Eij: jogador1 -->(countrec1, countrec2, countrecn)
		//			jogador2 -->(countrec1, countrec2, countrecn)
		Eij[1][j] = floodfill(LinhaJogador2, ColunaJogador2, usarmap, posicaorec[j][0], posicaorec[j][1]);
		Limpausarmap(map, usarmap);
	}

	//calculo do Eiplayer 1
	double somatorioplayer1 = 0.0;
	for (int i = 0; i < numrecursos; ++i)
	{
		somatorioplayer1 += ((double)(Eij[0][i])/(double)P);
	}

	double Eiplayer1 = 0.0;
	Eiplayer1 = (double)(1/(double)numrecursos)*(double)somatorioplayer1;
	printf("%lf\n", Eiplayer1);

	//calculo do Eiplayer 2
	double somatorioplayer2 = 0.0;
	for (int i = 0; i < numrecursos; ++i)
	{
		somatorioplayer2 += ((double)(Eij[1][i])/(double)P);
	}

	double Eiplayer2 = 0.0;
	Eiplayer2 = (double)(1/(double)numrecursos)*(double)somatorioplayer2;
	printf("%lf\n", Eiplayer2);

	if (Eiplayer1 == Eiplayer2)
	{
		printf("O mapa eh balanceado\n");
	}
	else
	{
		if (Eiplayer1 > Eiplayer2)
		{
			printf("O jogador 2 possui vantagem\n");
		}
		else
		{
			printf("O jogador 1 possui vantagem\n");
		}
	}
	

	//liberar HEAP de map
	for (int i = 0; i < 9; ++i)
	{
		free(map[i]);
	}
	free(map);

	//liberar HEAP de usarmap
	for (int i = 0; i < 9; ++i)
	{
		free(usarmap[i]);
	}
	free(usarmap);
	return 0;
}