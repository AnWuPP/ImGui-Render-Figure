#include "CGui.h"
#include <format>

CGui::CGui() {
    if (!glfwInit()) {
		return;
    }
	window = glfwCreateWindow(
		800,
		480,
		"Main window",
		NULL,
		NULL
	);
	if (window == nullptr) {
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

    ImGuiIO& io = ImGui::GetIO();
    ImFontConfig font_config;
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\trebucbd.ttf", 16.0f, &font_config, io.Fonts->GetGlyphRangesCyrillic());

    // add figuries
    auto one = addFigure<CRect>(40, 50, 0xCC00FFFF);
    one->setTitle("Hello");
    auto two = addFigure<CRect>(150, 150, 0x0CFFCCFF);
    auto [w, h] = two->getSize();
    auto title = std::format("Size: {} x {}", w, h);
    two->setTitle(title);
    addFigure<CRect>(40, 50, -1);
    auto circle = addFigure<CCircle>(50, 0xFFFBFA00);
    circle->setTitle("Привет :)");
}

template<class T>
std::shared_ptr<T> CGui::addFigure(unsigned int width, unsigned int height, uint32_t color) {
    auto ptr = std::make_shared<T>(width, height, color);
    figuries.push_back(ptr);
    return ptr;
}

template<class T>
std::shared_ptr<T> CGui::addFigure(unsigned int radius, uint32_t color) {
    auto ptr = std::make_shared<T>(radius, color);
    figuries.push_back(ptr);
    return ptr;
}

CGui::~CGui() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool CGui::isWindowOpen() {
    return window != nullptr && !glfwWindowShouldClose(window);
}

void CGui::renderWindow() {
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

    if (!figuries.empty()) {
        for (auto &f : figuries) {
            f->draw();
        }
    }

    ImGui::End();

    // ImGui go to render buffer
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // OpenGL buffer
    glfwSwapBuffers(window);
    glfwPollEvents();
}