#include "ScreenBuffer.h"
#include "ScreenTexture.h"
#include "vcruntime_string.h"

uint32_t ScreenBuffer::m_bufferData[SCREEN_BUFFER_SIZE];

void ScreenBuffer::SetPixel(uint32_t x, uint32_t y, uint32_t color)
{
	m_bufferData[y * RES_X + x] = color;
}

void ScreenBuffer::Clear()
{
	memset(m_bufferData, 0, sizeof(uint32_t) * SCREEN_BUFFER_SIZE);
}

void ScreenBuffer::Generate_ScreenTexture()
{
	ScreenTexture::Generate(m_bufferData);
}

void ScreenBuffer::Update_ScreenTexture()
{
	ScreenTexture::Update(m_bufferData);
}
