#include <GL/gl.h>
#include <dust.h>

bool Dust::_ready = false;
bool Dust::_enable = false;

Dust::Dust()
{
}

Dust::~Dust()
{
}

bool Dust::Init()
{
    bool result = true;

    return result;
}

void Dust::Render()
{
	RenderTest();
	//RenderDust();
}

void Dust::RenderDust()
{
}

void Dust::RenderTest()
{
    glPushMatrix();
    glLoadIdentity();
    glTranslatef( -0.05, 0.35, 0.0 );
    glColor3f( 0.4, 0.4, 0.4 );
    glBegin( GL_QUADS );
        glVertex2f( 0.0, 0.0 );
        glVertex2f( 0.1, 0.0 );
        glVertex2f( 0.1,  0.1 );
        glVertex2f( 0.0,  0.1 );
    glEnd();
    glPopMatrix();
}

