/*

#include <glut.h>// 引入 GLUT 库

// 渲染回调函数
void RenderSceneCB() {
    glClear(GL_COLOR_BUFFER_BIT); // 清空颜色缓冲区
    glutSwapBuffers(); // 交换前后缓冲
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // 初始化 GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 设置双缓冲、RGBA 颜色模式、深度缓冲
    glutInitWindowSize(1024, 768); // 设置窗口大小
    glutInitWindowPosition(100, 100); // 设置窗口位置
    glutCreateWindow("Tutorial 01"); // 创建窗口

    glutDisplayFunc(RenderSceneCB); // 注册渲染回调
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // 设置清屏颜色（黑色）

    glutMainLoop(); // 进入 GLUT 主循环
    return 0;
}
*/