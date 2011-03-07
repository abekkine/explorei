#include <generator.h>

Generator::Generator()
{
	initVars();
}

Generator::~Generator()
{
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

