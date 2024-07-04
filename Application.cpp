#include "Application.h"

// 构造函数
Application::Application()
    : position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f),scale(1.0f,1.0f,1.0f), isShowPos(false), isShowRot(false), text("") {}

void Application::Init(GLFWwindow* window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


    //初始化light
    lightPos = glm::vec3(0,1,-1);
    scale = glm::vec3(0.1, 0.1, 0.1);
}

void Application::RenderUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 创建一个设置窗口
    ImGui::Begin("UI");

    // 按钮在单击时返回true（大多数小部件在编辑/激活时返回true）
    if (ImGui::Button("EditMode"))
    {
        // 单击事件处理程序
    }
    ImGui::Checkbox("LightPos", &isShowLightPos);
    if (isShowLightPos) {
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("x", &lightPos.x, -1.0f, 1.0f);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("y", &lightPos.y, -1.0f, 1.0f);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("z", &lightPos.z, -1.0f, 1.0f);
    }
    ImGui::Checkbox("Position", &isShowPos);
    if (isShowPos) {
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("x", &position.x, -1.0f, 1.0f);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("y", &position.y, -1.0f, 1.0f);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("z", &position.z, -1.0f, 1.0f);
    }

    ImGui::Checkbox("Rotation", &isShowRot);
    if (isShowRot) {
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("x", &rotation.x, 0.0f, 360.0f);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("y", &rotation.y, 0.0f, 360.0f);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("z", &rotation.z, 0.0f, 360.0f);
    }
    ImGui::Checkbox("Scale", &isShowScale);
    if (isShowScale) {
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("x", &scale.x, 0.0f, 0.1f);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("y", &scale.y, 0.0f, 0.1f);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("z", &scale.z, 0.0f, 0.1f);
    }
    ImGui::Checkbox("Albedo", &isShowAlbedo);
    if (isShowAlbedo) {
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("r", &albedo.x, 0.0f, 1.0f);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("g", &albedo.y, 0.0f, 1.0f);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::SliderFloat("b", &albedo.z, 0.0f, 1.0f);
    }
    ImGui::SetNextItemWidth(100);
    ImGui::SliderFloat("metallic", &metallic, 0.0f, 1.0f);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    ImGui::SliderFloat("roughness", &roughness, 0.0f, 1.0f);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    ImGui::SliderFloat("ao", &ao, 0.0f, 1.0f);
    ImGui::End();
    ImGui::Render();
}

