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
    Vector::Vector() :
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
    Vector::Vector(const float x, const float y, const float z) :
        m_x(x), m_y(y), m_z(z)
    {
    }

    /**
     * @brief +演算子のオーバーロード
     * 
     * @param [in] v 加算するベクトル
     * @return Vector 加算後のベクトル
     */
    Vector Vector::operator+(const Vector& v) const
    {
        Vector t;
        t.m_x = this->m_x + v.m_x;
        t.m_y = this->m_y + v.m_y;
        t.m_z = this->m_z + v.m_z;
        return t;
    }

    /**
     * @brief -演算子のオーバーロード
     * 
     * @param [in] v 減算するベクトル
     * @return Vector 減算後のベクトル
     */
    Vector Vector::operator-(const Vector& v) const
    {
        Vector t;
        t.m_x = this->m_x - v.m_x;
        t.m_y = this->m_y - v.m_y;
        t.m_z = this->m_z - v.m_z;
        return t;
    }

    /**
     * @brief *演算子のオーバーロード
     * 
     * @param [in] v 乗算するベクトル
     * @return Vector 乗算後のベクトル（外積ベクトル）
     */
    Vector Vector::operator*(const Vector& v) const
    {
        Vector t;
        t.m_x = (this->m_y * v.m_z) - (this->m_z * v.m_y);
        t.m_y = (this->m_z * v.m_x) - (this->m_x * v.m_z);
        t.m_z = (this->m_x * v.m_y) - (this->m_y * v.m_x);
        return t;
    }

    /**
     * @brief +=演算子のオーバーロード
     * 
     * @param [in] v 加算するベクトル
     * @return Vector 加算後のベクトル
     */
    Vector& Vector::operator+=(const Vector& v)
    {
        this->m_x += v.m_x;
        this->m_y += v.m_y;
        this->m_z += v.m_z;
        return *this;
    }

    /**
     * @brief -=演算子のオーバーロード
     * 
     * @param [in] v 減算するベクトル
     * @return Vector 減算後のベクトル
     */
    Vector& Vector::operator-=(const Vector& v)
    {
        this->m_x -= v.m_x;
        this->m_y -= v.m_y;
        this->m_z -= v.m_z;
        return *this;
    }

    /**
     * @brief *=演算子のオーバーロード
     * 
     * @param [in] v 乗算するベクトル
     * @return Vector 乗算後のベクトル（外積ベクトル）
     */
    Vector& Vector::operator*=(const Vector& v)
    {
        Vector t;
        t.m_x = (this->m_y * v.m_z) - (this->m_z * v.m_y);
        t.m_y = (this->m_z * v.m_x) - (this->m_x * v.m_z);
        t.m_z = (this->m_x * v.m_y) - (this->m_y * v.m_x);
        *this = t;
        return *this;
    }

    /**
     * @brief X座標を取得
     * 
     * @return float X座標
     */
    float Vector::x() const { return this->m_x; }
    /**
     * @brief Y座標を取得
     * 
     * @return float Y座標
     */
    float Vector::y() const { return this->m_y; }
    /**
     * @brief Z座標を取得
     * 
     * @return float Z座標
     */
    float Vector::z() const { return this->m_z; }

    /**
     * @brief ベクトルの長さを取得
     * 
     * @return float ベクトルの長さ
     */
    float Vector::len() const { return sqrtf(this->len2()); }

    /**
     * @brief ベクトルの長さの2乗を取得
     * 
     * @return float ベクトルの長さの2乗
     */
    float Vector::len2() const { return (m_x * m_x) + (m_y * m_y) + (m_z * m_z); }
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
     * @brief 転置
     * 
     */
    void Matrix::transpose()
    {
        Matrix t;
        t[ 0] = (*this)[ 0]; t[ 1] = (*this)[ 4]; t[ 2] = (*this)[ 8]; t[ 3] = (*this)[12];
        t[ 4] = (*this)[ 1]; t[ 5] = (*this)[ 5]; t[ 6] = (*this)[ 9]; t[ 7] = (*this)[13];
        t[ 8] = (*this)[ 2]; t[ 9] = (*this)[ 6]; t[10] = (*this)[10]; t[11] = (*this)[14];
        t[12] = (*this)[ 3]; t[13] = (*this)[ 7]; t[14] = (*this)[11]; t[15] = (*this)[15];
        *this = t;
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
     * @param [in] v 移動量のベクトル
     * 
     * @return Matrix 平行移動する変換行列
     */
    Matrix Matrix::translate(const Vector& v)
    {
        Matrix t = Matrix::identity();
        t[3] = v.x(); t[7] = v.y(); t[11] = v.z();
        return t;
    }

    /**
     * @brief (x,y,z)倍に拡大縮小する変換行列を作成
     * 
     * @param [in] v 拡大縮小倍率のベクトル
     * 
     * @return Matrix 拡大縮小する変換行列
     */
    Matrix Matrix::scale(const Vector& v)
    {
        Matrix t = Matrix::identity();
        t[0] = v.x(); t[5] = v.y(); t[10] = v.z();
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

    /**
     * @brief 任意の(x,y,z)軸を中心にdegree度回転する変換行列を作成
     * 
     * @param [in] degree 角度[度]のインスタンス
     * @param [in] v 回転軸のベクトル
     * 
     * @return Matrix 回転する変換行列
     */
    Matrix Matrix::rotate(const Degree degree, const Vector& v)
    {
        const float rad = degree.radian().rad();
        const float d = sqrtf(v.x()*v.x() + v.y()*v.y() + v.z()*v.z());
        if (d > 0.0F) {
            return Matrix::identity();
        }

        const float l(v.x() / d), m(v.y() / d), n(v.z() / d);
        const float l2(l * l), m2(m * m), n2(n * n);
        const float lm(l * m), mn(m * n), nl(n * l);
        const float c(cosf(rad)), c1(1.0f - c), s(sinf(rad));

        Matrix t = Matrix::identity();
        t[ 0] = (1.0f - l2) * c + l2;
        t[ 1] = lm * c1 - n * s;
        t[ 2] = nl * c1 + m * s;
        t[ 4] = lm * c1 + n * s;
        t[ 5] = (1.0f - m2) * c + m2;
        t[ 6] = mn * c1 - l * s;
        t[ 8] = nl * c1 - m * s;
        t[ 9] = mn * c1 + l * s;
        t[10]= (1.0f - n2) * c + n2;
        return t;
    }

    /**
     * @brief ビュー変換行列を作成
     * 
     * @param [in] eye 視点の位置
     * @param [in] center 目標点の位置
     * @param [in] up 上方向のベクトル
     * 
     * @return Matrix ビュー変換行列
     */
    Matrix Matrix::lookat(const Vector eye, const Vector center, const Vector up)
    {
        // 平行移動の変換行列
        Vector _eye(-eye.x(), -eye.y(), -eye.z());
        const Matrix tv = translate(_eye);

        // t軸 = eye - center
        const Vector t = eye - center;
        // r軸 = up x t軸
        const Vector r = up * t;
        // s軸 = t軸 x r軸
        const Vector s = t * r;
        // s軸の長さのチェック
        if (s.len() == 0.0f) {
            return tv;
        }

        // 回転の変換行列
        Matrix rv = Matrix::identity();
        // r軸を正規化して配列変数に格納
        const float rlen = r.len();
        rv[ 0] = r.x() / rlen;
        rv[ 1] = r.y() / rlen;
        rv[ 2] = r.z() / rlen;
        // s軸を正規化して配列変数に格納
        const float slen = s.len();
        rv[ 4] = s.x() / slen;
        rv[ 5] = s.y() / slen;
        rv[ 6] = s.z() / slen;
        // t軸を正規化して配列変数に格納
        const float tlen = t.len();
        rv[ 8] = t.x() / tlen;
        rv[ 9] = t.y() / tlen;
        rv[10] = t.z() / tlen;

        // 視点の平行移動の変換行列に視線の回転の変換行列を乗じる
        return tv * rv;
    }

    /**
     * @brief 直交投影変換行列を作成
     * 
     * @param [in] left 視体積の前方面の左の垂直座標
     * @param [in] right 視体積の前方面の右の垂直座標
     * @param [in] bottom 視体積の前方面の下の水平座標
     * @param [in] top 視体積の前方面の上の水平座標
     * @param [in] znear 視点から最も近い距離
     * @param [in] zfar 視点から最も遠い距離
    * 
     * @return Matrix 直交投影変換行列
     */
    Matrix Matrix::orthogonal(const float left, const float right, const float bottom, const float top, const float znear, const float zfar)
    {
        Matrix t = my::Matrix::identity();
        const float dx = right - left;
        const float dy = top - bottom;
        const float dz = zfar - znear;
        if ((dx != 0.0f) && (dy != 0.0f) && (dz != 0.0f)) {
            t[ 0] = 2.0f / dx;
            t[ 3] = -(right + left) / dx;
            t[ 5] = 2.0f / dy;
            t[ 7] = -(top + bottom) / dy;
            t[10] = -2.0f / dz;
            t[11] = -(zfar + znear) / dz;
        }
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
        m1 = Matrix::scale({5.0F, 10.0F, 15.0F});
        m2 = Matrix::scale({20.0F, 3.0F, 2.0F});
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