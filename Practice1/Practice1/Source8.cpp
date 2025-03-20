/*
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

GLuint VBO;
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

void CreateVertexBuffer()
{
    Vector3f Vertices[3] = {
        Vector3f(-1.0f, -1.0f, 0.0f),
        Vector3f(1.0f, -1.0f, 0.0f),
        Vector3f(0.0f, 1.0f, 0.0f)
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    static float Scale = 0.0f;
    Scale += 0.01f;
    float ScalingFactor = (sinf(Scale) + 1.0f) / 2.0f; // 确保在 0 到 1 之间波动

    Matrix4f ScalingMatrix;
    ScalingMatrix.m[0][0] = ScalingFactor; ScalingMatrix.m[0][1] = 0.0f;         ScalingMatrix.m[0][2] = 0.0f;         ScalingMatrix.m[0][3] = 0.0f;
    ScalingMatrix.m[1][0] = 0.0f;         ScalingMatrix.m[1][1] = ScalingFactor; ScalingMatrix.m[1][2] = 0.0f;         ScalingMatrix.m[1][3] = 0.0f;
    ScalingMatrix.m[2][0] = 0.0f;         ScalingMatrix.m[2][1] = 0.0f;         ScalingMatrix.m[2][2] = ScalingFactor; ScalingMatrix.m[2][3] = 0.0f;
    ScalingMatrix.m[3][0] = 0.0f;         ScalingMatrix.m[3][1] = 0.0f;         ScalingMatrix.m[3][2] = 0.0f;         ScalingMatrix.m[3][3] = 1.0f;

    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &ScalingMatrix.m[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);

    glutPostRedisplay();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Scaling Transformation");

    GLenum res = glewInit();
    if (res != GLEW_OK) {
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    CreateVertexBuffer();
    CompileShaders();
    glutDisplayFunc(RenderSceneCB);
    glutMainLoop();

    return 0;
}
*/