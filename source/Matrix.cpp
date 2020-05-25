/**
 * @file Matrix.cpp
 * @author kota-kota
 * @brief 行列を扱うクラスの実装
 * @version 0.1
 * @date 2020-05-25
 * 
 * @copyright Copyright (c) 2020
 */

#define _USE_MATH_DEFINES
#include "Matrix.hpp"
#include <cmath>

namespace my {
    /**
     * @brief デフォルトコンストラクタ
     * 
     */
    Degree::Degree() : m_deg(0.0F) {}

    /**
     * @brief コンストラクタ
     * 
     * @param [in] deg 角度[度]の値
     */
    Degree::Degree(const float deg) : m_deg(deg) {}

    //! コンストラクタ
    /**
     * @brief コンストラクタ
     * 
     * @param [in] rad 角度[ラジアン]のインスタンス
     */
    Degree::Degree(const Radian rad) : m_deg(rad.degree().deg()) {}

     /**
      * @brief 角度[度]の値を取得
      * 
      * @return float 角度[度]の値
      */
    float Degree::deg() const { return this->m_deg; }

    /**
     * @brief 角度[ラジアン]のインスタンスを取得
     * 
     * @return Radian 角度[ラジアン]のインスタンス
     */
    Radian Degree::radian() const
    {
        float rad = this->m_deg * static_cast<float>(M_PI) / 180.0F;
        return Radian(rad);
    }


    /**
     * @brief デフォルトコンストラクタ
     * 
     */
    Radian::Radian() : m_rad(0.0F) {}

    /**
     * @brief コンストラクタ
     * 
     * @param [in] rad 角度[ラジアン]の値
     */
    Radian::Radian(const float rad) : m_rad(rad) {}

    /**
     * @brief コンストラクタ
     * 
     * @param [in] deg 角度[度]のインスタンス
     */
    Radian::Radian(const Degree deg) : m_rad(deg.radian().rad()) {}

    /**
     * @brief 角度[ラジアン]の値を取得
     * 
     * @return float 角度[ラジアン]の値
     */
    float Radian::rad() const { return this->m_rad; }

    /**
     * @brief 角度[度]のインスタンスを取得
     * 
     * @return Degree 角度[度]のインスタンス
     */
    Degree Radian::degree() const
    {
        float deg = this->m_rad * 180.0F / static_cast<float>(M_PI);
        return Degree(deg);
    }
}

namespace my {
    /**
     * @brief デフォルトコンストラクタ
     * 
     */
    Matrix::Matrix() :
        std::array<float, 16>({0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F})
    {
    }

    /**
     * @brief +演算子のオーバーロード
     * 
     * @param [in] m 加算する行列
     * @return Matrix 加算後の行列
     */
    Matrix Matrix::operator+(const Matrix& m) const
    {
        Matrix t;
        for (std::int32_t i = 0; i < 16; ++i) {
            t[i] = (*this)[i] + m[i];
        }
        return t;
    }

    /**
     * @brief -演算子のオーバーロード
     * 
     * @param [in] m 減算する行列
     * @return Matrix 減算後の行列
     */
    Matrix Matrix::operator-(const Matrix& m) const
    {
        Matrix t;
        for (std::int32_t i = 0; i < 16; ++i) {
            t[i] = (*this)[i] - m[i];
        }
        return t;
    }

    /**
     * @brief *演算子のオーバーロード
     * 
     * @param [in] m 乗算する行列
     * @return Matrix 乗算後の行列
     */
    Matrix Matrix::operator*(const Matrix& m) const
    {
        Matrix t;
        for (std::int32_t i = 0; i < 16; ++i) {
            const std::int32_t j = i & 3;
            const std::int32_t k = i & ~3;
            t[i] =
                (*this)[ 0 + j] * m[k + 0] +
                (*this)[ 4 + j] * m[k + 1] +
                (*this)[ 8 + j] * m[k + 2] +
                (*this)[12 + j] * m[k + 3];
        }
        return t;
    }

    /**
     * @brief +=演算子のオーバーロード
     * 
     * @param [in] m 加算する行列
     * @return Matrix 加算後の行列
     */
    Matrix& Matrix::operator+=(const Matrix& m)
    {
        for (std::int32_t i = 0; i < 16; ++i) {
            (*this)[i] += m[i];
        }
        return *this;
    }

    /**
     * @brief -=演算子のオーバーロード
     * 
     * @param [in] m 減算する行列
     * @return Matrix 減算後の行列
     */
    Matrix& Matrix::operator-=(const Matrix& m)
    {
        for (std::int32_t i = 0; i < 16; ++i) {
            (*this)[i] -= m[i];
        }
        return *this;
    }

    /**
     * @brief *=演算子のオーバーロード
     * 
     * @param [in] m 乗算する行列
     * @return Matrix 乗算後の行列
     */
    Matrix& Matrix::operator*=(const Matrix& m)
    {
        Matrix t;
        for (std::int32_t i = 0; i < 16; ++i) {
            const std::int32_t j = i & 3;
            const std::int32_t k = i & ~3;
            t[i] =
                (*this)[ 0 + j] * m[k + 0] +
                (*this)[ 4 + j] * m[k + 1] +
                (*this)[ 8 + j] * m[k + 2] +
                (*this)[12 + j] * m[k + 3];
        }
        *this = t;
        return *this;
    }

