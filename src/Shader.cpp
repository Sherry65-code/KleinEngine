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


	oShader.id = glCreateProgram();

	glAttachShader(oShader.id, vertexShader);
	glAttachShader(oShader.id, fragmentShader);
	glLinkProgram(oShader.id);

    int success3;
    char infoLog3[512];

	glGetProgramiv(oShader.id, GL_LINK_STATUS, &success3);
	if (!success3) {
		glGetShaderInfoLog(oShader.id, 512, nullptr, infoLog3);
	}


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::use() {
    glUseProgram(oShader.id);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(oShader.id, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(oShader.id, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(oShader.id, name.c_str()), value);
}