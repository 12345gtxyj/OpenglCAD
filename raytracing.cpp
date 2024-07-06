#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

#include "Model.h"

//imgui
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_glfw.h"

#include <windows.h>
#include "Application.h"



unsigned int FBO = 0;
unsigned int vao, vbo;
unsigned int trianglesTextureBuffer;
unsigned int lastFrame;

glm::mat4 projMat;
#pragma region Camera Declare
Camera camera(glm::vec3(0, 0, -5), 0, 0, glm::vec3(0, 1, 0));
#pragma endregion
int width = 512;
int height = 512;
#pragma region INputDeclare
float lastX;
float lastY;
bool firstMouse = true;
// 记录鼠标按钮状态的变量
bool mouse_button_pressed = false;
void PrepareRender(Shader* testShader, Model& testModel);
Application app;
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // 清空颜色缓冲区和深度缓冲区
        app.frameCounter = 0;
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, lastFrame, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
struct Triangle_encoded {
    glm::vec3 p1, p2, p3;    // 顶点坐标
    glm::vec3 n1, n2, n3;    // 顶点法线
    glm::vec3 emissive;      // 自发光参数
    glm::vec3 baseColor;     // 颜色
    glm::vec3 param1;        // (subsurface, metallic, specular)
    glm::vec3 param2;        // (specularTint, roughness, anisotropic)
    glm::vec3 param3;        // (sheen, sheenTint, clearcoat)
    glm::vec3 param4;        // (clearcoatGloss, IOR, transmission)
};
#pragma endregion

void bindData(bool finalPass = false) {
    // 创建并绑定帧缓冲对象和纹理
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glGenTextures(1, &lastFrame);
    glBindTexture(GL_TEXTURE_2D, lastFrame);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, lastFrame, 0);


    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    std::vector<glm::vec3> square = { glm::vec3(-1, -1, 0), glm::vec3(1, -1, 0), glm::vec3(-1, 1, 0), glm::vec3(1, 1, 0), glm::vec3(-1, 1, 0), glm::vec3(1, -1, 0) };
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * square.size(), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * square.size(), &square[0]);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);   // layout (location = 0) 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

}
void draw(unsigned int program) {
    glUseProgram(program);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer is not complete!" << std::endl;
    }
    glBindVertexArray(vao);

    glViewport(0, 0, width, height);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(vao);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

