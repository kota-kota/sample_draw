#include "Vertex.hpp"

#include <GLFW/glfw3.h>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace {
    //! ウインドウタイトル・幅・高さ
    constexpr char* WIN_TITLE = "01_window_event";
    constexpr std::int32_t WIN_W = 640;
    constexpr std::int32_t WIN_H = 480;
}

namespace {
    //! GLFWでエラーが発生したときに呼ばれるコールバック関数
    static void glfw_error_callback(int error, const char* description)
    {
        std::cerr << "GLFW ERROR -> (" << error << ") " << description << std::endl;
    }

    //! GLFWでウィンドウのサイズが変更されたときに呼ばれるコールバック関数
    void glfw_window_resize_callback(GLFWwindow* window, int width, int height)
    {
        std::cout << "GLFW RESIZE -> w:" << width << " h:" << height << " (" << window << ")" << std::endl;
    }

    //! GLFWでマウスの釦が押されたときに呼ばれるコールバック関数
    void glfw_window_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        std::cout << "GLFW MOUSE_BTN -> button:" << button << " action:" << action << " mods:" << mods << " (" << window << ")" << std::endl;
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            if (action == GLFW_PRESS) {
            }
            else {
            }
        }
        else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            if (action == GLFW_PRESS) {
            }
            else {
            }
        }
        else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
            if (action == GLFW_PRESS) {
            }
            else {
            }
        }
        else {
        }
    }

    //! GLFWでマウスカーソルの位置が変化したときに呼ばれるコールバック関数
    void glfw_window_mouse_position_callback(GLFWwindow *window, double x, double y)
    {
        std::cout << "GLFW MOUSE_POS -> x:" << x << " y:" << y << " (" << window << ")" << std::endl;
    }

    //! GLFWでマウスホイールを動かしたときに呼ばれるコールバック関数
    void glfw_window_mouse_scroll_callback(GLFWwindow *window, double x, double y)
    {
        std::cout << "GLFW MOUSE_SCRL -> x:" << x << " y:" << y << " (" << window << ")" << std::endl;
    }

    //! GLFWでキーが入力されたときに呼ばれるコールバック関数
    void glfw_window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        std::cout << "GLFW KEY -> key:" << key << " scancode:" << scancode << " action:" << action << " mods:0x" << mods << " (" << window << ")" << std::endl;
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

    // GLFWでウィンドウのサイズが変更されたときに呼ばれる関数を登録する
    glfwSetWindowSizeCallback(window, glfw_window_resize_callback);
    // GLFWでマウスの釦が押されたときに呼ばれる関数を登録する
    glfwSetMouseButtonCallback(window, glfw_window_mouse_button_callback);
    // GLFWでマウスカーソルの位置が変化したときに呼ばれる関数を登録する
    glfwSetCursorPosCallback(window, glfw_window_mouse_position_callback);
    // GLFWでマウスホイールを動かしたときに呼ばれる関数を登録する
    glfwSetScrollCallback(window, glfw_window_mouse_scroll_callback);
    // GLFWでキーが入力されたときに呼ばれる関数を登録する
    glfwSetKeyCallback(window, glfw_window_key_callback);

    // ウィンドウが開いている間繰り返す
    while (glfwWindowShouldClose(window) == GL_FALSE) {

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}