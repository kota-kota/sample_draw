/**
 * @file Object.hpp
 * @author kota-kota
 * @brief 描画オブジェクトに関連するクラスの定義
 * @version 0.1
 * @date 2020-05-19
 * 
 * @copyright Copyright (c) 2020
 */
#ifndef INCLUDED_OBJECT_HPP
#define INCLUDED_OBJECT_HPP

#include "Vertex.hpp"

#include <GL/glew.h>

#include <cstdint>

namespace my {
    /**
     * @class Shape
     * @brief 形状のオブジェクトを扱うクラス
     */
    class Shape {
    protected:
        GLuint      m_vao;          //!< 頂点配列オブジェクト
        GLuint      m_vertex_vbo;   //!< 頂点用のバッファオブジェクト
        GLuint      m_index_vbo;    //!< 頂点インデックス用のバッファオブジェクト
        GLenum      m_mode;         //!< 描画モード
        Vertexes    m_vertexes;     //!< 頂点座標の並び
        Indexes     m_indexes;      //!< 頂点インデックスの並び
        Colors      m_colors;       //!< 頂点色の並び

    public:
        //! コンストラクタ
        Shape(const GLenum mode, const Vertexes& vertexes, const Indexes& indexes, const Colors& colors);
        //! デストラクタ
        ~Shape();

        //! コピーコンストラクタによるコピー禁止
        Shape(const Shape& org) = delete;
        //! 代入によるコピー禁止
        Shape& operator=(const Shape& org) = delete;

    public:
        //! 描画
        void draw();
    };
}

#endif //INCLUDED_OBJECT_HPP
