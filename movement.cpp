#include <GL/gl.h>
#include <GL/glu.h>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <iostream>
#include <cmath>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"SDL.lib")
#pragma comment(lib,"SDLmain.lib")

const int screen_size[2] = {800,600};
float x = 0, y = 0, z = 0;
float angleX = 0, angleY = 0;

bool get_input(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: return false; //The little X in the window got pressed
            case SDL_KEYDOWN:
                if (event.key.keysym.sym==SDLK_ESCAPE) {
                    return false;
                }
                break;
        }
    }

    SDL_PumpEvents();
    Uint8 *keyboard_state = SDL_GetKeyState(NULL);
    if(keyboard_state[SDLK_UP])
        angleX--;
    if(keyboard_state[SDLK_DOWN])
        angleX++; if(keyboard_state[SDLK_LEFT]) angleY--;
    if(keyboard_state[SDLK_RIGHT])
        angleY++;

    if(keyboard_state[SDLK_w])
    {
        x-=.1*sin(angleY/180*M_PI);
        y+=.1*sin(angleX/180*M_PI);
        z+=.1*cos(angleY/180*M_PI);
    }
    if(keyboard_state[SDLK_s])
    {
        x+=.1*sin(angleY/180*M_PI);
        y-=.1*sin(angleX/180*M_PI);
        z-=.1*cos(angleY/180*M_PI);
    }
    if(keyboard_state[SDLK_a])
    {
        x-=.1*sin(angleX/180*M_PI);
        y-=.1*cos(angleY/180*M_PI);
    }
    if(keyboard_state[SDLK_d])
    {
        x+=.1*sin(angleX/180*M_PI);
        y+=.1*cos(angleY/180*M_PI);
    }
    if(keyboard_state[SDLK_q])
    {
        z+=.1;
    }
    if(keyboard_state[SDLK_e])
    {
        z-=.1;
    }

    return true;
}

void draw(void) {
    //Clear the screen's color and depth (default color is black, but can change with glClearColor(...))
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //Drawing to an area starting at the bottom left, screen_size[0] wide, and screen_size[1] high.
    glViewport(0,0,screen_size[0],screen_size[1]);
    //OpenGL is a state machine.  Tell it that future commands changing the matrix are to change OpenGL's projection matrix
    glMatrixMode(GL_PROJECTION);
    //Reset the projection matrix
    glLoadIdentity();
    //Multiply a perspective projection matrix into OpenGL's projection matrix
    gluPerspective(45.0, (double)(screen_size[0])/(double)(screen_size[1]), 0.1f,100.0f);

    //Tell it that future commands changing the matrix are to change the modelview matrix
    glMatrixMode(GL_MODELVIEW);

    //Reset the modelview matrix
    glLoadIdentity();

    //glRotate (a, x, y, z);
    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);
    //glRotatef(angleZ, 0, 0, -1);
    glTranslatef(x,y,z);


    gluLookAt(0, 0, -1, 0, 0, 0, 0, 1, 0);

    //Begin drawing triangles.  Every subsequent triplet of vertices will be interpreted as a single triangle.
    //OpenGL's default color is white (1.0,1.0,1.0), so that's what color the triangle will be.
    glBegin(GL_TRIANGLES);
    //Three vertices follow, these will form a triangle
    glVertex3f( 0.0f, 0.1f, 0.0f); //Vertex at ( 0.0, 0.1, 0.0)
    glVertex3f(-0.1f,-0.1f, 0.7f); //Vertex at (-0.1,-0.1, 0.7)
    glVertex3f( 1.0f,-0.2f, 0.0f); //Vertex at ( 1.0,-0.2, 0.0)
    //Done drawing triangles
    glEnd();

    //Now we're going to draw some lines to show the cardinal axes.  Every subsequent pair of vertices
    //will be a single line.
    glBegin(GL_LINES);
    //All subsequent vertices will be red.
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f); glVertex3f(1.0f,0.0,0.0);
    //All subsequent vertices will be green.
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(0.0f,0.0f,0.0f); glVertex3f(0.0f,1.0,0.0);
    //All subsequent vertices will be blue.
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(0.0f,0.0f,0.0f); glVertex3f(0.0f,0.0,1.0);
    //Since OpenGL thinks the color is blue now, all subsequent vertices will be blue.  But, we want the
    //triangle above to be white the *next* time we call this function!  So, reset the color to white.
    glColor3f(1.0f,1.0f,1.0f);
    glEnd();

    //OpenGL works best double-buffered.  SDL automatically sets that up for us.  This will draw what we have
    //just drawn to the screen so that we can see it.
    SDL_GL_SwapBuffers();
}
int main(int argc, char* argv[]) {
    //Initialize everything, but don't catch fatal signals; give them to the OS.
    SDL_Init(SDL_INIT_EVERYTHING|SDL_INIT_NOPARACHUTE);

    //Creates the window
    SDL_SetVideoMode(screen_size[0],screen_size[1], 32, SDL_OPENGL);

    //We now have an OpenGL context, and can call OpenGL functions.

    //Objects need to test each other to see which one is in front.  If you don't do this, you'll "see through" things!
    glEnable(GL_DEPTH_TEST);

    //Main application loop
    while (true) {
        if (!get_input()) break;
        draw();
        std::cout << x << " " << y << " " << z << std::endl;
        std::cout << angleX << " " << angleY << std::endl;
    }

    //Normally you'd need to use SDL_FreeSurface, but the SDL_Surface* returned by
    //SDL_SetVideoMode is special, and so it is cleaned up for us.

    //Clean up
    SDL_Quit();

    //Return success; program exits
    return 0;
}
