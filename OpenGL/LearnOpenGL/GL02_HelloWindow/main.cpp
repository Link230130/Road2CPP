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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,true);
    }
}

int main()
{
    // glfw ��ʼ��
    glfwInit();
    // ������Ҫ�ʹ�Ҫ�汾
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // �������ڶ���
    GLFWwindow* pWindow = glfwCreateWindow(800, 600, "OpenGL_Window", nullptr, nullptr);
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
    // �����ӿ�
    glViewport(0, 0, 800, 600);

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

        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    // �ͷ���Դ
    glfwTerminate();

    return 0;
}