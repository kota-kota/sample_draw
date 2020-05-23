#include "Vertex.hpp"
#include "GlobalDrawer.hpp"
#include "Object.hpp"

#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace {
    //! ウインドウタイトル・幅・高さ
    constexpr char* WIN_TITLE = "11_shape_simple";
    constexpr std::int32_t WIN_W = 640;
    constexpr std::int32_t WIN_H = 480;

    //! 初期クリア色(RGBA)
    constexpr std::uint8_t DEFCOLOR[4] = { 200, 200, 200, 255 };

    //! 一秒間に更新する回数
    constexpr double FPS = 30.0;

    //! 矩形
    const my::Vertexes RECT_V = {
        { -0.5F, -0.5F },
        { 0.5F, -0.5F },
        { 0.5F, 0.5F },
        { -0.5F, 0.5F }
    };
    const my::Indexes RECT_I = {
        0U, 1U, 2U, 3U
    };
    const my::Colors RECT_C = {
        { 255, 0, 0, 255 },
        { 255, 0, 0, 255 },
        { 255, 0, 0, 255 },
        { 255, 0, 0, 255 },
    };
}

namespace {
    //! タイマー
    class Timer {
        double m_time;      //!< チェック時間
        double m_current;   //!< 現在時間
        double m_last;      //!< 前回時間
        double m_elapsed;   //!< 差分時間

    public:
        //! デフォルトコンストラクタ
        Timer(const double time) :
            m_time(time), m_current(0.0), m_last(0.0), m_elapsed(0.0)
        {
            glfwSetTime(0.0);
        }

        //! 次タイマーへ（前回時間の更新）
        void next() { m_last = glfwGetTime(); }

        //! 指定した時間が経過したか判定
        bool isTime()
        {
            m_current = glfwGetTime();
            m_elapsed = m_current - m_last;

            bool is_time = false;
            if (m_elapsed >= m_time) {
                is_time = true;
            }
            return is_time;
        }

        //! 経過時間を取得[単位:msec]
        double getTime() const { return m_elapsed * 1000.0; }
    };
}

namespace {
    //! 画面クラス
    class Screen {
        GLFWwindow*     m_window;
        my::Color       m_bgcolor;
        my::Shape       m_rect;

    public:
        //! コンストラクタ
        Screen(GLFWwindow* window) :
            m_window(window),
            m_bgcolor(DEFCOLOR[0], DEFCOLOR[1], DEFCOLOR[2], DEFCOLOR[3]),
            m_rect(GL_LINE_LOOP, RECT_V, RECT_I, RECT_C)
        {
            // 画面サイズを変更
            std::int32_t width, height; 
            glfwGetWindowSize(window, &width, &height);
            this->resize(width, height);
        }

    public:
        //! 描画実行
        void draw()
        {
            this->clear();
            this->setup();
            this->draw_rectangle();
            glfwSwapBuffers(m_window);
        }

    public:
        //! 画面サイズを変更
        void resize(const std::int32_t w, const std::int32_t h)
        {
            my::GlobalDrawer& g_drawer = my::GlobalDrawer::instance();
            // 画面サイズを変更する
            g_drawer.resize(w, h);
            // フレームバッファサイズを変更する
            std::int32_t fbWidth, fbHeight;
            glfwGetFramebufferSize(m_window, &fbWidth, &fbHeight);
            g_drawer.changeFramebufferSize(fbWidth, fbHeight);
        }

    private:
        //! 画面クリア
        void clear()
        {
            glClearColor(m_bgcolor.clamp_r(), m_bgcolor.clamp_g(), m_bgcolor.clamp_b(), m_bgcolor.clamp_a());
            glClear(GL_COLOR_BUFFER_BIT);
        }

    private:
        //! セットアップ
        void setup()
        {
            my::GlobalDrawer& g_drawer = my::GlobalDrawer::instance();

            // ビューポートの設定
            std::int32_t fbWidth, fbHeight;
            g_drawer.getFramebufferSize(&fbWidth, &fbHeight);
            glViewport(0, 0, fbWidth, fbHeight);
        }

    private:
        //! 矩形描画
        void draw_rectangle()
        {
            m_rect.draw();
        }
    };
}

namespace {
    //! GLFWでエラーが発生したときにコールされるコールバック関数
    static void glfw_error_callback(int error, const char* description)
    {
        std::cerr << "glfw_error_callback() .. (" << error << ") " << description << std::endl;
    }

    //! GLFWでウィンドウのサイズが変更されたときに呼ばれるコールバック関数
    void glfw_window_resize_callback(GLFWwindow* window, int width, int height)
    {
        std::cout << "GLFW RESIZE -> w:" << width << " h:" << height << " (" << window << ")" << std::endl;
        // 画面インスタンスのポインタを取得する
        Screen* screen = static_cast<Screen*>(glfwGetWindowUserPointer(window));
        if (screen != nullptr) {
            // 描画
            screen->resize(width, height);
            screen->draw();
        }
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

    // OpenGL ES 3.2 Core Profile を選択する
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

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

    // 作成したウィンドウをOpenGLの処理対象にする
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // GLEW を初期化する
    if (glewInit() != GLEW_OK) {
        // GLEW の初期化に失敗した
        std::cerr << "glewInit() .. NG" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }
    std::cout << "glewInit() .. OK" << std::endl;

    // バージョン情報
    std::cout << "* Vendor :"<< glGetString(GL_VENDOR) << std::endl;
    std::cout << "* GPU : "<< glGetString(GL_RENDERER) << std::endl;
    std::cout << "* OpenGL Ver. : " << glGetString(GL_VERSION) << std::endl;

    // 画面の生成
    Screen screen(window);

    // 画面インスタンスのポインタを保持する
    glfwSetWindowUserPointer(window, &screen);

    // ウィンドウが開いている間繰り返す
    Timer timer(1.0 / FPS);
    while (glfwWindowShouldClose(window) == GL_FALSE) {
        if (timer.isTime()) {
            // 描画
            screen.draw();
            timer.next();

            // ウィンドウタイトルにFPSを表示する
            double fps = 1000.0 / timer.getTime();
            std::stringstream title;
            title << WIN_TITLE << " [" << std::fixed << std::setprecision(4) << fps << " FPS]";
            glfwSetWindowTitle(window, title.str().c_str());
        }

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}