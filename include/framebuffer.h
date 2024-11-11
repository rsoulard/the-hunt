#pragma once

typedef struct FrameBuffer* frameBuffer_t;

frameBuffer_t FrameBuffer_New();
void FrameBuffer_Destroy(frameBuffer_t this);