#include "ScreenTexture.h"

#include "GLErrorHandler.h"
#include "glad/glad.h"
#include "Config.h"

unsigned int ScreenTexture::rendererID;

void ScreenTexture::Generate(const uint32_t* buffer)
{
	GLCall(glGenTextures(1, &ScreenTexture::rendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, ScreenTexture::rendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, RES_X, RES_Y, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, buffer));
	Bind();
}

void ScreenTexture::Update(const uint32_t* buffer)
{
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, RES_X, RES_Y, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, buffer);
	Bind();
}

ScreenTexture::~ScreenTexture()
{
	GLCall(glDeleteTextures(1, &rendererID));
}

void ScreenTexture::Bind(unsigned int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));
}

void ScreenTexture::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
