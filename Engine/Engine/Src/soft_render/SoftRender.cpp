#include "SoftRender.h"
#include "ScreenBuffer.h"

#include <cmath>

void SoftRender::Render()
{
	ScreenBuffer::Clear();

	for (int x = 0; x < RES_X; x++)
	{
		for (int y = 0; y < RES_Y; y++)
		{	
			if ((x + y) % 2 == 0)
			{
				int32_t color = (255 << 24) | (32 << 16) | (54 << 8) | 255;
				ScreenBuffer::SetPixel(x, y, color);
			}
			else 
			{
				int32_t color = (4 << 24) | (74 << 16) | (12 << 8) | 255;
				ScreenBuffer::SetPixel(x, y, color);
			}
		}
	}

	ScreenBuffer::Update_ScreenTexture();
}
