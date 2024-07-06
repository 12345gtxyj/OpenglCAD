//#define GLEW_STATIC
//#include<GL/glew.h>
//#include<GLFW/glfw3.h>
//#include<iostream>
//#include "Shader.h"
//
//#define STB_IMAGE_IMPLEMENTATION
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include "Camera.h"
//
//#include "Model.h"
//
//#include <windows.h>
//#include "Application.h"
//
//glm::mat4 ModelMat();
//
//#pragma region Model Data
//
//#pragma endregion
//
//#pragma region Camera Declare
//Camera camera(glm::vec3(0, 0,-5),0, 0, glm::vec3(0, 1, 0));
//#pragma endregion
//
//#pragma region INputDeclare
//float lastX;
//float lastY;
//bool firstMouse = true;
//// 记录鼠标按钮状态的变量
//bool mouse_button_pressed = false;
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    float cameraSpeed = 0.05f; // adjust accordingly
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        camera.Position += camera.speed * camera.Up;
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        camera.Position -= camera.speed * camera.Up;
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        camera.Position -= glm::normalize(glm::cross(camera.Forward, camera.Up)) * camera.speed;
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        camera.Position += glm::normalize(glm::cross(camera.Forward, camera.Up)) * camera.speed;
//
//}
//// 鼠标移动回调函数
//void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
//    if (mouse_button_pressed) {
//        if (firstMouse) {
//            lastX = xpos;
//            lastY = ypos;
//            firstMouse = false;
//        }
//
//        float deltaX = xpos - lastX;
//        float deltaY = ypos - lastY;
//
//        lastX = xpos;
//        lastY = ypos;
//
//        // 调用你的摄像机处理函数
//        camera.ProcessMouseMovement(deltaX, deltaY);
//    }
//}
//
//// 鼠标按钮回调函数
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
//    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
//        if (action == GLFW_PRESS) {
//            mouse_button_pressed = true;
//        }
//        else if (action == GLFW_RELEASE) {
//            mouse_button_pressed = false;
//            firstMouse = true; // 当按钮释放时重置 firstMouse 以避免跳动
//        }
//    }
//}
////鼠标滚轮回调
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//
//    // 根据鼠标滚轮方向调整相机位置
//    float cameraSpeed = camera.speed * static_cast<float>(yoffset);
//    camera.Position += camera.Forward * cameraSpeed;
//}
//#pragma endregion
// 
//unsigned int LoadImageToGPU(const char* filename, int textureSlot)
//{
//    unsigned int textureBuffer;
//    glGenTextures(1, &textureBuffer);
//    glActiveTexture(GL_TEXTURE0 + textureSlot);
//    int width, height, nrComponents;
//    unsigned char* data = stbi_load(filename, &width, &height, &nrComponents, 0);
//    if (data)
//    {
//        GLenum imageFormat;
//        if (nrComponents == 1)
//            imageFormat = GL_RED;
//        else if (nrComponents == 3)
//            imageFormat = GL_RGB;
//        else if (nrComponents == 4)
//            imageFormat = GL_RGBA;
//        else
//            imageFormat = GL_RGB; // 默认格式
//
//        glBindTexture(GL_TEXTURE_2D, textureBuffer);
//        glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        stbi_image_free(data);
//    }
//    else
//    {
//        std::cout << "Failed to load texture: " << filename << std::endl;
//    }
//
//    return textureBuffer;
//}
//Application app;
//
//int main()
//{
//    
//#pragma region  openWindow
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    
//
//    //初始化GLFW
//    GLFWwindow* window = glfwCreateWindow(800,600,"LearnOpenGL",NULL,NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//
//    //隐藏游标
//   // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//    //鼠标点击事件回调
//    // 设置鼠标移动回调函数
//    glfwSetCursorPosCallback(window, cursor_position_callback);
//
//    // 设置鼠标按钮回调函数
//    glfwSetMouseButtonCallback(window, mouse_button_callback);
//   
//    // 注册鼠标滚轮回调函数
//    glfwSetScrollCallback(window, scroll_callback);
//   //初始化GLEW
//    glewExperimental = true;
//    if (glewInit()!=GLEW_OK)
//    {
//        std::cout << "Failed to create GLEW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glViewport(0, 0, 800, 600);
//   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//#pragma endregion
//
//#pragma region  可选剔除正面
//    //glEnable(GL_CULL_FACE);//开启面剔除
//    //glCullFace(GL_FRONT);
//#pragma endregion
//   
//
//    Shader* testShader = new Shader("PBR.vert", "PBR.frag");
//
//
//    Model testModel("nanosuit/nanosuit.obj");
//    Model lightModel("cube/cube.obj");
//#pragma region 以下步骤实现把数据传给GPU  包括绑定VAO，VBO，EBO
//
//    unsigned int VAO;//VAO的作用就是顶点属性调用都会储存在这个VAO中
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//
//    unsigned int VBO;//VBO全名顶点缓冲对象（Vertex Buffer Object）,他主要的作用就是可以一次性的发送一大批顶点数据到显卡上，而不是每个顶点发送一次
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//
//    unsigned int EBO;//索引缓冲对象
//    glGenBuffers(1, &EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
// 
//    //把图片颠倒过来
//    stbi_set_flip_vertically_on_load(true);
//    //cout << "加载" << endl;
//#pragma region 加载纹理并绑定
//    unsigned int textureA, textureB, textureC, textureD, textureE;
//    textureA = LoadImageToGPU("awesomeface.png",  0);
//    textureB = LoadImageToGPU("PBR/PBR_metallic.png", 1);
//    textureC = LoadImageToGPU("PBR/PBR_normal.png", 2);
//    textureD = LoadImageToGPU("PBR/PBR_roughness.png", 3);
//    textureE = LoadImageToGPU("PBR/PBR_uv.png", 4);
//#pragma endregion
//
//
//    //它的第一个参数是我们要将数据复制到的缓冲区类型：当前绑定到目标的顶点缓冲区对象。第二个参数指定要传递给缓冲区的数据大小（以字节为单位）;一个简单的顶点数据就足够了。第三个参数是我们要发送的实际数据。
//   //VBO操作
//
//
//
//#pragma endregion
//
//
//#pragma region 编译着色器并绑定(硬编码时使用)
//
//   // //编译顶点着色器
//   // unsigned int vertexShader;
//   // vertexShader = glCreateShader(GL_VERTEX_SHADER);
//   ////glShaderSource 函数将要编译到的着色器对象作为其第一个参数。第二个参数指定我们作为源代码传递的字符串数，只有一个。第三个参数是顶点着色器的实际源代码，我们可以将第 4 个参数留给 。NULL
//   // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//   // glCompileShader(vertexShader);
//
//   // //编译片元着色器
//   // unsigned int fragmentShader;
//   // fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//   // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//   // glCompileShader(fragmentShader);
//
//   // //把顶点着色器和片元着色器绑定到程序上
//   // unsigned int shaderProgram;
//   // shaderProgram = glCreateProgram();//glCreateProgram 函数创建一个程序，并返回对新创建的程序对象的 ID 引用。现在我们需要将之前编译的着色器附加到程序对象，然后将它们与 glLinkProgram 链接
//   // glAttachShader(shaderProgram, vertexShader);
//   // glAttachShader(shaderProgram, fragmentShader);
//   // glLinkProgram(shaderProgram);
//#pragma endregion
//
//
// // 位置属性
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,8* sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    //法线
//   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    // uv属性
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//    
//
//    // 在此之前不要忘记首先 use 对应的着色器程序（来设定uniform）
//  
//
//#pragma region Prepare MVP matrices
// ///变换操作
//    glm::mat4 projMat;
//    projMat = glm::perspective(glm::radians(45.0f), (float)800/ (float)600, 0.1f, 100.0f);   
//#pragma endregion
//
//    //VBO绘制4个点需要传给VAO六个参数浪费性能，因此使用EBO（索引缓冲对象）
//
//#pragma region Imgui
//  
//    app.Init(window);
//
//  
//#pragma endregion
//    while (!glfwWindowShouldClose(window))//glfwWindowShouldClose判断用户关不关弹窗
//    {
//#pragma region Imgui
//        app.RenderUI();
//#pragma endregion
//
//
//
//        //处理输入
//        processInput(window);
//        //camera.UpdateCameraPos();
//        //清屏
//        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);//设置清屏颜色
//        
//        testShader->use();
//
//        //开启深度测试
//        glEnable(GL_DEPTH_TEST);
//
//        ////这将会模拟我们没有启用深度测试时所得到的结果
//      /*  glEnable(GL_DEPTH_TEST);
//        glDepthFunc(GL_ALWAYS);*/
//
//
//        //启用模板测试，并设置测试通过或失败时的行为：
//        glEnable(GL_STENCIL_TEST);
//        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//
//
//        //清屏
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//
//       
//
//            glStencilFunc(GL_ALWAYS, 1, 0xFF); // 所有的片段都应该更新模板缓冲
//            glStencilMask(0xFF); // 启用模板缓冲写入
//
//            testShader->use();
//            testShader->setVec3("camPos", camera.Position);
//            testShader->setVec3("lightPos", app.lightPos);
//            glUniform1i(glGetUniformLocation(testShader->ID, "material.metallicMap"), 1); // 手动设置
//            glUniform1i(glGetUniformLocation(testShader->ID, "material.normalMap"), 2); // 手动设置
//            glUniform1i(glGetUniformLocation(testShader->ID, "material.roughnessMap"), 3); // 手动设置
//            glUniform1i(glGetUniformLocation(testShader->ID, "material.albedoMap"), 4); // 手动设置
//            glUniform1i(glGetUniformLocation(testShader->ID, "material.aoMap"), 4); // 手动设置
//            glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(ModelMat()));
//            glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
//            glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
//            //testShader->setMat4("model", model);
//            testModel.Draw(*testShader);
//
//
//            testShader->use();
//            testShader->setVec3("camPos", camera.Position);
//            testShader->setVec3("lightPos", app.lightPos);
//            glUniform1i(glGetUniformLocation(testShader->ID, "material.metallicMap"), 0); // 手动设置
//            glUniform1i(glGetUniformLocation(testShader->ID, "material.normalMap"), 0); // 手动设置
//            glUniform1i(glGetUniformLocation(testShader->ID, "material.roughnessMap"), 0); // 手动设置
//            glUniform1i(glGetUniformLocation(testShader->ID, "material.albedoMap"), 0); // 手动设置
//            glUniform1i(glGetUniformLocation(testShader->ID, "material.aoMap"), 0); // 手动设置
//            glm::mat4 lightM;
//            lightM= glm::scale(lightM, app.scale);
//            lightM = glm::translate(lightM, app.lightPos);
//            glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(lightM));
//            glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
//            glUniformMatrix4fv(glGetUniformLocation(testShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
//            //lightModel.Draw(*testShader);
//            //   //  Set Model
//            //glBindVertexArray(VAO);
//            ////DrawCall
//            //glDrawArrays(GL_TRIANGLES, 0, 36);
//            glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//            glStencilMask(0x00);
//            glDisable(GL_DEPTH_TEST);
//#pragma region 光照
//            //unsigned int lightVAO;
//            //glGenVertexArrays(1, &lightVAO);
//            //glBindVertexArray(lightVAO);
//            //// 只需要绑定VBO不用再次设置VBO的数据，因为箱子的VBO数据中已经包含了正确的立方体顶点数据
//            //glBindBuffer(GL_ARRAY_BUFFER, VBO);
//            //// 设置灯立方体的顶点属性（对我们的灯来说仅仅只有位置数据）
//            //glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//            //glEnableVertexAttribArray(6);
//
//            //lightShader->use();
//            //glUniformMatrix4fv(glGetUniformLocation(lightShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat1));
//            //glUniformMatrix4fv(glGetUniformLocation(lightShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
//            //glUniformMatrix4fv(glGetUniformLocation(lightShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
//            //glBindVertexArray(lightVAO);
//            //glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
//            //glStencilMask(0xFF);
//            //glEnable(GL_DEPTH_TEST);
//#pragma endregion
//       
//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//
//        glfwSwapBuffers(window);//交换用于在此渲染迭代期间渲染的颜色缓冲区(双缓冲区，防止屏幕撕裂doubleBuffer,前缓冲（最终输出的）后缓冲（绘制所有渲染命令）)
//        glfwPollEvents();//检查是否触发了任何事件（如键盘输入或鼠标移动事件），更新窗口状态，并调用相应的函数（我们可以通过回调方法注册）
//        //一般在最后一行获取输入，下一行的开始处理
//        //processInput(window);
//    } 
//    glfwTerminate();
//    return 0;
//}
//
//
//glm::mat4 ModelMat()
//{
//    // 设置模型矩阵
//    //先缩放再旋转再平移
//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::scale(model, app.scale);
//    model = glm::rotate(model, glm::radians(app.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
//    model = glm::rotate(model, glm::radians(app.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
//    model = glm::rotate(model, glm::radians(app.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
//    model = glm::translate(model,app.position);
//    
//    
//    return model;
//}
