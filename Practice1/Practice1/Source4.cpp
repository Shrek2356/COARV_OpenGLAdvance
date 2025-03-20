/*
#include <stdio.h>

#include <string>
#include <fstream>
#include <sstream>
#include <glew.h>
#include <freeglut.h>
#include "math_3d.h"

GLuint VBO;

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
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

bool ReadFile(const char* fileName, std::string& outFile)
{
    std::ifstream f(fileName);
    if (!f.is_open()) {
        printf("Failed to open file: %s\n", fileName);
        return false;
    }
    std::stringstream buffer;
    buffer << f.rdbuf();
    outFile = buffer.str();
    return true;
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
    glUseProgram(ShaderProgram);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("OpenGL Shader");

    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "GLEW Init Error: %s\n", glewGetErrorString(res));
        return 1;
    }

    CreateVertexBuffer();
    CompileShaders();
    glutDisplayFunc(RenderSceneCB);
    glutMainLoop();
    return 0;
}
*/