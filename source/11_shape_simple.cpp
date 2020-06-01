﻿#include "Vertex.hpp"
#include "GlobalDrawer.hpp"

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
    //! 形状
    class Shape {
        GLuint          m_vao;          //!< 頂点配列オブジェクト
        GLuint          m_vertex_vbo;   //!< 頂点用のバッファオブジェクト
        GLuint          m_index_vbo;    //!< 頂点インデックス用のバッファオブジェクト
        GLenum          m_mode;         //!< 描画モード
        my::Vertexes    m_vertexes;     //!< 頂点座標の並び
        my::Indexes     m_indexes;      //!< 頂点インデックスの並び
        my::Colors      m_colors;       //!< 頂点色の並び

    public:
        //! コンストラクタ
        Shape::Shape(const GLenum mode, const my::Vertexes& vertexes, const my::Indexes& indexes, const my::Colors& colors) :
            m_vao(0U), m_vertex_vbo(0U), m_index_vbo(0U),
            m_mode(mode), m_vertexes(vertexes), m_indexes(indexes), m_colors(colors)
        {
            std::cout << "[Shape::Shape()] call" << std::endl;
            // 頂点配列オブジェクトを作成する
            glGenVertexArrays(1, &this->m_vao);
            glBindVertexArray(this->m_vao);
            std::cout << "* VAO id:" << m_vao << std::endl;

            // 頂点用のバッファオブジェクトを作成する
            glGenBuffers(1, &this->m_vertex_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, this->m_vertex_vbo);
            const std::int32_t vsize = static_cast<std::int32_t>(vertexes.size() * sizeof(my::Vertex));
            const std::int32_t csize = static_cast<std::int32_t>(colors.size() * sizeof(my::Color));
            glBufferData(GL_ARRAY_BUFFER, vsize * csize, nullptr, GL_DYNAMIC_DRAW);
            // 頂点データを転送する
            glBufferSubData(GL_ARRAY_BUFFER, 0, vsize, &vertexes[0]);
            // 色データを転送する
            glBufferSubData(GL_ARRAY_BUFFER, vsize, csize, &colors[0]);
            std::cout << "* VBO(Vertex) id:" << m_vertex_vbo << " vertex size:" << vsize << " color size:" << csize << std::endl;

            // 頂点インデックス用のバッファオブジェクトを作成する
            glGenBuffers(1, &this->m_index_vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_index_vbo);
            const std::int32_t isize = static_cast<std::int32_t>(indexes.size() * sizeof(GLuint));
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, nullptr, GL_DYNAMIC_DRAW);
            // 頂点インデックスデータを転送する
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, isize, &indexes[0]);
            std::cout << "* VBO(Index) id:" << m_index_vbo << "index size:" << isize << std::endl;
        }

        //! デストラクタ
        ~Shape()
        {
            std::cout << "[Shape::~Shape()] call" << std::endl;
            // 頂点配列オブジェクトを破棄する
            glDeleteVertexArrays(1, &this->m_vao);
            // 頂点用のバッファオブジェクトを破棄する
            glDeleteBuffers(1, &this->m_vertex_vbo);
            // 頂点インデックス用のバッファオブジェクトを破棄する
            glDeleteBuffers(1, &this->m_index_vbo);
        }

        //! コピーコンストラクタによるコピー禁止
        Shape(const Shape& org) = delete;
        //! 代入によるコピー禁止
        Shape& operator=(const Shape& org) = delete;

    public:
        //! 描画
        void draw()
        {
            // シェーダ取得
            my::Shader_11ShapeSimple shader = my::GlobalDrawer::instance().getShaderBuilder().getShader_11ShapeSimple();
            const GLuint prog = shader.getProgram();
            const GLint pos_loc = shader.getPositionLocation();
            const GLint col_loc = shader.getColorLocation();

            // シェーダプログラムを指定
            glUseProgram(prog);

            // 頂点配列オブジェクトの結合
            glBindVertexArray(this->m_vao);
            glBindBuffer(GL_ARRAY_BUFFER, this->m_vertex_vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_index_vbo);
            // 頂点データを指定
            glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(pos_loc);
            // 色データを指定
            glVertexAttribPointer(col_loc, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, (GLubyte*)(this->m_vertexes.size() * sizeof(my::Vertex)));
            glEnableVertexAttribArray(col_loc);

            // 描画実行
            GLsizei icnt = static_cast<GLsizei>(this->m_indexes.size());
            glDrawElements(this->m_mode, icnt, GL_UNSIGNED_INT, nullptr);
        }
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
        GLFWwindow*     m_window;           //!< ウィンドウ
        std::int32_t    m_width;            //!< 画面幅[pixel]
        std::int32_t    m_height;           //!< 画面高さ[pixel]
        std::int32_t    m_fbWidth;          //!< フレームバッファ幅[pixel]
        std::int32_t    m_fbHeight;         //!< フレームバッファ高さ[pixel]
        float           m_scale;            //!< 拡大率
        my::Color       m_bgcolor;          //!< 背景色
        Shape           m_rect;             //!< 矩形

    public:
        //! コンストラクタ
        Screen(GLFWwindow* window) :
            m_window(window), m_width(0), m_height(0), m_fbWidth(0), m_fbHeight(0), m_scale(100.0F),
            m_bgcolor(DEFCOLOR[0], DEFCOLOR[1], DEFCOLOR[2], DEFCOLOR[3]),
            m_rect(GL_LINE_LOOP, RECT_V, RECT_I, RECT_C)
        {
            std::cout << "[Screen::Screen()] call" << std::endl;
            // 画面サイズを取得する
            glfwGetWindowSize(m_window, &m_width, &m_height);
            // フレームバッファサイズを取得する
            glfwGetFramebufferSize(m_window, &m_fbWidth, &m_fbHeight);
        }

    public:
        //! 画面サイズを変更
        void resize(const std::int32_t w, const std::int32_t h)
        {
            std::cout << "[Screen::resize()] call" << std::endl;
            // 画面サイズを変更する
            m_width = w; m_height = h;
            // フレームバッファサイズを変更する
            glfwGetFramebufferSize(m_window, &m_fbWidth, &m_fbHeight);
        }

    public:
        //! 描画実行
        void draw()
        {
            // 画面クリア
            glClearColor(m_bgcolor.clamp_r(), m_bgcolor.clamp_g(), m_bgcolor.clamp_b(), m_bgcolor.clamp_a());
            glClear(GL_COLOR_BUFFER_BIT);
            // ビューポートの設定
            glViewport(0, 0, m_fbWidth, m_fbHeight);
            // 矩形描画
            m_rect.draw();
            // 画面更新
            glfwSwapBuffers(m_window);
        }
    };
}

