#pragma once

#include <string>
#include "Config.h"

class ScreenTexture
{
private:
	static unsigned int rendererID;

public:
	~ScreenTexture();

	static void Generate(const uint32_t* buffer);
	static void Update(const uint32_t* buffer);
	static void Bind(unsigned int slot = 0);
	static void Unbind();
};
