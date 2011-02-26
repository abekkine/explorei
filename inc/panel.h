#ifndef PANEL_H
#define PANEL_H

#include <string>

class Panel
{
    public:
        Panel();
        ~Panel();
        bool Init( std::string location, int percentage );
        void Resize( int width, int height );
        void Render();

    private:
        // Methods

    private:
        // Members
};

#endif

