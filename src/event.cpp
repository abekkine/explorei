#include <event.h>

bool Event::_ready = false;
bool Event::_enable = false;

Event::Event()
{
//DEBUG
    puts("Event::Event()");
//END
}

Event::~Event()
{
//DEBUG
    puts("Event::~Event()");
//END
}

void Event::Defaults()
{
    _event_code = DEFAULT_INT;
    _command_code = DEFAULT_INT;
    _key_code = DEFAULT_INT;
    _mouse_x = DEFAULT_INT;
    _mouse_y = DEFAULT_INT;
    _button_code = DEFAULT_INT;
    _button_state = DEFAULT_INT;

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
    
    _event_code = NO_EVENT;

    Poll();

    CommandProcess();

    return result;
}

void Event::PanMode( bool value )
{
    _pan_mode = value;
}

void Event::PanCommand()
{
    switch( _button_state )
    {
        case PRESSED:
            PanMode( true );
            _pan_start_x = _mouse_x;
            _pan_start_y = _mouse_y;
            break;

        case RELEASED:
            PanMode( false );
            break;
    }
}

void Event::ZoomCommand()
{
    switch( _button_state )
    {
        case PRESSED:
            ZoomMode( true );
            _zoom_start_pos = _mouse_y;
            break;

        case RELEASED:
            ZoomMode( false );
            break;
    }
}

void Event::PanUpdate()
{
    if( _pan_mode )
    {
        _mouse_delta_x = _mouse_x - _pan_start_x;
        _mouse_delta_y = _mouse_y - _pan_start_y;

        _command_code = PAN_COMMAND;
		_command_queue.push( (int) _command_code );

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

        _command_code = ZOOM_COMMAND;
		_command_queue.push( (int) _command_code );

        _zoom_start_pos = _mouse_y;
    }
}

void Event::CommandProcess()
{
	_event_code = NO_EVENT;
	if( !_event_queue.empty() )
	{
		_event_code = _event_queue.front();
		_event_queue.pop();
	}

    if( _event_code == BUTTON_EVENT )
    {
        switch( _button_code )
        {
            case RIGHT_BUTTON:
                PanCommand();
                break;
    
            case MIDDLE_BUTTON:
                ZoomCommand();
                break;
        }
    }

    if( _event_code == MOTION_EVENT )
    {
        PanUpdate();
        ZoomUpdate();
    }
}

void Event::KeyEvent( SDL_KeyboardEvent& key )
{
	_event_code = KEY_EVENT;
	_event_queue.push( (int) _event_code );

	_key_code = (int) key.keysym.sym;
	
	_command_code = NO_COMMAND;
	
	switch( _key_code )
	{
		case SDLK_b:
			_command_code = TOGGLE_BACKGROUND_CMD; break;
			
		case SDLK_p:
			_command_code = TOGGLE_PANEL_CMD; break;
			
		case SDLK_q:
		case SDLK_ESCAPE:
			_command_code = QUIT_COMMAND; break;
		
		default:
			break;
	}

	if( _command_code != NO_COMMAND )
	{
		_command_queue.push( (int) _command_code );
	}
}

void Event::MotionEvent( SDL_MouseMotionEvent& motion )
{
	_event_code = MOTION_EVENT;
	_event_queue.push( (int) _event_code );

	_mouse_x = motion.x;
	_mouse_y = motion.y;
}

void Event::ButtonEvent( SDL_MouseButtonEvent& button )
{
	_event_code = BUTTON_EVENT;
	_event_queue.push( (int) _event_code );

	_mouse_x = button.x;
	_mouse_y = button.y;
	
	switch( button.button )
	{
		case SDL_BUTTON_LEFT:
			_button_code = LEFT_BUTTON;
			break;
			
		case SDL_BUTTON_RIGHT:
			_button_code = RIGHT_BUTTON;
			break;
			
		case SDL_BUTTON_MIDDLE:
			_button_code = MIDDLE_BUTTON;
			break;
			
		default:
			_button_code = UNDEFINED;
			break;
	}
	
	switch( button.state )
	{
		case SDL_PRESSED:
			_button_state = PRESSED;
			break;
			
		case SDL_RELEASED:
			_button_state = RELEASED;
			break;
			
		default:
			_button_state = UNDEFINED;
			break;
	}
}

void Event::QuitEvent()
{
	_event_code = QUIT_EVENT;
	_event_queue.push( (int) _event_code );
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
				QuitEvent();
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
	_command_code = NO_COMMAND;

	if( !_command_queue.empty() )
	{
	    _command_code = _command_queue.front();
		_command_queue.pop();
	}

	return _command_code;
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

int Event::GetKeyCode()
{
	return _key_code;
}

void Event::GetMousePosition( int& mouse_x, int& mouse_y )
{
	mouse_x = _mouse_x;
	mouse_y = _mouse_y;
}

void Event::GetButtonInfo( int& button_id, int& button_state )
{
	button_id = _button_code;
	button_state = _button_state;
}
