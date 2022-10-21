#include "SoftRender.h"
#include "ScreenBuffer.h"

void SoftRender::Render()
{
	ScreenBuffer::Clear();
	ScreenBuffer::Update_ScreenTexture();
}
