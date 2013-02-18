#include <font.h>

Font::Font()
{
//DEBUG
    puts("Font::Font()");
//END
    _font_name = "freemono.ttf";
    _font_folder = "../fonts/";
    _font_size = 12;
}

Font::~Font()
{
//DEBUG
    puts("Font::~Font()");
//END
    delete _font;
}

bool Font::Init()
{
    bool result = false;

    _font_path = _font_folder + _font_name;
    
    _font = new FTGLPixmapFont( _font_path.c_str() );
    
    if( ! _font->Error() )
    {
        _font->FaceSize( _font_size );
        result = true;
    }

    return result;
}

void Font::SelectFont( std::string name, int size )
{
    _font_name = name;
    _font_size = size;
}

void Font::Print( int x, int y, std::string text )
{
    //  Force all text to white color.
    glColor3f( 1.0, 1.0, 1.0 );

    glRasterPos2i( x, y );
    _font->Render( text.c_str() );
}

