#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>; // ����glad����ȡ���еı���OpenGLͷ�ļ�

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class CShader
{
public:
    CShader(const char* vertexPath, const char* fragmentPath);
    ~CShader();
    // ʹ��/�������
    void use();

    // uniform ���ߺ���
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

public:
    // ����ID
    unsigned int ID;

};

CShader::CShader(const char * vertexPath, const char * fragmentPath)
{
    // 1. �Ӵ��̶�ȡ��ɫ������
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ��֤ifstream��������׳��쳣��
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vertexStream;
        std::stringstream fragmentStream;
        vertexStream << vShaderFile.rdbuf();
        fragmentStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
    }
    catch (const std::exception&)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. ������ɫ��
    unsigned int vertexShader;
    unsigned int fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShader);
    int nSuccess = 0;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &nSuccess);
    if (!nSuccess)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &nSuccess);
    if (!nSuccess)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // ��ɫ������
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    // ��ӡ���Ӵ���
    glGetShaderiv(ID, GL_LINK_STATUS, &nSuccess);
    if (!nSuccess)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // ������ɺ�ɾ����ɫ��
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


}

CShader::~CShader()
{
    glDeleteShader(ID);
}

void CShader::use()
{
    glUseProgram(ID);
}

void CShader::setBool(const std::string & name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void CShader::setInt(const std::string & name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void CShader::setFloat(const std::string & name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
#endif


