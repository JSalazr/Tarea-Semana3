
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<map>
#include<vector>
#include <stdlib.h>
#include<SDL2/SDL_mixer.h>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character, *character2, *character3;
SDL_Rect rect_background,rect_character,rect_character2, rect_character3;


int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 500/*WIDTH*/, 250/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
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

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0; rect_background.y = 0; rect_background.w = w; rect_background.h = h;

    character = IMG_LoadTexture(renderer, "personaje/down1.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 0; rect_character.y = 100; rect_character.w = w; rect_character.h = h;

    character2 = IMG_LoadTexture(renderer, "personaje2/link1.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character2.x = 100; rect_character2.y = 100; rect_character2.w = 22; rect_character2.h = 28;

    character3 = IMG_LoadTexture(renderer, "personaje3/sonic1.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character3.x = 200; rect_character3.y = 100; rect_character3.w = 46; rect_character3.h = 28;

    char orientation = 'd';// d u l r
    int current_sprite = 0;
    int animation_velocity = 20;
    int velocity = 3;
    int frame = 0;
    char orientation2 = 'd';// d u l r
    int current_sprite2 = 0;
    char orientation3 = 'r';
    int current_sprite3=0;
    bool lado=true;
    map<char,vector<SDL_Texture*> >sprites, sprites2, sprites3;
    sprites['u'].push_back(IMG_LoadTexture(renderer, "personaje/up1.png"));
    sprites['u'].push_back(IMG_LoadTexture(renderer, "personaje/up2.png"));
    sprites['d'].push_back(IMG_LoadTexture(renderer, "personaje/down1.png"));
    sprites['d'].push_back(IMG_LoadTexture(renderer, "personaje/down2.png"));
    sprites['l'].push_back(IMG_LoadTexture(renderer, "personaje/left1.png"));
    sprites['l'].push_back(IMG_LoadTexture(renderer, "personaje/left2.png"));
    sprites['r'].push_back(IMG_LoadTexture(renderer, "personaje/right1.png"));
    sprites['r'].push_back(IMG_LoadTexture(renderer, "personaje/right2.png"));
    sprites2['u'].push_back(IMG_LoadTexture(renderer, "personaje2/link7.png"));
    sprites2['u'].push_back(IMG_LoadTexture(renderer, "personaje2/link8.png"));
    sprites2['d'].push_back(IMG_LoadTexture(renderer, "personaje2/link1.png"));
    sprites2['d'].push_back(IMG_LoadTexture(renderer, "personaje2/link2.png"));
    sprites2['l'].push_back(IMG_LoadTexture(renderer, "personaje2/link3.png"));
    sprites2['l'].push_back(IMG_LoadTexture(renderer, "personaje2/link4.png"));
    sprites2['r'].push_back(IMG_LoadTexture(renderer, "personaje2/link5.png"));
    sprites2['r'].push_back(IMG_LoadTexture(renderer, "personaje2/link6.png"));
    sprites3['r'].push_back(IMG_LoadTexture(renderer, "personaje3/sonic1.png"));
    sprites3['r'].push_back(IMG_LoadTexture(renderer, "personaje3/sonic2.png"));
    sprites3['l'].push_back(IMG_LoadTexture(renderer, "personaje3/sonic3.png"));
    sprites3['l'].push_back(IMG_LoadTexture(renderer, "personaje3/sonic4.png"));


    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2,2048);

    Mix_Music *music= Mix_LoadMUS("Zelda.wav");
    Mix_Chunk *sound= Mix_LoadWAV("Sonic.wav");

    //Main Loop
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

        if(!Mix_PlayingMusic())
            Mix_PlayMusic(music,1);

        if(lado)
        {
            rect_character3.x+=velocity;
            orientation3='r';
        }
        if(rect_character3.x>=300)
        {
            Mix_PlayChannel(-1,sound,0);
            lado=false;
        }
        if(rect_character3.x<=200)
            lado=true;
        if(lado==false)
        {
            rect_character3.x-=velocity;
            orientation3='l';
        }



        if(currentKeyStates[ SDL_SCANCODE_D ])
        {
            rect_character.x+=velocity;
            orientation='r';
        }
        if(currentKeyStates[ SDL_SCANCODE_A ])
        {
            rect_character.x-=velocity;
            orientation='l';
        }
        if(currentKeyStates[ SDL_SCANCODE_S ])
        {
            rect_character.y+=velocity;
            orientation='d';
        }
        if(currentKeyStates[ SDL_SCANCODE_W ])
        {
            rect_character.y-=velocity;
            orientation='u';
        }
        if(currentKeyStates[ SDL_SCANCODE_RIGHT ])
        {
            rect_character2.x+=velocity;
            orientation2='r';
        }
        if(currentKeyStates[ SDL_SCANCODE_LEFT ])
        {
            rect_character2.x-=velocity;
            orientation2='l';
        }
        if(currentKeyStates[ SDL_SCANCODE_DOWN ])
        {
            rect_character2.y+=velocity;
            orientation2='d';
        }
        if(currentKeyStates[ SDL_SCANCODE_UP ])
        {
            rect_character2.y-=velocity;
            orientation2='u';
        }
        if(currentKeyStates[ SDL_SCANCODE_LSHIFT ])
        {
            velocity=6;
            animation_velocity=10;
        }else
        {
            velocity=3;
            animation_velocity=20;
        }

        if(frame%animation_velocity==0)
        {
            current_sprite++;
            current_sprite2++;
            current_sprite3++;
            if(current_sprite>1)
                current_sprite=0;
            if(current_sprite2>1)
                current_sprite2=0;
            if(current_sprite3=0)
                current_sprite3=0;
        }

        SDL_Delay(17);

        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        SDL_RenderCopy(renderer, sprites[orientation][current_sprite], NULL, &rect_character);
        SDL_RenderCopy(renderer, sprites2[orientation2][current_sprite2], NULL, &rect_character2);
        SDL_RenderCopy(renderer, sprites3[orientation3][current_sprite3], NULL, &rect_character3);
        SDL_RenderPresent(renderer);
        frame++;
    }

	return 0;
}
