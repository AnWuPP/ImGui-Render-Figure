#include "CFigure.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// RECT
CRect::CRect(unsigned int inWidth, unsigned int inHegiht, uint32_t inColor) : 
    width(inWidth), height(inHegiht), color(inColor) { }

void CRect::draw() {
    auto drawList = ImGui::GetWindowDrawList();
    auto pos = ImGui::GetCursorScreenPos();
    drawList->AddRectFilled(pos, ImVec2(pos.x + width, pos.y + height), color);
    if (!title.empty()) {
        auto titleSize = ImGui::CalcTextSize(title.c_str());
        drawList->AddText(ImVec2(pos.x + width / 2.f - titleSize.x / 2, pos.y + height / 2.f - titleSize.y / 2.f),
            -1,
            title.c_str()
            );
    }
    ImGui::Dummy(ImVec2(width, height));
}

void CRect::setColor(uint32_t inColor) {
    color = inColor;
}

uint32_t CRect::getColor() {
    return color;
}

void CRect::setSize(unsigned int inWidth, unsigned int inHeight) {
    width = inWidth;
    height = inHeight;
}

std::tuple<unsigned int, unsigned int> CRect::getSize() {
    return std::make_tuple(width, height);
}

void CRect::setTitle(std::string_view inTitle) {
    title = inTitle;
}

std::string_view CRect::getTitle() {
    return title;
}

// TRIANGLE
CTriangle::CTriangle(unsigned int inWidth, unsigned int inHegiht, uint32_t inColor) : 
    width(inWidth), height(inHegiht), color(inColor) { }

void CTriangle::draw() {
    auto drawList = ImGui::GetWindowDrawList();
    auto pos = ImGui::GetCursorScreenPos();

    drawList->AddTriangleFilled(ImVec2(pos.x, pos.y + height),
        ImVec2(pos.x + width / 2.f, pos.y),
        ImVec2(pos.x + width, pos.y + height),
        color
        );
    if (!title.empty()) {
        auto titleSize = ImGui::CalcTextSize(title.c_str());
        drawList->AddText(ImVec2(pos.x + width / 2.f - titleSize.x / 2, pos.y + height / 2.f - titleSize.y / 2.f),
            -1,
            title.c_str()
            );
    }
    ImGui::Dummy(ImVec2(width, height));
}

void CTriangle::setColor(uint32_t inColor) {
    color = inColor;
}

uint32_t CTriangle::getColor() {
    return color;
}

void CTriangle::setSize(unsigned int inWidth, unsigned int inHeight) {
    width = inWidth;
    height = inHeight;
}

std::tuple<unsigned int, unsigned int> CTriangle::getSize() {
    return std::make_tuple(width, height);
}

void CTriangle::setTitle(std::string_view inTitle) {
    title = inTitle;
}

std::string_view CTriangle::getTitle() {
    return title;
}

// CIRCLE
CCircle::CCircle(unsigned int inRadius, uint32_t inColor) : 
    radius(inRadius), color(inColor) { }

void CCircle::draw() {
    auto drawList = ImGui::GetWindowDrawList();
    auto pos = ImGui::GetCursorScreenPos();

    drawList->AddCircleFilled(ImVec2(pos.x + radius, pos.y + radius),
        radius,
        color
        );
    if (!title.empty()) {
        auto titleSize = ImGui::CalcTextSize(title.c_str());
        drawList->AddText(ImVec2(pos.x + radius - titleSize.x / 2, pos.y + radius - titleSize.y / 2.f),
            -1,
            title.c_str()
            );
    }
    ImGui::Dummy(ImVec2(radius, radius));
}

void CCircle::setColor(uint32_t inColor) {
    color = inColor;
}

uint32_t CCircle::getColor() {
    return color;
}

void CCircle::setSize(unsigned int inRadius, unsigned int inRadiusTwo = 0) {
    radius = inRadius;
}

std::tuple<unsigned int, unsigned int> CCircle::getSize() {
    return std::make_tuple(radius, radius);
}

void CCircle::setTitle(std::string_view inTitle) {
    title = inTitle;
}

std::string_view CCircle::getTitle() {
    return title;
}