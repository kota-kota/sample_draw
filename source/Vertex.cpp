/**
 * @file Vertex.cpp
 * @author kota-kota
 * @brief 頂点に関連するクラスの実装
 * @version 0.1
 * @date 2020-05-21
 * 
 * @copyright Copyright (c) 2020
 */

#include "Vertex.hpp"

namespace my {
    /**
     * @brief デフォルトコンストラクタ
     * 
     */
    Color::Color() :
        m_r(0), m_g(0), m_b(0), m_a(0)
    {
    }

    /**
     * @brief コンストラクタ
     * 
     * @param [in] r [0-255]の範囲のR値
     * @param [in] g [0-255]の範囲のG値
     * @param [in] b [0-255]の範囲のB値
     * @param [in] a [0-255]の範囲のA値
     */
    Color::Color(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b, const std::uint8_t a) :
        m_r(r), m_g(g), m_b(b), m_a(a)
    {
    }

    /**
     * @brief R値を[0-255]の範囲で取得
     * 
     * @return std::uint8_t [0-255]の範囲のR値
     */
    std::uint8_t Color::r() const { return this->m_r; }
    /**
     * @brief G値を[0-255]の範囲で取得
     * 
     * @return std::uint8_t [0-255]の範囲のG値
     */
    std::uint8_t Color::g() const { return this->m_g; }
    /**
     * @brief B値を[0-255]の範囲で取得
     * 
     * @return std::uint8_t [0-255]の範囲のB値
     */
    std::uint8_t Color::b() const { return this->m_b; }
    /**
     * @brief A値を[0-255]の範囲で取得
     * 
     * @return std::uint8_t [0-255]の範囲のA値
     */
    std::uint8_t Color::a() const { return this->m_a; }

    /**
     * @brief R値を[0-1]の範囲で取得
     * 
     * @return float [0-1]の範囲のR値
     */
    float Color::clamp_r() const { return static_cast<float>(this->m_r) / 255.0F; }
    /**
     * @brief G値を[0-1]の範囲で取得
     * 
     * @return float [0-1]の範囲のG値
     */
    float Color::clamp_g() const { return static_cast<float>(this->m_g) / 255.0F; }
    /**
     * @brief B値を[0-1]の範囲で取得
     * 
     * @return float [0-1]の範囲のB値
     */
    float Color::clamp_b() const { return static_cast<float>(this->m_b) / 255.0F; }
    /**
     * @brief A値を[0-1]の範囲で取得
     * 
     * @return float [0-1]の範囲のA値
     */
    float Color::clamp_a() const { return static_cast<float>(this->m_a) / 255.0F; }
}

namespace my {
    /**
     * @brief デフォルトコンストラクタ
     * 
     */
    Vertex::Vertex() :
        m_x(0.0F), m_y(0.0F), m_z(0.0F)
    {
    }

    /**
     * @brief コンストラクタ
     * 
     * @param [in] x X座標
     * @param [in] y Y座標
     * @param [in] z Z座標
     */
    Vertex::Vertex(const float x, const float y, const float z) :
        m_x(x), m_y(y), m_z(z)
    {
    }

    /**
     * @brief X座標を取得
     * 
     * @return float X座標
     */
    float Vertex::x() const { return this->m_x; }
    /**
     * @brief Y座標を取得
     * 
     * @return float Y座標
     */
    float Vertex::y() const { return this->m_y; }
    /**
     * @brief Z座標を取得
     * 
     * @return float Z座標
     */
    float Vertex::z() const { return this->m_z; }
}

namespace my {
    /**
     * @brief デフォルトコンストラクタ
     * 
     */
    Index::Index() :
        m_idx(0U)
    {
    }

    /**
     * @brief コンストラクタ
     * 
     * @param [in] idx インデックス値
     */
    Index::Index(const std::uint32_t idx) :
        m_idx(idx)
    {
    }

    /**
     * @brief インデックス値を取得
     * 
     * @return std::uint32_t インデックス値
     */
    std::uint32_t Index::idx() const { return this->m_idx; }
}
