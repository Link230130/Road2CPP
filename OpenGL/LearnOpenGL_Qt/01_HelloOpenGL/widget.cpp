#include "widget.h"

#include <QDebug>

// 顶点数据
float vertices[] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};

unsigned int indices[] = {
    // 注意索引从0开始!
    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    // 这样可以由下标代表顶点组合成矩形

    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

Widget::~Widget()
{
    makeCurrent();
    // 回收资源
    glDeleteBuffers(1,&VAO);
    glDeleteBuffers(1,&EBO);
    glDeleteVertexArrays(1,&VAO);
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();

    bool success = false;
    /* 创建和编译着色器程序 */
    unsigned int vertexShader = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/shader.vert");
    unsigned int fragmentShader = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/shader.frag");
    success = shaderProgram.link();
    if(!success)
    {
        qDebug() << "ERR:"<< shaderProgram.log();
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 设置顶点数据和顶点属性
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    // 绑定缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 填充顶点数据到OpenGL的Array缓冲区
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 绑定EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // 填充EBO数据
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 解绑VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // 解绑VAO
    glBindVertexArray(0);
}

void Widget::resizeGL(int w, int h)
{
}

void Widget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 自定义清空屏幕的颜色缓冲，当调用glClear()后将使用glClearColor中的颜色填充屏幕
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO);
    // 渲染顶点数据
    shaderProgram.bind();

    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

    glBindVertexArray(0);
}

