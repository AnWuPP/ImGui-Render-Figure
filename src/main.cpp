#include "CGui.h"

int main() {
    // For demonstration, we will do without a control class, only an interface
    CGui gui;
    
    while(gui.IsWindowOpen()) {
        gui.RenderWindow();
    }
    return 0;
}