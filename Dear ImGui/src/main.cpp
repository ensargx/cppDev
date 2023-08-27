#include "gui.h"

#include <thread>

int __stdcall wWinMain(
    HINSTANCE instance,
    HINSTANCE previousInstance,
    PWSTR arguments,
    int commandShow)
{
    // Create Gui
    gui::CreateHWindow("Menu", "class");
    gui::CreateDevice();
    gui::CreateImGui();

    while (!gui::exit)
    {
        gui::BeginRender();
        gui::Render();
        gui::EndRender();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // Destroy Gui
    gui::DestroyImGui();
    gui::DestroyDevice();
    gui::DestroyHWindow();

    return EXIT_SUCCESS;
}
