#ifndef STAR_H
#define STAR_H

#include <definitions.h>
#include <generator.h>

class Star
{
    public:
        Star();
        ~Star();
        bool Init( Volume* viewport );
        void Render();

    private:
        // Methods.
        void RenderTest();
        void RenderStarLayer();
        void RenderSingleStar( double x, double y, double r, double g, double b );
        void Defaults();

    public:
        // Control members.
        static bool _ready;
        static bool _enable;

    private:
        // Member.
        double _zValue;
        Volume* _viewport;
        Generator* _generator;
};

#endif
