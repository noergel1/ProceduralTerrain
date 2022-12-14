#pragma once

unsigned int GetMSB( unsigned int val ) {
	unsigned int r = 0;
	
	while (val >>= 1) {
		r++;
	}

	return r;
}