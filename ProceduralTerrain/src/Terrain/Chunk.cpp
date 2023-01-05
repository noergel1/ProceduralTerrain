#include "Chunk.h"

void Chunk::Update() {
	// iterate through all voxels in chunk
	
}

std::vector<std::vector<uint16_t>>* Chunk::GetVoxels() {
	std::vector<std::vector<std::vector<uint16_t>>>* voxels = new std::vector<std::vector<std::vector<uint16_t>>>();

	(*voxels)[0][0][0] = 1;




}

void Chunk::Iterate( std::vector<std::vector<uint16_t>>* _voxels, Node* _node, uint16_t _curDepth, uint32_t _curLocCode ) {
	if (_curDepth == (s_ChunkDepth - 1)) {
		for (int i = 0; i < 8; i++) {
			if (_node->IsChildActive( i )) {
				glm::ivec3 pos =  
				(*_voxels)[]
			}
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			if (_node->IsChildActive( i )) {
				Iterate(
					_voxels, 
					_node->data.children[i],
					_curDepth+1,
					(_curLocCode << 3) & i
				);
			}
		}
	}
}


