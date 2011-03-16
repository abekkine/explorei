#include <GL/gl.h>
#include <version.h>
#include <panel.h>

Panel::Panel()
{
	Defaults();
}

Panel::~Panel()
{
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

	DisplayVersion();

    return result;
}

void Panel::Resize( int width, int height )
{
	_panel_left = _margin;
	_panel_right = width - _margin;
	_panel_bottom = height - _margin;
	_panel_top = height * ( 100 - _panel_percent ) / 100.0;

	_versionMsg.x = _panel_left + 4;
	_versionMsg.y = _panel_top + 16;
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
        glVertex3d( _panel_left, _panel_top, 0.8 );
        glVertex3d( _panel_right, _panel_top, 0.8 );
        glVertex3d( _panel_right, _panel_bottom, 0.8 );
        glVertex3d( _panel_left, _panel_bottom, 0.8 );
    glEnd();

    // Frame
    glColor4f( 1.0f, 1.0f, 1.0f, 0.5f );
    glBegin( GL_LINE_LOOP );
        glVertex3d( _panel_left, _panel_top, 0.85 );
        glVertex3d( _panel_right, _panel_top, 0.85 );
        glVertex3d( _panel_right, _panel_bottom, 0.85 );
        glVertex3d( _panel_left, _panel_bottom, 0.85 );
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

void Panel::DisplayVersion()
{
	_versionMsg.x = 0;
	_versionMsg.y = 0;
	_versionMsg.text = std::string( VERSION_STRING );

	_writer->AddDynamic( &_versionMsg );
}

