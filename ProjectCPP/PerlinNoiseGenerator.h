#pragma once
#include <noise/noise.h>
#include "noiseutils.h"
class PerlinNoiseGenerator
{

private:
	float xMin, xMax, zMin, zMax;
	module::Perlin myModule;
	utils::NoiseMap noiseMap;
	utils::NoiseMapBuilderPlane heightMapBuilder;

	const int octaveCount = 1;
	const int frequency = 1;
	
public:
	PerlinNoiseGenerator& setBounds(float xMin, float xMax, float zMin, float zMax);

	utils::NoiseMap& buildMap(unsigned int rows, unsigned int columns, float seed);
};

