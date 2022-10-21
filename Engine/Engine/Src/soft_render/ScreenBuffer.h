#pragma once

#include "Config.h"
#include <cstdint>

class ScreenBuffer
{
private:
	static uint32_t m_bufferData[RES_X * RES_Y];
	static const uint32_t clearColor;

public:
	static void SetPixel(uint32_t x, uint32_t y, uint32_t color);
	static void Clear();
};
