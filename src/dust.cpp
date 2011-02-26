#include <GL/gl.h>
#include <dust.h>

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

