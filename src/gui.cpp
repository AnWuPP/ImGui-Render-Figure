#include "gui.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <format>

Gui::Gui() {
    if (!glfwInit()) {
		return;
    }
	mWindow = glfwCreateWindow(
		800,
		480,
		"Main window",
		NULL,
		NULL
	);
	if (mWindow == nullptr) {
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(mWindow);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");

    ImGuiIO& io = ImGui::GetIO();
    ImFontConfig font_config;
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\trebucbd.ttf", 16.0f, &font_config, io.Fonts->GetGlyphRangesCyrillic());

    // add figuries
    AddFigure<DrawRect>(40, 50, 0xCC00FFFF);
    AddFigure<DrawTriangle>(40, 50, 0xCC00FFFF);
    AddFigure<DrawCircle>(50);
}

template<class T>
std::shared_ptr<T> Gui::AddFigure(uint32_t width, uint32_t height, uint32_t color) {
    auto ptr = std::make_shared<T>(width, height, color);
    mFiguries.push_back(ptr);
    return ptr;
}

template<class T>
std::shared_ptr<T> Gui::AddFigure(uint32_t radius, uint32_t color) {
    auto ptr = std::make_shared<T>(radius, color);
    mFiguries.push_back(ptr);
    return ptr;
}

template<class T>
std::shared_ptr<T> Gui::AddFigure(uint32_t radius) {
    auto ptr = std::make_shared<T>(radius);
    mFiguries.push_back(ptr);
    return ptr;
}

Gui::~Gui() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool Gui::IsWindowOpen() const {
    return mWindow != nullptr && !glfwWindowShouldClose(mWindow);
}

void Gui::ClearFiguries() {
    mFiguries.clear();
}

void Gui::RenderWindow() {
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
    static const char* colors[] = { "red", "green", "blue", "white" };
    static uint32_t colorInteger[] = { 0xFF0000FF, 0xFF00FF00, 0xFFFF0000, 0xFFFFFFFF };
    static int currentItem = 0;
    static int currentColor = 3;
    ImGui::PushItemWidth(140.f);
    ImGui::Combo("##combo", &currentItem, items, IM_ARRAYSIZE(items));
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::PushItemWidth(140.f);
    ImGui::Combo("##color", &currentColor, colors, IM_ARRAYSIZE(colors));
    ImGui::PopItemWidth();
    ImGui::SameLine();
    if (ImGui::Button("Add figure")) {
        if (currentItem == 0) {
            AddFigure<DrawRect>(80, 80, colorInteger[currentColor]);
        }
        else if (currentItem == 1) {
            AddFigure<DrawTriangle>(80, 80, colorInteger[currentColor]);
        }
        else if (currentItem == 2) {
            AddFigure<DrawCircle>(40, colorInteger[currentColor]);
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Clear")) {
        ClearFiguries();
    }
    ImGui::BeginChild("##figuries", ImVec2(0, 0), true);
    if (!mFiguries.empty()) {
        uint32_t count = 0;
        for (auto &f : mFiguries) {
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
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}