/*

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <glew.h>
#include <freeglut.h>

#include "ogldev-master/Include/ogldev_math_3d.h"

#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080

GLuint VBO;
GLuint IBO;
GLuint gWorldLocation;

// 摄像机位置
Vector3f CameraPos(0.0f, 0.0f, -3.0f);

// 处理键盘输入
void KeyboardCB(unsigned char key, int x, int y)
{
    float stepSize = 0.1f;
    switch (key) {
    case 'w': CameraPos.z += stepSize; break;
    case 's': CameraPos.z -= stepSize; break;
    case 'a': CameraPos.x -= stepSize; break;
    case 'd': CameraPos.x += stepSize; break;
    case 27: exit(0); // 按下 ESC 退出
    }
}

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static float Scale = 0.0f;
    Scale += 0.002f;

    // 旋转矩阵
    Matrix4f Rotation(cosf(Scale), 0.0f, -sinf(Scale), 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sinf(Scale), 0.0f, cosf(Scale), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);

    // 平移矩阵（使用摄像机位置）
    Matrix4f Translation(1.0f, 0.0f, 0.0f, CameraPos.x,
        0.0f, 1.0f, 0.0f, CameraPos.y,
        0.0f, 0.0f, 1.0f, CameraPos.z,
        0.0f, 0.0f, 0.0f, 1.0f);

    // 透视投影参数
    float VFOV = 45.0f;
    float ar = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
    float NearZ = 1.0f;
    float FarZ = 100.0f;
    float tanHalfVFOV = tanf(ToRadian(VFOV / 2.0f));
    float d = 1.0f / tanHalfVFOV;

    float zRange = NearZ - FarZ;
    float A = (FarZ + NearZ) / zRange;
    float B = (2.0f * FarZ * NearZ) / zRange;

    // 透视投影矩阵
    Matrix4f Projection(d / ar, 0.0f, 0.0f, 0.0f,
        0.0f, d, 0.0f, 0.0f,
        0.0f, 0.0f, A, B,
        0.0f, 0.0f, -1.0f, 0.0f);

    // 计算最终变换矩阵
    Matrix4f FinalMatrix = Projection * Translation * Rotation;

    // 传递矩阵到着色器
    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &FinalMatrix.m[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // 位置
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

    // 颜色
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glutSwapBuffers();
}

// 顶点结构
struct Vertex {
    Vector3f pos;
    Vector3f color;

    Vertex(float x, float y, float z) {
        pos = Vector3f(x, y, z);
        color = Vector3f(1.0f, 1.0f, 1.0f); // 统一设置为白色
    }
};

// 顶点和索引缓冲区
static void CreateVertexBuffer()
{
    Vertex Vertices[8] = {
        Vertex(0.5f,  0.5f,  0.5f),
        Vertex(-0.5f,  0.5f, -0.5f),
        Vertex(-0.5f,  0.5f,  0.5f),
        Vertex(0.5f, -0.5f, -0.5f),
        Vertex(-0.5f, -0.5f, -0.5f),
        Vertex(0.5f,  0.5f, -0.5f),
        Vertex(0.5f, -0.5f,  0.5f),
        Vertex(-0.5f, -0.5f,  0.5f)
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

static void CreateIndexBuffer()
{
    unsigned int Indices[] = {
        0, 1, 2,  1, 3, 4,  5, 6, 3,  7, 3, 6,
        2, 4, 7,  0, 7, 6,  0, 5, 1,  1, 5, 3,
        5, 0, 6,  7, 4, 3,  2, 1, 4,  0, 2, 7
    };

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Perspective Projection");

    glewInit();
    glEnable(GL_DEPTH_TEST);

    CreateVertexBuffer();
    CreateIndexBuffer();

    glutDisplayFunc(RenderSceneCB);
    glutKeyboardFunc(KeyboardCB); // 绑定键盘输入

    glutMainLoop();
    return 0;
}
*/