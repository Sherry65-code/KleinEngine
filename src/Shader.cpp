#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    
    std::string vertexCode;
    std::string fragmentCode;
    
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    const char* vShaderCode;
    const char* fShaderCode;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
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
    
        vShaderCode = vertexCode.c_str();
        fShaderCode = fragmentCode.c_str();

    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }


	uint32_t vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
	glCompileShader(vertexShader);

	int success1;
	char infoLog1[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success1);

	if (!success1) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog1);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION FAILED!\n" << infoLog1 << std::endl;
	}

	uint32_t fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
	glCompileShader(fragmentShader);


    int success2;
    char infoLog2[512];

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success2);


	if (!success2) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog2);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED!\n" << infoLog2 << std::endl;
	}


	id = glCreateProgram();

	glAttachShader(Shader::id, vertexShader);
	glAttachShader(Shader::id, fragmentShader);
	glLinkProgram(Shader::id);

    int success3;
    char infoLog3[512];

	glGetProgramiv(Shader::id, GL_LINK_STATUS, &success3);
	if (!success3) {
		glGetShaderInfoLog(Shader::id, 512, nullptr, infoLog3);
	}


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}


void Shader::use() const
{
    glUseProgram(Shader::id);
}
void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(Shader::id, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(Shader::id, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(Shader::id, name.c_str()), value);
}
void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(Shader::id, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(Shader::id, name.c_str()), x, y);
}
void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(Shader::id, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(Shader::id, name.c_str()), x, y, z);
}
void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(Shader::id, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(Shader::id, name.c_str()), x, y, z, w);
}
void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(Shader::id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(Shader::id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(Shader::id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
