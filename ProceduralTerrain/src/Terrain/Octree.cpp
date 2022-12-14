#include "Octree.h"

#include "../Util/Helper.h"

#include <glm/glm.hpp>



NoiseGenerator* Octree::Node::s_Noise = new NoiseGenerator();

#define DEFAULT_SIZE 128

glm::vec3 Octree::GetOctantOffset( Octant _octant ) {
	switch (_octant) {
		case Octant::O1:
			return glm::vec3( 0.5f, 0.5f, 0.5f );
		case Octant::O2:
			return glm::vec3( 0.5f, 0.5f, -0.5f );
		case Octant::O3:
			return glm::vec3( -0.5f, 0.5f, -0.5f );
		case Octant::O4:
			return glm::vec3( -0.5f, 0.5f, 0.5f );
		case Octant::O5:
			return glm::vec3( 0.5f, -0.5f, 0.5f );
		case Octant::O6:
			return glm::vec3( 0.5f, -0.5f, -0.5f );
		case Octant::O7:
			return glm::vec3( -0.5f, -0.5f, -0.5f );
		case Octant::O8:
			return glm::vec3( -0.5f, -0.5f, 0.5f );
	}
}


Octree::Node::Node() 
	:m_Radius(0) 
{

}

Octree::Node::Node( unsigned int _size )
	:m_Radius(2^(GetMSB(_size)+1))
{
		
}

Octree::Node::Node( VoxelPos* _pos, unsigned int _size, std::vector<VoxelPos*> _voxelList )
	:m_Radius(2^(GetMSB(_size)+1))
{
	// insert voxellist

	Node* childNodes[8];
	childNodes[0] = new Node(_pos+(_size << 1) * GetOctantOffset(Octant::O1));



}


bool Octree::Node::IsPosInBounds(VoxelPos _pos) {

	
}
void Octree::Node::Update() {

}

// rebuilds whole octree
void Octree::Node::BuildFrom2DNoise() {

}
void Octree::Node::BuildFrom3DNoise() {

}

bool Octree::Node::Insert( VoxelPos _voxelPos ) {
	
}

bool Octree::Node::Insert( std::vector<VoxelPos*> _voxels ) {
	for (int i = 0; i < _voxels.size(); i++) {
		m_Queue.push( _voxels[i] );
	}
}

void Octree::Node::Clear() {

}

Octree::VoxelPos Octree::Node::WorldToSVOCoord( VoxelPos _pos ) {
	// get normalized SVO Coordinate to convert it into node index later
	return VoxelPos(
		_pos.x - (-m_Radius/2),
		_pos.y - (-m_Radius/2),
		_pos.z - (-m_Radius/2)
	);

}
