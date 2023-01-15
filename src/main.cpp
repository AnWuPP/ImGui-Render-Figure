#include "Gui.h"

int main() {
    // For demonstration, we will do without a control class, only an interface
    Gui gui;
    
    while(gui.IsWindowOpen()) {
        gui.RenderWindow();
    }
    return 0;
}