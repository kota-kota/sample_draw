#include "Vertex.hpp"

#include <GLFW/glfw3.h>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace {
    //! ウインドウタイトル・幅・高さ
    constexpr char* WIN_TITLE = "00_window_create";
    constexpr std::int32_t WIN_W = 640;
    constexpr std::int32_t WIN_H = 480;
}

namespace {
    //! GLFWでエラーが発生したときにコールされるコールバック関数
    static void glfw_error_callback(int error, const char* description)
    {
        std::cerr << "glfw_error_callback() .. (" << error << ") " << description << std::endl;
    }
}

int main()
{
    // GLFWでエラーが発生したときにコールされる関数を登録する
    glfwSetErrorCallback(glfw_error_callback);

    // GLFWを初期化する
    if (glfwInit() == GL_FALSE) {
        // 失敗
        std::cerr << "glfwInit() .. NG" << std::endl;
        return 1;
    }
    std::cout << "glfwInit() .. OK" << std::endl;

    // ウィンドウを作成する
    GLFWwindow* const window = glfwCreateWindow(WIN_W, WIN_H, WIN_TITLE, nullptr, nullptr);
    if (window == nullptr) {
        // 失敗
        std::cerr << "glfwCreateWindow() .. NG" << std::endl;
        glfwTerminate();
        return 1;
    }
    std::cout << "glfwCreateWindow() .. OK (0x" << window << ")" << std::endl;

    // ウィンドウが開いている間繰り返す
    while (glfwWindowShouldClose(window) == GL_FALSE) {

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}