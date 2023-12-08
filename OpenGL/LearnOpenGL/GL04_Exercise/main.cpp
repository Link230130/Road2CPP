#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// ����ˢ�»ص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// �������봦��
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
// ������ɫ��
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Ƭ����ɫ��
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

// ��������
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
    // glfw ��ʼ��
    glfwInit();
    // ������Ҫ�ʹ�Ҫ�汾
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // �������ڶ���
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

    /* �����ͱ�����ɫ������ */
    // 1.������ɫ��
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

    // 2.Ƭ����ɫ��
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
    

    // 3.���Ӷ����Ƭ����ɫ��
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

    // 4.���ö������ݺͶ�������
    unsigned int VBO[2];
    unsigned int VAO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glBindVertexArray(VAO[0]);
    // �󶨻�����
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    // ��䶥�����ݵ�OpenGL��Array������
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)(3 * 3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    
    // ���VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // ���VAO
    glBindVertexArray(0);

    // ע�ᴰ�ڻص�����
    glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);

    // ������Ⱦѭ��
    while (!glfwWindowShouldClose(pWindow))
    {
        // �����������
        processInput(pWindow);

        // �Զ��������Ļ����ɫ���壬������glClear()��ʹ��glClearColor�е���ɫ�����Ļ
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 5. ��Ⱦ��������
        glUseProgram(shaderProgram1);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);   // ���Ƶ�һ��������

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);   // ���Ƶڶ���������

        glBindVertexArray(0);

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    // �ͷ���Դ 
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteShader(shaderProgram1);
    glDeleteShader(shaderProgram2);

    // �ͷ���Դ
    glfwTerminate();

    return 0;
}