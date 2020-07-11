#include "Vertex.hpp"
#include "Matrix.hpp"
#include "GlobalDrawer.hpp"

#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace {
    //! ウインドウタイトル・幅・高さ
    constexpr char* WIN_TITLE = "sample_draw";
    constexpr std::int32_t WIN_W = 1280;
    constexpr std::int32_t WIN_H = 720;

    //! 初期拡大率
    //! 拡大率 = オブジェクトの座標系に対するデバイス座標系の拡大率
    constexpr float DEFSCALE = 1.0F;

    //! 初期クリア色(RGBA)
    constexpr std::uint8_t DEFCOLOR[4] = { 200, 200, 200, 255 };

    //! 一秒間に更新する回数
    constexpr double FPS = 30.0;

    //! 線描画
    const my::Vector LINES_POS = {80.0F, 80.0F, 0.0F};
    const my::Vector LINE_STRIP_POS = {220.0F, 80.0F, 0.0F};
    const my::Vector LINE_LOOP_POS = {360.0F, 80.0F, 0.0F};
    const my::Vertexes LINE_V = {
        { -40.0F, -40.0F },
        { -20.0F, 20.0F },
        { 0.0F, -40.0F },
        { 20.0F, 20.0F },
        { 40.0F, -40.0F },
        { 60.0F, 20.0F }
    };
    const my::Indexes LINE_I = {
        0U, 1U, 2U, 3U, 4U, 5U
    };
    const my::Colors LINE_C = {
        { 255, 0, 0, 255 },
        { 0, 255, 0, 255 },
        { 0, 0, 255, 255 },
        { 255, 255, 0, 255 },
        { 0, 255, 255, 255 },
        { 255, 0, 255, 255 },
    };

    //! 面描画
    const my::Vector TRIANGLES_POS = {500.0F, 80.0F, 0.0F};
    const my::Vector TRIANGLE_STRIP_POS = {640.0F, 80.0F, 0.0F};
    const my::Vector TRIANGLE_FAN_POS = {780.0F, 80.0F, 0.0F};
    const my::Vertexes TRIANGLE_V = {
        { -40.0F, -40.0F },
        { -20.0F, 20.0F },
        { 0.0F, -40.0F },
        { 20.0F, 20.0F },
        { 40.0F, -40.0F },
        { 60.0F, 20.0F }
    };
    const my::Indexes TRIANGLE_I = {
        0U, 1U, 2U, 3U, 4U, 5U
    };
    const my::Colors TRIANGLE_C = {
        { 255, 0, 0, 255 },
        { 0, 255, 0, 255 },
        { 0, 0, 255, 255 },
        { 255, 255, 0, 255 },
        { 0, 255, 255, 255 },
        { 255, 0, 255, 255 },
    };

    //! 点描画
    const my::Vector POINTS_POS = {920.0F, 80.0F, 0.0F};
    const my::Vertexes POINT_V = {
        { -40.0F, -40.0F },
        { -20.0F, 20.0F },
        { 0.0F, -40.0F },
        { 20.0F, 20.0F },
        { 40.0F, -40.0F },
        { 60.0F, 20.0F }
    };
    const my::Indexes POINT_I = {
        0U, 1U, 2U, 3U, 4U, 5U
    };
    const my::Colors POINT_C = {
        { 255, 0, 0, 255 },
        { 0, 255, 0, 255 },
        { 0, 0, 255, 255 },
        { 255, 255, 0, 255 },
        { 0, 255, 255, 255 },
        { 255, 0, 255, 255 },
    };

    //! テキスト描画
    const std::wstring TEXT_ASCII = L"abcdefghijklmnopqrstuvwxyz";
    const my::Vector TEXT_ASCII_POS = { 350.0F, 160.0F, 0.0F };
    const my::Color TEXT_ASCII_C = { 255, 0, 0, 255 };
    const std::int32_t TEXT_ASCII_SZ = 32;

    const std::wstring TEXT_KANA = L"さんぷる　サンプル　ｻﾝﾌﾟﾙ";
    const my::Vector TEXT_KANA_POS = { 180.0F, 200.0F, 0.0F };
    const my::Color TEXT_KANA_C = { 255, 255, 0, 255 };
    const std::int32_t TEXT_KANA_SZ = 16;

    const std::wstring TEXT_BOLD = L"太字Bold";
    const my::Vector TEXT_BOLD_POS = { 100.0F, 230.0F, 0.0F };
    const my::Color TEXT_BOLD_C = { 0, 0, 255, 255 };
    const std::int32_t TEXT_BOLD_SZ = 16;
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
        my::Vector      m_pos;          //!< 描画位置
        my::Vector      m_scale;        //!< 描画スケール

    public:
        //! コンストラクタ
        Shape(const GLenum mode, const my::Vertexes& vertexes, const my::Indexes& indexes, const my::Colors& colors) :
            m_vao(0U), m_vertex_vbo(0U), m_index_vbo(0U),
            m_mode(mode), m_vertexes(vertexes), m_indexes(indexes), m_colors(colors),
            m_pos({0.0F, 0.0F, 0.0F}), m_scale({1.0F, 1.0F, 1.0F})
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
        //! 描画位置の設定
        void setPosition(const my::Vector& pos) { this->m_pos = pos; }

        //! 描画スケールの設定
        void setScale(const my::Vector& scale) { this->m_scale = scale; }

        //! 描画
        void draw(const my::Matrix& view, const my::Matrix& proj)
        {
            // シェーダ取得
            my::ShapeShader shader = my::GlobalDrawer::instance().getShaderBuilder().getShapeShader();
            const GLuint prog = shader.getProgram();
            const GLint modelview_loc = shader.getModelViewLocation();
            const GLint projection_loc = shader.getProjectionLocation();
            const GLint pointsize_loc = shader.getPointSizeLocation();
            const GLint pos_loc = shader.getPositionLocation();
            const GLint col_loc = shader.getColorLocation();

            // シェーダプログラムを指定
            glUseProgram(prog);

            // モデルの配置（モデルビュー変換行列）
            my::Matrix model = my::Matrix::translate(m_pos) * my::Matrix::scale(m_scale);
            my::Matrix modelview = view * model;
            modelview.transpose();
            glUniformMatrix4fv(modelview_loc, 1, GL_FALSE, modelview.data());

            // 投影変換（プロジェクション変換行列）
            my::Matrix projection = proj;
            projection.transpose();
            glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection.data());

            // ポイントサイズ（固定）
            glUniform1f(pointsize_loc, 5.0F);

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

            // 頂点配列オブジェクトの結合を解除
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
    };
}

