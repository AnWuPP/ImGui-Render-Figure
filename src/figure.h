#pragma once

#include <memory>

struct Size {
    uint32_t x, y;
};

struct BaseFigure {
    uint32_t color;
    ~BaseFigure() = default;
};

struct Rect : BaseFigure {
    Size size;
    Rect(uint32_t width, uint32_t height, uint32_t inColor);
    Rect(uint32_t width, uint32_t height);
};

struct Triangle : BaseFigure {
    Size size;
    Triangle(uint32_t width, uint32_t height, uint32_t inColor);
    Triangle(uint32_t width, uint32_t height);
};

struct Circle : BaseFigure {
    uint32_t radius;
    Circle(uint32_t inRadius, uint32_t inColor);
    Circle(uint32_t inRadius);
};