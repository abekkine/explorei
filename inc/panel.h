#ifndef PANEL_H
#define PANEL_H

#include <string>

#include <writer.h>

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
		void Defaults();
		void RenderPanel();
		void RenderTest();
		void DisplayVersion();

    private:
        // Members
		Writer* _writer;
		int _margin;
		int _panel_left;
		int _panel_right;
		int _panel_bottom;
		int _panel_top;
		int _panel_percent;

	private:
		// Messages
		Writer::MessageDisplayType _versionMsg;
};

#endif

