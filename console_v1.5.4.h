#ifndef _CONSOLE
#define _CONSOLE

#include <windows.h>
/* -> Estrutura COORD:
      typedef struct _COORD{
              SHORT X;   -> inteiro curto
              SHORT Y;   -> inteiro curto
              } COORD;
   -> Tipos WORD, DWORD e LPSTR
*/

/****************************************************************************************************************/
/*                                  INÍCIO DAS DECLARAÇÕES DE DEFINES E CONSTANTES                              */
/****************************************************************************************************************/
#define F1 112
#define F2 113
#define F3 114
#define F4 115
#define F5 116
#define F6 117
#define F7 118
#define F8 119
#define F9 120
#define F10 121
#define F11 122
#define F12 123

#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define ESPACO 32
#define TAB 9

/* Enhanced keys */
#define INSERT 45
#define DEL 46
#define PAGE_UP 33
#define PAGE_DOWN 34
#define END 35
#define HOME 36
#define SETA_PARA_ESQUERDA 37
#define SETA_PARA_CIMA 38
#define SETA_PARA_DIREITA 39
#define SETA_PARA_BAIXO 40

/* Teclas de status */
#define SHIFT_ESQUERDO_PRESSIONADO 0x0200  /* (constante definida por mim = 0x200 = shift esquerdo pressionado) + (0x010 = shift pressionado) = 0x210. Valor definido com base em uma extensão dos valores contidos na tabela: http://msdn.microsoft.com/pt-br/library/windows/desktop/ms684166%28v=vs.85%29.aspx */
#define SHIFT_DIREITO_PRESSIONADO 0x0400  /* (constante definida por mim = 0x400 = shift direito pressionado) + (0x010 = shift pressionado) = 0x410. Valor definido com base em uma extensão dos valores contidos na tabela: http://msdn.microsoft.com/pt-br/library/windows/desktop/ms684166%28v=vs.85%29.aspx */


/* constantes definidas para identificar a liberação de um determinado botão do mouse */
#define FROM_LEFT_1ST_BUTTON_RELEASED FROM_LEFT_1ST_BUTTON_PRESSED
#define FROM_LEFT_2ND_BUTTON_RELEASED FROM_LEFT_2ND_BUTTON_PRESSED
#define FROM_LEFT_3RD_BUTTON_RELEASED FROM_LEFT_3RD_BUTTON_PRESSED
#define FROM_LEFT_4TH_BUTTON_RELEASED FROM_LEFT_4TH_BUTTON_PRESSED
#define RIGHTMOST_BUTTON_RELEASED RIGHTMOST_BUTTON_PRESSED

/* dar a opção ao programador de usar constantes em português, caso queira */
#define BOTAO_ESQUERDO_PRESSIONADO FROM_LEFT_1ST_BUTTON_PRESSED
#define BOTAO_ESQUERDO_LIBERADO FROM_LEFT_1ST_BUTTON_RELEASED
#define BOTAO_DIREITO_PRESSIONADO RIGHTMOST_BUTTON_RELEASED
#define BOTAO_DIREITO_LIBERADO RIGHTMOST_BUTTON_RELEASED

/* constantes utilizadas pela função IdentificarEvento() para definir o nivel
   de detalhamento das informações a serem coletadas de um evento */
#define MINIMO 1
#define MAXIMO 2

#define BIT_SHORT_MAIS_SIGNIFICATIVO 0x80  /* (0x80) na base hexadecimal = (128) na base 10 = (1000 0000) na base 2 */
#define TECLA_PRESSIONADA 0x80
/****************************************************************************************************************/
/*                                  FIM DAS DECLARAÇÕES DE DEFINES E CONSTANTES                              */
/****************************************************************************************************************/




