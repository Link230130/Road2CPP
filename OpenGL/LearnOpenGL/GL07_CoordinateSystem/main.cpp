#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// 窗口刷新回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// 窗口输入处理
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

// 立方体顶点
float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

//float vertices[] = {
//    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};

unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

int main()
{
    // glfw 初始化
    glfwInit();
    // 设置主要和次要版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口对象
    GLFWwindow* pWindow = glfwCreateWindow(800, 600, "OpenGL_CoordinateSystem", nullptr, nullptr);
    if (pWindow == nullptr)
    {
        std::cout << "Create Window failed!\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD!\n";
        return -1;
    }

    CShader myShader("./shader.vs", "./shader.fs");

    // 4.设置顶点数据和顶点属性
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // 绑定缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 填充顶点数据到OpenGL的Array缓冲区
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 顶点坐标
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

    // 纹理坐标
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    /* 使用纹理 */
    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // 设置纹理对象的环绕方式和过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    int width = 0;
    int height = 0;
    int channels = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("../Resources/images/container.jpg", &width, &height, &channels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture image." << std::endl;
    }
    stbi_image_free(data);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    data = stbi_load("../Resources/images/awesomeface.png", &width, &height, &channels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture image." << std::endl;
    }
    stbi_image_free(data);

    myShader.use();
    // 为采样器绑定纹理单元
    myShader.setInt("texture1", 0);
    myShader.setInt("texture2", 1);


    // 解绑VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // 解绑VAO
    glBindVertexArray(0);

    // 注册窗口回调函数
    glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);
    // 开启深度测试
    glEnable(GL_DEPTH_TEST);

    myShader.use();

    // 创建模型矩阵，围绕X轴旋转（矩阵一定要初始化）
    glm::mat4 modelMat = glm::mat4(1.0f);
    //modelMat = glm::rotate(modelMat, glm::radians(-60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMat = glm::rotate(modelMat, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    // 创建观察矩阵，将场景后移(右手坐标系)
    glm::mat4 viewMat = glm::mat4(1.0f);
    viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));

    // 创建投影矩阵，实现透视效果
    glm::mat4 projectionMat = glm::mat4(1.0f);
    projectionMat = glm::perspective(glm::radians(45.0f), (float)800.0f / (float)600.0f, 0.1f, 100.0f);
    // 将矩阵传入着色器

    unsigned int matLoc = glGetUniformLocation(myShader.ID, "model");
    glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    unsigned int viewLoc = glGetUniformLocation(myShader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "projection"), 1, GL_FALSE, &projectionMat[0][0]);


    // 创建渲染循环
    while (!glfwWindowShouldClose(pWindow))
    {
        // 处理键盘输入
        processInput(pWindow);

        // 自定义清空屏幕的颜色缓冲，当调用glClear()后将使用glClearColor中的颜色填充屏幕
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        myShader.use();
        //modelMat = glm::rotate(modelMat, glm::sin((float)glfwGetTime())* glm::radians(1.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        //glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
#if 0
        // 创建模型矩阵，围绕X轴旋转（矩阵一定要初始化）
        glm::mat4 modelMat = glm::mat4(1.0f);
        //modelMat = glm::rotate(modelMat, glm::radians(-60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        modelMat = glm::rotate(modelMat, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        // 创建观察矩阵，将场景后移(右手坐标系)
        glm::mat4 viewMat = glm::mat4(1.0f);
        viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));

        // 创建投影矩阵，实现透视效果
        glm::mat4 projectionMat = glm::mat4(1.0f);
        projectionMat = glm::perspective(glm::radians(45.0f), (float)800.0f / (float)600.0f, 0.1f, 100.0f);
        // 将矩阵传入着色器

        unsigned int matLoc = glGetUniformLocation(myShader.ID, "model");
        glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
        unsigned int viewLoc = glGetUniformLocation(myShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "projection"), 1, GL_FALSE, &projectionMat[0][0]);
#endif
        // 5. 渲染顶点数据
        glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        for (int nI = 0; nI < 10; nI++)
        {
            modelMat = glm::mat4(1.0f);
            modelMat = glm::translate(modelMat, cubePositions[nI]);
            modelMat = glm::rotate(modelMat, glm::sin((float)(glfwGetTime()))*glm::radians(50.0f*(nI+1))/*glm::radians(20.0f * nI)*/, glm::vec3(0.5f, 1.0f, 0.0f));
            
            glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //glBindVertexArray(0);

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    // 释放资源 
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // 释放资源
    glfwTerminate();

    return 0;
}