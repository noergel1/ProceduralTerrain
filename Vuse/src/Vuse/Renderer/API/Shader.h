#pragma once

#include <glm/glm.hpp>

namespace Vuse
{
	class Shader
	{
	public:
		Shader( const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr );
		~Shader();

		void Bind();
		static void Unbind();

		void SetBool(std::string name, bool value );
		void SetInt(  std::string name, int value	);
		void SetFloat( std::string name, float value );
		void SetVec2( std::string name, glm::vec2 value );
		void SetVec2( std::string name, float x, float y );
		void SetVec3( std::string name, glm::vec3 value );
		void SetVec3( std::string name, float x, float y, float z	);
		void SetVec4( std::string name, glm::vec4 value );
		void SetVec4( std::string name, float x, float y, float z, float w );
		void SetMat3( std::string name, glm::mat3 value );
		void SetMat4( std::string name, glm::mat4 value );

	private:
		static void CheckCompileErrors( uint32_t shader, std::string type );

	private:
		uint32_t m_ID;
	};
}