int main()
{

#pragma region  openWindow
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    //初始化GLFW
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    //初始化GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to create GLEW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#pragma endregion


    Shader* testShader = new Shader("raytracing/vshader.vert", "raytracing/fshader.frag");
    Model testModel("cube/cube.obj");
    // 三角形数组
    std::vector<Triangle_encoded> triangles_encoded;
    cout << testModel.meshes[0].indices.size() << endl;
    for (int i = 0; i < testModel.meshes[0].indices.size(); i += 3)
    {
        Triangle_encoded triangle;
        triangle.p1 = testModel.meshes[0].vertices[testModel.meshes[0].indices[i]].Position;
        triangle.p2 = testModel.meshes[0].vertices[testModel.meshes[0].indices[i + 1]].Position;
        triangle.p3 = testModel.meshes[0].vertices[testModel.meshes[0].indices[i + 2]].Position;
        triangle.n1 = testModel.meshes[0].vertices[testModel.meshes[0].indices[i]].Normal;
        triangle.n2 = testModel.meshes[0].vertices[testModel.meshes[0].indices[i + 1]].Normal;
        triangle.n3 = testModel.meshes[0].vertices[testModel.meshes[0].indices[i + 2]].Normal;
        triangle.baseColor = glm::vec3(1, 0, 0);
        triangle.emissive = glm::vec3(0.5, 0, 0);
        triangles_encoded.push_back(triangle);
    }
    for (int i = 0; i < testModel.meshes[0].indices.size(); i += 3)
    {
        Triangle_encoded triangle;
        triangle.p1 = testModel.meshes[0].vertices[testModel.meshes[0].indices[i]].Position + glm::vec3(-1, -2.3, 0);
        triangle.p2 = testModel.meshes[0].vertices[testModel.meshes[0].indices[i + 1]].Position + glm::vec3(-1, -2.3, 0);
        triangle.p3 = testModel.meshes[0].vertices[testModel.meshes[0].indices[i + 2]].Position + glm::vec3(-1, -2.3, 0);
        triangle.n1 = testModel.meshes[0].vertices[testModel.meshes[0].indices[i]].Normal;
        triangle.n2 = testModel.meshes[0].vertices[testModel.meshes[0].indices[i + 1]].Normal;
        triangle.n3 = testModel.meshes[0].vertices[testModel.meshes[0].indices[i + 2]].Normal;
        triangle.baseColor = glm::vec3(0, 1, 0);
        triangle.emissive = glm::vec3(0, 0.5, 0);
        triangles_encoded.push_back(triangle);
    }
    unsigned int tbo0;
    glGenBuffers(1, &tbo0);
    glBindBuffer(GL_TEXTURE_BUFFER, tbo0);
    glBufferData(GL_TEXTURE_BUFFER, triangles_encoded.size() * sizeof(Triangle_encoded), &triangles_encoded[0], GL_STATIC_DRAW);
    glGenTextures(1, &trianglesTextureBuffer);
    glBindTexture(GL_TEXTURE_BUFFER, trianglesTextureBuffer);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB32F, tbo0);

  
    //
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_BUFFER, trianglesTextureBuffer);
    glUniform1i(glGetUniformLocation(testShader->ID, "triangles"), 0);
    //VBO绘制4个点需要传给VAO六个参数浪费性能，因此使用EBO（索引缓冲对象）

#pragma region Imgui

    app.Init(window);
    bindData();

#pragma endregion
    while (!glfwWindowShouldClose(window))//glfwWindowShouldClose判断用户关不关弹窗
    {
#pragma region Imgui
        app.RenderUI();
#pragma endregion

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//设置清屏颜色



        //开启深度测试
        glEnable(GL_DEPTH_TEST);

        ////这将会模拟我们没有启用深度测试时所得到的结果
      /*  glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);*/





        glStencilFunc(GL_ALWAYS, 1, 0xFF); // 所有的片段都应该更新模板缓冲
        glStencilMask(0xFF); // 启用模板缓冲写入

        PrepareRender(testShader, testModel);
        // testModel.Draw(*testShader);
       

        draw(testShader->ID);




        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);//交换用于在此渲染迭代期间渲染的颜色缓冲区(双缓冲区，防止屏幕撕裂doubleBuffer,前缓冲（最终输出的）后缓冲（绘制所有渲染命令）)
        glfwPollEvents();//检查是否触发了任何事件（如键盘输入或鼠标移动事件），更新窗口状态，并调用相应的函数（我们可以通过回调方法注册）
        //一般在最后一行获取输入，下一行的开始处理
        //processInput(window);
    }
    glfwTerminate();
    return 0;
}

void PrepareRender(Shader* testShader, Model& testModel)
{
    testShader->use();
    testShader->setVec3("eye", app.cameraPos);
    glm::mat4 cameraRotate = glm::lookAt(app.cameraPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));  // 相机注视着原点
    cameraRotate = inverse(cameraRotate);   // lookat 的逆矩阵将光线方向进行转换
    //glm::vec3 camRotation(camera.pitch, camera.yaw, 0);
    testShader->setMat4("cameraRotate", cameraRotate);
    testShader->setInt("width", width);
    testShader->setInt("height", height);
    testShader->setVec3("eye", app.cameraPos);
    testShader->setVec3("lightPos", app.lightPos);
    testShader->setInt("nTriangles", 2 * testModel.meshes[0].indices.size() / 3);
    testShader->setInt("frameCounter", app.frameCounter);// 传计数器用作随机种子
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, lastFrame);
    glUniform1i(glGetUniformLocation(testShader->ID, "lastFrame"), 2);



}