namespace {
    //! テキスト
    class Text {
    public:
        //! 太字
        enum class BOLD { NO, YES };

    private:
        GLuint          m_vao;          //!< 頂点配列オブジェクト
        GLuint          m_vertex_vbo;   //!< 頂点用のバッファオブジェクト
        GLuint          m_index_vbo;    //!< 頂点インデックス用のバッファオブジェクト
        GLuint          m_texid;        //!< テキスト画像のテクスチャID
        my::Image       m_image;        //!< テキスト画像
        std::wstring    m_text;         //!< テキスト文字列
        my::Vertexes    m_vertexes;     //!< 頂点座標の並び
        my::Indexes     m_indexes;      //!< 頂点インデックスの並び
        my::Color       m_color;        //!< テキスト色
        my::Vector      m_pos;          //!< 描画位置
        my::Vector      m_scale;        //!< 描画スケール
        std::int32_t    m_size;         //!< テキストサイズ
        BOLD            m_bold;         //!< 太字

    public:
        //! コンストラクタ
        Text(const std::wstring& text) :
            m_vao(0U), m_vertex_vbo(0U), m_index_vbo(0U), m_texid(0), m_image(),
            m_text(text), m_vertexes(), m_indexes({0U, 1U, 2U, 3U}), m_color({0, 0, 0, 255}),
            m_pos({0.0F, 0.0F, 0.0F}), m_scale({1.0F, 1.0F, 1.0F}), m_size(8), m_bold(BOLD::NO)
        {
            std::cout << "[Text::Text()] call" << std::endl;
            std::cout << "* input text <" << text.c_str() << ">" << std::endl;
            // 頂点配列オブジェクトを作成する
            glGenVertexArrays(1, &this->m_vao);
            std::cout << "* VAO id:" << m_vao << std::endl;
            // 頂点用のバッファオブジェクトを作成する
            glGenBuffers(1, &this->m_vertex_vbo);
            std::cout << "* VBO(Vertex) id:" << m_vertex_vbo << std::endl;
            // 頂点インデックス用のバッファオブジェクトを作成する
            glGenBuffers(1, &this->m_index_vbo);
            std::cout << "* VBO(Index) id:" << m_index_vbo << std::endl;
        }

