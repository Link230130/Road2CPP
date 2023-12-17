#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QImage>
#include <QOpenGLTexture>

class Widget : public QOpenGLWidget,public QOpenGLFunctions_4_5_Core
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

private:
    QOpenGLShaderProgram shaderProgram;
    QOpenGLTexture *textureWall;
};
#endif // WIDGET_H
