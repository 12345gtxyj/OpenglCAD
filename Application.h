#pragma once
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include <iostream>
#include <string>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Application {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec3 lightPos;
    glm::vec3 cameraPos;
    int frameCount = 0;
    bool isShowLightPos;
    bool isShowPos;
    bool isShowRot;
    bool isShowScale;
    bool isShowAlbedo;
    bool isRayTracing;
    std::string text;
    float metallic;
    float roughness;
    float ao;
    glm::vec3  albedo;
    Application(); // ¹¹Ôìº¯Êý

    void UpdateFPS();

    void Init(GLFWwindow* window);
    void RenderUI();
}
;