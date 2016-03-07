#include "memory.h"



void creer_grillage(SDL_Surface* screen)
{
    SDL_Rect position_ligne[NB_LIGNE];
    SDL_Surface* grillage[NB_LIGNE];
    int i;
    int ecart_entre_ligne_verticale = TAILLE_CARTE;
    int ecart_entre_ligne_horizontale = TAILLE_CARTE;

    for(i=0 ; i < 10; i++)
    {
        // positionnement des lignes vertivale
        if((i%2) == 0)
        {
            position_ligne[i].x = ecart_entre_ligne_verticale;
            position_ligne[i].y = 0;
            grillage[i] = SDL_CreateRGBSurface(SDL_HWSURFACE,5,WINDOW_SIZE, 32,0,0,0,0);
            ecart_entre_ligne_verticale += TAILLE_CARTE ;
            SDL_FillRect(grillage[i],&position_ligne[i],SDL_MapRGB(grillage[i]->format,0,0,0));
            SDL_BlitSurface(grillage[i], 0, screen, &position_ligne[i]);
        }
        // positionnement des lignes horizontale
        else
        {
            position_ligne[i].x = 0 ;
            position_ligne[i].y = ecart_entre_ligne_horizontale;
            grillage[i] = SDL_CreateRGBSurface(SDL_HWSURFACE,WINDOW_SIZE, 5, 32,0,0,0,0);
            ecart_entre_ligne_horizontale += TAILLE_CARTE;
            SDL_FillRect(grillage[i],&position_ligne[i],SDL_MapRGB(grillage[i]->format,0,0,0));
            SDL_BlitSurface(grillage[i], 0, screen, &position_ligne[i]);

        }
    }

}

void ajouter_image_dans_la_grille(SDL_Surface* screen){


}
int jouer_memory()
{
    // initialize SDL video
    SDL_Init( SDL_INIT_VIDEO );
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(WINDOW_SIZE, WINDOW_SIZE, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    if ( !screen )
    {
        printf("Unable to set %dx%d video: %s\n",WINDOW_SIZE,WINDOW_SIZE,SDL_GetError());
        return 1;
    }

    // load an image
    SDL_Surface* image = SDL_LoadBMP("foret.bmp");

    if (!image)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }


    // centre the bitmap on screen
    SDL_Rect pos_image_de_fond;
    pos_image_de_fond.x =0;
    pos_image_de_fond.y =0;

    // program main loop
    int done = 0;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = 1;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                case SDLK_ESCAPE :
                    done = 1;
                    break;


                }
            } // end switch
        } // end of message processing

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));

        // draw bitmap
        SDL_BlitSurface(image, 0, screen, &pos_image_de_fond);
        // positioonnement du grillage
        creer_grillage(screen); // mauvaise idee

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(image);
    SDL_FreeSurface(screen);
    return 0 ;

}
int main ( int argc, char** argv )
{
    jouer_memory();

    return 0;
}