/****************************************************************************************************************/
/*                                   DECLARAÇÕES DE ESTRUTURAS E ENUMERAÇÕES                                    */
/****************************************************************************************************************/

 /* estrutura para o armazenamento das cores da janela de console */
    typedef struct{
                  int CorTexto;      /* cor do texto da janela de prompt atual */
		          int CorFundo;      /* cor de fundo da janela de prompt atual */
                  }CORES;


 /* tipo STATUS contendo os valores para ligar e desligar o cursor do mouse da tela */
    typedef enum{DESLIGAR, LIGAR} STATUS;


 /* tipo VISIBILIDADE */
    typedef enum{INVISIVEL, VISIVEL} VISIBILIDADE;


 /* tipo que permite identificar que tipo de evento deve ser verificada a existência no buffer de eventos */
    typedef enum{KEYBOARD_HIT, MOUSE_HIT, ALL} TYPE_HIT;


 /* Detalhes desta estrutura, ver link:
    http://msdn.microsoft.com/en-us/library/windows/desktop/ms684166%28v=vs.85%29.aspx */
    enum T_STATUS_TECLA{LIBERADA, PRESSIONADA};
    typedef struct T_TECLADO{
                            enum T_STATUS_TECLA status_tecla; /* LIBERADA ou PRESSIONADA */
		 				    DWORD codigo_tecla; /* código numérico que identifica uma tecla independente do tipo do teclado */
                            DWORD status_teclas_controle; /* CAPSLOCK_ON, ENHANCED_KEY (insert, delete, home, end, pg up, pg downl,
						                                   setas de direção, etc), LEFT_ALT_PRESSED, LEFT_CTRL_PRESSED,
						                                   NUMLOCK_ON, RIGHT_ALT_PRESSED, RIGHT_CTRL_PRESSED, SCROLLLOCK_ON,
								 						   SHIFT_PRESSED */
                            } TECLADO;

 /* Detalhes desta estrutura, ver link:
    http://msdn.microsoft.com/en-us/library/windows/desktop/ms684239%28v=vs.85%29.aspx */
    typedef struct T_MOUSE{
                          DWORD botao_pressionado; /* FROM_LEFT_1ST_BUTTON_PRESSED, FROM_LEFT_2ND_BUTTON_PRESSED, FROM_LEFT_3RD_BUTTON_PRESSED,
                                                      FROM_LEFT_4TH_BUTTON_PRESSED, RIGHTMOST_BUTTON_PRESSED */
		 				  DWORD botao_clicou;      /* se o botão tiver sido liberado, após ter sido pressionado */
                          COORD posicao; /* coordenadas (em forma de células de caracteres e não de pixels) do cursor do
						                    mouse em termos do tamanho (em linhas e colunas) do buffer
							 			    de console que estiver definido para a janela */
                          DWORD status_teclas_controle; /* CAPSLOCK_ON, ENHANCED_KEY (insert, delete, home, end, pg up, pg downl,
						                                   setas de direção, etc), LEFT_ALT_PRESSED, LEFT_CTRL_PRESSED,
						                                   NUMLOCK_ON, RIGHT_ALT_PRESSED, RIGHT_CTRL_PRESSED, SCROLLLOCK_ON,
							 							   SHIFT_PRESSED */
						  DWORD flags_qual_evento_mouse; /* DOUBLE_CLICK, MOUSE_HWHEELED, MOUSE_MOVED, MOUSE_WHEELED */
                          } MOUSE;

 /* Evento que pode ter acontecido e que é identificado pela função Evento() */
    typedef struct T_EVENTO{
                           WORD tipo_evento; /* pode ser MOUSE_EVENT ou KEY_EVENT */
		  				   TECLADO teclado; /* caso tenha ocorrido um KEY_EVENT, então esta estrutura será prenchida
						                    com os dados correspondentes */
						   MOUSE mouse;    /* caso tenha ocorrido um MOUSE_EVENT, então esta estrutura será prenchida
						                    com os dados correspondentes */
                           }EVENTO;


/****************************************************************************************************************/
/*                                  FIM DAS DECLARAÇÕES DE ESTRUTURAS E ENUMERAÇÕES                             */
/****************************************************************************************************************/





