﻿//*
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <glew.h>
#include <freeglut.h>
#include "math_3d.h"

#define GLEW_STATIC  

GLuint VBO, IBO;
GLuint VAO;
GLint gWorldLocation;

bool ReadFile(const char* fileName, std::string& outFile)
{
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    outFile = buffer.str();
    return true;
}

void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);
    if (ShaderObj == 0) {
        exit(1);
    }

    const GLchar* p[1] = { pShaderText };
    GLint Lengths[1] = { (GLint)strlen(pShaderText) };

    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

void CompileShaders()
{
    GLuint ShaderProgram = glCreateProgram();
    if (ShaderProgram == 0) {
        exit(1);
    }

    std::string vs, fs;
    if (!ReadFile("shader.vs", vs)) exit(1);
    if (!ReadFile("shader.fs", fs)) exit(1);

    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    glLinkProgram(ShaderProgram);
    gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld");

    if (gWorldLocation == -1) {
        exit(1);
    }

    glValidateProgram(ShaderProgram);
    glUseProgram(ShaderProgram);
}

void CreateBuffers()
{
    // 顶点数据（4个顶点）
    Vector3f Vertices[4] = {
        Vector3f(-1.0f, -1.0f, 0.0f),  // V0
        Vector3f(1.0f, -1.0f, 0.0f),   // V1
        Vector3f(0.0f, -1.0f, 1.0f),   // V2
        Vector3f(0.0f, 1.0f, 0.0f)     // V3（顶点）
    };

    // 索引数据（4个三角形）
    unsigned int Indices[] = {
        0, 3, 1,  // 三角形 1
        1, 3, 2,  // 三角形 2
        2, 3, 0,  // 三角形 3
        0, 1, 2   // 三角形 4（底部）
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Indexed Drawing - Pyramid");

    GLenum res = glewInit();
    if (res != GLEW_OK) {
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    CreateBuffers();
    CompileShaders();
    glutDisplayFunc(RenderSceneCB);
    glutMainLoop();

    return 0;
}
//*/