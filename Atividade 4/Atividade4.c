#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//vamos tratar cada par do elemento juntos
typedef struct Elemento
{
	int Numerador;
	int Denominador;
}elemento;

int mmc(int n1, int n2)
{
    int i, gcd, lcm;

    for(i=1; i <= n1 && i <= n2; ++i)
    {
        if(n1%i==0 && n2%i==0)
        {
            gcd = i;
        }
    }

    lcm = (n1*n2)/gcd;

    return lcm;
}

void Swap(elemento** Matriz, int linhapivo, int i)
{
	elemento* swap;
	swap = Matriz[i];
	Matriz[i] = Matriz[linhapivo];
	Matriz[linhapivo] = swap;
}

void FazendoContas(elemento** Matriz, int j, int i, int NumeroCoeficientes,int linhapivo, int NumeroEquacoes, int k)
{
	//criando uma copia da linha pivo para fazer calculos
	elemento NovaLinha[NumeroCoeficientes];
	for (int j2 = j; j2 < NumeroCoeficientes + j; ++j2)
	{
		NovaLinha[j2].Numerador = Matriz[k][j2].Numerador;
		NovaLinha[j2].Denominador =  Matriz[k][j2].Denominador;
	}

	//fazer a multiplicacao dos coeficientes e a razao do pivo/linha
	elemento razao;

	razao.Numerador = Matriz[i][j].Numerador * Matriz[k][j].Denominador;
	razao.Denominador = Matriz[i][j].Denominador * Matriz[k][j].Numerador;

	for (int j2 = j; j2 < NumeroCoeficientes + j; ++j2)
	{
		NovaLinha[j2].Numerador = NovaLinha[j2].Numerador * razao.Numerador;
		NovaLinha[j2].Denominador = NovaLinha[j2].Denominador * razao.Denominador;
	}

	//fazer o menor multiplo comum no divisor para a subtracao
	for (int j2 = j; j2 < NumeroCoeficientes + j; ++j2)
	{
		int calculador = mmc(NovaLinha[j2].Denominador, Matriz[i][j2].Denominador);
		NovaLinha[j2].Numerador = calculador / NovaLinha[j2].Denominador * NovaLinha[j2].Numerador;
		NovaLinha[j2].Denominador = calculador;
		Matriz[i][j2].Numerador = calculador / Matriz[i][j2].Denominador * Matriz[i][j2].Numerador;
		Matriz[i][j2].Denominador = calculador;
	}

	//fazer a subtracao
	for (int j2 = j; j2 < NumeroCoeficientes + j; ++j2)
	{
		Matriz[i][j2].Numerador -= NovaLinha[j2].Numerador;
	}

}

bool Escalonamento(int NumeroEquacoes, int NumeroCoeficientes, int j, int i, elemento** Matriz, int NumeroEquacoes2, int NumeroCoeficientes2)
{
	//se eu cheguei na ultima linha
	//vamos verificar se d != 0
	int contador = 0;
	if (j == 3)
	{
		for (int i2 = 0; i2 < NumeroEquacoes2; ++i2)
		{
			if(Matriz[i2][j].Numerador != 0)
			{
				for (int j2 = 0; j2 < NumeroCoeficientes2; ++j2)
				{
					if (Matriz[i2][j2].Numerador == 0)
					{
						contador++;		
					}
				}
				if(contador == 3)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}
	//printf("%d %d", i ,NumeroEquacoes);
	//vamos procurar o pivo
	int linhapivo = -1;
	bool flagdopivo = true;
	for (int i2 = i; i2 < NumeroEquacoes; ++i2)
	{
		if (Matriz[i2][j].Numerador != 0 && flagdopivo)
		{
			linhapivo = i2;
			flagdopivo = false;
		}
	}
	//printf("passei\n");
	//printf("%d\n", linhapivo);
	//caso eu nao encontre um 0 na coluna j, retorno para a proxima coluna
	if (linhapivo == -1)
	{
		//printf("bug\n");
		j += 1;
		return Escalonamento (NumeroEquacoes, NumeroCoeficientes, j, i, Matriz, NumeroEquacoes2, NumeroCoeficientes2);
	}
	else if (linhapivo == i)
	{
		//fazer nada
	}
	else
	{
		Swap(Matriz, linhapivo, i);
	}

	//recalcular a linha
	for (int i2 = i + 1; i2 < NumeroEquacoes + i; ++i2)
	{
		FazendoContas(Matriz, j, i2, NumeroCoeficientes, linhapivo, NumeroEquacoes, i);
	}

	j++;
	i++;
	NumeroCoeficientes--;
	NumeroEquacoes--;
	return Escalonamento(NumeroEquacoes, NumeroCoeficientes, j, i, Matriz, NumeroEquacoes2, NumeroCoeficientes2);
}

int main(int argc, char const *argv[])
{
	int NumeroEquacoes;
	int NumeroCoeficientes;
	int NumeroEquacoes2;
	int NumeroCoeficientes2;


	scanf("%d", &NumeroEquacoes);
	scanf("%d", &NumeroCoeficientes);

	NumeroEquacoes2 = NumeroEquacoes;
	NumeroCoeficientes2 = NumeroCoeficientes;
	//p ou r
	char c1;

	//Matriz de Struct Dinamica
	elemento** Matriz = NULL;
	Matriz = (elemento **)malloc(sizeof(elemento *) * NumeroEquacoes);
	for (int i = 0; i < NumeroEquacoes; ++i)
	{
		Matriz[i] = (elemento *)malloc(sizeof(elemento) * NumeroCoeficientes);
	}

	//Vou precisar saber quantas linhas ja foram inseridas
	int Inseridas = 0;

	//Vamos ler duas variaveis r ou p;
	for (int k = 0; k < 2; ++k)
	{
		scanf(" %c", &c1);
		if (c1 == 'r')
		{
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < NumeroCoeficientes; ++j)
				{
					scanf("%d", &(Matriz[Inseridas][j].Numerador));
					scanf("%d", &(Matriz[Inseridas][j].Denominador));
				}
				Inseridas++;	
			}
		}
		else
		{
			for (int j = 0; j < NumeroCoeficientes; ++j)
			{
				scanf("%d", &(Matriz[Inseridas][j].Numerador));
				scanf("%d", &(Matriz[Inseridas][j].Denominador));
			}
			Inseridas++;	
		}
	}

	bool flag;
	flag = Escalonamento(NumeroEquacoes,  NumeroCoeficientes,  0, 0, Matriz, NumeroEquacoes2, NumeroCoeficientes2);

	if (flag)
	{
		printf("sim\n");
	}
	else
	{
		printf("nao\n");
	}

	//printar matriz:
	for (int x = 0; x < NumeroEquacoes; ++x)
	{
		for (int y = 0; y < NumeroCoeficientes; ++y)
		{
			if (Matriz[x][y].Numerador % Matriz[x][y].Denominador == 0)
			{
				printf("%d\t", Matriz[x][y].Numerador / Matriz[x][y].Denominador);
			}
			else
			{
				printf("%d/%d\t", Matriz[x][y].Numerador, Matriz[x][y].Denominador);
			}
		}
		printf("\n");
	}

	for (int i = 0; i < NumeroEquacoes; ++i)
	{
		free(Matriz[i]);
	}
	free(Matriz);
	return 0;
}