/****************************************************************************************************************/
/*                                INÍCIO DAS DECLARAÇÕES DOS PROTÓTIPOS DAS FUNÇÕES                             */
/****************************************************************************************************************/

 /*****************************************************************************************************************
  Descrição: imprime a mensagem do tipo LPSTR (ponteiro para uma string) juntamente com o código do último erro
             ocorrido no programa obtido do fluxo de erro (stderr) e encerra o programa.
  Parâmetros de entrada:
   -> Variável do tipo LPSTR: uma mensagem a ser impressa na tela.
  Retorno da função:
   -> Nenhum.
 *****************************************************************************************************************/
 void ErrorExit (LPSTR);




 /*****************************************************************************************************************
  Descrição: permitir e identificar com todos os detalhes, eventos originários do teclado e/ou do mouse.
  Parâmetros de entrada:
   -> Nenhum.
  Retorno da função:
   -> Estrutura EVENTO:
      - Campo "tipo_evento" que é do tipo WORD (inteiro sem sinal de 2 bytes):
	      -> Valor MOUSE_EVENT: significa que o evento lido do buffer da janela de console é um evento originário do
		                       MOUSE;
		  -> Valor KEY_EVENT: significa que o evento lido do buffer da janela de console é um evento originário do
		                     TECLADO;
		  -> Observação 1: esta função descarta os eventos FOCUS_EVENT, MENU_EVENT e WINDOW_BUFFER_SIZE_EVENT.
		                   Caso a identificação de algum desses eventos seja necessário, a função deve ser
			 			   estendida para que armazene neste campo o valor correspondente a um desses 3 eventos;
          -> Observação 2: o campo "tipo_evento" é um campo de bits. Isto é, cada um dos valores indicados
		                   está associado a um bit do campo. Portanto, a identificação de qual valor está armazenado
                           no campo deve ser feito por meio dos operadores bit-a-bit.
						   Exemplo: EVENTO e;
						            e = Evento();
						            if (e.tipo_evento & MOUSE_EVENT) printf("Foi gerado um evento pelo mouse");
						            if (e.tipo_evento & KEY_EVENT) printf("Foi gerado um evento pelo teclado");
	  - Campo "teclado" que é uma estrutura do tipo TECLADO: se o campo "tipo_evento" contiver um valor KEY_EVENT
	                                                         então esta estrutura conterá todos os dados relativos
															 a esse evento. Caso contrário, os valores contidos
															 nesta estrutura não tem sentido e, portanto, não devem
 															 ser utilizados.
	      -> Campo "status_tecla" do tipo enumeração: armazena se o evento do teclado foi o pressionamento
		                                              ou a liberação de uma tecla.
		     - Valor LIBERADA: evento corresponde à liberação do pressionamento de uma tecla;
			 - Valor PRESSIONADA: evento corresponde ao pressionamento de uma tecla.
		  -> Campo "codigo_tecla" do tipo DWORD: contem um valor inteiro único independente do tipo do teclado para
		                                       cada uma das teclas do teclado.
		     - Observação:
			   Recomenda-se o uso das constantes definidas no início deste arquivo (#defines) para
			   referenciar as teclas, ao invés da escrita no programa do próprio código da tecla.
		  -> Campo "status_teclas_controle" do tipo DWORD (4 bytes): contem o status das diversas teclas de
		                                                             controle.
             - Valor CAPSLOCK_ON: a luz da tecla CAPSLOCK está ligada;
             - Valor ENHANCED_KEY: a tecla pressionada é uma tecla estendida (INSERT, DELETE, HOME, END, PG UP,
			                       PG DOWN, SETAS DE DIREÇÃO, etc.);
             - Valor LEFT_ALT_PRESSED: a tecla ALT da esquerda está pressionada;
             - Valor LEFT_CTRL_PRESSED: a tecla CTRL da esquerda está pressionada;
             - Valor NUMLOCK_ON: a luz da tecla NUMLOCK está ligada;
             - Valor RIGHT_ALT_PRESSED: a tecla ALT da direita está pressionada;
             - Valor RIGHT_CTRL_PRESSED: a tecla CTRL da direita está pressionada;
             - Valor SCROLLLOCK_ON: a luz da tecla SCROLLLOCK está ligada;
             - Valor SHIFT_PRESSED: uma, ou mesmo ambas, as teclas SHIFT estão pressionadas.
			 - Valor SHIFT_ESQUERDO_PRESSIONADO: se foi pressionada a tecla de SHIFT ESQUERDA;
			 - Valor SHIFT_DIREITO_PRESSIONADO: se foi pressionada a tecla de SHIFT DIREITO;
             -> Observação:
			    Este campo "status_teclas_controle" é um campo de bits. Isto é, cada um dos valores indicados
		        está associado a um bit do campo. Portanto, a identificação de qual valor está armazenado
                no campo deve ser feito por meio dos operadores bit-a-bit.
				Exemplo: EVENTO e;
				         e = Evento();
				         if (e.teclado.status_teclas_controle & CAPSLOCK_ON) printf("A luz da tecla CAPSLOCK está acessa");
	  - Campo "mouse" que é uma estrutura do tipo MOUSE:
          -> Campo "botao_pressionado" do tipo DWORD:
             - Valor FROM_LEFT_1ST_BUTTON_PRESSED: primeiro botão da esquerda pressionado;
			 - Valor FROM_LEFT_2ND_BUTTON_PRESSED: segundo botão da esquerda pressionado;
			 - Valor RIGHTMOST_BUTTON_PRESSED: botão mais à direita pressionado.
             -> Observação 1:
			    Este campo "botao_pressionado" é um campo de bits. Isto é, cada um dos valores indicados está
				associado a um bit do campo. Portanto, a identificação de qual valor está armazenado no campo deve
				ser feito por meio dos operadores bit-a-bit.
			    Exemplo: EVENTO e;
				         e = Evento();
				         if (e.mouse.botao_pressionado & RIGHTMOST_BUTTON_PRESSED)
						     printf("O botão da direita está pressionado");
             -> Observação 2:
			    Foram definidas, na seção "DEFINES e CONSTANTES", constantes em português, para os botões esquerdo
                e direito do mouse, que podem ser utilizadas ao invés dos valores anteriores para aumentar
				a legibilidade do código:
				- BOTAO_ESQUERDO_PRESSIONADO
                - BOTAO_DIREITO_PRESSIONADO
             -> Observação 3:
			    Embora o "windows.h" colete e disponibilize informações para mais dois botões que porventura o
				mouse tenha (constantes FROM_LEFT_3RD_BUTTON_PRESSED e FROM_LEFT_4TH_BUTTON_PRESSED, correspondentes
				ao terceiro e quarto botões da esquerda, respectivamente), esta função ignora esses valores. Portanto,
				caso seja necessário essa identificação, a função deve ser estendida nesse aspecto.
		  -> Campo "botao_clicou" do tipo DWORD: contém se o evento foi a liberação de algum dos botões do mouse
		                                         que previamente estavam pressionados, definindo um clique do mouse.
             - Valor FROM_LEFT_1ST_BUTTON_RELEASED: primeiro botão da esquerda foi liberado (clicou);
			 - Valor FROM_LEFT_2ND_BUTTON_RELEASED: segundo botão da esquerda foi liberado (clicou);
			 - Valor RIGHTMOST_BUTTON_RELEASED: botão mais à direita foi liberado (clicou).
             -> Observação 1:
			    Este campo "botao_clicou" é um campo de bits. Isto é, cada um dos valores indicados está
				associado a um bit do campo. Portanto, a identificação de qual valor está armazenado no campo deve
				ser feito por meio dos operadores bit-a-bit.
			    Exemplo: EVENTO e;
				         e = Evento();
				         if (e.mouse.botao_clicou & RIGHTMOST_BUTTON_RELEASED)
						     printf("O botão da direita clicou/foi liberado");
             -> Observação 2:
			    Foram definidas, na seção "DEFINES e CONSTANTES", constantes em português, para os botões esquerdo
                e direito do mouse, que podem ser utilizadas ao invés dos valores anteriores para aumentar
				a legibilidade do código:
				- BOTAO_ESQUERDO_LIBERADO
                - BOTAO_DIREITO_LIBERADO
          -> Campo "posicao" que é uma estrutura do tipo COORD: guarda as coordenadas (x,y) na janela de console em
                                                                que ocorreu o evento do mouse. As coordenadas são
																dadas em posições de caracteres e não de pixels.
			 - Campo X: coluna da janela de console em que ocorreu o evento do mouse;
             - Campo Y: linha da janela de console em que ocorreu o evento do mouse.

		  -> Campo "status_teclas_controle" do tipo DWORD: contem o status das diversas teclas de controle, quando
		                                                   ocorreu o evento do mouse.
             - Valor CAPSLOCK_ON: a luz da tecla CAPSLOCK está ligada;
             - Valor ENHANCED_KEY: a tecla pressionada é uma tecla estendida (INSERT, DELETE, HOME, END, PG UP,
			                       PG DOWN, SETAS DE DIREÇÃO, etc.);
             - Valor LEFT_ALT_PRESSED: a tecla ALT da esquerda está pressionada;
             - Valor LEFT_CTRL_PRESSED: a tecla CTRL da esquerda está pressionada;
             - Valor NUMLOCK_ON: a luz da tecla NUMLOCK está ligada;
             - Valor RIGHT_ALT_PRESSED: a tecla ALT da direita está pressionada;
             - Valor RIGHT_CTRL_PRESSED: a tecla CTRL da direita está pressionada;
             - Valor SCROLLLOCK_ON: a luz da tecla SCROLLLOCK está ligada;
             - Valor SHIFT_PRESSED: uma, ou mesmo ambas, as teclas SHIFT estão pressionadas;
			 - Valor SHIFT_ESQUERDO_PRESSIONADO: se foi pressionada a tecla de SHIFT ESQUERDA;
			 - Valor SHIFT_DIREITO_PRESSIONADO: se foi pressionada a tecla de SHIFT DIREITO;
             -> Observação:
			    O campo "status_teclas_controle" é um campo de bits. Isto é, cada um dos valores indicados
		        está associado a um bit do campo. Portanto, a identificação de qual valor está armazenado
                no campo deve ser feito por meio dos operadores bit-a-bit.
				Exemplo: EVENTO e;
				         e = Evento();
				         if (e.teclado.status_teclas_controle & CAPSLOCK_ON) printf("A luz da tecla CAPSLOCK está acessa");
		  -> Campo "flags_qual_evento_mouse" do tipo DWORD: identifica qual o tipo de evento do mouse que ocorreu.
             - Valor DOUBLE_CLICK: o segundo clique (pressionado de botão de um duplo-clique ocorreu.
               * Observação: o primeiro clique é retornado como um evento normal de pressionamento de botão.
             - Valor MOUSE_HWHEELED:  a roda de rolagem horizontal do mouse foi girada.
			   * Observação: se a HIGH WORD do campo "botao_pressionado" contiver um valor positivo, então a roda foi
			                 girada para a direita. Caso contrário, a roda foi girada para a esquerda.
			                 Exemplo de identificação: EVENTO e;
                                                       e = Evento();
                                                       if( (int)e.mouse.botao_pressionado > 0)
                                                          printf("A roda do mouse foi girada para a direita");
                                                       else
                                                          printf("A roda do mouse foi girada para a esquerda");
             - Valor MOUSE_MOVED: ocorreu uma mudança na posição do mouse;
             - Valor MOUSE_WHEELED: a roda de rolagem vertical do mouse foi girada.
			   * Observação: se a HIGH WORD do campo "botao_pressionado" contiver um valor positivo, então a roda foi
			                 girada para a frente. Caso contrário, a roda foi girada para trás.
			                 Exemplo de identificação: EVENTO e;
                                                       e = Evento();
                                                       if( (int)e.mouse.botao_pressionado > 0)
                                                          printf("A roda do mouse foi girada para frente");
                                                       else
                                                          printf("A roda do mouse foi girada para trás");
  Observações:
   a) Deve ser dada preferência ao uso desta função ao invés da função getch();
   b) Ver a declaração da estrutura EVENTO na seção anterior denominada "DECLARAÇÕES DE ESTRUTURAS E ENUMERAÇÕES".
   c) Ver a declaração da estrutura COORD na seção anterior denominada "DECLARAÇÕES DE ESTRUTURAS E ENUMERAÇÕES".
   d) Ver a declaração da estrutura TECLADO na seção anterior denominada "DECLARAÇÕES DE ESTRUTURAS E ENUMERAÇÕES";
   e) Ver a declaração da estrutura MOUSE na seção anterior denominada"DECLARAÇÕES DE ESTRUTURAS E ENUMERAÇÕES".
   f) O tipo WORD é um inteiro sem sinal longo de 2 bytes definido na "windows.h";
   g) O tipo DWORD é um inteiro sem sinal longo de 4 bytes definido na "windows.h";
   h) Os tipos comuns definidos na "windows.h" podem ser consultados em:
      http://msdn.microsoft.com/en-us/library/cc230309.aspx
 *****************************************************************************************************************/
 EVENTO Evento(void);





