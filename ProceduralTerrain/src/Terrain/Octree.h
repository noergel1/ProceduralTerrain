#pragma once

#include "NoiseGenerator.h"
#include "VoxelData.h"

#include <queue>
#include <list>


namespace Octree {

	enum class Octant : unsigned char {
		O1 = 0x01,	//	=	0b00000001
		O2 = 0x02,	//	=	0b00000010
		O3 = 0x04,	//	=	0b00000100
		O4 = 0x08,	//	=	0b00001000
		O5 = 0x10,	//	=	0b00010000
		O6 = 0x20,	//	=	0b00100000
		O7 = 0x40,	//	=	0b01000000
		O8 = 0x80,	//	=	0b10000000
	};
	glm::vec3 GetOctantOffset( Octant _octant );


	uint32_t abs_svo( int32_t _n ) {
		return _n < 0 ? -_n - 1 : _n;
	}
	bool comp_against_svo_bounds( int32_t _x, int32_t _y, int32_t _z, int32_t _d ) {
		return (abs_svo( _x ) | abs_svo( _y ) | abs_svo( _z )) >= _d;
	}

	
	struct VoxelPos {
		VoxelPos( int32_t _x, int32_t _y, int32_t _z ) 
			:x(_x)
			,y(_y)
			,z(_z)
		{}

		VoxelPos& operator*( glm::vec3 vec ) {
			x = 
		}

		int32_t x;
		int32_t y;
		int32_t z;
	}; 
 

	class Node 
	{
	public:
		Node();
		Node( unsigned int _size );
		Node( VoxelPos* _pos, unsigned int _size, std::vector<VoxelPos*> _voxelList);

		~Node() { Clear(); }

		void Update();

		bool IsPosInBounds( VoxelPos _pos );

		// rebuilds whole octree
		void BuildFrom2DNoise();
		void BuildFrom3DNoise();

		bool Insert( VoxelPos _voxel );
		bool Insert( std::vector<VoxelPos*> _voxels );

		static void SetNoise( NoiseGenerator* _noise ) { s_Noise = _noise; }
		static NoiseGenerator* GetNoise() { return s_Noise; }

	private:
		void Clear();

		VoxelPos WorldToSVOCoord( VoxelPos _pos );

	public:
		static const unsigned int s_MaxDepth = 15; 

	private:
		Node* m_Parent;
		Node* m_Children[8];

		VoxelPos* m_Pos;
		unsigned int m_Radius;
	
		// bitmask identifying which child nodes exist
		unsigned char m_Voxel;
		unsigned char m_ActiveChildren;

		// objects to be inserted into octree
		std::queue<VoxelPos*> m_Queue;

		// noise generator for world generation
		static NoiseGenerator* s_Noise;
	};
}
