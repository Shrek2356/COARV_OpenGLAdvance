/*
#include <glew.h>   // 引入 GLEW 库
#include <glut.h>   // 引入 GLUT 库
#include <stdio.h>
#include "math_3d.h"   // 自定义数学库，定义 Vector3f 结构体

GLuint VBO; // 顶点缓冲对象（Vertex Buffer Object）

// 渲染回调函数
void RenderSceneCB() {
    glClear(GL_COLOR_BUFFER_BIT); // 清除颜色缓冲区

    glEnableVertexAttribArray(0); // 启用顶点属性数组
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // 绑定 VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // 指定顶点数据格式

    glDrawArrays(GL_POINTS, 0, 1); // 绘制 1 个点
    glDisableVertexAttribArray(0); // 禁用顶点属性数组

    glutSwapBuffers(); // 交换前后缓冲区
}

// 初始化 OpenGL
void CreateVertexBuffer() {
    Vector3f Vertices[1];
    Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f); // 顶点位于屏幕中心

    glGenBuffers(1, &VBO); // 生成 VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // 绑定 VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); // 传输数据到 VBO
}

// 主函数
int main(int argc, char** argv) {
    glutInit(&argc, argv); // 初始化 GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 双缓冲 + RGBA 颜色模式
    glutInitWindowSize(1024, 768); // 窗口大小
    glutInitWindowPosition(100, 100); // 窗口位置
    glutCreateWindow("Tutorial 02"); // 创建窗口

    GLenum res = glewInit(); // 初始化 GLEW
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res)); // 错误处理
        return 1;
    }

    CreateVertexBuffer(); // 创建顶点缓冲区
    glutDisplayFunc(RenderSceneCB); // 注册渲染回调
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // 设置清屏颜色（黑色）

    glutMainLoop(); // 进入 GLUT 主循环
    return 0;
}
*/