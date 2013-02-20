#include <stdio.h>
#include <GL/gl.h>

#include <background.h>

bool Background::_ready = false;
bool Background::_enable = false;

Background::Background()
{
//DEBUG
    puts("Background::Background()");
//END

    _wireframe = false;
}

Background::~Background()
{
//DEBUG
    puts("Background::~Background()");
//END
    delete _generator;
}

bool Background::Init( Volume* viewport )
{
    bool result = true;

    //DEBUG
    _zoom_level = 1.0;

    _zValue = -0.9;
    _viewport = viewport;

    _config = Config::GetInstance();

    _size_0 = _config->background_tile_size;
    _size = _size_0;
    _height = 0.866 * _size;
    _halfSide = 0.5 * _size;
    _brightness = 0.2;
    _colorMethod = FILLMETHOD_CORNER;
    
    _red_offset = _config->background_red_offset;
    _green_offset = _config->background_green_offset;
    _blue_offset = _config->background_blue_offset;

    _generator = new Generator();
// TODO : magic number
    _generator->SetOctaves( 4 );

    return result;
}

void Background::ToggleWireframe()
{
    if( _wireframe ) {
        _wireframe = false;
    } else {
        _wireframe = true;
    }
}

//DEBUG
void Background::SetZoomLevel( double zoom )
{
    _zoom_level = zoom;
    _size = _size_0 * _zoom_level;
    _height = 0.866 * _size;
    _halfSide = 0.5 * _size;
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

    x_begin = _viewport->left;
    x_end = _viewport->right;
    y_end = _viewport->top;
    y_begin = _viewport->bottom;

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
        glVertex3d( x, y, _zValue );
        glVertex3d( x+ _halfSide, y+ _height, _zValue );
        glVertex3d( x+ _size, y, _zValue );
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
        glVertex3d( x, y, _zValue );
        if ( _colorMethod == FILLMETHOD_CORNER )
        {
            VertexColor( x+_halfSide, y+_height );
        }
        glVertex3d( x+ _halfSide, y+ _height, _zValue );
        if ( _colorMethod == FILLMETHOD_CORNER )
        {
            VertexColor( x+_size, y );
        }
        glVertex3d( x+ _size, y, _zValue );
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
        glVertex3d( x, y, _zValue );
        glVertex3d( x+ _size, y, _zValue );
        glVertex3d( x+ _halfSide, y-_height, _zValue );
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
        glVertex3d( x, y, _zValue );
        if ( _colorMethod == FILLMETHOD_CORNER )
        {
            VertexColor( x+_size, y );
        }
        glVertex3d( x+ _size, y, _zValue );
        if ( _colorMethod == FILLMETHOD_CORNER )
        {
            VertexColor( x+_halfSide, y-_height );
        }
        glVertex3d( x+ _halfSide, y-_height, _zValue );
        glEnd();
    }

    _vertexCount += 3;
}
