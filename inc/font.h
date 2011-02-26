#ifndef FONT_H
#define FONT_H

#include <string>

#include <GL/gl.h>
#include <FTGL/ftgl.h>

class Font
{
    public:
        Font();
        ~Font();
        bool Init();
        void SelectFont( std::string name, int size );
        void Print( int x, int y, std::string text );

    private:
        // Methods

    private:
        // Members
        FTGLPixmapFont* _font;
        std::string _font_name;
        std::string _font_path;
        std::string _font_folder;
        int _font_size;
};

#endif

