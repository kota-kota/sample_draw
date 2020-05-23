/**
 * @file Object.cpp
 * @author kota-kota
 * @brief 描画オブジェクトに関連するクラスの実装
 * @version 0.1
 * @date 2020-05-19
 * 
 * @copyright Copyright (c) 2020
 */
#include "Object.hpp"
#include "GlobalDrawer.hpp"

#include <iostream>

namespace my {
    /**
     * @brief コンストラクタ
     * 
     * @param [in] mode OpenGLの描画モードを指定する（glDrawElementsの第1引数と同じ）
     * @param [in] vertexes 頂点の並び
     * @param [in] indexes 頂点インデックスの並び
     * @param [in] colors 頂点色の並び
     * 
     * @par 詳細
     *      オブジェクト描画に必要な資源を生成する。
     *      主な資源は、以下。
     *          頂点配列オブジェクト
     *          頂点バッファオブジェクト
     *          頂点インデックスバッファオブジェクト
     */
    Shape::Shape(const GLenum mode, const Vertexes& vertexes, const Indexes& indexes, const Colors& colors) :
        m_vao(0U), m_vertex_vbo(0U), m_index_vbo(0U), m_mode(mode), m_vertexes(vertexes), m_indexes(indexes), m_colors(colors)
    {
        // 頂点配列オブジェクトを作成する
        glGenVertexArrays(1, &this->m_vao);
        std::cout << "* VAO:" << m_vao << std::endl;
        glBindVertexArray(this->m_vao);

        // 頂点用のバッファオブジェクトを作成する
        glGenBuffers(1, &this->m_vertex_vbo);
        std::cout << "* VBO V:" << m_vertex_vbo << std::endl;
        glBindBuffer(GL_ARRAY_BUFFER, this->m_vertex_vbo);
        const std::int32_t vsize = static_cast<std::int32_t>(vertexes.size() * sizeof(Vertex));
        const std::int32_t csize = static_cast<std::int32_t>(colors.size() * sizeof(Color));
        glBufferData(GL_ARRAY_BUFFER, vsize * csize, nullptr, GL_DYNAMIC_DRAW);
        // 頂点データを転送する
        glBufferSubData(GL_ARRAY_BUFFER, 0, vsize, &vertexes[0]);
        // 色データを転送する
        glBufferSubData(GL_ARRAY_BUFFER, vsize, csize, &colors[0]);

        // 頂点インデックス用のバッファオブジェクトを作成する
        glGenBuffers(1, &this->m_index_vbo);
        std::cout << "* VBO I:" << m_index_vbo << std::endl;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_index_vbo);
        const std::int32_t isize = static_cast<std::int32_t>(indexes.size() * sizeof(GLuint));
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize, nullptr, GL_DYNAMIC_DRAW);
        // 頂点インデックスデータを転送する
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, isize, &indexes[0]);
    }

    /**
     * @brief デストラクタ
     * 
     * @par 詳細
     *      オブジェクト描画に必要な資源を破棄する。
     */
    Shape::~Shape()
    {
        // 頂点配列オブジェクトを破棄する
        glDeleteVertexArrays(1, &this->m_vao);
        // 頂点用のバッファオブジェクトを破棄する
        glDeleteBuffers(1, &this->m_vertex_vbo);
        // 頂点インデックス用のバッファオブジェクトを破棄する
        glDeleteBuffers(1, &this->m_index_vbo);
    }

    /**
     * @brief 描画
     * 
     * @par 詳細
     *      なし
     */
    void Shape::draw()
    {
        // シェーダ取得
        Shader_11ShapeSimple shader = GlobalDrawer::instance().getShader_11ShapeSimple();
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
        glVertexAttribPointer(col_loc, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, (GLubyte*)(this->m_vertexes.size() * sizeof(Vertex)));
        glEnableVertexAttribArray(col_loc);

        // 描画実行
        GLsizei icnt = static_cast<GLsizei>(this->m_indexes.size());
        glDrawElements(this->m_mode, icnt, GL_UNSIGNED_INT, nullptr);
    }
}
