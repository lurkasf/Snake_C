/*gcc cobrinha3.c console_v1.5.4.c graphics_v1.1.c -o SnakeGame.exe -lgdi32 -Wall -pedantic -Wextra*/

 /* Descrição: Ler uma tecla específica do teclado */
 /* 14/03/2015 */
 /* Declaração dos arquivos cabeçalhos */
 #include <stdio.h>            /* função printf() */
 #include "console_v1.5.4.h"  /* função Evento() */
 #include "graphics_v1.1.h"  /*funções graficas */
 #include <string.h>
 #include <stdlib.h>
 #include <time.h>
 #include <windows.h>
 
 COORD comida()
{
	 int i;
	 COLORREF cor=RGB(255,0,0);
	 COORD tamL = getTamanhoFonteConsole();
	 COORD tam = tamanhoJanelaConsole();
	 COORD mac;
	 mac.X =  rand()%(tam.X*tamL.X);
	 mac.Y =  rand()%(tam.Y*tamL.Y);
	/*printf ("Um numero entre 20 e 29: %d\n", rand()%10+20);*/
	 for(i=0;i<5;i++)
	 {
		circulo(mac.X,mac.Y,i,cor);
	 }
	 /*printf("comida criada em: %i %i", mac.X,mac.Y);*/
	 return (mac);
}
 
