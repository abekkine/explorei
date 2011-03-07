#ifndef GENERATOR_H
#define GENERATOR_H

#include <libnoise/noise.h>

using namespace noise;

class Generator
{
	public:
		Generator();
		~Generator();

		double GetValue( double x, double y, double z );
		void SetOctaves( int n );

	private:
		// Members
		module::Perlin _noiseModule;

	private:
		// Methods
		void initVars();
		
};

#endif

