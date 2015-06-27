//Librerías necesarias
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<vector>
#include <iostream>
#include<cstdlib>
#include<SDL_mixer.h>

using namespace std;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event,e;
SDL_Texture *background,*instrucciones, *menu2, *nivel1, *nivel2, *nivel3, *nube, *nube2;
SDL_Rect rect_background,rect_instrucciones, rect_menu2, rect_nivel1, rect_nivel2, rect_nivel3, rect_nube,rect_nube2;
Mix_Music *gMusic = NULL;
Mix_Chunk *perder = NULL;
Mix_Chunk *ganar = NULL;
bool estado_menu=true;
char opc='m';
char ani='n';
int numero, temp;
int numpres;
void perdiste()
{
    Mix_PlayChannel( -1, perder, 0 );
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Pegale","Lo siento, has perdido :/ ",NULL);
    opc='m';
}
void ganaste()
{
      Mix_PlayChannel( -1, ganar, 0 );
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Pegale","Felicidades!!! Has ganado!!",NULL);
    opc='m';
}

int main(int argc, char* args[])
{
    	 //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					cout<<( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
				}
   //Inicializando componentes SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creando mi ventana
    if((window = SDL_CreateWindow("Pegale!!!", 300, 200, 700/*WIDTH*/, 350/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }

    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }


     //Inicializando texturas
    int w=0,h=0; //Variables ancho y largo
    perder = Mix_LoadWAV( "perder.wav" );
    ganar = Mix_LoadWAV( "ganar.wav" );
    //Fondo del juego, mi menu.
    background = IMG_LoadTexture(renderer,"menu.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = w;
    rect_background.h = h;

    //Instrucciones del juego.
    instrucciones = IMG_LoadTexture(renderer,"instrucciones.png");
    SDL_QueryTexture(instrucciones, NULL, NULL, &w, &h);
    rect_instrucciones.x = 0;
    rect_instrucciones.y = 0;
    rect_instrucciones.w = w;
    rect_instrucciones.h = h;

    //Imagen Menu2
    menu2= IMG_LoadTexture(renderer,"menu2.png");
    SDL_QueryTexture(menu2, NULL, NULL, &w, &h);
    rect_menu2.x = 0;
    rect_menu2.y = 0;
    rect_menu2.w = w;
    rect_menu2.h = h;

     //Imagen Nube Superior
    nube= IMG_LoadTexture(renderer,"nube.png");
    SDL_QueryTexture(nube, NULL, NULL, &w, &h);
    rect_nube.x = -300;
    rect_nube.y = 0;
    rect_nube.w = w;
    rect_nube.h = h;
    //Imagen Nube Inferior
    nube2= IMG_LoadTexture(renderer,"nube2.png");
    SDL_QueryTexture(nube2, NULL, NULL, &w, &h);
    rect_nube2.x = 700;
    rect_nube2.y = 250;
    rect_nube2.w = w;
    rect_nube2.h = h;

    //Imagen Nivel Fácil
    nivel1= IMG_LoadTexture(renderer,"nivel1.png");
    SDL_QueryTexture(nivel1, NULL, NULL, &w, &h);
    rect_nivel1.x = 0;
    rect_nivel1.y = 0;
    rect_nivel1.w = w;
    rect_nivel1.h = h;

    //Imagen Nivel Cardiaco
    nivel2= IMG_LoadTexture(renderer,"nivel2.png");
    SDL_QueryTexture(nivel2, NULL, NULL, &w, &h);
    rect_nivel2.x = 0;
    rect_nivel2.y = 0;
    rect_nivel2.w = w;
    rect_nivel2.h = h;

    //Imagen Nivel Mortal
    nivel3= IMG_LoadTexture(renderer,"nivel3.png");
    SDL_QueryTexture(nivel3, NULL, NULL, &w, &h);
    rect_nivel3.x = 0;
    rect_nivel3.y = 0;
    rect_nivel3.w = w;
    rect_nivel3.h = h;
//Animaciones
   vector<SDL_Texture*>caritas;
    caritas.push_back(IMG_LoadTexture(renderer,"c1.png"));
    caritas.push_back(IMG_LoadTexture(renderer,"c2.png"));
    caritas.push_back(IMG_LoadTexture(renderer,"c3.png"));
    caritas.push_back(IMG_LoadTexture(renderer,"c4.png"));
    caritas.push_back(IMG_LoadTexture(renderer,"c5.png"));
    caritas.push_back(IMG_LoadTexture(renderer,"c6.png"));
    SDL_Rect rect_caritas;
    SDL_QueryTexture(caritas[0], NULL, NULL, &w, &h);
    rect_caritas.x = 600;
    rect_caritas.y = 160;
    rect_caritas.w = w;
    rect_caritas.h = h;

    vector<SDL_Texture*>circulos;
    circulos.push_back(IMG_LoadTexture(renderer,"circulos/1.png"));
    circulos.push_back(IMG_LoadTexture(renderer,"circulos/2.png"));
    circulos.push_back(IMG_LoadTexture(renderer,"circulos/3.png"));
    circulos.push_back(IMG_LoadTexture(renderer,"circulos/4.png"));
    circulos.push_back(IMG_LoadTexture(renderer,"circulos/5.png"));
    SDL_Rect rect_circulos;
    SDL_QueryTexture(circulos[0], NULL, NULL, &w, &h);
    rect_circulos.x = 10;
    rect_circulos.y = 50;
    rect_circulos.w = w;
    rect_circulos.h = h;
    //Animacion del Luchador
    vector<SDL_Texture*>luchador;
    luchador.push_back(IMG_LoadTexture(renderer,"luchador/1.png"));
    luchador.push_back(IMG_LoadTexture(renderer,"luchador/2.png"));
    luchador.push_back(IMG_LoadTexture(renderer,"luchador/3.png"));
    luchador.push_back(IMG_LoadTexture(renderer,"luchador/4.png"));
    luchador.push_back(IMG_LoadTexture(renderer,"luchador/5.png"));
    SDL_Rect rect_luchador;
    SDL_QueryTexture(luchador[0], NULL, NULL, &w, &h);
    rect_luchador.x = 500;
    rect_luchador.y = 50;
    rect_luchador.w = w;
    rect_luchador.h = h;

    vector<SDL_Texture*>raton;
    raton.push_back(IMG_LoadTexture(renderer,"raton/1.png"));
    raton.push_back(IMG_LoadTexture(renderer,"raton/2.png"));
    raton.push_back(IMG_LoadTexture(renderer,"raton/3.png"));
    SDL_Rect rect_raton;
    SDL_QueryTexture(raton[0], NULL, NULL, &w, &h);
    rect_raton.x = -50;
    rect_raton.y = 300;
    rect_raton.w = w;
    rect_raton.h = h;

    int imagen_actual=0;
    int imagen_actual_aux=0;
    int imagen_actual2=0;
    int imagen_actual2_aux=0;
    int imagen_actual3=0;
    int imagen_actual3_aux=0;
    int imagen_actual4=0;
    int imagen_actual4_aux=0;

     while(true)
     {
        while(SDL_PollEvent(&Event))
        {
             if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_1 && opc=='m') //Si presiona 1 y la opcion es m que vaya al menú 2
                {
                    SDL_RenderCopy(renderer,menu2, NULL, &rect_menu2);
                    opc='j';
                     break;
                }
                if(Event.key.keysym.sym == SDLK_2 && opc=='m')
                {
                    SDL_RenderCopy(renderer,instrucciones, NULL, &rect_instrucciones);
                    opc='i';
                    break;
                }
                if(Event.key.keysym.sym == SDLK_3 && opc=='m')
                {exit(0);}

                if(Event.key.keysym.sym == SDLK_1 && opc=='j')
                {
                     numero=1+rand()%(4-1);
                    cout<<numero<<endl;
                    SDL_RenderCopy(renderer,nivel1, NULL, &rect_nivel1);
                    opc='a';
                    break;
                }
                if(Event.key.keysym.sym == SDLK_2 && opc=='j') //Nivel 2
                {
                    SDL_RenderCopy(renderer,nivel2, NULL, &rect_nivel2);
                    numero=1+rand()%(6-1);;
                    cout<<numero<<endl;
                    opc='a';
                    break;
                }
                if(Event.key.keysym.sym == SDLK_3 && opc=='j') //Nivel 3
                {
                    SDL_RenderCopy(renderer,nivel3, NULL, &rect_nivel3);
                    numero=1+rand()%(9-1);;
                    cout<<numero<<endl;
                    opc='a';
                    break;
                }

                //Conjunto de condiciones para jugar en los niveles
                if(Event.key.keysym.sym == SDLK_1 && opc=='a')
                {

                    if (numero==1)
                    {
                        ganaste();
                    } else
                    {
                       perdiste();

                    }

                }
                   if(Event.key.keysym.sym == SDLK_2 && opc=='a')
                {

                    if (numero==2)
                    {
                      ganaste();
                    } else
                    {
                       perdiste();
                    }
                }
                   if(Event.key.keysym.sym == SDLK_3 && opc=='a')
                {

                    if (numero==3)
                    {
                        ganaste();
                    } else
                    {
                       perdiste();
                    }

                }
                    if(Event.key.keysym.sym == SDLK_4 && opc=='a')
                {

                    if (numero==4)
                    {
                       ganaste();
                    } else
                    {
                        cout<<"Perdisteeee"<<endl;
                       perdiste();
                    }
                }

                    if(Event.key.keysym.sym == SDLK_5 && opc=='a')
                {

                    if (numero==5)
                    {
                        ganaste();
                    } else
                    {
                       perdiste();
                    }
                }
                    if(Event.key.keysym.sym == SDLK_6 && opc=='a')
                {
                    if (numero==6)
                    {
                        ganaste();
                    } else
                    {
                       perdiste();
                    }
                }
                    if(Event.key.keysym.sym == SDLK_7 && opc=='a')
                {

                    if (numero==7)
                    {
                        ganaste();
                    } else
                    {
                    perdiste();
                    }
                }
                    if(Event.key.keysym.sym == SDLK_8 && opc=='a')
                {

                    if (numero==8)
                    {
                    ganaste();
                    } else
                     {
                         perdiste();
                    }
                }

                if(Event.key.keysym.sym == SDLK_RETURN)
                {
                    opc='m';
                }

            } //Fin IF SDLKEYDOWN
        }//Fin del segundo While
         if(opc=='m')
        {
            SDL_RenderCopy(renderer, background, NULL, &rect_background);
            SDL_RenderCopy(renderer,caritas[imagen_actual],NULL,&rect_caritas);
            imagen_actual_aux++;
            if(imagen_actual_aux==60)
            {
                imagen_actual++;
                if(imagen_actual==6)
                imagen_actual=0;
                imagen_actual_aux=0;
            }

            SDL_RenderCopy(renderer,circulos[imagen_actual2],NULL,&rect_circulos);
            imagen_actual2_aux++;
            if(imagen_actual2_aux==60)
            {
                imagen_actual2++;
                if(imagen_actual2==5)
                imagen_actual2=0;
                imagen_actual2_aux=0;
            }

             SDL_RenderCopy(renderer,luchador[imagen_actual3],NULL,&rect_luchador);
            imagen_actual3_aux++;
            if(imagen_actual3_aux==60)
            {
                imagen_actual3++;
                if(imagen_actual3==5)
                imagen_actual3=0;
                imagen_actual3_aux=0;
            }
             SDL_RenderCopy(renderer,raton[imagen_actual4],NULL,&rect_raton);
            imagen_actual4_aux++;
            if(imagen_actual4_aux==60)
            {
                imagen_actual4++;
                if(imagen_actual4==3)
                imagen_actual4=0;
                imagen_actual4_aux=0;
            }
            SDL_RenderCopy(renderer, nube, NULL, &rect_nube);
            SDL_RenderCopy(renderer, nube2, NULL, &rect_nube2);
            if (rect_nube.x==900)
             {
                rect_nube.x=-300;
             }
               if (rect_nube2.x==-150)
             {
                rect_nube2.x=700;
             }
                  if (rect_raton.x==730)
             {
                rect_raton.x=-50;
             }

        }

          rect_nube.x++;
         rect_nube2.x--;
          rect_raton.x++;
        SDL_RenderPresent(renderer);
        SDL_Delay(7);
     }//FIN WHILE PRINCIPAL
    return 0;
}
