/**
 * @file Matrix.hpp
 * @author kota-kota
 * @brief 行列を扱うクラスの定義
 * @version 0.1
 * @date 2020-05-25
 * 
 * @copyright Copyright (c) 2020
 */
#ifndef INCLUDED_MATRIX_HPP
#define INCLUDED_MATRIX_HPP

#include <array>

namespace my {
    class Degree;
    class Radian;

    /**
     * @class Degree
     * @brief 角度を度の単位で扱うクラス
     * 
     */
    class Degree {
        float   m_deg;  //!< 角度[度]
    public:
        //! デフォルトコンストラクタ
        Degree();
        //! コンストラクタ
        Degree(const float deg);
        //! コンストラクタ
        Degree(const Radian rad);
    public:
        //! 角度[度]の値を取得
        float deg() const;
        //! 角度[ラジアン]のインスタンスを取得
        Radian radian() const;
    };

    /**
     * @class Radian
     * @brief 角度をラジアンの単位で扱うクラス
     * 
     */
    class Radian {
        float   m_rad;  //!< 角度[ラジアン]
    public:
        //! デフォルトコンストラクタ
        Radian();
        //! コンストラクタ
        Radian(const float rad);
        //! コンストラクタ
        Radian(const Degree deg);
    public:
        //! 角度[ラジアン]の値を取得
        float rad() const;
        //! 角度[度]のインスタンスを取得
        Degree degree() const;
    };
}

namespace my {
    /**
     * @class Matrix
     * @brief 4x4行列
     * 
     * @par 詳細
     *      4x4行列を要素数16の固定長配列で表現する。
     *      [ 0] [ 1] [ 2] [ 3]
     *      [ 4] [ 5] [ 6] [ 7]
     *      [ 8] [ 9] [10] [11]
     *      [12] [13] [14] [15]
     * 
     */
    class Matrix : public std::array<float, 16> {
    public:
        //! デフォルトコンストラクタ
        Matrix();

    public:
        //! +演算子のオーバーロード
        Matrix operator+(const Matrix& m) const;
        //! -演算子のオーバーロード
        Matrix operator-(const Matrix& m) const;
        //! *演算子のオーバーロード
        Matrix operator*(const Matrix& m) const;
        //! +=演算子のオーバーロード
        Matrix& operator+=(const Matrix& m);
        //! -=演算子のオーバーロード
        Matrix& operator-=(const Matrix& m);
        //! *=演算子のオーバーロード
        Matrix& operator*=(const Matrix& m);

    public:
        //! 単位行列を作成
        static Matrix identity();
        //! (x,y,z)だけ平行移動する変換行列を作成
        static Matrix translate(const float x, const float y, const float z);
        //! (x,y,z)倍に拡大縮小する変換行列を作成
        static Matrix scale(const float x, const float y, const float z);
        //! X軸を中心にdegree度回転する変換行列を作成
        static Matrix rotate_x(const Degree degree);
        //! Y軸を中心にdegree度回転する変換行列を作成
        static Matrix rotate_y(const Degree degree);
        //! Z軸を中心にdegree度回転する変換行列を作成
        static Matrix rotate_z(const Degree degree);
        //! 任意の(x,y,z)軸を中心にdegree度回転する変換行列を作成
        static Matrix rotate(const Degree degree, const float x, const float y, const float z);
    };
}

namespace my {
    //! Matrixクラスのテストコードを実行
    bool testcode_Matrix();
}

#endif //INCLUDED_MATRIX_HPP
