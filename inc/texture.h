#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <SDL/SDL.h>
#include <GL/gl.h>

class Texture
{
    public:
        Texture();
        ~Texture();
        bool Init();
		bool Load( std::string filename );
		void Select();
		GLuint GetTexture();
		void CheckError( std::string message );

    private:
        // Methods
		void Defaults();

	public:
		// Control Members
		static bool _ready;
		static bool _enable;

    private:
        // Members
		SDL_Surface* _surface;
		GLuint _texture;
		GLenum _textureFormat;
		GLint _nOfColors;
};

#endif