/*****************************************************************************************************************
  Descrição: obter as cores de fundo e do texto definidas para a janela de console
  Parâmetros de entrada:
   -> Nenhum.
  Retorno da função:
   -> Estrutura CORES:
      - Campo CorTexto: cor definida para a escrita de na janela de console.
	  - Campo CorFundo: cor definida para o fundo de qualquer caracteres escrito na
	                    janela de console

  Observação:
   -> Ver a declaração da estrutura CORES na seção anterior denominada
      "DECLARAÇÕES DE ESTRUTURAS E ENUMERAÇÕES".
 *****************************************************************************************************************/
 CORES getCoresJanela(void);




 /*****************************************************************************************************************
  Descrição: obter as coordenadas atuais da janela de console na tela.
  Parâmetros de entrada:
   -> Nenhum.
  Retorno da função:
   -> Estrutura COORD:
      - Campo X representa a linha do pixel da borda superior da janela de console.
      - Campo Y representa a coluna do pixel da borda esquerda da janela de console

  Observações:
   a) A estrutura COORD é incluída por meio do arquivo cabeçalho "windows.h". Contudo, a sua declaração
      pode ser consultada anteriormente neste mesmo arquivo, na linha em que é incluído o arquivo
	  cabeçalho "windows.h".
   b) Em outras palavras, retorna as coodenadas (x,y) do pixel do canto superior
      esquerdo da janela de console.
 *****************************************************************************************************************/
 COORD getPosicaoJanela(void);
 


 
 /*****************************************************************************************************************
  Descrição: obter a resolução do monitor em pixels:
  Parâmetros de entrada:
   -> Nenhum.
  Retorno da função:
   -> Estrutura COORD:
      - Campo X representa o número de pixels da largura
      - Campo Y representa o número de pixels da altura

  Observação:
   -> A estrutura COORD é incluída por meio do arquivo cabeçalho "windows.h". Contudo, a sua declaração
      pode ser consultada anteriormente neste mesmo arquivo, na linha em que é incluído o arquivo
	  cabeçalho "windows.h".
 *****************************************************************************************************************/
 COORD getResolucaoMonitor(void);




 /*****************************************************************************************************************
  Descrição: obter, em número de pixels, as dimensões horizontal e vertical da fonte da janela do console.
  Parâmetros de entrada:
   -> Nenhum.
  Retorno da função:
   -> Estrutura COORD:
      - Campo X representa a quantidade de pixels na horizontal ocupada por um caractere na janela do console.
      - Campo Y representa a quantidade de pixels na vertical ocupada por um caractere na janela do console.

  Observação:
   -> A estrutura COORD é incluída por meio do arquivo cabeçalho "windows.h". Contudo, a sua declaração
      pode ser consultada anteriormente neste mesmo arquivo, na linha em que é incluído o arquivo
	  cabeçalho "windows.h".
 *****************************************************************************************************************/
 COORD getTamanhoFonteConsole(void);




 /*****************************************************************************************************************
  Descrição: obter o título da janela de console.
  Parâmetros de entrada:
   -> Nenhum.
   Retorno da função:
   -> Um ponteiro ponteiro para o endereço da string contendo o título da janela, ou NULL se a janela
      não tiver um título
 *****************************************************************************************************************/
 char *getTituloConsole(void);




 /*****************************************************************************************************************
  Descrição: obter se há algum evento (teclado, mouse, ou redimensionamento da janela) no buffer de eventos
             da janela de console.
  Parâmetros de entrada:
   -> Enumeração TYPE_HIT:
      - Valor KEYBOARD_HIT: identificar somente os eventos originários do teclado;
	  - Valor MOUSE_HIT: identificar somente os eventos originários do mouse;
	  - Valor ALL: identificar qualquer evento presente no buffer de eventos da janela de console, sejam
	               oriundos do teclado, do mouse, ou do redimensionamento da janela.
  Retorno da função:
   -> Um valor inteiro:
      - Valor 0: não há eventos do tipo solicitado no parâmetro da função no buffer de eventos da janela de
	             console;
	  - Valor 1: há um ou mais eventos do tipo solicitado no parâmetro da função no buffer de eventos
	             da janela de console.

  Observação:
   -> Ver a declaração da enumeração TYPE_HIT na seção anterior denominada
      "DECLARAÇÕES DE ESTRUTURAS E ENUMERAÇÕES".
 *****************************************************************************************************************/
 int hit(TYPE_HIT);




