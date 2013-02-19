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
    delete _generator;
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

    _generator = new Generator();
// TODO : magic number
    _generator->SetOctaves( 4 );

    return result;
}

void Star::Render()
{
    //RenderTest();
    RenderStarLayer();
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

void Star::RenderSingleStar( double x, double y )
{
    glColor3f( 1.0, 1.0, 1.0 );
    glPointSize(2.0);
    glBegin( GL_POINTS );
        glVertex3d( x, y, _zValue );
    glEnd();
}

void Star::RenderStarLayer()
{
#ifdef TEST
    RenderSingleStar( 0.0, 0.0 );
#else
    double x_begin, x_end;
    double y_begin, y_end;
    double x_step, y_step;
    double s_value;
    double x_begin_rounded;
    double y_begin_rounded;

    x_begin = _viewport->left;
    y_begin = _viewport->bottom;

    x_begin_rounded = floor( x_begin );
    y_begin_rounded = floor( y_begin );

    x_end = _viewport->top;
    y_end = _viewport->right;

    for( x_step = x_begin_rounded; x_step < x_end; x_step += 0.05 ) {
        for( y_step = y_begin_rounded; y_step < y_end; y_step += 0.05 ) {
            s_value = _generator->GetValue( x_step, y_step, 1.2 );

            if( s_value > 0.0 ) {
                RenderSingleStar(x_step, y_step);
            }
        }
    }
#endif
}

