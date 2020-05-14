#include <cstdlib>
#include <iostream>
#include <GLFW/glfw3.h>

namespace {
    //ウインドウタイトル・幅・高さ
    constexpr char* WIN_TITLE = "clear";
    constexpr std::int32_t WIN_W = 640;
    constexpr std::int32_t WIN_H = 480;

    //初期クリア色(RGBA)
    constexpr GLfloat DEFCOLOR[4] = { 255.0F, 255.0F, 255.0F, 255.0F };

    //一秒間に更新する回数
    constexpr double FPS = 30.0;

    //クリア色更新カウンタ
    GLfloat color_count = 0.0F;
}

namespace {
    //GLFWでエラーが発生したときにコールされる
    static void glfw_error_callback(int error, const char* description)
    {
        std::cerr << "glfw_error_callback() .. (" << error << ") " << description << std::endl;
    }

    //描画
    static void draw(GLFWwindow* window)
    {
        //背景色を指定する
        GLclampf r = (DEFCOLOR[0] - color_count) / 255.0F;
        GLclampf g = (DEFCOLOR[1] - color_count) / 255.0F;
        GLclampf b = DEFCOLOR[2] / 255.0F;
        GLclampf a = DEFCOLOR[3] / 255.0F;
        glClearColor(r, g, b, a);

        //ウィンドウを消去する
        glClear(GL_COLOR_BUFFER_BIT);

        //カラーバッファを入れ替える
        glfwSwapBuffers(window);

        //クリア色更新カウンタを更新する
        color_count += 1.0F;
        if (color_count > 255.0F) { color_count = 0.0F; }
    }
}

int main()
{
    //GLFWでエラーが発生したときにコールされる関数を登録する
    glfwSetErrorCallback(glfw_error_callback);

    //GLFWを初期化する
    if (glfwInit() == GL_FALSE) {
        //失敗
        std::cerr << "glfwInit() .. NG" << std::endl;
        return 1;
    }
    std::cout << "glfwInit() .. OK" << std::endl;

    //プログラム終了時の処理を登録する
    atexit(glfwTerminate);

    //ウィンドウを作成する
    GLFWwindow* const window = glfwCreateWindow(WIN_W, WIN_H, WIN_TITLE, nullptr, nullptr);
    if (window == nullptr) {
        //失敗
        std::cerr << "glfwCreateWindow() .. NG" << std::endl;
        glfwTerminate();
        return 1;
    }
    std::cout << "glfwCreateWindow() .. OK" << std::endl;

    //作成したウィンドウをOpenGLの処理対象にする
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    //タイマーのセッティング
    double currentTime = 0.0, lastTime = 0.0, elapsedTime = 0.0;
    //タイマーを初期化する
    glfwSetTime(0.0);

    //ウィンドウが開いている間繰り返す
    while (glfwWindowShouldClose(window) == GL_FALSE) {
        currentTime = glfwGetTime();
        elapsedTime = currentTime - lastTime;
        if (elapsedTime >= (1.0 / FPS)) {
            //描画
            std::cout << elapsedTime * 1000.0F << "ms: draw" << std::endl;
            draw(window);
            lastTime = glfwGetTime();
        } 

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}