        //! デストラクタ
        ~Text()
        {
            std::cout << "[Image::~Image()] call" << std::endl;
            // 頂点配列オブジェクトを破棄する
            glDeleteVertexArrays(1, &this->m_vao);
            // 頂点用のバッファオブジェクトを破棄する
            glDeleteBuffers(1, &this->m_vertex_vbo);
            // 頂点インデックス用のバッファオブジェクトを破棄する
            glDeleteBuffers(1, &this->m_index_vbo);
            //テクスチャ破棄
            if(m_texid != 0) {
                glDeleteTextures(1, &m_texid);
            }
        }

        //! コピーコンストラクタによるコピー禁止
        Text(const Text& org) = delete;
        //! 代入によるコピー禁止
        Text& operator=(const Text& org) = delete;

    public:
        //! 描画位置の設定
        void setPosition(const my::Vector& pos) { this->m_pos = pos; }

        //! 描画スケールの設定
        void setScale(const my::Vector& scale) { this->m_scale = scale; }

        //! テキスト色の設定
        void setColor(const my::Color& color) { this->m_color = color; }

        //! 文字サイズの設定
        void setSize(const std::int32_t size) { this->m_size = size; }

        //! 太字の設定
        void setBold(const BOLD bold) { this->m_bold = bold; }

