=============================== READ ME ===============================

Universidade Federal da Fronteira Sul - UFFS
Disciplina de Computação Gráfica - 2016/02
Professor	José Carlos Bins
Alunos 	Edimar Roque Martello Júnior - 1111100038 - Noturno
	Edirlan José Censi - 1211100030 - Matutino
=======================================================================

COMPILAR
* Abra o terminar 
* Acesse o local dos arquivos, por exemplo:
	meucomputador@meuusuario:~/Área de Trabalho/CompGrafica/Trabalho 1$
* Entre com o comando:
	make
	//O mesmo executará o Makefile (retornará um warning que pode ser ignorado)

EXECUTAR
* Entre com o comando:
	./meu

INSTRUÇÕES
* Iterações com o teclado:
	W = Move o observador para cima
	S = Move o observador para baixo
	A = Move o observador para a esquerda
	D = Move o observador para a direita
	O = Aproxima o observador dos objetos (cena)
	P = Afasta o observador dos objetos (cena)
	I = Retorna a cena no estado inicial
	M = Pausa a cena, para visualização parada
	N = Despausa a cena, para visualização em movimento

OBSERVAÇÕES
* Utilize as teclas que movem o observador (W S A D), juntamente com as teclas que aproxima ou afasta o observador (O P)
	//Ao mover o observador ele se afasta o objeto, sem se aproximar poderá sair da área de visão do objeto
* Se sair da área de visão do objeto, utilize a tecla I para retornar a cena no estado inicial
* Para se aproximar do objeto é indicado pausar a cena utilizando a tecla M
	//Pois o objeto está em movimento, ao se aproximar do mesmo ele poderá sair da área de visão

=======================================================================
