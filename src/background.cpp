#include <stdio.h>
#include <GL/gl.h>
#include <background.h>

Background::Background()
{
}

Background::~Background()
{
}

bool Background::Init()
{
    bool result = true;

    return result;
}

void Background::Render()
{
    // render a blue square as background.
    glPushMatrix();
    glLoadIdentity();
    glTranslatef( -0.45, 0.35, 0.0 );
    glColor3f( 0.0, 0.0, 1.0 );
    glBegin( GL_QUADS );
        glVertex2f( 0.0, 0.0 );
        glVertex2f( 0.1, 0.0 );
        glVertex2f( 0.1,  0.1 );
        glVertex2f( 0.0,  0.1 );
    glEnd();
    glPopMatrix();
}

