#pragma once

#include <string>
#include <memory>

struct FSize {
    uint32_t x, y;
};

struct CBaseFigure {
    ~CBaseFigure() = default;

    uint32_t color;
    std::string title;
};

struct CRect : CBaseFigure {
    FSize size;
    CRect(uint32_t width, uint32_t height, uint32_t inColor) {
        size = {width, height};
        color = inColor;
    }
    CRect(uint32_t width, uint32_t height) {
        size = { width, height };
        color = 0xFFFFFFFF;
    }
};

struct CTriangle : CBaseFigure {
    FSize size;
    CTriangle(uint32_t width, uint32_t height, uint32_t inColor) {
        size = {width, height};
        color = inColor;
    }
    CTriangle(uint32_t width, uint32_t height) {
        size = { width, height };
        color = 0xFFFFFFFF;
    }
};

struct CCircle : CBaseFigure {
    uint32_t radius;
    CCircle(uint32_t inRadius, uint32_t inColor) {
        radius = inRadius;
        color = inColor;
    }
    CCircle(uint32_t inRadius) {
        radius = inRadius;
        color = 0xFFFFFFFF;
    }
};