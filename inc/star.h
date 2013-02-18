#ifndef STAR_H
#define STAR_H

#include <definitions.h>

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
        void RenderStar();
        void Defaults();

    public:
        // Control members.
        static bool _ready;
        static bool _enable;

    private:
        // Member.
        double _zValue;
        Volume* _viewport;
};

#endif
