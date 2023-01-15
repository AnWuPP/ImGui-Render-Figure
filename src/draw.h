#pragma once

#include "figure.h"
#include <memory>

struct BaseDraw {
    virtual ~BaseDraw() = default;
    virtual void Draw() const = 0;
};

struct DrawRect : BaseDraw {
    Rect rect;
    DrawRect(uint32_t width, uint32_t height, uint32_t color);
    DrawRect(uint32_t width, uint32_t height);
    void Draw() const override;
};
struct DrawTriangle : BaseDraw {
    Triangle triangle;
    DrawTriangle(uint32_t width, uint32_t height, uint32_t color);
    DrawTriangle(uint32_t width, uint32_t height);
    void Draw() const override;
};
struct DrawCircle : BaseDraw {
    Circle circle;
    DrawCircle(uint32_t radius, uint32_t color);
    DrawCircle(uint32_t radius);
    void Draw() const override;
};