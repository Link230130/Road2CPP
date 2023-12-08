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
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

// ��������
float vertices[] = {
    0.5f, 0.5f, 0.0f,   // ���Ͻ�
    0.5f, -0.5f, 0.0f,  // ���½�
    -0.5f, -0.5f, 0.0f, // ���½�
    -0.5f, 0.5f, 0.0f   // ���Ͻ�
};

unsigned int indices[] = {
    // ע��������0��ʼ! 
    // ����������(0,1,2,3)���Ƕ�������vertices���±꣬
    // �����������±��������ϳɾ���

    0, 1, 3, // ��һ��������
    1, 2, 3  // �ڶ���������
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
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Fragment shader compile failed!-->" << infoLog << std::endl;
    }

    // 3.���Ӷ����Ƭ����ɫ��
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "Shader program link failed!-->" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 4.���ö������ݺͶ�������
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    // �󶨻�����
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // ��䶥�����ݵ�OpenGL��Array������
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ��EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // ���EBO����
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
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
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        glBindVertexArray(0);

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }
    
    // �ͷ���Դ 
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteShader(shaderProgram);

    // �ͷ���Դ
    glfwTerminate();

    return 0;
}