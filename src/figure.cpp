#include "figure.h"

Rect::Rect(uint32_t width, uint32_t height, uint32_t inColor) : BaseFigure({ inColor }), size({ width, height }) { }
Rect::Rect(uint32_t width, uint32_t height) : BaseFigure({ 0xFFFFFFFF }), size({ width, height }) { }

Triangle::Triangle(uint32_t width, uint32_t height, uint32_t inColor) : BaseFigure({ inColor }), size({ width, height }) { }
Triangle::Triangle(uint32_t width, uint32_t height) : BaseFigure({ 0xFFFFFFFF }), size({ width, height }) { }

Circle::Circle(uint32_t inRadius, uint32_t inColor) : BaseFigure({ inColor }), radius(inRadius) { }
Circle::Circle(uint32_t inRadius) : BaseFigure({ 0xFFFFFFFF }), radius(inRadius) { }