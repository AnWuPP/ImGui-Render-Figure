#pragma once

#include "CFigure.hpp"
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include <variant>

struct CDraw {
    virtual ~CDraw() = default;
    virtual void Draw() = 0;
};

struct CDrawRect : CDraw {
    CRect rect;
    CDrawRect(uint32_t width, uint32_t height, uint32_t color);
    CDrawRect(uint32_t width, uint32_t height);
    void Draw() override;
};
struct CDrawTriangle : CDraw {
    CTriangle triangle;
    CDrawTriangle(uint32_t width, uint32_t height, uint32_t color);
    CDrawTriangle(uint32_t width, uint32_t height);
    void Draw() override;
};
struct CDrawCircle : CDraw {
    CCircle circle;
    CDrawCircle(uint32_t radius, uint32_t color);
    CDrawCircle(uint32_t radius);
    void Draw() override;
};

class CGui {
public:
    CGui();
    ~CGui();
    void RenderWindow();
    bool IsWindowOpen();
    template<class T>
    std::shared_ptr<T> AddFigure(uint32_t width, uint32_t height, uint32_t color);
    template<class T>
    std::shared_ptr<T> AddFigure(uint32_t radius, uint32_t color);
    template<class T>
    std::shared_ptr<T> AddFigure(uint32_t radius);

    // figuries render
    void Draw(CRect& rect);
    void Draw(CTriangle& triangle);
    void Draw(CCircle& circle);
private:
	GLFWwindow* window_;
    std::vector<std::shared_ptr<CDraw>> figuries_;
};