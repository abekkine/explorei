#ifndef GENERATOR_H
#define GENERATOR_H

#include <libnoise/noise.h>

class Generator
{
    public:
        Generator();
        ~Generator();

        double GetValue( double x, double y, double z );
        void SetOctaves( int n );

    private:
        // Members
        noise::module::Perlin _noiseModule;

    private:
        // Methods
        void initVars();
        
};

#endif

