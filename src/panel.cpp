#include <GL/gl.h>
#include <panel.h>

Panel::Panel()
{
}

Panel::~Panel()
{
}

bool Panel::Init( std::string location, int percentage )
{
    bool result = true;

    location = location;
    percentage = percentage;

    return result;
}

void Panel::Resize( int width, int height )
{
    width = width;
    height = height;
}

void Panel::Render()
{
    glPushMatrix();
    glLoadIdentity();
    glTranslatef( 0.15, 0.35, 0.0 );
    glColor3f( 1.0, 0.5, 0.0 );
    glBegin( GL_QUADS );
        glVertex2f( 0.0, 0.0 );
        glVertex2f( 0.1, 0.0 );
        glVertex2f( 0.1,  0.1 );
        glVertex2f( 0.0,  0.1 );
    glEnd();
    glPopMatrix();
}