/*****************************************************************************************************************
  Descrição: apresentação detalhada de todas as informações possíveis de serem coletadas sobre um determinado evento
             ocorrido, cuja origem seja, ou o teclado, ou o mouse.
  Parâmetros de entrada:
   -> Variável do tipo da estrutura EVENTO:
      - Essa variável deve conter os dados do evento lido anteriormente sobre o qual serão coletadas as informações;
	  - Ver descrição do conteúdo dos campos da estrutura EVENTO na função Evento();
	  - Exemplo de código: EVENTO e;
	                       e = Evento();
						   IdentificarEvento(e, MAXIMO);
   -> Número inteiro que pode ser dois valores:
      - Valor 0: apresentar na tela o mínimo de informações sobre o evento passado como parâmetro;
	  - Valor 1: apresentar na tela o máximo de informações (todas as possíveis) sobre o evento passado como parâmetro;
	  -> Observação:
	     Foram definidas duas constantes do tipo DEFINE para este parâmetro, em substituição ao valores numéricos 0 e 1.
		 Constantes MINIMO e MAXIMO, correspondente aos valores 0 e 1, respectivamente.
  Retorno da função:
   -> Nenhum.

  Observação:
   -> Ver a declaração da estrutura EVENTO na seção anterior denominada "DECLARAÇÕES DE ESTRUTURAS E ENUMERAÇÕES".
 *****************************************************************************************************************/
 void IdentificarEvento(EVENTO, int);




 /*****************************************************************************************************************
  Descrição: obter as dimensões máximas possíveis de uma janela na resolução atual
             do monitor em pixels.
  Parâmetros de entrada:
   -> Nenhum.
  Retorno da função:
   -> Estrutura COORD:
     - Campo X representa o número de caracteres da largura
     - Campo Y representa o número de caracteres da altura

  Observações:
   a) A estrutura COORD é incluída por meio do arquivo cabeçalho "windows.h". Contudo, a sua declaração
      pode ser consultada anteriormente neste mesmo arquivo, na linha em que é incluído o arquivo
	  cabeçalho "windows.h".
   b) Para poder utilizar esta função é necessário fazer uma correção no arquivo WINCON.H do gcc.
      Isso porque esta função MaxDimensaoJanela(void) utiliza a função da API do Windows
	  denominada GetCurrentConsoleFont() que somente está disponível no Windows XP em diante e
 	  por isso o gcc não incluiu esse cabeçalho (embora exista sua implementação no ".lib" do gcc).
      - CORREÇÃO A SER FEITA:
	    Caso não exista, deve adicionar a seguinte linha no arquivo "wincon.h":
	         BOOL WINAPI GetCurrentConsoleFont(HANDLE, BOOL, PCONSOLE_FONT_INFO);
	  - ONDE DEVE SER ACRESCENTADA ESSA LINHA NO ARQUIVO "wincon.h":
        1) No arquivo "wincon.h" que está localizado dentro do diretório "include" da sua instalação do gcc for Windows
	    2) A linha indicada deve ser adicionada dentro do define (caso não exista, crie ele)
		     #if (_WIN32_WINNT >= 0x0500)
		          BOOL WINAPI GetCurrentConsoleFont(HANDLE, BOOL, PCONSOLE_FONT_INFO);
		          ... -> mantenha tudo o que já existir anteriormente definido dentro do define
		     #endif
 *****************************************************************************************************************/
 COORD MaxDimensaoJanela(void);




 /*****************************************************************************************************************
  Descrição: ligar ou desligar o cursor piscante na janela de console.
  Parâmetros de entrada:
   -> Uma string contendo o novo título da janela de console.
  Retorno da função:
   -> Enumeração STATUS:
      - Valor DESLIGAR: desligar o cursor piscante na janela de console;
	  - Valor LIGAR: ligar o cursos piscante na janela de console.

  Observação:
   -> Ver a declaração da enumeração STATUS na seção anterior denominada
      "DECLARAÇÕES DE ESTRUTURAS E ENUMERAÇÕES".
 *****************************************************************************************************************/
 void setCursorStatus(STATUS);




 /*****************************************************************************************************************
  Descrição: função que permite redimensionar a janela de console.
  Parâmetros de entrada:
   -> Estrutura COORD:
      - Campo X representa o número de caracteres da nova largura da janela
      - Campo Y representa o número de caracteres da nova altura da janela
  Retorno da função:
   -> Nenhum.

  Observação:
   - Recomenda-se que obtenha os valores máximos possíveis para o redimensionamento
     da janela do console por meio de uma chamada à função MaxDimensaoJanela(). Desse
     modo, conseguirá garantir que os valores passados como parâmetros para esta função
     não ultrapassará os valores máximos possíveis de redimensionamento da janela do
     console.
 *****************************************************************************************************************/
 void setDimensaoJanela(int largura, int altura);




 /*****************************************************************************************************************
  Descrição: esconder ou tornar visível a Barra de Tarefas da área de trabalho do Windows.
  Parâmetros de entrada:
   -> Enumeração VISIBILIDADE:
      - Valor VISIVEL: tornar visível a Barra de Tarefas;
      - Valor INVISIVEL: esconder a Barra de Tarefas.
  Retorno da função:
   -> Nenhum.

  Observação:
   -> Ver a declaração da enumeração VISIBILIDADE na seção anterior denominada
      "DECLARAÇÕES DE ESTRUTURAS E ENUMERAÇÕES".
 *****************************************************************************************************************/
 void setEstadoBarraTarefas(VISIBILIDADE);




