#include <stdio.h>

#include <generator.h>

Generator::Generator()
{
//DEBUG
    puts("Generator::Generator()");
//END
	initVars();
}

Generator::~Generator()
{
//DEBUG
    puts("Generator::~Generator()");
//END
}

double Generator::GetValue( double x, double y, double z )
{
	return _noiseModule.GetValue( x, y, z );
}

void Generator::SetOctaves( int n )
{
	_noiseModule.SetOctaveCount( n );
}

void Generator::initVars()
{
	// TODO : Nothing to initiate?
}

