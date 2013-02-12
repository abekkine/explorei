#include <stdio.h>

#include <GL/gl.h>
#include <stars.h>

bool Stars::_ready = false;
bool Stars::_enable = false;

Stars::Stars()
{
//DEBUG
    puts("Stars::Stars()");
//END
}

Stars::~Stars()
{
//DEBUG
    puts("Stars::~Stars()");
//END
}

bool Stars::Init()
{
    bool result = true;

    return result;
}

void Stars::Render()
{
	RenderTest();
	//RenderStars();
}

void Stars::RenderStars()
{
	// TODO : Stars display implementation.
}

void Stars::RenderTest()
{
    // render a yellow square as stars.
    glPushMatrix();
    glLoadIdentity();
    glTranslatef( -0.25, 0.35, 0.0 );
    glColor3f( 1.0, 1.0, 0.0 );
    glBegin( GL_QUADS );
        glVertex2f( 0.0, 0.0 );
        glVertex2f( 0.1, 0.0 );
        glVertex2f( 0.1,  0.1 );
        glVertex2f( 0.0,  0.1 );
    glEnd();
    glPopMatrix();
}