    /**
     * @brief 単位行列を作成
     * 
     * @return Matrix 単位行列
     */
    Matrix Matrix::identity()
    {
        Matrix t;
        t[0] = 1.0F; t[5] = 1.0F; t[10] = 1.0F; t[15] = 1.0F;
        return t;
    }

    //! (x,y,z)だけ平行移動する変換行列を作成
    /**
     * @brief (x,y,z)だけ平行移動する変換行列を作成
     * 
     * @param [in] x X方向への移動量
     * @param [in] y Y方向への移動量
     * @param [in] z Z方向への移動量
     * 
     * @return Matrix 平行移動する変換行列
     */
    Matrix Matrix::translate(const float x, const float y, const float z)
    {
        Matrix t = Matrix::identity();
        t[3] = x; t[7] = y; t[11] = z;
        return t;
    }

    /**
     * @brief (x,y,z)倍に拡大縮小する変換行列を作成
     * 
     * @param [in] x X方向への拡大縮小倍率
     * @param [in] y Y方向への拡大縮小倍率
     * @param [in] z Z方向への拡大縮小倍率
     * 
     * @return Matrix 拡大縮小する変換行列
     */
    Matrix Matrix::scale(const float x, const float y, const float z)
    {
        Matrix t = Matrix::identity();
        t[0] = x; t[5] = y; t[10] = z;
        return t;
    }

    /**
     * @brief X軸を中心にdegree度回転する変換行列を作成
     * 
     * @param [in] degree 角度[度]のインスタンス
     * 
     * @return Matrix 回転する変換行列
     */
    Matrix Matrix::rotate_x(const Degree degree)
    {
        const float rad = degree.radian().rad();

        Matrix t = Matrix::identity();
        t[5] = cosf(rad); t[6] = -sinf(rad);
        t[9] = sinf(rad); t[10] = cosf(rad);
        return t;
    }

    /**
     * @brief Y軸を中心にdegree度回転する変換行列を作成
     * 
     * @param [in] degree 角度[度]のインスタンス
     * 
     * @return Matrix 回転する変換行列
     */
    Matrix Matrix::rotate_y(const Degree degree)
    {
        const float rad = degree.radian().rad();

        Matrix t = Matrix::identity();
        t[0] = cosf(rad); t[2] = sinf(rad);
        t[8] = sinf(rad); t[10] = cosf(rad);
        return t;
    }

    /**
     * @brief Z軸を中心にdegree度回転する変換行列を作成
     * 
     * @param [in] degree 角度[度]のインスタンス
     * 
     * @return Matrix 回転する変換行列
     */
    Matrix Matrix::rotate_z(const Degree degree)
    {
        const float rad = degree.radian().rad();

        Matrix t = Matrix::identity();
        t[0] = cosf(rad); t[1] = -sinf(rad);
        t[4] = sinf(rad); t[5] = cosf(rad);
        return t;
    }
    //! 任意の(x,y,z)軸を中心にdeg度回転する変換行列を作成
    /**
     * @brief 任意の(x,y,z)軸を中心にdegree度回転する変換行列を作成
     * 
     * @param [in] degree 角度[度]のインスタンス
     * @param [in] x 回転軸のX座標
     * @param [in] y 回転軸のY座標
     * @param [in] z 回転軸のZ座標
     * 
     * @return Matrix 回転する変換行列
     */
    Matrix Matrix::rotate(const Degree degree, const float x, const float y, const float z)
    {
        const float rad = degree.radian().rad();
        const float d = sqrtf(x*x + y*y + z*z);
        if (d > 0.0F) {
            return Matrix::identity();
        }

        const float l(x / d), m(y / d), n(z / d);
        const float l2(l * l), m2(m * m), n2(n * n);
        const float lm(l * m), mn(m * n), nl(n * l);
        const float c(cosf(rad)), c1(1.0f - c), s(sinf(rad));

        Matrix t = Matrix::identity();
        t[ 0] = (1.0f - l2) * c + l2;
        t[ 1] = lm * c1 + n * s;
        t[ 2] = nl * c1 - m * s;
        t[ 4] = lm * c1 - n * s;
        t[ 5] = (1.0f - m2) * c + m2;
        t[ 6] = mn * c1 + l * s;
        t[ 8] = nl * c1 + m * s;
        t[ 9] = mn * c1 - l * s;
        t[10]= (1.0f - n2) * c + n2;
        return t;
    }
}

namespace my {
    /**
     * @brief Matrixクラスのテストコードを実行
     * 
     */
    bool testcode_Matrix()
    {
        float deg = 0.0F, rad = 0.0F;
        Degree degree(45.0F);
        Radian radian = degree.radian();
        deg = radian.degree().deg();
        rad = radian.rad();

        Matrix m1 ,m2;
        m1 = Matrix::scale(5.0F, 10.0F, 15.0F);
        m2 = Matrix::scale(20.0F, 3.0F, 2.0F);
        Matrix add = m1 + m2;
        Matrix del = m1 - m2;
        Matrix mul = m1 * m2;

        Matrix add_eq = m1;
        add_eq += m2;
        Matrix del_eq = m1;
        del_eq -= m2;
        Matrix mul_eq = m1;
        mul_eq *= m2;

        return true;
    }
}