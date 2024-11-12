#pragma once
#include <stdint.h>
#include <windows.h>

typedef struct FrameBuffer* frameBuffer_t;

frameBuffer_t FrameBuffer_New();
void FrameBuffer_Destroy(frameBuffer_t this);
void FrameBuffer_Resize(frameBuffer_t this, int width, int height);
void FrameBuffer_Paint(frameBuffer_t this, HDC destinationDeviceContext, PAINTSTRUCT paintStruct);
extern inline void FrameBuffer_SetPixel(frameBuffer_t this, uint32_t value);
