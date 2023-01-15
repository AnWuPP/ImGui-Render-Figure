#pragma once

#include "figure.h"
#include "draw.h"
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include <variant>

class Gui {
public:
    Gui();
    ~Gui();
    void RenderWindow();
    bool IsWindowOpen() const;
    template<class T>
    std::shared_ptr<T> AddFigure(uint32_t width, uint32_t height, uint32_t color);
    template<class T>
    std::shared_ptr<T> AddFigure(uint32_t radius, uint32_t color);
    template<class T>
    std::shared_ptr<T> AddFigure(uint32_t radius);
private:
	GLFWwindow* mWindow;
    std::vector<std::shared_ptr<BaseDraw>> mFiguries;
    void ClearFiguries();
};