namespace {
    //! GLFWでエラーが発生したときにコールされるコールバック関数
    static void glfw_error_callback(int error, const char* description)
    {
        std::cerr << "[GLFW ERROR] (" << error << ") " << description << std::endl;
    }

    //! GLFWでウィンドウのサイズが変更されたときに呼ばれるコールバック関数
    void glfw_window_resize_callback(GLFWwindow* window, int width, int height)
    {
        std::cout << "[GLFW RESIZE] w:" << width << " h:" << height << " (" << window << ")" << std::endl;
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
    std::cout << "[main] app start" << std::endl;
    // GLFWでエラーが発生したときにコールされる関数を登録する
    glfwSetErrorCallback(glfw_error_callback);

    // GLFWを初期化する
    if (glfwInit() == GL_FALSE) {
        // 失敗
        std::cerr << "* glfwInit() .. NG" << std::endl;
        return 1;
    }
    std::cout << "* glfwInit() .. OK" << std::endl;

    // OpenGL ES 3.2 Core Profile を選択する
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    // ウィンドウを作成する
    GLFWwindow* const window = glfwCreateWindow(WIN_W, WIN_H, WIN_TITLE, nullptr, nullptr);
    if (window == nullptr) {
        // 失敗
        std::cerr << "* glfwCreateWindow() .. NG" << std::endl;
        glfwTerminate();
        return 1;
    }
    std::cout << "* glfwCreateWindow() .. OK (0x" << window << ")" << std::endl;

    // GLFWでウィンドウのサイズが変更されたときに呼ばれる関数を登録する
    glfwSetWindowSizeCallback(window, glfw_window_resize_callback);

    // 作成したウィンドウをOpenGLの処理対象にする
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // GLEW を初期化する
    if (glewInit() != GLEW_OK) {
        // GLEW の初期化に失敗した
        std::cerr << "* glewInit() .. NG" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }
    std::cout << "* glewInit() .. OK" << std::endl;

    // バージョン情報
    std::cout << "[main] graphics info"<< glGetString(GL_VENDOR) << std::endl;
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

    std::cout << "[main] app end" << std::endl;
    return 0;
}