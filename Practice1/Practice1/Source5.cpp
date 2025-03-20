/*
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glew.h>
#include <freeglut.h>
#include "math_3d.h"

#define GLEW_STATIC  // 

GLuint VBO;
GLint gScaleLocation;

//
bool ReadFile(const char* fileName, std::string& outFile)
{
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    outFile = buffer.str();
    return true;
}

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    static float Scale = 0.0f;
    static float Delta = 0.001f;

    Scale += Delta;
    if ((Scale >= 1.0f) || (Scale <= -1.0f)) {
        Delta *= -1.0f;
    }

    glUniform1f(gScaleLocation, Scale);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);

    glutPostRedisplay();
    glutSwapBuffers();
}

static void CreateVertexBuffer()
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

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(1);
    }

    const GLchar* p[1] = { pShaderText };
    GLint Lengths[1] = { (GLint)strlen(pShaderText) };

    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

static void CompileShaders()
{
    GLuint ShaderProgram = glCreateProgram();
    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    std::string vs, fs;
    if (!ReadFile("shader.vs", vs)) exit(1);
    if (!ReadFile("shader.fs", fs)) exit(1);

    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    glLinkProgram(ShaderProgram);
    gScaleLocation = glGetUniformLocation(ShaderProgram, "gScale");

    if (gScaleLocation == -1) {
        printf("Error getting uniform location of 'gScale'\n");
        exit(1);
    }

    glValidateProgram(ShaderProgram);
    glUseProgram(ShaderProgram);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(200, 100);
    int win = glutCreateWindow("Tutorial 05");
    printf("window id: %d\n", win);

    GLenum res = glewInit();

}
*/