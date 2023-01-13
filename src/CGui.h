#pragma once

#include "CFigure.hpp"
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include <variant>

class CGui {
public:
    CGui();
    ~CGui();
    void RenderWindow();
    bool IsWindowOpen();
    template<class T>
    void AddFigure(uint32_t width, uint32_t height, uint32_t color);
    template<class T>
    void AddFigure(uint32_t radius, uint32_t color);
    template<class T>
    void AddFigure(uint32_t radius);

    // figuries render
    void Draw(CRect& rect);
    void Draw(CTriangle& triangle);
    void Draw(CCircle& circle);
private:
	GLFWwindow* window_;
    std::vector<std::variant<CRect, CCircle, CTriangle>> figuries_;
};