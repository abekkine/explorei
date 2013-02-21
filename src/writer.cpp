#include <writer.h>

bool Writer::_ready = false;
bool Writer::_enable = false;

Writer* Writer::_instance = NULL;

Writer* Writer::GetInstance()
{
    if( _instance == NULL )
    {
        _instance = new Writer();
    }
    
    return _instance;
}

Writer::Writer()
{
//DEBUG
    puts("Writer::Writer()");
//END
    Defaults();
}

Writer::~Writer()
{
//DEBUG
    puts("Writer::~Writer()");
//END
    for( _iMessage = _message_list.begin(); _iMessage != _message_list.end(); ++_iMessage )
    {
        _a_message = *_iMessage;
        delete _a_message;
    }

    delete _font;
}

void Writer::Defaults()
{
    _font = NULL;
    _a_message = NULL;
    _message_list.clear();
    _iMessage = _message_list.end();
}

bool Writer::Init()
{
    bool result = false;

    _font = new Font();
    
    result = _font->Init();
    
    return result;
}

void Writer::UpdateOrigin( int x, int y )
{
    _origin_x = x;
    _origin_y = y;
}

void Writer::Add( std::string text, int x, int y, bool* control )
{
    MessageDisplayType* new_message = new MessageDisplayType;

    new_message->x = x;
    new_message->y = y;
    new_message->type = 'T';
    new_message->format = text;
    new_message->value = 0;
    new_message->control = control;

    _message_list.push_back( new_message );
}

void Writer::Add( std::string format, int* value, int x, int y, bool* control )
{
    MessageDisplayType* new_message = new MessageDisplayType;

    new_message->x = x;
    new_message->y = y;
    new_message->type = 'I';
    new_message->format = format;
    new_message->value = (void *) value;
    new_message->control = control;

    _message_list.push_back( new_message );
}

void Writer::Add( std::string format, double* value, int x, int y, bool* control )
{
    MessageDisplayType* new_message = new MessageDisplayType;

    new_message->x = x;
    new_message->y = y;
    new_message->type = 'D';
    new_message->format = format;
    new_message->value = (void *) value;
    new_message->control = control;

    _message_list.push_back( new_message );
}

void Writer::Render()
{
    for( _iMessage = _message_list.begin(); _iMessage != _message_list.end(); ++_iMessage )
    {
        _a_message = *_iMessage;
        if( *(_a_message->control) == true )
        {
            memset(_text_buffer, 0, 256);
            switch( _a_message->type ) {
                case 'T':
                    strcpy( _text_buffer, _a_message->format.c_str() );
                    break;

                case 'I':
                    sprintf( _text_buffer, _a_message->format.c_str(), *((int *) _a_message->value) );
                    break;

                case 'D':
                    sprintf( _text_buffer, _a_message->format.c_str(), *((double *) _a_message->value) );
                    break;
            }

            _font->Print( _origin_x + _a_message->x, _origin_y + _a_message->y, std::string(_text_buffer) );
        }
    }
}

