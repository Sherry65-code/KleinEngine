#ifndef _IMAGE_LOADER_H_
#define _IMAGE_LOADER_H_
#include <glad/glad.h>


#include "ThirdParty/stb_image.h"

#include <GLFW/glfw3.h>
#include <iostream>

class Texture {
public:
	typedef uint32_t t_Texture;
	t_Texture tex;
	Texture(std::string ImagePath);
};

#endif