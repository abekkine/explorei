#include <stdio.h>

#include <GL/gl.h>
#include <star.h>

bool Star::_ready = false;
bool Star::_enable = false;

Star::Star()
{
//DEBUG
    puts("Star::Star()");
//END
    Defaults();
}

Star::~Star()
{
//DEBUG
    puts("Star::~Star()");
//END
}

void Star::Defaults()
{
    _ready = false;
    _enable = false;

    _zValue = 0.0;
}

bool Star::Init( Volume* viewport )
{
    bool result = true;
    
    _viewport = viewport;

    return result;
}

void Star::Render()
{
    //RenderTest();
    RenderStar();
}

void Star::RenderTest()
{
    glColor3f( 1.0f, 0.5f, 0.0f );
    glBegin( GL_QUADS );
        glVertex2d( 10, 10 );
        glVertex2d( 50, 10 );
        glVertex2d( 50, 50 );
        glVertex2d( 10, 50 );
    glEnd();

    glColor3f( 1.0f, 1.0f, 1.0f );
    glBegin( GL_LINE_LOOP );
        glVertex2d( 10, 10 );
        glVertex2d( 50, 10 );
        glVertex2d( 50, 50 );
        glVertex2d( 10, 50 );
    glEnd();
}

void Star::RenderStar()
{
    glColor3f( 1.0, 1.0, 1.0 );
    glPointSize(5.0);
    glBegin( GL_POINTS );
        glVertex3d( 0.0, 0.0, _zValue );
    glEnd();
}

