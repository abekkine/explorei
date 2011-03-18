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

bool Background::Init( Volume* viewport )
{
    bool result = true;

	_viewport = viewport;

	_config = Config::GetInstance();

	_size = _config->background_tile_size;
	_height = 0.866 * _size;
	_halfSide = 0.5 * _size;
	_brightness = 0.2;
	_colorMethod = FILLMETHOD_CORNER;
	
	_red_offset = _config->background_red_offset;
	_green_offset = _config->background_green_offset;
	_blue_offset = _config->background_blue_offset;

	_generator = new Generator();
	_generator->SetOctaves( 4 );

    return result;
}

void Background::Render()
{
	//RenderTest();
	RenderBackground();
}

void Background::RenderBackground()
{
	double x_begin, x_end;
	double y_begin, y_end;
	double x_begin_validated;
	double y_begin_validated;
	float x_step, y_step;

	GetViewport( &x_begin, &x_end, &y_end, &y_begin );

	x_begin_validated = floor( x_begin );
	y_begin_validated = 2.0 * floor( 0.5 * y_begin / _height ) * _height; 

	if( Background::_enable )
	{
		for( x_step = x_begin_validated; x_step < x_end; x_step += _size )
		{
			for( y_step = y_begin_validated; y_step < y_end; y_step += 2.0*_height )
			{
				Mesh( x_step, y_step );
			}
		}
	}
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

void Background::VertexColor( float x, float y )
{
    glColor3f( _brightness * _generator->GetValue( x, y, _red_offset ),
               _brightness * _generator->GetValue( x, y, _green_offset ),
               _brightness * _generator->GetValue( x, y, _blue_offset ) );
}

void Background::Mesh( float x, float y )
{
    Triangle( x, y );
    Triangle( x+_halfSide, y+_height );
    ReverseTriangle( x, y + _height*2.0 );
    ReverseTriangle( x+_halfSide, y+ _height );
}

void Background::Triangle( float x, float y )
{
    if ( _wireframe )
    {
        glColor3f( 0.15, 0.15, 0.15 );
        glBegin( GL_LINE_LOOP );
        glVertex3d( x, y, 0.0 );
        glVertex3d( x+ _halfSide, y+ _height, 0.0 );
        glVertex3d( x+ _size, y, 0.0 );
        glEnd();
    }
    else
    {

        if ( _colorMethod == FILLMETHOD_CENTER )
        {
            VertexColor( x + _halfSide, y + _height/3.0 );
        }

        glBegin( GL_TRIANGLES );
        if ( _colorMethod == FILLMETHOD_CORNER )
        {
            VertexColor( x, y );
        }
        glVertex3d( x, y, 0.0 );
        if ( _colorMethod == FILLMETHOD_CORNER )
        {
            VertexColor( x+_halfSide, y+_height );
        }
        glVertex3d( x+ _halfSide, y+ _height, 0.0 );
        if ( _colorMethod == FILLMETHOD_CORNER )
        {
            VertexColor( x+_size, y );
        }
        glVertex3d( x+ _size, y, 0.0 );
        glEnd();

    }

    _vertexCount += 3;
}

void Background::ReverseTriangle( float x, float y )
{
    if ( _wireframe )
    {
        glColor3f( 0.15, 0.15, 0.15 );
        glBegin( GL_LINE_LOOP );
        glVertex3d( x, y, 0.0 );
        glVertex3d( x+ _size, y, 0.0 );
        glVertex3d( x+ _halfSide, y-_height, 0.0 );
        glEnd();
    }
    else
    {

        if ( _colorMethod == FILLMETHOD_CENTER )
        {
            VertexColor( x + _halfSide, y - _height/3.0 );
        }

        glBegin( GL_TRIANGLES );
        if ( _colorMethod == FILLMETHOD_CORNER )
        {
            VertexColor( x, y );
        }
        glVertex3d( x, y, 0.0 );
        if ( _colorMethod == FILLMETHOD_CORNER )
        {
            VertexColor( x+_size, y );
        }
        glVertex3d( x+ _size, y, 0.0 );
        if ( _colorMethod == FILLMETHOD_CORNER )
        {
            VertexColor( x+_halfSide, y-_height );
        }
        glVertex3d( x+ _halfSide, y-_height, 0.0 );
        glEnd();
    }

    _vertexCount += 3;
}

void Background::GetViewport( double* left, double* right, double* top, double* bottom )
{
	*left = _viewport->left;
	*right = _viewport->right;
	*top = _viewport->top;
	*bottom = _viewport->bottom;
}
