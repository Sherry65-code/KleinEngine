#include "ImageLoader.hpp"

Texture::Texture(std::string FilePath) {

	glGenTextures(1, &tex);

	glBindTexture(GL_TEXTURE_2D, tex);
	
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// load image, create texture and generate mipmaps

	int width, height, nrChannels;
	unsigned char* data = stbi_load(FilePath.c_str(), &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ERROR: Failed to load texture \"" << FilePath << "\"" << std::endl;
	}

	stbi_image_free(data);
}