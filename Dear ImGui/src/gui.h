#pragma once
#include <d3d9.h>

namespace gui
{
    // ImGui window size
    constexpr int WIDTH = 500;
    constexpr int HEIGHT = 300;
 
    inline bool exit = false;

    // winapi window vars
    inline HWND window = nullptr;
    inline WNDCLASSEX wc = { };

    // window movement vars
    inline POINTS position = { };

    // diretx vars
    inline LPDIRECT3D9 d3d = nullptr;
    inline LPDIRECT3DDEVICE9 device = nullptr;
    inline D3DPRESENT_PARAMETERS presentParameters = { };

    // Handle window creation and destruction
    void CreateHWindow(
        const char* title,
        const char* className
        ) noexcept;
    void DestroyHWindow() noexcept;

    // Handle device creation and destruction
    void CreateDevice() noexcept;
    void ResetDevice() noexcept;
    void DestroyDevice() noexcept;

    // Handle ImGui creation and destruction
    void CreateImGui() noexcept;
    void DestroyImGui() noexcept;

    void BeginRender() noexcept;
    void EndRender() noexcept;
    void Render() noexcept;
}