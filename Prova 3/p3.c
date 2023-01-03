#include <stdio.h>
#include <stdlib.h>


// sugestao de questao
void questaoX(){
	
	// coloque aqui o seu codigo...
	
	// le a imagem.....
	????? = leImagem();

	// coloque aqui o seu codigo...


	// libera a imagem
	liberaImagem(??????);
}


int main(int argc, char const *argv[])
{

	int opcao;

	// le a primeira linha do caso de teste que contem a questao a ser resolvida
	scanf("%d", &opcao);


	switch (opcao){
		case 1:
			// chama a questao 1
			//questao1();
		break;
		case 2:
			// Chama a questao 2
			//questao2();
		break;
		case 3:
			// Chama a questao 3
			//questao3();
		break;
		case 4:
			// Chama a questao 4
			//questao4();
		break;

	}

	return(1);

}

