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
        if( _a_message->internal == true )
        {
            delete _a_message;
        }
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

void Writer::AddStatic( int x, int y, std::string text )
{
    MessageDisplayType* new_message = new MessageDisplayType;

    new_message->x = x;
    new_message->y = y;
    new_message->text = text;
    new_message->internal = true;

    _message_list.push_back( new_message );
}

void Writer::AddDynamic( MessageDisplayType* message )
{
    message->internal = false;

    _message_list.push_back( message );
}

void Writer::Render()
{
    for( _iMessage = _message_list.begin(); _iMessage != _message_list.end(); ++_iMessage )
    {
        _a_message = *_iMessage;
        if( *(_a_message->control) == true )
        {
            _font->Print( _a_message->x, _a_message->y, _a_message->text );
        }
    }
}

