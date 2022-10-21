#pragma once

#include "Config.h"
#include <cstdint>

class ScreenBuffer
{
private:
	static uint32_t m_bufferData[SCREEN_BUFFER_SIZE];

public:
	static void SetPixel(uint32_t x, uint32_t y, uint32_t color);
	static void Clear();

	static void Generate_ScreenTexture();
	static void Update_ScreenTexture();
};
