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
}

bool Star::Init( Volume* viewport )
{
    bool result = true;
    Volume* _viewport = viewport;

//DEBUG
    printf("_viewport->left(%f)\n", _viewport->left);
//END

    return result;
}

void Star::Render()
{
    //RenderTest();
    //RenderStar();
}

void Star::RenderTest()
{
    glPushMatrix();
    glLoadIdentity();
    glTranslatef( -0.25, 0.35, 0.0 );
    glColor3f( 1.0, 1.0, 0.0 );
    glBegin( GL_QUADS );
        glVertex2f( 0.0, 0.0 );
        glVertex2f( 0.1, 0.0 );
        glVertex2f( 0.1, 0.1 );
        glVertex2f( 0.0, 0.1 );
    glEnd();
    glPopMatrix();
}

void Star::RenderStar()
{
}

