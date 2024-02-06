#include <SDL2/SDL.h>
#include <unistd.h>
#include "function.h"
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH  700
#define WINDOW_HEIGHT 850
#define FPS 60
#define tabMAX 3

int xball;
int yball;
int rayonBall;
int vitesseBallx;
int vitesseBally;

int xsquare;
int ysquare;
int lsquare;
int vbarre;

int xBrick;
int yBrick;
int longBrick;
int largBrick;
int espaceBrick;
int pvBrick;
int pvJoueur;
int ecartx;
int ecarty;
int nbBrick;
//taille perfecte tableau 7/4

int Tabvie[7][4];
int tabX[7][4];
int tabY[7][4];
int nbC = 7;
int nbL = 4;






void drawvie(){
    if(pvJoueur == 3){
        sprite(20,WINDOW_HEIGHT-40,"assets/pv.bmp");
        sprite(50,WINDOW_HEIGHT-40,"assets/pv.bmp");
        sprite(80,WINDOW_HEIGHT-40,"assets/pv.bmp");
    }
    else if(pvJoueur == 2){
        sprite(20,WINDOW_HEIGHT-40,"assets/pv.bmp");
        sprite(50,WINDOW_HEIGHT-40,"assets/pv.bmp");
    }
    else if(pvJoueur == 1){
        sprite(20,WINDOW_HEIGHT-40,"assets/pv.bmp");
    }

}
void ecranwin(){
    clear;
    sprite(0,WINDOW_HEIGHT/2,"assets/win.bmp");
    vitesseBally = 0;
    vitesseBallx = 0;

}

void ecranmort(){
    clear;
    sprite(0, WINDOW_HEIGHT/2,"assets/écran de mort.bmp");
    vitesseBally = 0;
    vitesseBallx = 0;

}

void vieBrick(){

    for(int i = 0; i < nbC ; i++){

        for(int j = 0; j < nbL; j++){

            if(Tabvie[i][j] == 1){
            xBrick = ecarty + i * (longBrick + espaceBrick);
            yBrick = ecarty + j * (largBrick + espaceBrick);
            tabX[j][i]= xBrick;
            tabY[j][i]= yBrick;
            changeColor(102,153,153);
            drawRect(tabX[j][i], tabY[j][i], longBrick, largBrick);
            
            
            
            
            //dessous
                if((yball<(tabY[j][i]+largBrick+rayonBall)) && (xball<(tabX[j][i]+longBrick)) && (xball>tabX[j][i]) && (yball>(tabY[j][i]+largBrick))){
                    
                    Tabvie[i][j] = 0;
                    pvBrick--;
                    vitesseBally = -vitesseBally;
                 
                }
                
                //dessus
                else if((yball>(tabY[j][i]-rayonBall)) && (xball<(tabX[j][i]+longBrick)) && (xball>tabX[j][i])&& (yball<(tabY[j][i]))){
                    
                    Tabvie[i][j] = 0;
                    pvBrick--;
                    vitesseBally = -vitesseBally;
                }

                //gauche
                if((xball>(tabX[j][i]-rayonBall)) && (yball>(tabY[j][i]-rayonBall))&& (yball<tabY[j][i]+largBrick) && (xball<(tabX[j][i]))){
                                 
                    Tabvie[i][j] = 0;
                    pvBrick--;
                    vitesseBallx = -vitesseBallx;
                }

                //droite
                else if((xball<(tabX[j][i]+longBrick+rayonBall)) && (yball>(tabY[j][i]+rayonBall))&& (yball<tabY[j][i]+largBrick) && (xball>(tabX[j][i]+longBrick))){
                
                    Tabvie[i][j] = 0;
                    pvBrick--;
                    vitesseBallx = -vitesseBallx;
                }
            }
            if(pvJoueur == 0)
            {
                ecranmort();
                    
            }

            if(pvBrick == 0)
            {
                ecranwin();
            }

            

        }
}


}
//-1
void rebondBall(){

	if((xball+rayonBall >= WINDOW_WIDTH) || (xball <= rayonBall)){
    
	vitesseBallx = -vitesseBallx;
	}
                            
	else if((yball+rayonBall <= 0) || (yball <= rayonBall)){

	vitesseBally = -vitesseBally;
    }

    //rebond barre et balle
    else if(((yball+rayonBall >= ysquare) && (xball+rayonBall >= xsquare) && (xball+rayonBall <= xsquare+lsquare))){
    
    vitesseBally = -vitesseBally;

	}
    //retour au début quand une vie en moins + enlève de la vie
    else if((yball+rayonBall >= WINDOW_HEIGHT) || (yball<=rayonBall)){
        xsquare = WINDOW_WIDTH/2;
        xball = xsquare+lsquare/2;
        yball = WINDOW_HEIGHT-100;
        vitesseBally = -vitesseBally;
        pvJoueur--;
    }
}

