#include <texture.h>

Texture::Texture()
{
	Defaults();
}

Texture::~Texture()
{
}

void Texture::Defaults()
{
}

bool Texture::Init()
{
    bool result = false;

    return result;
}

bool Texture::Load( std::string filename )
{
    bool result = false;

    _surface = SDL_LoadBMP( filename.c_str() );
    if( _surface != NULL )
    {
        // Width and height is power of two?
        if( (_surface->w & (_surface->w-1)) != 0 )
        {
            printf( "Warning: Width is not power of 2.\n" );
        }

        if( (_surface->h & (_surface->h-1)) != 0 )
        {
            printf( "Warning: Height is not power of 2.\n" );
        }

        _nOfColors = _surface->format->BytesPerPixel;
        if( _nOfColors == 4 )
        {
            if( _surface->format->Rmask == 0x000000ff )
            {
                _textureFormat = GL_RGBA;
            }
            else
            {
                _textureFormat = GL_BGRA;
            }
        }
        else if( _nOfColors == 3 )
        {
            if( _surface->format->Rmask == 0x000000ff )
            {
                _textureFormat = GL_RGB;
            }
            else
            {
                _textureFormat = GL_BGR;
            }
        }
        else
        {
            printf( "Warning: Image is not true color.\n" );
        }

        glGenTextures( 1, &_texture );
        CheckError( "GLTexture::Load() : glGenTextures" );

        glBindTexture( GL_TEXTURE_2D, _texture );
        CheckError( "GLTexture::Load() : glBindTexture" );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        CheckError( "GLTexture::Load() : glTexParameteri() : MIN" );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        CheckError( "GLTexture::Load() : glTexParameteri() : MAG" );

        //DEBUG
        printf( "_nOfColors(%d)\n_surface->w(%d)\n_surface->h(%d)\n_textureFormat(%8x)\n", _nOfColors, _surface->w, _surface->h, _textureFormat );
        glTexImage2D( GL_TEXTURE_2D, 0, _nOfColors, _surface->w, _surface->h, 0, _textureFormat, GL_UNSIGNED_BYTE, _surface->pixels );
        CheckError( "GLTexture::Load() : glTexImage2D()" );

        result = true;

        // Free surface since we don't need (?) it anymore.
        if( _surface )
        {
            SDL_FreeSurface( _surface );
        }
    }
    else
    {
        printf( "Error: Unable to load image: %s\n", SDL_GetError() );
        result = false;
    }

    return result;
}

void Texture::Select()
{
	glBindTexture( GL_TEXTURE_2D, _texture );
	CheckError( "Texture::Select() : glBindTexture()" );
}

void Texture::CheckError( std::string message )
{
	bool showMessage = true;
	GLenum errorCode = glGetError();

	switch( errorCode )
	{
        case GL_NO_ERROR:
            showMessage = false;
            break;

        case GL_INVALID_ENUM:
            puts( "GL Invalid Enum" );
            break;

        case GL_INVALID_VALUE:
            puts( "GL Invalid Value" );
            break;

        case GL_INVALID_OPERATION:
            puts( "GL Invalid Operation" );
            break;

        case GL_STACK_OVERFLOW:
            puts( "GL Stack Overflow" );
            break;

        case GL_STACK_UNDERFLOW:
            puts( "GL Stack Underflow" );
            break;

        case GL_OUT_OF_MEMORY:
            puts( "GL Out of memory" );
            break;

        case GL_TABLE_TOO_LARGE:
            puts( "GL Table too large" );
            break;

        default:
            puts( "Unknown error" );
            break;
    }

    if( showMessage )
    {
        puts( message.c_str() );
    }
}

