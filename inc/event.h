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
        void GetMousePosition( int& mouse_x, int& mouse_y );
        void GetMouseDelta( int* dx, int* dy );
        
    public:
        // Initial Value.
        static const int DEFAULT_INT = -1000;

        // Event Definitions.
        static const int LEFTBUTTON_PRESSED_EVENT = 100;
        static const int LEFTBUTTON_RELEASED_EVENT = 101;
        static const int RIGHTBUTTON_PRESSED_EVENT = 102;
        static const int RIGHTBUTTON_RELEASED_EVENT = 103;
        static const int MIDBUTTON_PRESSED_EVENT = 104;
        static const int MIDBUTTON_RELEASED_EVENT = 105;
        
        // Command Definitions.
        static const int TOGGLE_WIREFRAME_CMD = 204;
        static const int TOGGLE_BACKGROUND_CMD = 205;
        static const int TOGGLE_PANEL_CMD = 211;
        static const int QUIT_COMMAND = 212;
        static const int ZOOM_COMMAND = 213;
        static const int PAN_COMMAND = 214;

        static const int NO_EVENT = -3;
        static const int NO_COMMAND = -2;
        static const int UNDEFINED = -1;
        static const int TRUE = 1;
        static const int FALSE = 0;

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
        void ProcessLeftButton( SDL_MouseButtonEvent& button );
        void ProcessMiddleButton( SDL_MouseButtonEvent& button );
        void ProcessRightButton( SDL_MouseButtonEvent& button );
        void QuitEvent();
        void PanMode( bool value );
        void ZoomMode( bool value );
        void PushCommand( int code );
        void PushEvent( int code );
        int PopEvent();

    public:
        // Control Members.
        static bool _ready;
        static bool _enable;

    private:
        // Members.
        int _mouse_x;
        int _mouse_y;

        bool _pan_mode;
        bool _zoom_mode;
        int _speed_factor;
        int _pan_start_x;
        int _pan_start_y;
        int _zoom_start_pos;
        int _mouse_delta_x;
        int _mouse_delta_y;

        std::queue< int > _event_queue;
        std::queue< int > _command_queue;
};

#endif

