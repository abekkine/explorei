#include <version.h>
#include <display.h>

Display::Display()
{
//DEBUG
    puts("Display::Display()");
//END
    Defaults();
}

Display::~Display()
{
//DEBUG
    puts("Display::~Display()");
//END
    delete _writer;
    delete _panel;
    delete _event;
    delete _background;
}

void Display::Defaults()
{
    // Get config instance.
    _config = Config::GetInstance();

    // Screen defaults.
    _screen = NULL;
    _screen_width = _config->display_screen_width;
    _screen_height = _config->display_screen_height;

    // Background color from config.
    _background_red = _config->display_background_red;
    _background_green = _config->display_background_green;
    _background_blue = _config->display_background_blue;
    _background_alpha = 1.0;

    // Viewport-world from config.
    _world_width = _config->display_world_width;
    _world_height = _config->display_world_height;

    // Screen center.
    _center_x = 0.0;
    _center_y = 0.0;

    // Zoom defaults.
    _zoom_level = 1.0;

    // Component defaults.
    _writer = NULL;
    _panel = NULL;
    _event = NULL;
    _background = NULL;

    _viewport.left = -0.5;
    _viewport.right = 0.5;
    _viewport.bottom = -0.5;
    _viewport.top = 0.5;
    _viewport.near = 0.0;
    _viewport.far = 1.0;

    _scale_x = 1.0;
    _scale_y = 1.0;

	_quit_condition_check = false;
}

bool Display::Init()
{
    bool result = false;
    int rc;

    InitComponents();

    rc = SDL_Init( SDL_INIT_VIDEO );
    if( rc < 0 )
    {
        fprintf( stderr, "Unable to init SDL : %s\n", SDL_GetError() );
    }
    else
    {
        atexit( SDL_Quit );

        _screen = SDL_SetVideoMode( _screen_width, _screen_height, 32, SDL_OPENGL );
        if( _screen == NULL )
        {
            fprintf( stderr, "Unable to set video mode %dx%d : %s\n", _screen_width, _screen_height, SDL_GetError() );
        }
        else
        {
            InitGL();

            Reshape( _screen->w, _screen->h );

            result = true;
        }
    }

    return result;
}

void Display::InitComponents()
{
	_writer = Writer::GetInstance();
    Writer::_ready = _writer->Init();
    Writer::_enable = true;
    
    _panel = new Panel();
    // Location and percentage of panel.
    Panel::_ready = _panel->Init( "bottom", 20 );
    Panel::_enable = true;

    _event = new Event();
    Event::_ready = _event->Init();
    Event::_enable = true;

    _background = new Background();
    Background::_ready = _background->Init( &_viewport );
    Background::_enable = true;
}

void Display::InitGL()
{
    glShadeModel( GL_SMOOTH );
    glClearColor( _background_red, _background_green, _background_blue, _background_alpha );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );

    // Enable blending and alpha channel.
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    // Enable depth buffer.
    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );
    glDepthMask( GL_TRUE );
}

void Display::Reshape()
{
    Reshape( _screen_width, _screen_height );
}

void Display::Reshape( int width, int height )
{
    if( height == 0 )
    {
        height = 1;
    }

    glViewport( 0, 0, width, height );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    UpdateViewport();

    glOrtho( _viewport.left, _viewport.right, _viewport.bottom, _viewport.top, _viewport.near, _viewport.far );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

	if( Panel::_ready && Panel::_enable )
	{
		    _panel->Resize( width, height );
	}
}

void Display::UpdateViewport()
{
    // TODO : Magic number '0.5' should be replaced with something sensible.
    double zoomed_width;
    double zoomed_height;
   
    _zoom_level += _zoom_delta * 0.002;

    zoomed_width = 0.5 * _world_width * _zoom_level;
    zoomed_height = 0.5 * _world_height * _zoom_level;

    UpdateScale();
    _center_x -= _scale_x * _pan_x_delta;
    _center_y -= _scale_y * _pan_y_delta;

    _viewport.left   = _center_x - zoomed_width;
    _viewport.right  = _center_x + zoomed_width;
    _viewport.top    = _center_y + zoomed_height;
    _viewport.bottom = _center_y - zoomed_height;
}

