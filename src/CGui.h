#pragma once

#include "CFigure.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <vector>

class CGui {
public:
    CGui();
    ~CGui();
    void renderWindow();
    bool isWindowOpen();
    template<class T>
    std::shared_ptr<T> addFigure(unsigned int width, unsigned int height, uint32_t color);
    template<class T>
    std::shared_ptr<T> addFigure(unsigned int raduis, uint32_t color);
private:
	GLFWwindow* window;
    std::vector<std::shared_ptr<CFigure>> figuries;
};