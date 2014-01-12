#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <cmath>

const int SCREEN_WIDTH = 640; const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

const int FPS = 60;

float x = 2.0, y = 3.0, z = 4.0;
float yaw = 60.0, pitch = -150.0, roll = 0.0;

bool running = true;
SDL_Event event;

void check_input()
{
    while( SDL_PollEvent( &event ) )
    {
        if( event.type == SDL_QUIT )
        {
            running = false;
        }
    }



    Uint8* keyboard_state = SDL_GetKeyState(NULL);
    float speed = 0.1;

    if(keyboard_state[SDLK_w])
    {
        x+=speed * cos(pitch * 3.14 / 180.0)*cos(yaw * 3.14 / 180.0);
        y+=speed * sin(pitch * 3.14 / 180.0);
        z+=speed * cos(pitch * 3.14 / 180.0)*sin(yaw * 3.14 / 180.0);
    }
    if(keyboard_state[SDLK_s])
    {
        x-=speed * cos(pitch * 3.14 / 180.0)*cos(yaw * 3.14 / 180.0);
        y-=speed * sin(pitch * 3.14 / 180.0);
        z-=speed * cos(pitch * 3.14 / 180.0)*sin(yaw * 3.14 / 180.0);
    }
    if(keyboard_state[SDLK_LEFT])
    {
        yaw -= 1.0;
    }
    if(keyboard_state[SDLK_RIGHT])
    {
        yaw += 1.0;
    }
    if(keyboard_state[SDLK_UP])
    {
        pitch -= 1.0;
    }
    if(keyboard_state[SDLK_DOWN])
    {
        pitch += 1.0;
    }
}

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL);

    SDL_WM_SetCaption("OpenGL Test", NULL);

    glEnable(GL_DEPTH_TEST);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        printf("Error");
    }

    while (running)
    {
        check_input();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (double)SCREEN_WIDTH/(double)SCREEN_HEIGHT, 0.1f,100.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(x, y, z, x + 5 * cos(pitch * 3.14 / 180.0)*cos(yaw * 3.14 / 180.0), y + 5 * sin(pitch * 3.14 / 180.0), z + 5 * cos(pitch * 3.14 / 180.0)*sin(yaw * 3.14 / 180.0), 0.0f, 1.0f, 0.0f);
        glBegin(GL_LINES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 1.0f);
        glEnd();
        printf("%f:%f\n", yaw, pitch);

        SDL_GL_SwapBuffers();
    }

    SDL_Quit();

    return 0;
}

