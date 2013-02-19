#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <definitions.h>
#include <config.h>
#include <generator.h>

class Background
{
    public:
        Background();
        ~Background();
        bool Init( Volume* viewport );
        void Render();
        void ToggleWireframe();

    private:
        // Methods.
        void RenderTest();
        void RenderBackground();

        void VertexColor( float x, float y );
        void Triangle( float x, float y );
        void ReverseTriangle( float x, float y );
        void Mesh( float x, float y );

    public:
        static bool _ready;
        static bool _enable;

    private:
        // Members.
        Config* _config;
        Volume* _viewport;
        Generator* _generator;

        int _vertexCount;
        bool _wireframe;
        double _zValue;
        float _size;
        float _height;
        float _halfSide;
        float _brightness;
        float _red_offset;
        float _green_offset;
        float _blue_offset;
        FillMethodType _colorMethod;
};

#endif

