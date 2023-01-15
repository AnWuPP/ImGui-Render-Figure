#include "draw.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

DrawRect::DrawRect(uint32_t width, uint32_t height, uint32_t color) : rect(width, height, color) { }
DrawRect::DrawRect(uint32_t width, uint32_t height) : rect(width, height) { }
void DrawRect::Draw() const {
    auto drawList = ImGui::GetWindowDrawList();
    auto pos = ImGui::GetCursorScreenPos();
    drawList->AddRectFilled(pos, ImVec2(pos.x + rect.size.x, pos.y + rect.size.y), rect.color);
    ImGui::Dummy(ImVec2(rect.size.x, rect.size.y));
}

DrawTriangle::DrawTriangle(uint32_t width, uint32_t height, uint32_t color) : triangle(width, height, color) { }
DrawTriangle::DrawTriangle(uint32_t width, uint32_t height) : triangle(width, height) { }
void DrawTriangle::Draw() const {
    auto drawList = ImGui::GetWindowDrawList();
    auto pos = ImGui::GetCursorScreenPos();

    drawList->AddTriangleFilled(ImVec2(pos.x, pos.y + triangle.size.y),
        ImVec2(pos.x + triangle.size.x / 2.f, pos.y),
        ImVec2(pos.x + triangle.size.x, pos.y + triangle.size.y),
        triangle.color
        );
    ImGui::Dummy(ImVec2(triangle.size.x, triangle.size.y));
}

DrawCircle::DrawCircle(uint32_t radius, uint32_t color) : circle(radius, color) { }
DrawCircle::DrawCircle(uint32_t radius) : circle(radius) { }
void DrawCircle::Draw() const {
    auto drawList = ImGui::GetWindowDrawList();
    auto pos = ImGui::GetCursorScreenPos();

    drawList->AddCircleFilled(ImVec2(pos.x + circle.radius, pos.y + circle.radius),
        circle.radius,
        circle.color
        );
    ImGui::Dummy(ImVec2(circle.radius * 2, circle.radius * 2));
}