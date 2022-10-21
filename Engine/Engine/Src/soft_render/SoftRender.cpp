#include "SoftRender.h"
#include "ScreenBuffer.h"

void SoftRender::Render()
{
	ScreenBuffer::Clear();

	for (int x = 25; x < 75; x++)
	for (int y = 25; y < 75; y++)
	{
		ScreenBuffer::SetPixel(x, y, 593049);
	}
}
