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



#pragma region Model Data
float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
#pragma endregion

#pragma region Camera Declare
Camera camera(glm::vec3(0, 0,-5),0, 0, glm::vec3(0, 1, 0));
#pragma endregion

#pragma region INputDeclare
float lastX;
float lastY;
bool firstMouse = true;
// 记录鼠标按钮状态的变量
bool mouse_button_pressed = false;
unsigned int loadTexture(char const* path);
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.speedZ = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.speedZ = -1.0f;
    }
    else {
        camera.speedZ = 0;
    }
    float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.Position += cameraSpeed * camera.Forward;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.Position -= cameraSpeed * camera.Forward;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.Position -= glm::normalize(glm::cross(camera.Forward, camera.Up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.Position += glm::normalize(glm::cross(camera.Forward, camera.Up)) * cameraSpeed;

}
// 鼠标移动回调函数
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (mouse_button_pressed) {
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float deltaX = xpos - lastX;
        float deltaY = ypos - lastY;

        lastX = xpos;
        lastY = ypos;

        // 调用你的摄像机处理函数
        camera.ProcessMouseMovement(deltaX, deltaY);
    }
}

// 鼠标按钮回调函数
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            mouse_button_pressed = true;
        }
        else if (action == GLFW_RELEASE) {
            mouse_button_pressed = false;
            firstMouse = true; // 当按钮释放时重置 firstMouse 以避免跳动
        }
    }
}
#pragma endregion

   
unsigned int LoadImageToGPU(const char* filename,GLint internalFormat,GLenum format,int textureSlot)
{
    unsigned int textureBuffer;
    glGenTextures(1, &textureBuffer);
    glActiveTexture(GL_TEXTURE0+textureSlot);
    glBindTexture(GL_TEXTURE_2D, textureBuffer);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return textureBuffer;
}


