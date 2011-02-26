#include <GL/gl.h>
#include <parameter.h>

Parameter::Parameter()
{
}

Parameter::~Parameter()
{
}

bool Parameter::Init()
{
    bool result = true;

    return result;

}

void Parameter::Render()
{
    glPushMatrix();
    glLoadIdentity();
    glTranslatef( 0.35, 0.35, 0.0 );
    glColor3f( 1.0, 0.5, 1.0 );
    glBegin( GL_QUADS );
        glVertex2f( 0.0, 0.0 );
        glVertex2f( 0.1, 0.0 );
        glVertex2f( 0.1,  0.1 );
        glVertex2f( 0.0,  0.1 );
    glEnd();
    glPopMatrix();
}

