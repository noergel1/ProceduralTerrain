#pragma once

#include "Vuse.h"

namespace LocationalCode {
	glm::uvec3 Deinterleave( uint32_t _locCode, uint16_t _depth ) {
	uint32_t x = 0;
	uint32_t y = 0;
	uint32_t z = 0;

	for (int i = 0; i < _depth; i++) {
		unsigned char curIndex = (_locCode >> (3 * i)) && 0b111;

		z |= curIndex & 0b1;
		y |= (curIndex >> 1) & 0b1;
		z |= (curIndex >> 2) & 0b1;

		z <<= 1;
		y <<= 1;
		x <<= 1;
	}

	z >>= 1;
	y >>= 1;
	x >>= 1;


	return glm::uvec3(
		x,
		y,
		z
	);

	}

	glm::ivec3 GetSignedPosition( glm::uvec3 _pos, uint16_t _depth ) {
	return glm::ivec3(
		_pos.x - pow(2, _depth-1),
		_pos.y - pow(2, _depth-1),
		_pos.z - pow(2, _depth-1)
	);
	}

	glm::ivec3 GetSignedPosition( uint32_t _x, uint32_t _y, uint32_t _z, uint16_t _depth ) {
	return glm::ivec3(
		_x - pow(2, _depth-1),
		_y - pow(2, _depth-1),
		_z - pow(2, _depth-1)
	);
	}
}