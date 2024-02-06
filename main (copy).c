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
int ecartx;
int ecarty;
int nbBrick;

int tabX[4][4];
int tabY[4][4];
int nbC = 4;
int nbL = 4;

/*Rebond angle

yballe - ybrick == xballe-xbrick*/

void vieBrick(){

    for(int i = 0; i < nbC ; i++){

        for(int j = 0; j < nbL; j++){
            xBrick = ecarty + i * (longBrick + espaceBrick);
            yBrick = ecarty + j * (largBrick + espaceBrick);
            tabX[j][i]= xBrick;
            tabY[j][i]= yBrick;
            drawRect(tabX[j][i], tabY[j][i], longBrick, largBrick);
            
            if((xball+rayonBall >= tabX[j][i]) && (xball-rayonBall <= tabX[j][i]+longBrick) && (yball+rayonBall >= tabY[j][i]) && (yball-rayonBall<= tabY[j][i]+largBrick)){/*dessus de brique*/
            vitesseBally = -vitesseBally;
        }
            else if((xball+rayonBall >= tabX[j][i]) && (xball-rayonBall >= tabX[j][i]+longBrick) && (yball-rayonBall >= tabY[j][i]) && (yball+rayonBall <= tabY[j][i]-largBrick)){/*dessous de brique*/
            vitesseBally = -vitesseBally;

        }

        }
}


}

void rebondBricks(){

    if((yball-rayonBall == yBrick+largBrick) && (xball-rayonBall <= xBrick+largBrick) && (xball+rayonBall+yball == xBrick+yBrick) || (xball-rayonBall <= xBrick+longBrick) && (yball-rayonBall <= yBrick+largBrick)){

        vitesseBally = -vitesseBally;
    }
}

void BricksSansTableau(){
    for(int i = 0;i < nbBrick; i++){
        xBrick = ecartx + i * (longBrick + espaceBrick);

        for(int j = 0;j < 4;j++){
            xBrick = ecarty + i * (longBrick + espaceBrick);
            yBrick = ecarty + j * (largBrick + espaceBrick);
            drawRect(xBrick, yBrick, longBrick, largBrick);

        }
    }
    rebondBricks();

}

void rebondBall(){

	if((xball+rayonBall >= WINDOW_WIDTH) || (xball <= rayonBall)){
    
	vitesseBallx = -vitesseBallx;
	}
                            
	if((yball+rayonBall >= WINDOW_HEIGHT) || (yball <= rayonBall)){

	vitesseBally = -vitesseBally;
    }


    if(((yball+rayonBall >= ysquare) && (xball+rayonBall >= xsquare) && (xball+rayonBall <= xsquare+lsquare))){
    
    vitesseBally = -vitesseBally;

	}
}

void drawBall(){

    changeColor(255,153,255);
    drawCircle(xball,yball,rayonBall);
    // sprite(xball-rayonBall,yball-rayonBall,"assets/balle.bmp");
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
	vbarre = 15;

    xBrick = 0;
    yBrick = 850;
    longBrick = 50;
    largBrick = 30;
    espaceBrick = 70;
    //pvBrick = 1;
    ecartx = (WINDOW_WIDTH-((nbBrick*longBrick)+((nbBrick-1)*espaceBrick)))/2;
    ecarty = 40;
    nbBrick = 6;

    vieBrick();
	
    //mettre votre code d'initialisation ici
}

void drawGame(){
    /* Ici je dessine mon jeu
     * exemple position x, y modifiés dans KeyPressed() et utilisés pour
     * pouvoir deplacer la figure à chaque boucle de gameLoop()
     */
    clear();
    drawBall();
    vieBrick();
    //BricksSansTableau();
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

        // case SDLK_SPACE;
        // clear();


        // break;
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