void Display::UpdateScale()
{
    _scale_x = (_viewport.right - _viewport.left) / (_world_width * _screen_width);
    _scale_y = (_viewport.bottom - _viewport.top) / (_world_height * _screen_height);
}

void Display::PreRender()
{
    // Clear screen.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Display::PostRender()
{
    // Swap buffers.
    SDL_GL_SwapBuffers();
}

void Display::Render()
{
    if( Background::_ready && Background::_enable )
    {
        _background->Render();
    }

    if( Panel::_ready && Panel::_enable )
    {
		OrthoBegin();
        _panel->Render();
		OrthoEnd();
    }

    if( Writer::_ready && Writer::_enable )
    {
		OrthoBegin();
		_writer->Render();
		OrthoEnd();
	}
}

void Display::Update()
{
    PreRender();
    Render();
    PostRender();

    if( Event::_ready && Event::_enable )
    {
        _event->Update();
        
        ProcessEvents();
        ProcessCommands();
    }
}

void Display::ResetCommandParam()
{
    _zoom_delta = 0;
    _pan_x_delta = 0;
    _pan_y_delta = 0;
}   

void Display::ProcessCommands()
{
	int commandCode = _event->GetCommandCode();

    ResetCommandParam();

	switch( commandCode )
	{
		case Event::TOGGLE_BACKGROUND_CMD:
			ToggleBackground();
            break;

		case Event::TOGGLE_PANEL_CMD:
			TogglePanel();
            break;

        case Event::ZOOM_COMMAND:
            _event->GetMouseDelta( NULL, &_zoom_delta );
            Reshape();
            break;

        case Event::PAN_COMMAND:
            _event->GetMouseDelta( &_pan_x_delta, &_pan_y_delta );
            Reshape();
            break;

        case Event::QUIT_COMMAND:
            _quit_condition_check = true;
            break;

		case Event::NO_COMMAND:
		default:
			break;
	}
}

void Display::ProcessEvents()
{
	int eventCode = _event->CheckEventCode();
	
	switch( eventCode )
	{
		case Event::KEY_EVENT:
		case Event::MOTION_EVENT:
		case Event::BUTTON_EVENT:
            // Do nothing for now.
            break;
		
		case Event::QUIT_EVENT:
			_quit_condition_check = true;
			break;
		
		case Event::NO_EVENT:
		default:
			break;
    }
}

bool Display::CheckQuitCondition()
{
	return _quit_condition_check;
}

void Display::OrthoBegin()
{
    glDisable( GL_DEPTH_TEST );

    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    glOrtho( 0, _screen_width, _screen_height, 0, -1.0, 1.0 );
    glMatrixMode( GL_MODELVIEW );
}

void Display::OrthoEnd()
{
    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );

    glEnable( GL_DEPTH_TEST );
}

void Display::CheckError()
{
    GLenum errorCode = glGetError();

    switch( errorCode )
    {
        case GL_NO_ERROR:
            break;

        case GL_INVALID_ENUM:
            puts( "GL Invalid Enum" );
            break;

        case GL_INVALID_VALUE:
            puts( "GL Invalid Value" );
            break;

        case GL_INVALID_OPERATION:
            puts( "GL Invalid Operation" );
            break;

        case GL_STACK_OVERFLOW:
            puts( "GL Stack Overflow" );
            break;

        case GL_STACK_UNDERFLOW:
            puts( "GL Stack Underflow" );
            break;

        case GL_OUT_OF_MEMORY:
            puts( "GL Out of memory" );
            break;

        case GL_TABLE_TOO_LARGE:
            puts( "GL Table too large" );
            break;

        default:
            puts( "Unknown error" );
            break;
    }
}

void Display::ToggleBackground()
{
    //DEBUG
    puts( "ToggleBackground()" );

    Background::_enable ^= 1;
}

void Display::TogglePanel()
{
    //DEBUG
    puts( "TogglePanel()" );

    Panel::_enable ^= 1;
}
