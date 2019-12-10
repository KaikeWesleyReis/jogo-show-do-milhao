#include <allegro.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
using namespace std;

//VARIAVEIS TEMPORIZADOR
volatile int tempo;

//FUNCOES
void decrementa_tempo(){tempo--;};
END_OF_FUNCTION(decrementa_tempo)

void swap (int *a, int *b){ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 
END_OF_FUNCTION(swap)

void randomize ( int arr[], int n ){ 
    srand ( time(NULL) ); 
    for (int i = n-1; i > 0; i--) 
    { 
        int j = rand() % (i+1); 
        swap(&arr[i], &arr[j]); 
    } 
} 
END_OF_FUNCTION(randomize)


int main(){
	//INICIALIZACOES ALLEGRO
	allegro_init();
	install_timer();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	install_keyboard();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1000,600,0,0);
	set_window_title("SHOW DO HULK");
	
	//VARIAVEIS VISUAIS
	BITMAP* buffer = create_bitmap(997,600);
	BITMAP* menu = load_bitmap("menu.bmp", NULL);
	BITMAP* instrucoes = load_bitmap("instrucoes.bmp", NULL);
	BITMAP* start_quest = load_bitmap("inicioPerguntas.bmp", NULL);
	BITMAP* gameover = load_bitmap("errou.bmp", NULL);
	BITMAP* win = load_bitmap("win.bmp", NULL);
	BITMAP* desistiu = load_bitmap("desistiu.bmp", NULL);
	BITMAP* imgTela; //alteravel ao longo do jogo
	
	//VARIAVEIS SONORAS
	SAMPLE *abertura = load_sample("abertura.wav");
	SAMPLE *suspense = load_sample("suspense.wav");
	SAMPLE *vencedor = load_sample("hojeSim.wav");
	SAMPLE *perdedor = load_sample("hojeNao.wav");

	//VARIAVEIS DO JOGO
	string perguntas[] = {"10.bmp", "11.bmp","12.bmp","13.bmp","14.bmp","15.bmp","16.bmp","17.bmp","18.bmp","19.bmp","20.bmp","21.bmp","22.bmp","23.bmp","24.bmp","25.bmp","26.bmp","27.bmp","28.bmp","29.bmp","30.bmp"};
	int respostas[] = {1,1,1,1,1,1,1,1,3,2,2,4,2,2,2,1,4,4,3,4,3};
	int n_perguntas = 10;
	int indexadores[] = {0,1,2,3,4,5,6,7,8,9}, temp[n_perguntas];
	int qtd = 10; 
	int index,resp_corr,resp_usuario;
	for(int j =0; j < n_perguntas;j++){
		temp[j] = indexadores[j];	
	}
	
	//JOGO FUNCIONAMENTO
	play_sample(abertura, 255, 128, 1000, 1);
	imgTela = menu;
	int perde = 0;
	int venceu = 0;
	int desiste = 0;
	int chave = 0;
	int sai = 0;
	volatile int placar;
	//LOOP DO JOGO
	while(!key[KEY_ESC]){	
		
		//JOGADOR VENCEU
		if(venceu == 1){
			venceu = 0; 
			imgTela = win;
			chave = 4;
			stop_sample(suspense);
			play_sample(vencedor, 255, 128, 1000, 1);
			draw_sprite(buffer, imgTela, 0, 0);	
			textprintf_centre_ex(buffer, font, 150,530,	makecol(255,255,0), -1, "%d",placar);	
			draw_sprite(screen, buffer,0,0);
			clear(buffer);
			rest(1500);
			imgTela = load_bitmap("winTeclas.bmp", NULL);
			draw_sprite(buffer, imgTela, 0, 0);
			textprintf_centre_ex(buffer, font, 150,530,	makecol(255,255,0), -1, "%d",placar);	
			draw_sprite(screen, buffer,0,0);
			clear(buffer);
			while(1){
				//tela pra sair ou rejogar de fato
				if(key[KEY_SPACE]){stop_sample(vencedor);break;};
				if(key[KEY_ESC]){stop_sample(vencedor);sai = 1;break;};
			}
		}
		venceu = 0;
		//JOGADOR PERDEU 
		if(perde == 1){
			perde = 0; 
			imgTela = gameover;
			chave = 4;
			stop_sample(suspense);
			play_sample(perdedor, 255, 128, 1000, 1);
			draw_sprite(buffer, imgTela, 0, 0);	
			draw_sprite(screen, buffer,0,0);
			clear(buffer);
			rest(1500);
			imgTela = load_bitmap("errouTeclas.bmp", NULL);
			draw_sprite(buffer, imgTela, 0, 0);
			draw_sprite(screen, buffer,0,0);
			clear(buffer);
			while(1){
				//tela pra sair ou rejogar de fato
				if(key[KEY_SPACE]){stop_sample(perdedor);break;};
				if(key[KEY_ESC]){stop_sample(perdedor);sai = 1;break;};
			}
		}
		//JOGADOR DESISTIU DE JOGAR 
		if(desiste == 1){
			desiste = 0; 
			imgTela = desistiu;
			chave = 4;
			stop_sample(suspense);
			play_sample(perdedor, 255, 128, 1000, 1);
			draw_sprite(buffer, imgTela, 0, 0);
			textprintf_centre_ex(buffer, font, 300,250,	makecol(255,255,0), -1, "%d",placar);	
			draw_sprite(screen, buffer,0,0);
			clear(buffer);
			rest(1500);
			imgTela = load_bitmap("desistiuTeclas.bmp", NULL);
			draw_sprite(buffer, imgTela, 0, 0);
			textprintf_centre_ex(buffer, font, 300,250,	makecol(255,255,0), -1, "%d",placar);	
			draw_sprite(screen, buffer,0,0);
			clear(buffer);			
			while(1){
				//tela pra sair ou rejogar de fato
				if(key[KEY_SPACE]){stop_sample(perdedor);break;};
				if(key[KEY_ESC]){stop_sample(perdedor);sai = 1;break;};
			}
		}
		placar = 0;
		//JOGADOR NAO VAI JOGAR MAIS
		if(sai == 1){break;};
		// VOLTA PARA O MENU
		if(chave == 4){perde = 0; imgTela = menu;chave = 0;play_sample(abertura, 255, 128, 1000, 1);rest(300);};
		//Segue em frente para tela de instrucoes
		if(chave == 0 && key[KEY_SPACE]){chave = 1;imgTela = instrucoes;rest(300);};
		//Segue em frente para a tela de preparo
		if(chave == 1 && key[KEY_SPACE]){chave = 2;imgTela = start_quest;rest(300);};
		//Segue em frente para as perguntas
		if(chave == 2 && key[KEY_SPACE]){
			stop_sample(abertura);
			rest(500);
			play_sample(suspense, 255, 128, 1000, 1);
			//RANDOMIZAR PERGUNTAS
			for(int j =0; j < n_perguntas;j++){
				indexadores[j] = temp[j];	
			}
			randomize (indexadores, 10); 
			for(int i = 0; i < qtd; i++){
				//Perdeu por tempo ou resp errada
				if(perde == 1 || desiste == 1){break;};
				//Definir o index da pergunta com sua resposta em uma var temp
				index = indexadores[i];
				//Define a pergunta
				const char *stc = perguntas[index].c_str();
				imgTela = load_bitmap(stc, NULL);
				//Define a resposta
				resp_corr = respostas[index];
				//Reseta a resposta dada pelo usuario/inicia
				resp_usuario = 0;
				//Inicializando temporizador
				tempo = 10;
				LOCK_FUNCTION(decrementa_tempo);
				LOCK_VARIABLE(tempo);
				//LOOP DA PERGUNTA
				while(1){
					//Decrementa o tempo
					install_int_ex(decrementa_tempo, SECS_TO_TIMER(1));
					
					//OPC Usuario :: Alternativas - 1,2,3,4
					if(key[KEY_1]){resp_usuario = 1;};
					if(key[KEY_2]){resp_usuario = 2;};
					if(key[KEY_3]){resp_usuario = 3;};
					if(key[KEY_4]){resp_usuario = 4;};
					//OPC Usuario :: Confirmar resposta
					if(resp_usuario != 0 && key[KEY_SPACE]){
						if(resp_usuario == resp_corr){
							placar += 10000;
							//comemoracao
							break;
							};
						if(resp_usuario != resp_corr){perde = 1;break;rest(300);};
					}
					//Tempo esgotou & perdeu
					if(tempo == 0){perde = 1;break;};
					//Desistiu e saiu com x valores
					if(key[KEY_TAB]){desiste = 1;break;};
					// Refresh na tela
					draw_sprite(buffer, imgTela, 0, 0);	
					textprintf_centre_ex(buffer, font, 900,525,	makecol(255,255,0), -1, "%d",placar);
					textprintf_centre_ex(buffer, font, 730,80,	makecol(255,255,255), -1, "%d",tempo);
					draw_sprite(screen, buffer,0,0);
				}
				clear(buffer);
				if(i == qtd - 1 && perde == 0 && desiste == 0) venceu = 1;//condicao de vitoria
			}		
		}
		//reset de tela - MENU INSTRUCOES START QUEST
		draw_sprite(buffer, imgTela, 0, 0);	
		draw_sprite(screen, buffer,0,0);
		clear(buffer);
	}
	//DESTRUINDO OS BITMAPS CRIADOS
	destroy_bitmap(buffer);
	destroy_bitmap(menu);
	destroy_bitmap(instrucoes);
	destroy_bitmap(start_quest);
	destroy_bitmap(gameover);
	destroy_bitmap(win);
	destroy_bitmap(imgTela);
	//DESTRUINDO OS SAMPLES CRIADOS
	destroy_sample(abertura);
	destroy_sample(vencedor);
	destroy_sample(perdedor);
	destroy_sample(suspense);
	return 0;		
}
END_OF_MAIN()