int main()
{
    
#pragma region  openWindow
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    

    //初始化GLFW
    GLFWwindow* window = glfwCreateWindow(800,600,"LearnOpenGL",NULL,NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //隐藏游标
   // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //鼠标点击事件回调
    // 设置鼠标移动回调函数
    glfwSetCursorPosCallback(window, cursor_position_callback);

    // 设置鼠标按钮回调函数
    glfwSetMouseButtonCallback(window, mouse_button_callback);
   
   
   //初始化GLEW
    glewExperimental = true;
    if (glewInit()!=GLEW_OK)
    {
        std::cout << "Failed to create GLEW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, 800, 600);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#pragma endregion

#pragma region  可选剔除正面
    //glEnable(GL_CULL_FACE);//开启面剔除
    //glCullFace(GL_FRONT);
#pragma endregion
   
    /// <summary>
    /// 应完成glfw初始化
    /// </summary>
    /// <returns></returns>


    



    Shader* testShader = new Shader("VertexSource.vert", "FragmentSource.frag");
    Shader* lightShader=new Shader("LightVert.vert", "LightFrag.frag ");


    Model testModel("nanosuit/nanosuit.obj");
#pragma region 以下步骤实现把数据传给GPU  包括绑定VAO，VBO，EBO

    unsigned int VAO;//VAO的作用就是顶点属性调用都会储存在这个VAO中
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;//VBO全名顶点缓冲对象（Vertex Buffer Object）,他主要的作用就是可以一次性的发送一大批顶点数据到显卡上，而不是每个顶点发送一次
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    unsigned int EBO;//索引缓冲对象
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
 
    //把图片颠倒过来
    stbi_set_flip_vertically_on_load(true);

#pragma region 加载纹理并绑定
    unsigned int textureA, textureB;
    textureA = LoadImageToGPU("container2.png", GL_RGBA, GL_RGBA, 0);
    //textureB = LoadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 0);
 
#pragma endregion

  //  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //它的第一个参数是我们要将数据复制到的缓冲区类型：当前绑定到目标的顶点缓冲区对象。第二个参数指定要传递给缓冲区的数据大小（以字节为单位）;一个简单的顶点数据就足够了。第三个参数是我们要发送的实际数据。
   //VBO操作
     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



#pragma endregion


#pragma region 编译着色器并绑定(硬编码时使用)

   // //编译顶点着色器
   // unsigned int vertexShader;
   // vertexShader = glCreateShader(GL_VERTEX_SHADER);
   ////glShaderSource 函数将要编译到的着色器对象作为其第一个参数。第二个参数指定我们作为源代码传递的字符串数，只有一个。第三个参数是顶点着色器的实际源代码，我们可以将第 4 个参数留给 。NULL
   // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
   // glCompileShader(vertexShader);

   // //编译片元着色器
   // unsigned int fragmentShader;
   // fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
   // glCompileShader(fragmentShader);

   // //把顶点着色器和片元着色器绑定到程序上
   // unsigned int shaderProgram;
   // shaderProgram = glCreateProgram();//glCreateProgram 函数创建一个程序，并返回对新创建的程序对象的 ID 引用。现在我们需要将之前编译的着色器附加到程序对象，然后将它们与 glLinkProgram 链接
   // glAttachShader(shaderProgram, vertexShader);
   // glAttachShader(shaderProgram, fragmentShader);
   // glLinkProgram(shaderProgram);
#pragma endregion


 // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,8* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //法线
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // uv属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    /*unsigned int  textureC = LoadImageToGPU("container2.png", GL_RGBA, GL_RGBA, 0);
    unsigned int  textureD = LoadImageToGPU("container2_specular.png", GL_RGBA, GL_RGBA, 1);*/

    // 在此之前不要忘记首先 use 对应的着色器程序（来设定uniform）
    testShader->use();
    testShader->setVec3("objectColor", 0.5f, 0.5f, 0.5f);
    testShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    testShader->setVec3("specularColor", 1.0f, 1.0f, 1.0f);
    testShader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    testShader->setInt("material.diffuse",0);
    testShader->setInt("material.specular",1);
    testShader->setFloat("material.shininess", 32.0f);
    testShader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    testShader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // 将光照调暗了一些以搭配场景
    testShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
#pragma region Prepare MVP matrices
 ///变换操作
    glm::mat4 trans;
    glm::mat4 modelMat;
    glm::vec3 personPos(0.0f, -10.0f, 10.0f);
    modelMat= glm::translate(modelMat, personPos);
    glm::mat4 modelMat1;
    modelMat1 = glm::rotate(modelMat1, glm::radians(0.0f), glm::vec3(0, 1.0, 1.0));
    modelMat1 = glm::scale(modelMat1, glm::vec3(1.1, 1.1, 1.1));
    glm::mat4 viewMat;
   // viewMat=glm::translate(trans, glm::vec3(0, 0, -3.0f));
    glm::mat4 projMat;
    projMat = glm::perspective(glm::radians(45.0f), (float)800/ (float)600, 0.1f, 100.0f);   
     //由相机计算的viewmat
    viewMat = camera.GetViewMatrix();


    //灯
    glm::vec3 lightPos(0.0f, 1.0f,0.0f);
    glm::mat4 model = glm::mat4();
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f));
#pragma endregion

    //VBO绘制4个点需要传给VAO六个参数浪费性能，因此使用EBO（索引缓冲对象）

#pragma region Imgui
      // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  
#pragma endregion
    while (!glfwWindowShouldClose(window))//glfwWindowShouldClose判断用户关不关弹窗
    {
#pragma region Imgui
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ///*
        //* 添加自己的代码,App的实现见下面的代码
        //*/
     
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }
        //App::RenderUI();

        //// Rendering
        ImGui::Render();
#pragma endregion



        //处理输入
        processInput(window);
        //camera.UpdateCameraPos();
        viewMat = camera.GetViewMatrix();
        //清屏
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);//设置清屏颜色

        lightShader->use();
        testShader->use();

        //开启深度测试
        glEnable(GL_DEPTH_TEST);

        ////这将会模拟我们没有启用深度测试时所得到的结果
      /*  glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);*/


        //启用模板测试，并设置测试通过或失败时的行为：
        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);


        //清屏
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

       

            glStencilFunc(GL_ALWAYS, 1, 0xFF); // 所有的片段都应该更新模板缓冲
            glStencilMask(0xFF); // 启用模板缓冲写入


            testShader->setVec3("viewPos", camera.Position);
            testShader->setVec3("lightPos", lightPos);
            glUniform1i(glGetUniformLocation(testShader->ID, "ourTexture"), 0); // 手动设置
            glUniform1i(glGetUniformLocation(testShader->ID, "ourFace"), 4); // 手动设置
            glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
            glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
            //testShader->setMat4("model", model);
            testModel.Draw(*testShader);

              //  Set Model
            glBindVertexArray(VAO);
            //DrawCall
            glDrawArrays(GL_TRIANGLES, 0, 36);

           // 第二个cube
            lightShader->use();
            lightShader->setVec3("viewPos", camera.Position);
            lightShader->setVec3("lightPos", lightPos);
            glUniformMatrix4fv(glGetUniformLocation(lightShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat1));
            glUniformMatrix4fv(glGetUniformLocation(lightShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(lightShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
            // testShader->setMat4("model", model);

           
            //   //  Set Model
            //glBindVertexArray(VAO);
            ////DrawCall
            //glDrawArrays(GL_TRIANGLES, 0, 36);
            glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
            glStencilMask(0x00);
            glDisable(GL_DEPTH_TEST);
#pragma region 光照
            //unsigned int lightVAO;
            //glGenVertexArrays(1, &lightVAO);
            //glBindVertexArray(lightVAO);
            //// 只需要绑定VBO不用再次设置VBO的数据，因为箱子的VBO数据中已经包含了正确的立方体顶点数据
            //glBindBuffer(GL_ARRAY_BUFFER, VBO);
            //// 设置灯立方体的顶点属性（对我们的灯来说仅仅只有位置数据）
            //glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            //glEnableVertexAttribArray(6);

            //lightShader->use();
            //glUniformMatrix4fv(glGetUniformLocation(lightShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat1));
            //glUniformMatrix4fv(glGetUniformLocation(lightShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            //glUniformMatrix4fv(glGetUniformLocation(lightShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
            //glBindVertexArray(lightVAO);
            //glDrawArrays(GL_TRIANGLES, 0, 36);


            //glStencilMask(0xFF);
            //glEnable(GL_DEPTH_TEST);
#pragma endregion
       
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);//交换用于在此渲染迭代期间渲染的颜色缓冲区(双缓冲区，防止屏幕撕裂doubleBuffer,前缓冲（最终输出的）后缓冲（绘制所有渲染命令）)
        glfwPollEvents();//检查是否触发了任何事件（如键盘输入或鼠标移动事件），更新窗口状态，并调用相应的函数（我们可以通过回调方法注册）
        //一般在最后一行获取输入，下一行的开始处理
        //processInput(window);
    } 
    glfwTerminate();
    return 0;
}
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
