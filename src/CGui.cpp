#include "CGui.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <format>

CDrawRect::CDrawRect(uint32_t width, uint32_t height, uint32_t color) : rect(width, height, color) { }
CDrawRect::CDrawRect(uint32_t width, uint32_t height) : rect(width, height) { }
void CDrawRect::Draw() {
    auto drawList = ImGui::GetWindowDrawList();
    auto pos = ImGui::GetCursorScreenPos();
    drawList->AddRectFilled(pos, ImVec2(pos.x + rect.size.x, pos.y + rect.size.y), rect.color);
    ImGui::Dummy(ImVec2(rect.size.x, rect.size.y));
}

CDrawTriangle::CDrawTriangle(uint32_t width, uint32_t height, uint32_t color) : triangle(width, height, color) { }
CDrawTriangle::CDrawTriangle(uint32_t width, uint32_t height) : triangle(width, height) { }
void CDrawTriangle::Draw() {
    auto drawList = ImGui::GetWindowDrawList();
    auto pos = ImGui::GetCursorScreenPos();

    drawList->AddTriangleFilled(ImVec2(pos.x, pos.y + triangle.size.y),
        ImVec2(pos.x + triangle.size.x / 2.f, pos.y),
        ImVec2(pos.x + triangle.size.x, pos.y + triangle.size.y),
        triangle.color
        );
    ImGui::Dummy(ImVec2(triangle.size.x, triangle.size.y));
}

CDrawCircle::CDrawCircle(uint32_t radius, uint32_t color) : circle(radius, color) { }
CDrawCircle::CDrawCircle(uint32_t radius) : circle(radius) { }
void CDrawCircle::Draw() {
    auto drawList = ImGui::GetWindowDrawList();
    auto pos = ImGui::GetCursorScreenPos();

    drawList->AddCircleFilled(ImVec2(pos.x + circle.radius, pos.y + circle.radius),
        circle.radius,
        circle.color
        );
    ImGui::Dummy(ImVec2(circle.radius * 2, circle.radius * 2));
}

CGui::CGui() {
    if (!glfwInit()) {
		return;
    }
	window_ = glfwCreateWindow(
		800,
		480,
		"Main window",
		NULL,
		NULL
	);
	if (window_ == nullptr) {
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window_);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window_, true);
	ImGui_ImplOpenGL3_Init("#version 330");

    ImGuiIO& io = ImGui::GetIO();
    ImFontConfig font_config;
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\trebucbd.ttf", 16.0f, &font_config, io.Fonts->GetGlyphRangesCyrillic());

    // add figuries
    AddFigure<CDrawRect>(40, 50, 0xCC00FFFF);
    AddFigure<CDrawTriangle>(40, 50, 0xCC00FFFF);
    AddFigure<CDrawCircle>(50);
}

template<class T>
std::shared_ptr<T> CGui::AddFigure(uint32_t width, uint32_t height, uint32_t color) {
    auto ptr = std::make_shared<T>(width, height, color);
    figuries_.push_back(ptr);
    return ptr;
}

template<class T>
std::shared_ptr<T> CGui::AddFigure(uint32_t radius, uint32_t color) {
    auto ptr = std::make_shared<T>(radius, color);
    figuries_.push_back(ptr);
    return ptr;
}

template<class T>
std::shared_ptr<T> CGui::AddFigure(uint32_t radius) {
    auto ptr = std::make_shared<T>(radius);
    figuries_.push_back(ptr);
    return ptr;
}

CGui::~CGui() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool CGui::IsWindowOpen() {
    return window_ != nullptr && !glfwWindowShouldClose(window_);
}

void CGui::RenderWindow() {
    if (!ImGui::GetCurrentContext()) {
        return;
    }
    // OpenGL cleares
    glClearColor(.0f, .0f, .0f, .0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Init new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Set ImGui position by GL window
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    // Window
    ImGui::Begin("##MainWindow", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    static const char* items[] = { "Rect", "Triangle", "Circle" };
    static int currentItem = 0;
    ImGui::Combo("##combo", &currentItem, items, IM_ARRAYSIZE(items));
    ImGui::SameLine();
    if (ImGui::Button("Add figure")) {
        if (currentItem == 0) {
            AddFigure<CDrawRect>(80, 80, 0xFF505050 + figuries_.size() * 10);
        }
        else if (currentItem == 1) {
            AddFigure<CDrawTriangle>(80, 80, 0xFF505050 + figuries_.size() * 10);
        }
        else if (currentItem == 2) {
            AddFigure<CDrawCircle>(40, 0xFF505050 + figuries_.size() * 10);
        }
    }
    ImGui::BeginChild("##figuries", ImVec2(0, 0), true);
    if (!figuries_.empty()) {
        uint32_t count = 0;
        for (auto &f : figuries_) {
            f->Draw();
            count++;
            if (count % 8 != 0) {
                ImGui::SameLine();
            }
        }
    }
    ImGui::EndChild();

    ImGui::End();

    // ImGui go to render buffer
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // OpenGL buffer
    glfwSwapBuffers(window_);
    glfwPollEvents();
}