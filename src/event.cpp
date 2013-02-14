#include <event.h>

bool Event::_ready = false;
bool Event::_enable = false;

Event::Event()
{
//DEBUG
    puts("Event::Event()");
//END
    Defaults();
}

Event::~Event()
{
//DEBUG
    puts("Event::~Event()");
//END
}

void Event::Defaults()
{
    _mouse_x = DEFAULT_INT;
    _mouse_y = DEFAULT_INT;

    _pan_mode = false;
    _zoom_mode = false;
    _pan_start_x = DEFAULT_INT;
    _pan_start_y = DEFAULT_INT;
    _zoom_start_pos = DEFAULT_INT;
    _mouse_delta_x = DEFAULT_INT;
    _mouse_delta_y = DEFAULT_INT;
}

bool Event::Init()
{
    bool result = true;

    return result;
}

bool Event::Update()
{
    bool result = true;
    
    Poll();

    CommandProcess();

    return result;
}

void Event::PanMode( bool value )
{
    _pan_mode = value;
}

void Event::PanUpdate()
{
    if( _pan_mode )
    {
        _mouse_delta_x = _mouse_x - _pan_start_x;
        _mouse_delta_y = _mouse_y - _pan_start_y;

        PushCommand( PAN_COMMAND );

        _pan_start_x = _mouse_x;
        _pan_start_y = _mouse_y;
    }
}

void Event::ZoomMode( bool value )
{
    _zoom_mode = value;
}

void Event::ZoomUpdate()
{
    if( _zoom_mode )
    {
        _mouse_delta_x = 0;
        _mouse_delta_y = _mouse_y - _zoom_start_pos;

        PushCommand( ZOOM_COMMAND );

        _zoom_start_pos = _mouse_y;
    }
}

void Event::CommandProcess()
{
    int event_code = PopEvent();
   
    switch( event_code )
    {
        case RIGHTBUTTON_PRESSED_EVENT:
            PanMode( true );
            _pan_start_x = _mouse_x;
            _pan_start_y = _mouse_y;
            break;

        case RIGHTBUTTON_RELEASED_EVENT:
            PanMode( false );
            break;

        case MIDBUTTON_PRESSED_EVENT:
            ZoomMode( true );
            _zoom_start_pos = _mouse_y;
            break;

        case MIDBUTTON_RELEASED_EVENT:
            ZoomMode( false );
            break;
    }
}

void Event::KeyEvent( SDL_KeyboardEvent& key )
{
	switch( key.keysym.sym )
	{
		case SDLK_b:
			PushCommand( TOGGLE_BACKGROUND_CMD );
            break;
			
		case SDLK_p:
			PushCommand( TOGGLE_PANEL_CMD );
            break;
			
		case SDLK_q:
		case SDLK_ESCAPE:
			PushCommand( QUIT_COMMAND );
            break;
		
		default:
			break;
	}
}

void Event::PushEvent( int code )
{
	_event_queue.push( code );
}

int Event::PopEvent()
{
    int code = NO_EVENT;
	if( !_event_queue.empty() )
	{
		code = _event_queue.front();
		_event_queue.pop();
	}

    return code;
}

void Event::PushCommand( int code ) 
{
	if( code != NO_COMMAND )
	{
		_command_queue.push( code );
	}
}

void Event::MotionEvent( SDL_MouseMotionEvent& motion )
{
	_mouse_x = motion.x;
	_mouse_y = motion.y;

    PanUpdate();
    ZoomUpdate();
}

void Event::ButtonEvent( SDL_MouseButtonEvent& button )
{
	_mouse_x = button.x;
	_mouse_y = button.y;
	
	switch( button.button )
	{
		case SDL_BUTTON_LEFT:
            ProcessLeftButton(button);
			break;
			
		case SDL_BUTTON_RIGHT:
            ProcessRightButton(button);
			break;
			
		case SDL_BUTTON_MIDDLE:
            ProcessMiddleButton(button);
			break;
			
		default:
			break;
	}
}

void Event::ProcessLeftButton( SDL_MouseButtonEvent& button )
{
    static int prevState = UNDEFINED;
    int pressed = UNDEFINED;
    
    switch( button.state ) {
        case SDL_PRESSED:
            pressed = TRUE;
            if( pressed != prevState ) {
                PushEvent( LEFTBUTTON_PRESSED_EVENT );
            }
            prevState = pressed;
            break;

        case SDL_RELEASED:
            pressed = FALSE;
            if( pressed != prevState ) {
                PushEvent( LEFTBUTTON_RELEASED_EVENT );
            }
            prevState = pressed;
            break;
    }
}

void Event::ProcessRightButton( SDL_MouseButtonEvent& button )
{
    static int prevState = UNDEFINED;
    int pressed = UNDEFINED;

    switch( button.state ) {
        case SDL_PRESSED:
            pressed = TRUE;
            if( pressed != prevState ) {
                PushEvent( RIGHTBUTTON_PRESSED_EVENT );
            }
            prevState = pressed;
            break;

        case SDL_RELEASED:
            pressed = FALSE;
            if( pressed != prevState ) {
                PushEvent( RIGHTBUTTON_RELEASED_EVENT );
            }
            prevState = pressed;
            break;
    }
}

void Event::ProcessMiddleButton( SDL_MouseButtonEvent& button )
{
    static int prevState = UNDEFINED;
    int pressed = UNDEFINED;

    switch( button.state ) {
        case SDL_PRESSED:
            pressed = TRUE;
            if( pressed != prevState ) {
                PushEvent( MIDBUTTON_PRESSED_EVENT );
            }
            prevState = pressed;
            break;

        case SDL_RELEASED:
            pressed = FALSE;
            if( pressed != prevState ) {
                PushEvent( MIDBUTTON_RELEASED_EVENT );
            }
            prevState = pressed;
            break;
    }
}

void Event::Poll()
{
	SDL_Event event;
	
    while( SDL_PollEvent(&event) )
    {
        switch( event.type )
        {
            case SDL_KEYDOWN:
				KeyEvent( event.key );
                break;

            case SDL_MOUSEMOTION:
				MotionEvent( event.motion );
                break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
				ButtonEvent( event.button );
                break;

            case SDL_QUIT:
                PushCommand( QUIT_COMMAND );
                break;
        }
    }
}

int Event::CheckEventCode()
{
    int result = NO_EVENT;

    if( !_event_queue.empty() )
    {
        result = _event_queue.front();
    }

    return result;
}

int Event::GetCommandCode()
{
	int command_code = NO_COMMAND;

	if( !_command_queue.empty() )
	{
	    command_code = _command_queue.front();
		_command_queue.pop();
	}

	return command_code;
}

void Event::GetMouseDelta( int* dx, int* dy )
{
    if( dx != NULL )
    {
        *dx = _mouse_delta_x;
    }

    if( dy != NULL )
    {
        *dy = _mouse_delta_y;
    }
}

void Event::GetMousePosition( int& mouse_x, int& mouse_y )
{
	mouse_x = _mouse_x;
	mouse_y = _mouse_y;
}
