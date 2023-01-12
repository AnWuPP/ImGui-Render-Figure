#pragma once
#include <string>
#include <string_view>
#include <memory>

class CFigure {
    unsigned int width;
    unsigned int height;
    uint32_t color;
    std::string title;
public:
    virtual ~CFigure() { };

    virtual void draw() = 0;
    virtual void setColor(uint32_t inColor) = 0;
    virtual uint32_t getColor() = 0;
    virtual void setSize(unsigned int inWidth, unsigned int inHeight) = 0;
    virtual std::tuple<unsigned int, unsigned int> getSize() = 0;
    virtual void setTitle(std::string_view inTitle) = 0;
    virtual std::string_view getTitle() = 0;
};

class CRect : public CFigure {
    unsigned int width;
    unsigned int height;
    uint32_t color;
    std::string title;
public:
    CRect(unsigned int inWidth, unsigned int inHegiht, uint32_t inColor);

    void draw() override;
    void setColor(uint32_t inColor) override;
    uint32_t getColor() override;
    void setSize(unsigned int inWidth, unsigned int inHeight) override;
    std::tuple<unsigned int, unsigned int> getSize() override;
    void setTitle(std::string_view inTitle) override;
    std::string_view getTitle() override;
};

class CTriangle : public CFigure {
    unsigned int width;
    unsigned int height;
    uint32_t color;
    std::string title;
public:
    CTriangle(unsigned int inWidth, unsigned int inHegiht, uint32_t inColor);

    void draw() override;
    void setColor(uint32_t inColor) override;
    uint32_t getColor() override;
    void setSize(unsigned int inWidth, unsigned int inHeight) override;
    std::tuple<unsigned int, unsigned int> getSize() override;
    void setTitle(std::string_view inTitle) override;
    std::string_view getTitle() override;
};

class CCircle : public CFigure {
    unsigned int radius;
    uint32_t color;
    std::string title;
public:
    CCircle(unsigned int inRadius, uint32_t inColor);

    void draw() override;
    void setColor(uint32_t inColor) override;
    uint32_t getColor() override;
    void setSize(unsigned int inWidth, unsigned int inHeight) override;
    std::tuple<unsigned int, unsigned int> getSize() override;
    void setTitle(std::string_view inTitle) override;
    std::string_view getTitle() override;
};