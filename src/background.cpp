#include <stdio.h>
#include <GL/gl.h>
#include <background.h>

bool Background::_ready = false;
bool Background::_enable = false;

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
	RenderTest();
	//RenderBackground();
}

void Background::RenderBackground()
{
	// TODO : Background display implementation.
}

void Background::RenderTest()
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

