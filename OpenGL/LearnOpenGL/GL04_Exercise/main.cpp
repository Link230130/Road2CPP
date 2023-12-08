#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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
// 顶点着色器
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// 片段着色器
const char *fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.2f, 0.2f, 1.0f);\n"
"}\n\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
"}\n\0";

// 顶点数据
float vertices[] = {
    -0.5f,0.5f,0.0f,
    -0.75f,-0.5f,0.0f,
    -0.25,-0.5f,0.0,
    0.5f,0.5f,0.0f,
    0.75f,-0.5f,0.0f,
    0.25,-0.5f,0.0,
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
    GLFWwindow* pWindow = glfwCreateWindow(800, 600, "OpenGL_Triangle", nullptr, nullptr);
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

    /* 创建和编译着色器程序 */
    // 1.顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    int success = 0;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "Vertex shader compile failed!-->" << infoLog << std::endl;
    }

    // 2.片段着色器
    unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, nullptr);
    glCompileShader(fragmentShader1);
    glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader1, 512, nullptr, infoLog);
        std::cout << "Fragment shader compile failed!-->" << infoLog << std::endl;
    }
    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, nullptr);
    glCompileShader(fragmentShader2);
    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader2, 512, nullptr, infoLog);
        std::cout << "Fragment shader compile failed!-->" << infoLog << std::endl;
    }
    

    // 3.链接顶点和片段着色器
    unsigned int shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);

    glLinkProgram(shaderProgram1);
    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram1, 512, nullptr, infoLog);
        std::cout << "Shader program link failed!-->" << infoLog << std::endl;
    }

    unsigned int shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram2, 512, nullptr, infoLog);
        std::cout << "Shader program link failed!-->" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);
    glDeleteShader(fragmentShader2);

    // 4.设置顶点数据和顶点属性
    unsigned int VBO[2];
    unsigned int VAO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glBindVertexArray(VAO[0]);
    // 绑定缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    // 填充顶点数据到OpenGL的Array缓冲区
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)(3 * 3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    
    // 解绑VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // 解绑VAO
    glBindVertexArray(0);

    // 注册窗口回调函数
    glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);

    // 创建渲染循环
    while (!glfwWindowShouldClose(pWindow))
    {
        // 处理键盘输入
        processInput(pWindow);

        // 自定义清空屏幕的颜色缓冲，当调用glClear()后将使用glClearColor中的颜色填充屏幕
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 5. 渲染顶点数据
        glUseProgram(shaderProgram1);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);   // 绘制第一个三角形

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);   // 绘制第二个三角形

        glBindVertexArray(0);

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    // 释放资源 
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteShader(shaderProgram1);
    glDeleteShader(shaderProgram2);

    // 释放资源
    glfwTerminate();

    return 0;
}