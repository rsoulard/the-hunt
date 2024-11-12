#include <assert.h>

#include "framebuffer.h"

struct FrameBuffer
{
    BITMAPINFO bitmapInfo;
    HBITMAP bitmap;
    HDC deviceContext;

    uint32_t* pixels;
};

frameBuffer_t FrameBuffer_New()
{
    frameBuffer_t this = malloc(sizeof *this);

    assert(this);

    this->bitmapInfo.bmiHeader.biSize = sizeof(this->bitmapInfo.bmiHeader);
    this->bitmapInfo.bmiHeader.biPlanes = 1;
    this->bitmapInfo.bmiHeader.biBitCount = 32;
    this->bitmapInfo.bmiHeader.biCompression = BI_RGB;

    this->deviceContext = CreateCompatibleDC(0);

    this->pixels = NULL;

    return this;
}

void FrameBuffer_Resize(frameBuffer_t this, int width, int height)
{
    this->bitmapInfo.bmiHeader.biWidth = width;
    this->bitmapInfo.bmiHeader.biHeight = height;

    if (this->bitmap)
    {
        DeleteObject(this->bitmap);
    }

    this->bitmap = CreateDIBSection(NULL, &this->bitmapInfo, DIB_RGB_COLORS, (void**)&this->pixels, 0, 0);

	assert(this->bitmap);

    SelectObject(this->deviceContext, this->bitmap);
}

void FrameBuffer_Paint(frameBuffer_t this, HDC destinationDeviceContext, PAINTSTRUCT paintStruct)
{
	StretchBlt(
		destinationDeviceContext,
		paintStruct.rcPaint.left,
		paintStruct.rcPaint.top,
		paintStruct.rcPaint.right - paintStruct.rcPaint.left,
		paintStruct.rcPaint.bottom - paintStruct.rcPaint.top,
		this->deviceContext,
		paintStruct.rcPaint.left,
		paintStruct.rcPaint.top,
		this->bitmapInfo.bmiHeader.biWidth,
		this->bitmapInfo.bmiHeader.biHeight,
		SRCCOPY
	);
	BitBlt(
		this->deviceContext,
		paintStruct.rcPaint.left,
		paintStruct.rcPaint.top,
		this->bitmapInfo.bmiHeader.biWidth,
		this->bitmapInfo.bmiHeader.biHeight,
		NULL,
		0,
		0,
		BLACKNESS
	);
}

inline void FrameBuffer_SetPixel(frameBuffer_t this, uint32_t value)
{
	this->pixels[1000] = value;
}

void FrameBuffer_Destroy(frameBuffer_t this)
{
    if (this->bitmap)
    {
        DeleteObject(this->bitmap);
    }

    free(this);
}