#include <stdio.h>

#include <GL/gl.h>
#include <parameter.h>

bool Parameter::_ready = false;
bool Parameter::_enable = false;

Parameter::Parameter()
{
//DEBUG
    puts("Parameter::Parameter()");
//END
}

Parameter::~Parameter()
{
//DEBUG
    puts("Parameter::~Parameter()");
//END
}

bool Parameter::Init()
{
    bool result = true;

    return result;

}

void Parameter::Render()
{
	RenderTest();
	//RenderParam();
}

void Parameter::RenderParam()
{
}

void Parameter::RenderTest()
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

