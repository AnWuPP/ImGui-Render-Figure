#include "CGui.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <format>
#include <functional>

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
    AddFigure<CRect>(40, 50, 0xCC00FFFF);
    AddFigure<CTriangle>(40, 50, 0xCC00FFFF);
    AddFigure<CCircle>(50);
}

template<class T>
void CGui::AddFigure(uint32_t width, uint32_t height, uint32_t color) {
    figuries_.push_back(T(width, height, color));
}

template<class T>
void CGui::AddFigure(uint32_t radius, uint32_t color) {
    figuries_.push_back(T(radius, color));
}

template<class T>
void CGui::AddFigure(uint32_t radius) {
    figuries_.push_back(T(radius));
}

CGui::~CGui() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool CGui::IsWindowOpen() {
    return window_ != nullptr && !glfwWindowShouldClose(window_);
}

void CGui::Draw(CRect& rect) {
    auto drawList = ImGui::GetWindowDrawList();
    auto pos = ImGui::GetCursorScreenPos();
    drawList->AddRectFilled(pos, ImVec2(pos.x + rect.size.x, pos.y + rect.size.y), rect.color);
    if (!rect.title.empty()) {
        auto titleSize = ImGui::CalcTextSize(rect.title.c_str());
        drawList->AddText(ImVec2(pos.x + rect.size.x / 2.f - titleSize.x / 2, pos.y + rect.size.y / 2.f - titleSize.y / 2.f),
            -1,
            rect.title.c_str()
            );
    }
    ImGui::Dummy(ImVec2(rect.size.x, rect.size.y));
}

void CGui::Draw(CTriangle& triangle) {
    auto drawList = ImGui::GetWindowDrawList();
    auto pos = ImGui::GetCursorScreenPos();

    drawList->AddTriangleFilled(ImVec2(pos.x, pos.y + triangle.size.y),
        ImVec2(pos.x + triangle.size.x / 2.f, pos.y),
        ImVec2(pos.x + triangle.size.x, pos.y + triangle.size.y),
        triangle.color
        );
    if (!triangle.title.empty()) {
        auto titleSize = ImGui::CalcTextSize(triangle.title.c_str());
        drawList->AddText(ImVec2(pos.x + triangle.size.x / 2.f - titleSize.x / 2, pos.y + triangle.size.y / 2.f - titleSize.y / 2.f),
            -1,
            triangle.title.c_str()
            );
    }
    ImGui::Dummy(ImVec2(triangle.size.x, triangle.size.y));
}

void CGui::Draw(CCircle& circle) {
    auto drawList = ImGui::GetWindowDrawList();
    auto pos = ImGui::GetCursorScreenPos();

    drawList->AddCircleFilled(ImVec2(pos.x + circle.radius, pos.y + circle.radius),
        circle.radius,
        circle.color
        );
    if (!circle.title.empty()) {
        auto titleSize = ImGui::CalcTextSize(circle.title.c_str());
        drawList->AddText(ImVec2(pos.x + circle.radius - titleSize.x / 2, pos.y + circle.radius - titleSize.y / 2.f),
            -1,
            circle.title.c_str()
            );
    }
    ImGui::Dummy(ImVec2(circle.radius, circle.radius));
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

    if (!figuries_.empty()) {
        for (auto &f : figuries_) {
            std::visit([this](auto& fi) { return Draw(fi); }, f);
        }
    }

    ImGui::End();

    // ImGui go to render buffer
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // OpenGL buffer
    glfwSwapBuffers(window_);
    glfwPollEvents();
}