int main(int argc, char **argv)
{	
	COLORREF frente;
	/* Variável que armazenará o evento do teclado */
	EVENTO keyEvent;	
	/* Silenciar o warning relativo aos parämetros não usados da função main() */
	COORD comidas;
	COORD letras = getTamanhoFonteConsole();
	COLORREF colorLine;
	/*COORD tela = tamanhoJanelaConsole();*/
	int i;
	int cabx = 60;
	int caby = 60;
	setTituloConsole("SNAKE");
	setCursorStatus(DESLIGAR);
	setPosicaoJanela(360,100);
	setDimensaoJanela(100,30);
	/*COORD max = MaxDimensaoJanela();*/
	system("cls");
	srand(time(NULL));
	colorLine=RGB(rand()%255,rand()%255,rand()%255);
	argc = argc;
	argv = argv;
	comidas = comida();
	do
	{
		keyEvent = Evento();
        if (keyEvent.tipo_evento & KEY_EVENT) 
		{
			if(keyEvent.teclado.codigo_tecla == ESC)
			{
				setDimensaoJanela(20,20);
				for(i=0;i<500;i++){
					printf("<-");
				}
				system("cls");
				setDimensaoJanela(80,30);
				setCursorStatus(LIGAR);
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tJOGO TERMINADO!\n\n\n");
				break;
			}
			switch(keyEvent.teclado.codigo_tecla)
			{
				case SETA_PARA_CIMA:
					/*colorLine=RGB(rand()%255,rand()%255,rand()%255);
					putpixel(cabx,caby--,colorLine);
					putpixel(cabx+1,caby--,colorLine);
					putpixel(cabx+2,caby--,colorLine);*/
					colorLine=RGB(rand()%255,rand()%255,rand()%255);
					
					circulo(cabx,caby--,5,colorLine);
					circulo(cabx,caby--,5,colorLine);
					circulo(cabx,caby--,5,colorLine);
					
					frente=getpixel(cabx,caby-5);
				break;
				case SETA_PARA_BAIXO:
					/*colorLine=RGB(rand()%255,rand()%255,rand()%255);
					putpixel(cabx,caby++,colorLine);
					putpixel(cabx+1,caby++,colorLine);
					putpixel(cabx+2,caby++,colorLine);*/
					colorLine=RGB(rand()%255,rand()%255,rand()%255);
					circulo(cabx,caby++,5,colorLine);
					circulo(cabx,caby++,5,colorLine);
					circulo(cabx,caby++,5,colorLine);
					frente=getpixel(cabx,caby+5);
				break;
				case SETA_PARA_DIREITA:
					/*colorLine=RGB(rand()%255,rand()%255,rand()%255);
					putpixel(cabx++,caby,colorLine);
					putpixel(cabx++,caby+1,colorLine);
					putpixel(cabx++,caby+2,colorLine);*/
					colorLine=RGB(rand()%255,rand()%255,rand()%255);
					circulo(cabx++,caby,5,colorLine);
					circulo(cabx++,caby,5,colorLine);
					circulo(cabx++,caby,5,colorLine);
					frente=getpixel(cabx+5,caby);
				break;
				case SETA_PARA_ESQUERDA:
					/*colorLine=RGB(rand()%255,rand()%255,rand()%255);
					putpixel(cabx--,caby,colorLine);
					putpixel(cabx--,caby+1,colorLine);
					putpixel(cabx--,caby+2,colorLine);*/
					colorLine=RGB(rand()%255,rand()%255,rand()%255);
					circulo(cabx--,caby,5,colorLine);
					circulo(cabx--,caby,5,colorLine);
					circulo(cabx--,caby,5,colorLine);
					frente=getpixel(cabx-5,caby);
				break;
				case 'W':
					/*colorLine=RGB(rand()%255,rand()%255,rand()%255);
					putpixel(cabx,caby--,colorLine);
					putpixel(cabx+1,caby--,colorLine);
					putpixel(cabx+2,caby--,colorLine);
					colorLine=RGB(rand()%255,rand()%255,rand()%255);*/
					circulo(cabx,caby--,5,colorLine);
				break;
				case 'S':
					/*colorLine=RGB(rand()%255,rand()%255,rand()%255);
					putpixel(cabx,caby++,colorLine);
					putpixel(cabx+1,caby++,colorLine);
					putpixel(cabx+2,caby++,colorLine);
					colorLine=RGB(rand()%255,rand()%255,rand()%255);*/
					circulo(cabx,caby++,5,colorLine);
				break;
				case 'D':
					/*colorLine=RGB(rand()%255,rand()%255,rand()%255);
					putpixel(cabx++,caby,colorLine);
					putpixel(cabx++,caby+1,colorLine);
					putpixel(cabx++,caby+2,colorLine);
					colorLine=RGB(rand()%255,rand()%255,rand()%255);*/
					circulo(cabx++,caby,5,colorLine);
				break;
				case 'A':
					/*colorLine=RGB(rand()%255,rand()%255,rand()%255);
					putpixel(cabx--,caby,colorLine);
					putpixel(cabx--,caby+1,colorLine);
					putpixel(cabx--,caby+2,colorLine);
					colorLine=RGB(rand()%255,rand()%255,rand()%255);*/
					circulo(cabx--, caby,5,colorLine);
				break;
				case ESPACO:
					colorLine=RGB(rand()%255,rand()%255,rand()%255);
				break;
			}
			/*printf("cobra: %i %i",cabx,caby);*/
			if(caby*letras.Y < comidas.Y*letras.Y+55  && caby*letras.Y > comidas.Y*letras.Y-55 && cabx*letras.X < comidas.X*letras.X+55 && cabx*letras.X > comidas.X*letras.X-55)
			{
				comidas = comida();
				Beep(5000,80);
				Beep(3000,80);
				Beep(8000,80);
				/*printf("\a");*/
			}
			
			if (frente == RGB(0,0,0))
			{
				continue;
			}else
			{
				if(frente != RGB(255,0,0))
				{	
					setDimensaoJanela(20,20);
					for(i=0;i<500;i++){
						printf("<-");
					}
					system("cls");
					setDimensaoJanela(80,30);
					setCursorStatus(LIGAR);
					Beep(4000,80);
					Beep(6000,80);
					Beep(2000,100);
					printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tMORTO\n\n\n");
					break;
				}
			}
			
		}	
	}while(1); 
	/* Retornar que o programa encerrou com sucesso */
	return 0;
}