        //! 描画
        void draw(const my::Matrix& view, const my::Matrix& proj)
        {
            // UV座標
            const GLint pointNum = 4;
            GLfloat uv[pointNum * 2] = {
                0.0F, 0.0F,
                1.0F, 0.0F,
                0.0F, 1.0F,
                1.0F, 1.0F,
            };

            // テキスト画像の生成
            if(m_texid == 0) {
                bool isBold = (m_bold == BOLD::YES) ? true : false;
                m_image = my::GlobalDrawer::instance().getTextBuilder().build(m_text, m_size, isBold);

                // テクスチャ生成
                glGenTextures(1, &m_texid);
                // テクスチャロード
                glBindTexture(GL_TEXTURE_2D, m_texid);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, m_image.width(), m_image.height(), 0, GL_ALPHA, GL_UNSIGNED_BYTE, &m_image[0]);
                glBindTexture(GL_TEXTURE_2D, 0);

                const float xmin = -(static_cast<float>(m_image.width()) / 2.0F);
                const float ymin = -(static_cast<float>(m_image.height()) / 2.0F);
                const float xmax = (static_cast<float>(m_image.width()) / 2.0F);
                const float ymax = (static_cast<float>(m_image.height()) / 2.0F);

                m_vertexes = {
                    { xmin, ymax, 0.0F },
                    { xmax, ymax, 0.0F },
                    { xmin, ymin, 0.0F },
                    { xmax, ymin, 0.0F }
                };

                glBindVertexArray(this->m_vao);

                // 頂点データを転送する
                const std::int32_t vsize = static_cast<std::int32_t>(m_vertexes.size() * sizeof(my::Vertex));
                const std::int32_t uvsize = static_cast<std::int32_t>(pointNum * 2 * sizeof(GLfloat));
                glBindBuffer(GL_ARRAY_BUFFER, this->m_vertex_vbo);
                glBufferData(GL_ARRAY_BUFFER, vsize + uvsize, nullptr, GL_DYNAMIC_DRAW);
                glBufferSubData(GL_ARRAY_BUFFER, 0, vsize, &m_vertexes[0]);
                glBufferSubData(GL_ARRAY_BUFFER, vsize, uvsize, &uv[0]);

                // 頂点インデックスデータを転送する
                const std::int32_t isize = static_cast<std::int32_t>(m_indexes.size() * sizeof(GLuint));
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_index_vbo);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, nullptr, GL_DYNAMIC_DRAW);
                glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, isize, &m_indexes[0]);
            }

            // シェーダ取得
            my::TextShader shader = my::GlobalDrawer::instance().getShaderBuilder().getTextShader();
            const GLuint prog = shader.getProgram();
            const GLint modelview_loc = shader.getModelViewLocation();
            const GLint projection_loc = shader.getProjectionLocation();
            const GLint texture_loc = shader.getTextureLocation();
            const GLint texcolor_loc = shader.getTexColorLocation();
            const GLint pos_loc = shader.getPositionLocation();
            const GLint uv_loc = shader.getUVLocation();

            // シェーダプログラムを指定
            glUseProgram(prog);

            // モデルの配置（モデルビュー変換行列）
            my::Matrix model = my::Matrix::translate(m_pos) * my::Matrix::scale(m_scale);
            my::Matrix modelview = view * model;
            modelview.transpose();
            glUniformMatrix4fv(modelview_loc, 1, GL_FALSE, modelview.data());

            // 投影変換（プロジェクション変換行列）
            my::Matrix projection = proj;
            projection.transpose();
            glUniformMatrix4fv(projection_loc, 1, GL_FALSE, projection.data());

            // GL描画設定
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glEnable(GL_TEXTURE_2D);

            // テクスチャバインド
            glBindTexture(GL_TEXTURE_2D, m_texid);

            // テクスチャパラメータ設定
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            // テクスチャユニット0を指定
            glUniform1i(texture_loc, 0);

            //テクスチャ色
            GLfloat color[4];
            color[0] = m_color.r() / 255.0F;
            color[1] = m_color.g() / 255.0F;
            color[2] = m_color.b() / 255.0F;
            color[3] = m_color.a() / 255.0F;
            glUniform4fv(texcolor_loc, 1, &color[0]);

            // 頂点配列オブジェクトの結合
            glBindVertexArray(this->m_vao);
            glBindBuffer(GL_ARRAY_BUFFER, this->m_vertex_vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_index_vbo);
            // 頂点データを指定
            glEnableVertexAttribArray(pos_loc);
            glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            // UV座標データを指定
            glEnableVertexAttribArray(uv_loc);
            glVertexAttribPointer(uv_loc, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)(m_vertexes.size() * sizeof(my::Vertex)));

            // 描画実行
            GLsizei icnt = static_cast<GLsizei>(m_indexes.size());
            glDrawElements(GL_TRIANGLE_STRIP, icnt, GL_UNSIGNED_INT, nullptr);

            // 頂点配列オブジェクトの結合を解除
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            //テクスチャアンバインド
            glBindTexture(GL_TEXTURE_2D, 0);

            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
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
        Shape           m_lines;            //!< 線：ライン
        Shape           m_line_strip;       //!< 線：ラインストリップ
        Shape           m_line_loop;        //!< 線：ラインループ
        Shape           m_triangles;        //!< 面：ポリゴン
        Shape           m_triangle_strip;   //!< 面：ストリップ
        Shape           m_triangle_fan;     //!< 面：ファン
        Shape           m_points;           //!< 点
        Text            m_text_ascii;       //!< テキスト
        Text            m_text_kana;        //!< テキスト
        Text            m_text_bold;        //!< テキスト

    public:
        //! コンストラクタ
        Screen(GLFWwindow* window) :
            m_window(window), m_width(0), m_height(0), m_fbWidth(0), m_fbHeight(0), m_scale(DEFSCALE),
            m_bgcolor(DEFCOLOR[0], DEFCOLOR[1], DEFCOLOR[2], DEFCOLOR[3]),
            m_lines(GL_LINES, LINE_V, LINE_I, LINE_C),
            m_line_strip(GL_LINE_STRIP, LINE_V, LINE_I, LINE_C),
            m_line_loop(GL_LINE_LOOP, LINE_V, LINE_I, LINE_C),
            m_triangles(GL_TRIANGLES, TRIANGLE_V, TRIANGLE_I, TRIANGLE_C),
            m_triangle_strip(GL_TRIANGLE_STRIP, TRIANGLE_V, TRIANGLE_I, TRIANGLE_C),
            m_triangle_fan(GL_TRIANGLE_FAN, TRIANGLE_V, TRIANGLE_I, TRIANGLE_C),
            m_points(GL_POINTS, POINT_V, POINT_I, POINT_C),
            m_text_ascii(TEXT_ASCII),
            m_text_kana(TEXT_KANA),
            m_text_bold(TEXT_BOLD)
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
            const float w_f = static_cast<float>(m_fbWidth);
            const float h_f = static_cast<float>(m_fbHeight);

            // 画面クリア
            glClearColor(m_bgcolor.clamp_r(), m_bgcolor.clamp_g(), m_bgcolor.clamp_b(), m_bgcolor.clamp_a());
            glClear(GL_COLOR_BUFFER_BIT);
            // ビューポートの設定
            glViewport(0, 0, m_fbWidth, m_fbHeight);
            // カメラの設定（ビュー変換行列）
            const my::Vector CAMERA_EYE = {w_f / 2.0F, h_f / 2.0F, 5.0f};
            const my::Vector CAMERA_CENTER = {w_f / 2.0F, h_f / 2.0F, 0.0F};
            const my::Vector CAMERA_UP = {0.0F, 1.0F, 0.0F};
            my::Matrix view = my::Matrix::lookat(CAMERA_EYE, CAMERA_CENTER, CAMERA_UP);
            // 投影変換
            const float w = m_fbWidth / m_scale / 2.0F;
            const float h = m_fbHeight / m_scale / 2.0F;
            my::Matrix proj = my::Matrix::orthogonal(-w, w, -h, h, 1.0F, 10.0F);
            // 線：ライン描画
            glLineWidth(5.0F);
            m_lines.setPosition(LINES_POS);
            m_lines.draw(view, proj);
            // 線：ラインストリップ描画
            m_line_strip.setPosition(LINE_STRIP_POS);
            m_line_strip.draw(view, proj);
            // 線：ラインループ描画
            m_line_loop.setPosition(LINE_LOOP_POS);
            m_line_loop.draw(view, proj);
            // 面：ポリゴン描画
            m_triangles.setPosition(TRIANGLES_POS);
            m_triangles.draw(view, proj);
            // 面：ポリゴン描画
            m_triangle_strip.setPosition(TRIANGLE_STRIP_POS);
            m_triangle_strip.draw(view, proj);
            // 面：ポリゴン描画
            m_triangle_fan.setPosition(TRIANGLE_FAN_POS);
            m_triangle_fan.draw(view, proj);
            // 点
            glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
            m_points.setPosition(POINTS_POS);
            m_points.draw(view, proj);
            // テキスト
            m_text_ascii.setPosition(TEXT_ASCII_POS);
            m_text_ascii.setSize(TEXT_ASCII_SZ);
            m_text_ascii.setColor(TEXT_ASCII_C);
            m_text_ascii.draw(view, proj);
            // テキスト
            m_text_kana.setPosition(TEXT_KANA_POS);
            m_text_kana.setSize(TEXT_KANA_SZ);
            m_text_kana.setColor(TEXT_KANA_C);
            m_text_kana.draw(view, proj);
            // テキスト
            m_text_bold.setPosition(TEXT_BOLD_POS);
            m_text_bold.setSize(TEXT_BOLD_SZ);
            m_text_bold.setBold(Text::BOLD::YES);
            m_text_bold.setColor(TEXT_BOLD_C);
            m_text_bold.draw(view, proj);
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
    static void glfw_window_resize_callback(GLFWwindow* window, int width, int height)
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

    //! GLFWでマウスの釦が押されたときに呼ばれるコールバック関数
    static void glfw_window_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        std::cout << "[GLFW MOUSE_BTN] button:" << button << " action:" << action << " mods:" << mods << " (" << window << ")" << std::endl;
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
    static void glfw_window_mouse_position_callback(GLFWwindow *window, double x, double y)
    {
        //std::cout << "[GLFW MOUSE_POS] x:" << x << " y:" << y << " (" << window << ")" << std::endl;
    }

    //! GLFWでマウスホイールを動かしたときに呼ばれるコールバック関数
    static void glfw_window_mouse_scroll_callback(GLFWwindow *window, double x, double y)
    {
        std::cout << "[GLFW MOUSE_SCRL] x:" << x << " y:" << y << " (" << window << ")" << std::endl;
    }

    //! GLFWでキーが入力されたときに呼ばれるコールバック関数
    static void glfw_window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        std::cout << "[GLFW KEY] key:" << key << " scancode:" << scancode << " action:" << action << " mods:0x" << mods << " (" << window << ")" << std::endl;
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
    // GLFWでマウスの釦が押されたときに呼ばれる関数を登録する
    glfwSetMouseButtonCallback(window, glfw_window_mouse_button_callback);
    // GLFWでマウスカーソルの位置が変化したときに呼ばれる関数を登録する
    glfwSetCursorPosCallback(window, glfw_window_mouse_position_callback);
    // GLFWでマウスホイールを動かしたときに呼ばれる関数を登録する
    glfwSetScrollCallback(window, glfw_window_mouse_scroll_callback);
    // GLFWでキーが入力されたときに呼ばれる関数を登録する
    glfwSetKeyCallback(window, glfw_window_key_callback);

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