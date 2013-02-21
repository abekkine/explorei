#include <GL/gl.h>
#include <version.h>
#include <panel.h>

bool Panel::_ready = false;
bool Panel::_enable = false;

Panel::Panel()
{
//DEBUG
    puts("Panel::Panel()");
//END
    Defaults();
}

Panel::~Panel()
{
//DEBUG
    puts("Panel::~Panel()");
//END
}

void Panel::Defaults()
{
    // Impossible values.
    _panel_left = -999;
    _panel_right = -999;
    _panel_bottom = -999;
    _panel_top = -999;

    _margin = 10;
    _panel_percent = 20;
}

bool Panel::Init( std::string location, int percentage )
{
    bool result = true;

    location = location;
    percentage = percentage;

    _writer = Writer::GetInstance();
    _writer->Add( VERSION_STRING, 4, 16, &Panel::_enable );

    return result;
}

void Panel::Resize( int width, int height )
{
    _panel_left = _margin;
    _panel_right = width - _margin;
    _panel_bottom = height - _margin;
    _panel_top = height * ( 100 - _panel_percent ) / 100.0;

    _writer->UpdateOrigin( _panel_left, _panel_top );
}

void Panel::Render()
{
#ifdef DISPLAY_DEBUG
    RenderTest();
#else
    RenderPanel();
#endif
}

void Panel::RenderPanel()
{
    // Background
    glColor4f( 0.0f, 0.0f, 0.5f, 0.5f );
    glBegin( GL_QUADS );
        glVertex2d( _panel_left, _panel_top );
        glVertex2d( _panel_right, _panel_top );
        glVertex2d( _panel_right, _panel_bottom );
        glVertex2d( _panel_left, _panel_bottom );
    glEnd();

    // Frame
    glColor4f( 1.0f, 1.0f, 1.0f, 0.5f );
    glBegin( GL_LINE_LOOP );
        glVertex2d( _panel_left, _panel_top );
        glVertex2d( _panel_right, _panel_top );
        glVertex2d( _panel_right, _panel_bottom );
        glVertex2d( _panel_left, _panel_bottom );
    glEnd();
}

void Panel::RenderTest()
{
    glPushMatrix();
    glLoadIdentity();
    glTranslatef( 0.15, 0.35, 0.0 );
    glColor3f( 1.0, 0.5, 0.0 );
    glBegin( GL_QUADS );
        glVertex2f( 0.0, 0.0 );
        glVertex2f( 0.1, 0.0 );
        glVertex2f( 0.1, 0.1 );
        glVertex2f( 0.0, 0.1 );
    glEnd();
    glPopMatrix();
}

