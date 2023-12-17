#include "widget.h"
#include <QDebug>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define QOPENGL 0       // 使用Qt的类封装OpenGL函数

float vertices[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};

unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;
unsigned int texture;

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    ,textureWall(nullptr)
{
}

Widget::~Widget()
{
    makeCurrent();
    // 回收资源
    glDeleteBuffers(1,&EBO);
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
#if QOPENGL
    if(textureWall)
    {
        textureWall->destroy();
        delete textureWall;
        textureWall = nullptr;
    }
#endif
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();

    bool success = false;
    /* 1.创建和编译着色器程序 */
    unsigned int vertexShader = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/Resources/shaders/shader.vert");
    unsigned int fragmentShader = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/Resources/shaders/shader.frag");
    success = shaderProgram.link();
    if(!success)
    {
        qDebug() << "ERR:"<< shaderProgram.log();
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /* 2.设置顶点数据和顶点属性 */
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1,&EBO);

    // 2.1 绑定VAO
    glBindVertexArray(VAO);

    // 2.2 绑定VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 2.3 绑定EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 2.3 解析顶点数据
    // 2.3.1 位置
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 2.3.2 颜色
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(sizeof(float)*3));
    glEnableVertexAttribArray(1);
    // 2.3.3 纹理
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(sizeof(float)*6));
    glEnableVertexAttribArray(2);

#if QOPENGL
    textureWall = new QOpenGLTexture(QImage(":/Resources/images/wall.jpg"));
    textureWall->setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::Repeat);
    textureWall->setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::Repeat);
    textureWall->setMinMagFilters(QOpenGLTexture::Linear,QOpenGLTexture::Linear);
#else
    /* 3.创建纹理 */
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    // 3.1 为当前绑定的纹理设置环绕和过滤方式
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 3.2 加载图片，并生成纹理以及多级渐远纹理（Mipmap）
    QImage wallImage =QImage(":/Resources/images/container.jpg");
    // 须将格式转为RGB888，否则会出现显示异常
    wallImage = wallImage.convertToFormat(QImage::Format_RGB888);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wallImage.width(), wallImage.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, wallImage.bits());
    glGenerateMipmap(GL_TEXTURE_2D);
#endif

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

    // 绑定纹理
#if QOPENGL
    textureWall->bind();
#else
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
#endif
    // 渲染顶点数据
    shaderProgram.bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}

