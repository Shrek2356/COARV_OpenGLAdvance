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
#define ToRadian(x) ((x) * M_PI / 180.0f)

GLuint VBO, IBO;
GLuint VAO;
GLint gWorldLocation;

class Pipeline {
public:
    Pipeline() : m_scale(1.0f, 1.0f, 1.0f), m_worldPos(0.0f, 0.0f, 0.0f), m_rotateInfo(0.0f, 0.0f, 0.0f) {}

    void Scale(float ScaleX, float ScaleY, float ScaleZ) {
        m_scale = Vector3f(ScaleX, ScaleY, ScaleZ);
    }

    void WorldPos(float x, float y, float z) {
        m_worldPos = Vector3f(x, y, z);
    }

    void Rotate(float RotateX, float RotateY, float RotateZ) {
        m_rotateInfo = Vector3f(RotateX, RotateY, RotateZ);
    }

    const Matrix4f* GetTrans() {
        Matrix4f ScaleTrans, RotateTrans, TranslationTrans;
        InitScaleTransform(ScaleTrans);
        InitRotateTransform(RotateTrans);
        InitTranslationTransform(TranslationTrans);
        m_transformation = TranslationTrans * RotateTrans * ScaleTrans;
        return &m_transformation;
    }

private:
    Vector3f m_scale;
    Vector3f m_worldPos;
    Vector3f m_rotateInfo;
    Matrix4f m_transformation;

    void InitScaleTransform(Matrix4f& m) {
        m.InitIdentity();
        m.m[0][0] = m_scale.x;
        m.m[1][1] = m_scale.y;
        m.m[2][2] = m_scale.z;
    }

    void InitTranslationTransform(Matrix4f& m) {
        m.InitIdentity();
        m.m[0][3] = m_worldPos.x;
        m.m[1][3] = m_worldPos.y;
        m.m[2][3] = m_worldPos.z;
    }

    void InitRotateTransform(Matrix4f& m) {
        Matrix4f rx, ry, rz;

        float x = ToRadian(m_rotateInfo.x);
        float y = ToRadian(m_rotateInfo.y);
        float z = ToRadian(m_rotateInfo.z);

        rx.InitIdentity();
        rx.m[1][1] = cosf(x); rx.m[1][2] = -sinf(x);
        rx.m[2][1] = sinf(x); rx.m[2][2] = cosf(x);

        ry.InitIdentity();
        ry.m[0][0] = cosf(y); ry.m[0][2] = sinf(y);
        ry.m[2][0] = -sinf(y); ry.m[2][2] = cosf(y);

        rz.InitIdentity();
        rz.m[0][0] = cosf(z); rz.m[0][1] = -sinf(z);
        rz.m[1][0] = sinf(z); rz.m[1][1] = cosf(z);

        m = rz * ry * rx;
    }
};

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
    Vector3f Vertices[3] = {
        Vector3f(-1.0f, -1.0f, 0.0f),
        Vector3f(1.0f, -1.0f, 0.0f),
        Vector3f(0.0f, 1.0f, 1.0f)
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    static float Scale = 0.0f;
    Scale += 0.01f;

    Pipeline p;
    p.Scale(0.5f, 0.5f, 0.5f);
    p.WorldPos(sinf(Scale), 0.0f, 0.0f);
    p.Rotate(sinf(Scale) * 90.0f, sinf(Scale) * 90.0f, sinf(Scale) * 90.0f);

    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, (const GLfloat*)p.GetTrans());

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Combined Transformations");

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
*/