/*****************************************************************************************************************
  Descrição: posicionar a janela em uma determinada posição na tela.
  Parâmetros de entrada:
   -> Estrutura COORD:
      - Campo X representa a linha do pixel da borda superior da janela de console.
      - Campo Y representa a coluna do pixel da borda esquerda da janela de console
  Retorno da função:
   -> Nenhum.
 *****************************************************************************************************************/
 void setPosicaoJanela(int top, int left);




 /*****************************************************************************************************************
  Descrição: definir um titulo para a janela de console.
  Parâmetros de entrada:
   -> Uma string contendo o novo título da janela de console.
  Retorno da função:
   -> Nenhum.
 *****************************************************************************************************************/
 void setTituloConsole(char *);




 /*****************************************************************************************************************
  Descrição: obter o tamanho da janela de console atual em quantidade de caracteres.
  Parâmetros de entrada:
   -> Nenhum.
  Retorno da função:
   -> Estrutura COORD:
      - Campo X representa a largura da janela de console em número de caracteres
      - Campo Y representa a altura da janela de console em número de caracteres

  Observação:
   -> A estrutura COORD é incluída por meio do arquivo cabeçalho "windows.h". Contudo, a sua declaração
      pode ser consultada anteriormente neste mesmo arquivo, na linha em que é incluído o arquivo
	  cabeçalho "windows.h".
 *****************************************************************************************************************/
 COORD tamanhoJanelaConsole(void);




/****************************************************************************************************************/
/*                                  FIM DAS DECLARAÇÕES DOS PROTÓTIPOS DAS FUNÇÕES                              */
/****************************************************************************************************************/

#endif
