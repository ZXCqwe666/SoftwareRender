#include "ScreenBuffer.h"
#include "ScreenTexture.h"
#include <vcruntime_string.h>

uint8_t ScreenBuffer::m_bufferData[SCREEN_BUFFER_SIZE];

void ScreenBuffer::SetPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
{
	m_bufferData[(x * RES_X + y) * 4 + 0] = r;
	m_bufferData[(x * RES_X + y) * 4 + 1] = g;
	m_bufferData[(x * RES_X + y) * 4 + 2] = b;
	m_bufferData[(x * RES_X + y) * 4 + 3] = 1;
}

void ScreenBuffer::Clear()
{
	for (int i = 0; i < SCREEN_BUFFER_SIZE; i++)
	{
		m_bufferData[i] = 255;
	}

	//memset(m_bufferData, 0, SCREEN_BUFFER_SIZE);
}

void ScreenBuffer::Generate_ScreenTexture()
{
	ScreenTexture::Generate(m_bufferData);
}

void ScreenBuffer::Update_ScreenTexture()
{
	ScreenTexture::Update(m_bufferData);
}
