#include "gui.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
    HWND window,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
);

long __stdcall WindowProcess(
    HWND window,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_SIZE: {
        if (gui::device && wParam != SIZE_MINIMIZED)
        {
            gui::presentParameters.BackBufferWidth = LOWORD(lParam);
            gui::presentParameters.BackBufferHeight = HIWORD(lParam);
            gui::ResetDevice();
        }
    } return 0;

    case WM_SYSCOMMAND: {
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
    } break;

    case WM_DESTROY: {
        PostQuitMessage(0);
    } return 0;
    
    case WM_LBUTTONDOWN: {
        gui::position = MAKEPOINTS(lParam);
    } return 0;
    
    case WM_MOUSEMOVE: {
        if (wParam == MK_LBUTTON)
        {
            const auto points = MAKEPOINTS(lParam);
            auto rect = ::RECT{ };

            GetWindowRect(window, &rect);

            rect.left += points.x - gui::position.x;
            rect.top += points.y - gui::position.y;

            if (gui::position.x >= 0 &&
                gui::position.x <= gui::WIDTH &&
                gui::position.y >= 0 &&
                gui::position.y <= 19)
                SetWindowPos(
                    gui::window,
                    HWND_TOPMOST,
                    rect.left,
                    rect.top,
                    0,
                    0,
                    SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
                );
        }
    } return 0;

    }

    return DefWindowProc(window, message, wParam, lParam);
}

void gui::CreateHWindow(
    const char* title,
    const char* className
) noexcept
{
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_CLASSDC;
    windowClass.lpfnWndProc = WindowProcess;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = GetModuleHandleA(0);
    windowClass.hIcon = 0;
    windowClass.hCursor = 0;
    windowClass.hbrBackground = 0;
    windowClass.lpszMenuName = 0;
    windowClass.lpszClassName = className;
    windowClass.hIconSm = 0;

    RegisterClassEx(&windowClass);

    window = CreateWindowA(
        className,
        title,
        WS_POPUP,
        100,
        100,
        WIDTH,
        HEIGHT,
        0,
        0,
        windowClass.hInstance,
        0
    );

    ShowWindow(window, SW_SHOWDEFAULT);
    UpdateWindow(window);
}

void gui::DestroyHWindow() noexcept
{
    DestroyWindow(window);
    UnregisterClassA(windowClass.lpszClassName, windowClass.hInstance);
}

bool gui::CreateDevice() noexcept
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);

    if (!d3d)
        return false;

    ZeroMemory(&presentParameters, sizeof(presentParameters));

    presentParameters.Windowed = TRUE;
    presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
    presentParameters.EnableAutoDepthStencil = TRUE;
    presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
    presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

    if (d3d->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        window,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &presentParameters,
        &device) < 0)
        return false;
    
    return true;
}
void gui::ResetDevice() noexcept
{
    ImGui_ImplDX9_InvalidateDeviceObjects();

    const auto result = device->Reset(&presentParameters);

    if (result == D3DERR_INVALIDCALL)
        IM_ASSERT(0);

    ImGui_ImplDX9_CreateDeviceObjects();
}
void gui::DestroyDevice() noexcept
{
    if (device)
    {
        device->Release();
        device = nullptr;
    }

    if (d3d)
    {
        d3d->Release();
        d3d = nullptr;
    }
}

void gui::CreateImGui() noexcept
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.IniFilename = NULL;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX9_Init(device);
}
void gui::DestroyImGui() noexcept
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void gui::BeginRender() noexcept
{
    MSG message;
    while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    // Start the Dear ImGui frame
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}
void gui::EndRender() noexcept
{
    ImGui::EndFrame();

    device->SetRenderState(D3DRS_ZENABLE, FALSE);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

    if (device->BeginScene() >= 0)
    {
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        device->EndScene();
    }

    const auto result = device->Present(nullptr, nullptr, nullptr, nullptr);

    // Handle loss of D3D9 device
    if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
        ResetDevice();
}
void gui::Render() noexcept
{
    ImGui::SetNextWindowPos({ 0, 0 });
    ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
    ImGui::Begin(
        "Test",
        &exit,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoMove);

    ImGui::Button("Test2");

    ImGui::End();
}