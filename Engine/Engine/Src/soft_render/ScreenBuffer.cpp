#include "ScreenBuffer.h"
#include <vcruntime_string.h>

uint32_t ScreenBuffer::m_bufferData[SCREEN_BUFFER_SIZE];
const uint32_t ScreenBuffer::clearColor = 0;

void ScreenBuffer::SetPixel(uint32_t x, uint32_t y, uint32_t color)
{
	m_bufferData[x * RES_X + y] = color;
}

void ScreenBuffer::Clear()
{
	memset(m_bufferData, clearColor, SCREEN_BUFFER_SIZE);
}
