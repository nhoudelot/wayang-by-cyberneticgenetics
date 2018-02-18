#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_mixer.h>
#include <unistd.h>

#include "wayang.h"

int main(){
SDL_Event event;
Uint32 start, time;
Mix_Music *music;

/* Initializations */
SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
SDL_SetVideoMode( 1024, 768, 32, SDL_OPENGL |
                                SDL_GL_DOUBLEBUFFER |
                                SDL_HWPALETTE |
                                SDL_RESIZABLE);
SDL_ShowCursor(SDL_DISABLE);
/* OpenGL related settings */
glClearColor(0.0,0.0,0.0,0.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
/* Extremly big space because the meses are big */
glOrtho(-2000.0, 2000.0, -1500.0, 1500.0, -800.0, 800.0);
glEnable(GL_TEXTURE_2D);
glEnable(GL_DEPTH_TEST);
glPixelStorei(GL_UNPACK_ALIGNMENT,1);
glEnableClientState(GL_COLOR_ARRAY);
glEnableClientState(GL_VERTEX_ARRAY);
glEnable(GL_BLEND);
/* Demo related initialization */
init_wayang();
/* Music initialization */
Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
music = Mix_LoadMUS("/usr/share/wayang-by-cyberneticgenetics/data/wayang.ogg");
Mix_PlayMusic(music, 0);
start = SDL_GetTicks();

/* Event handling */
while(Mix_PlayingMusic()){
   while( SDL_PollEvent( &event) ){
      switch(event.type){
         case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) Mix_HaltMusic();
      }
   }
   /* Drawing */
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   time = SDL_GetTicks();
   show_wayang(time - start);
   SDL_GL_SwapBuffers();
}

/* Exit from demo */
SDL_ShowCursor(SDL_ENABLE);
free_wayang();
Mix_FreeMusic(music);
Mix_CloseAudio();
SDL_Quit();
return(0);
}
