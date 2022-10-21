#pragma once

#include "Config.h"
#include <cstdint>

class ScreenBuffer
{
private:
	static uint8_t m_bufferData[SCREEN_BUFFER_SIZE];

public:
	static void SetPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
	static void Clear();

	static void Generate_ScreenTexture();
	static void Update_ScreenTexture();
};
