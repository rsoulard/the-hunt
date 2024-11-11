#include <assert.h>
#include <stdint.h>
#include <windows.h>

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
    SelectObject(this->deviceContext, this->bitmap);
}

void FrameBuffer_Destroy(frameBuffer_t this)
{
    if (this->bitmap)
    {
        DeleteObject(this->bitmap);
    }

    if (this->pixels)
    {
        free(this->pixels);
    }

    free(this);
}