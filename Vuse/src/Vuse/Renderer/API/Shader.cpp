#include "vuse_pch.h"
#include "Shader.h"

#include <glad/gl.h>
#include <glm/ext.hpp>
#include "glm/gtc/matrix_transform.hpp"

namespace Vuse
{
	Shader::Shader( const char* vertexPath, const char* fragmentPath, const char* geometryPath )
	{
		// 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();		
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();			
            // if geometry shader path is present, also load a geometry shader
            if(geometryPath != nullptr)
            {
                gShaderFile.open(geometryPath);
                std::stringstream gShaderStream;
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();
            }
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, "FRAGMENT");
        // if geometry shader is given, compile geometry shader
        unsigned int geometry;
        if(geometryPath != nullptr)
        {
            const char * gShaderCode = geometryCode.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            CheckCompileErrors(geometry, "GEOMETRY");
        }

        // create shader Program
        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertex);
        glAttachShader(m_ID, fragment);
        if(geometryPath != nullptr)
            glAttachShader(m_ID, geometry);
        glLinkProgram(m_ID);
        CheckCompileErrors(m_ID, "PROGRAM");

        // delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if(geometryPath != nullptr)
            glDeleteShader(geometry);
	}

	Shader::~Shader()
	{
        glDeleteProgram( m_ID );
	}

	void Shader::Bind()
	{
        glUseProgram( m_ID );
	}

	void Shader::Unbind()
	{
        glUseProgram( 0 );
	}

	void Shader::SetBool( std::string name, bool value )
	{
        unsigned int uniformId = glGetUniformLocation(m_ID, name.c_str());
        if (uniformId == -1)
            VUSE_ERROR("Couldnt find boolean Uniform {0}", name);
        else
            glUniform1i(uniformId, (int)value);
	}

	void Shader::SetInt( std::string name, int value )
	{
        unsigned int uniformId = glGetUniformLocation(m_ID, name.c_str());
        if (uniformId == -1)
            VUSE_ERROR( "Couldnt find boolean Uniform {0}", name );
        else
            glUniform1i(uniformId, value);
	}

	void Shader::SetFloat( std::string name, float value )
	{
        unsigned int uniformId = glGetUniformLocation(m_ID, name.c_str());
        if (uniformId == -1)
            VUSE_ERROR( "Couldnt find float Uniform {0}", name );
        else
            glUniform1f(uniformId, value);
	}

	void Shader::SetVec2( std::string name, glm::vec2 value )
	{
        unsigned int uniformId = glGetUniformLocation(m_ID, name.c_str());
        if (uniformId == -1)
            VUSE_ERROR( "Couldnt find vec2 Uniform {0}", name );
        else
            glUniform2f(uniformId, value.x, value.y);
	}

    void Shader::SetVec2( std::string name, float x, float y )
    {
        unsigned int uniformId = glGetUniformLocation(m_ID, name.c_str());
        if (uniformId == -1)
            VUSE_ERROR( "Couldnt find vec2 Uniform {0}", name );
        else
            glUniform2f(uniformId, x, y);
    }

	void Shader::SetVec3( std::string name, glm::vec3 value )
	{
        unsigned int uniformId = glGetUniformLocation(m_ID, name.c_str());
        if (uniformId == -1)
            VUSE_ERROR( "Couldnt find vec3 Uniform {0}", name );
        else
            glUniform3f(uniformId, value.x, value.y, value.z);
	}

    void Shader::SetVec3( std::string name, float x, float y, float z )
    {
        unsigned int uniformId = glGetUniformLocation(m_ID, name.c_str());
        if (uniformId == -1)
            VUSE_ERROR( "Couldnt find vec3 Uniform {0}", name );
        else
            glUniform3f(uniformId, x, y, z);
    }

	void Shader::SetVec4( std::string name, glm::vec4 value )
	{
        unsigned int uniformId = glGetUniformLocation(m_ID, name.c_str());
        if (uniformId == -1)
            std::cout << "Couldnt find vec4 Uniform " + name + "!\n";
        else
            glUniform4f(uniformId, value.x, value.y, value.z, value.w);
	}

    void Shader::SetVec4( std::string name, float x, float y, float z, float w )
    {
        unsigned int uniformId = glGetUniformLocation(m_ID, name.c_str());
        if (uniformId == -1)
            VUSE_ERROR( "Couldnt find vec4 Uniform {0}", name );
        else
            glUniform4f(uniformId, x, y, z, w);
    }

	void Shader::SetMat3( std::string name, glm::mat3 value )
	{
        unsigned int uniformId = glGetUniformLocation(m_ID, name.c_str());
        if (uniformId == -1)
            VUSE_ERROR( "Couldnt find mat3 Uniform {0}", name );
        else
            glUniformMatrix3fv(uniformId, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::SetMat4( std::string name, glm::mat4 value )
	{
        unsigned int uniformId = glGetUniformLocation(m_ID, name.c_str());
        if (uniformId == -1)
            VUSE_ERROR( "Couldnt find mat4 Uniform {0}", name );
        else
            glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::CheckCompileErrors( uint32_t shader, std::string type )
	{
        GLint success;
        GLchar infoLog[1024];
        if(type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
	}
}