void drawBall(){

    changeColor(255,153,0);
    drawCircle(xball,yball,rayonBall);
    //sprite(xball-rayonBall,yball-rayonBall,"assets/balle.bmp");
	//printf("xballe :%d - yballe :%d\n", xball, yball);
	xball += vitesseBallx;
	yball += vitesseBally;
	rebondBall();
}

void drawBarre(){
    if(xsquare>=WINDOW_WIDTH/2){
        changeColor(255,100,100);
    }
    else if(xsquare<=WINDOW_WIDTH/2)
    {
        changeColor(111,100,255);
    }

	drawRect(xsquare,ysquare,lsquare, 5);
	//printf("xsquare :%d - ysquare :%d\n", xsquare, ysquare);

    
	
}
	
void init_game(){

	xball = WINDOW_WIDTH/2;
	yball = WINDOW_HEIGHT-100;
	vitesseBallx = 6;
	vitesseBally = -6;
	rayonBall = 15;

	xsquare = WINDOW_WIDTH/2;
	ysquare = WINDOW_HEIGHT - 65;
	lsquare = 100;
	//rebondBarre;
	vbarre = 10;

    xBrick = 0;
    yBrick = 850;
    longBrick = 80;
    largBrick = 40;
    espaceBrick = 5;
    pvBrick = nbC*nbL;
    pvJoueur = 3;
    ecartx = (WINDOW_WIDTH-((nbBrick*longBrick)+((nbBrick-1)*espaceBrick)))/2;
    ecarty = 60;
    nbBrick = 6;
    
    for(int i = 0; i < nbC ; i++){

        for(int j = 0; j < nbL; j++){

        Tabvie[i][j] = 1;

    }
    }
    vieBrick();
	
    //mettre votre code d'initialisation icixball = WINDOW_WIDTH/2;
        yball = WINDOW_HEIGHT-100;
        vitesseBally = -vitesseBally;
}

void drawGame(){
    clear();
    sprite(0,0,"assets/Background.bmp");
    drawBall();
    vieBrick();
    drawvie();
    drawBarre();
    actualize();
    usleep(1000000 / FPS); // 60 images par seconde | 1000000 = 1 seconde

}
void KeyPressed(SDL_Keycode touche){
    /** @brief event.key.keysym.sym renvoi la touche appuyé
     *
     */
    switch (touche) {
        // Voir doc SDL_Keycode pour plus de touches https://wiki.libsdl.org/SDL_Keycode

	case SDLK_LEFT:
	clear();
	xsquare = xsquare+vbarre;
	
	if(xsquare > 0){
        vbarre = 0;
        xsquare=xsquare -10;
	
	}
	    break;
	    
	case SDLK_RIGHT :
	clear();
	
	if(xsquare+lsquare < WINDOW_WIDTH ){
        vbarre = 0;
       xsquare=xsquare+10;
	
	}
	
	    break;
	
        case SDLK_ESCAPE:
            freeAndTerminate();
            break;
        default:
            break;
    }
}
void joyButtonPressed(){
}

void gameLoop() {
    int programLaunched = 1;
    while (programLaunched == 1) {
        // Boucle pour garder le programme ouvert
        // lorsque programLaunched est different de 1
        // on sort de la boucle, donc de la fonction
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // boucle pour la gestion d'évenement
            switch (event.type) {
                /** event.type renvoi le type d'evenement qui se passe
                 * (si on appuie sur une touche, clique de souris...)
                 * en fonction du type d'évènement on à alors
                 * différentes information accessibles
                 * voir doc pour plus d'event https://wiki.libsdl.org/SDL_EventType
                 */
                case SDL_QUIT:
                    // quand on clique sur fermer la fénêtre en haut à droite
                    programLaunched = 0;
                    break;
                case SDL_MOUSEBUTTONUP:
                    /* clique de la souris
                     * event.motion.y | event.motion.x pour les positions de la souris
                     */
                    printf("position de la souris x : %d , y : %d\n", event.motion.x, event.motion.y);
                    break;
                case SDL_KEYDOWN:
                    KeyPressed(event.key.keysym.sym);
                    break;
                case SDL_JOYBUTTONDOWN:
                    break;
                default:
                    break;
            }
        }
        /* coder ici pour que le code s'execute après chaque évenement
         * exemple dessiner un carré avec position int x, int y qu'on peut
         * deplacer lorsqu'on appuie sur une touche
         */
        drawGame();
    }
}

int main(){
    /** @description 3 fonctions dans le main qui permettent de créer l'application et la maintenir ouverte :
     *  init(...) : initialiser la SDL/ fenêtre
     *  gameLoop() : boucle de jeu dans laquelle l'application reste ouverte
     *  freeAndTerminate() : quitte le programme proprement
     */
    init(WINDOW_WIDTH, WINDOW_HEIGHT);
    init_game();
    gameLoop();
    printf("Fin du programme\n");
    freeAndTerminate();
}