#ifndef EVENT_H
#define EVENT_H

#include <queue>

#include <SDL/SDL.h>

class Event
{
    public:
        Event();
        ~Event();
        bool Init();
        bool Update();
	int CheckEventCode();
        int GetCommandCode();
        int GetKeyCode();
        void GetMousePosition( int& mouse_x, int& mouse_y );
        void GetMouseDelta( int* dx, int* dy );
        void GetButtonInfo( int& button_id, int& button_state );
        
    public:
        // Initial Value.
        static const int DEFAULT_INT = -1000;

        // Event Definitions.
	    static const int KEY_EVENT = 101;
	    static const int MOTION_EVENT = 102;
	    static const int BUTTON_EVENT = 103;
	    static const int QUIT_EVENT = 104;
	    static const int LEFT_BUTTON = 105;
	    static const int RIGHT_BUTTON = 106;
	    static const int MIDDLE_BUTTON = 107;
	    static const int PRESSED = 108;
	    static const int RELEASED = 109;
	    
        // Command Definitions.
	    static const int NEXT_PARAMETER_CMD = 201;
	    static const int PREV_PARAMETER_CMD = 202;
	    static const int NEXT_VALUE_CMD = 203;
	    static const int PREV_VALUE_CMD = 204;
	    static const int TOGGLE_BACKGROUND_CMD = 205;
	    static const int TOGGLE_PLANETS_CMD = 206;
	    static const int TOGGLE_FONT_TEST_CMD = 207;
	    static const int TOGGLE_PARAM_DISPLAY_CMD = 208;
	    static const int TOGGLE_FPS_CMD = 209;
	    static const int TOGGLE_WIREFRAME_CMD = 210;
	    static const int TOGGLE_PANEL_CMD = 211;
	    static const int QUIT_COMMAND = 212;
	    static const int ZOOM_COMMAND = 213;
	    static const int PAN_COMMAND = 214;
        static const int TOGGLE_DUST_CMD = 216;

		static const int NO_EVENT = -3;
	    static const int NO_COMMAND = -2;
        static const int UNDEFINED = -1;

    private:
        // Methods.
        void Defaults();
        void Poll();
        void CommandProcess();
        void PanCommand();
        void PanUpdate();
        void ZoomCommand();
        void ZoomUpdate();
        void KeyEvent( SDL_KeyboardEvent& key );
        void MotionEvent( SDL_MouseMotionEvent& motion );
        void ButtonEvent( SDL_MouseButtonEvent& button );
        void QuitEvent();
        void PanMode( bool value );
        void ZoomMode( bool value );

	public:
		// Control Members.
		static bool _ready;
		static bool _enable;

    private:
        // Members.
        int _event_code;
        int _command_code;
        int _key_code;
        int _mouse_x;
        int _mouse_y;
        int _button_code;
        int _button_state;

        bool _pan_mode;
        bool _zoom_mode;
        int _pan_start_x;
        int _pan_start_y;
        int _zoom_start_pos;
        int _mouse_delta_x;
        int _mouse_delta_y;

		std::queue< int > _event_queue;
		std::queue< int > _command_queue;
};

#endif

