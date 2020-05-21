/**
 * @file Vertex.hpp
 * @author kota-kota
 * @brief 頂点に関連するクラスの定義
 * @version 0.1
 * @date 2020-05-19
 * 
 * @copyright Copyright (c) 2020
 */
#ifndef INCLUDED_VERTEX_HPP
#define INCLUDED_VERTEX_HPP

#include <cstdint>
#include <vector>

namespace my {
    /**
     * @class Color
     * @brief 色を扱うクラス
     */
    class Color {
        std::uint8_t   m_r; //!< [0-255]の範囲のR値
        std::uint8_t   m_g; //!< [0-255]の範囲のG値
        std::uint8_t   m_b; //!< [0-255]の範囲のB値
        std::uint8_t   m_a; //!< [0-255]の範囲のA値

    public:
        //! デフォルトコンストラクタ
        Color();
        //! コンストラクタ
        Color(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b, const std::uint8_t a);

    public:
        //! R値を[0-255]の範囲で取得
        std::uint8_t r() const;
        //! G値を[0-255]の範囲で取得
        std::uint8_t g() const;
        //! B値を[0-255]の範囲で取得
        std::uint8_t b() const;
        //! A値を[0-255]の範囲で取得
        std::uint8_t a() const;

    public:
        //! R値を[0-1]の範囲で取得
        float clamp_r() const;
        //! G値を[0-1]の範囲で取得
        float clamp_g() const;
        //! B値を[0-1]の範囲で取得
        float clamp_b() const;
        //! A値を[0-1]の範囲で取得
        float clamp_a() const;
    };

    /**
     * @brief Colorの並び
     * 
     */
    using Colors = std::vector<Color>;
}

namespace my {
    /**
     * @class Vertex
     * @brief 頂点を扱うクラス
     */
    class Vertex {
        float   m_x;    //!< X座標
        float   m_y;    //!< Y座標
        float   m_z;    //!< Z座標

    public:
        //! デフォルトコンストラクタ
        Vertex();
        //! コンストラクタ
        Vertex(const float x, const float y, const float z = 0.0F);

    public:
        //! X座標を取得
        float x() const;
        //! Y座標を取得
        float y() const;
        //! Z座標を取得
        float z() const;
    };

    /**
     * @brief Vertexの並び
     * 
     */
    using Vertexes = std::vector<Vertex>;
}

namespace my {
    /**
     * @class Index
     * @brief 頂点インデックスを扱うクラス
     */
    class Index {
        std::uint32_t   m_idx;    //!< インデックス値

    public:
        //! デフォルトコンストラクタ
        Index();
        //! コンストラクタ
        Index(const std::uint32_t idx);

    public:
        //! インデックス値を取得
        std::uint32_t idx() const;
    };

    /**
     * @brief Indexの並び
     * 
     */
    using Indexes = std::vector<Index>;
}

#endif //INCLUDED_VERTEX_HPP
