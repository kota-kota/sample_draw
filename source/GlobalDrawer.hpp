/**
 * @file GlobalDrawer.hpp
 * @author kota-kota
 * @brief グローバルな描画資源を扱うクラスの定義
 * @version 0.1
 * @date 2020-05-19
 * 
 * @copyright Copyright (c) 2020
 */
#ifndef INCLUDED_GLOBALDRAWER_HPP
#define INCLUDED_GLOBALDRAWER_HPP

#include <GL/glew.h>

#include <cstdint>
#include <string>

namespace my {
    /**
     * @class Shader_11ShapeSimple
     * @brief 11_shape_simpleシェーダのプログラムを扱うクラス
     * 
     */
    class Shader_11ShapeSimple {
        GLuint  m_progid;   //!< シェーダプログラムID
        GLint   m_loc_pos;  //!< 頂点のattribute位置
        GLint   m_loc_col;  //!< 色のattribute位置

    public:
        //! デフォルトコンストラクタ
        Shader_11ShapeSimple();
        //! コンストラクタ
        Shader_11ShapeSimple(const GLuint progid, const GLint loc_pos, const GLint loc_col);

    public:
        //! シェーダプログラムを取得
        GLuint getProgram() const;
        //! 頂点のattribute位置を取得
        GLint getPositionLocation() const;
        //! 色のattribute位置を取得
        GLint getColorLocation() const;
    };
}

namespace my {
    /**
     * @class Shader_12ShapeMVP
     * @brief 12_shape_mvpシェーダのプログラムを扱うクラス
     * 
     */
    class Shader_12ShapeMVP {
        GLuint  m_progid;       //!< シェーダプログラムID
        GLint   m_loc_model;    //!< モデル変換行列のunifrom位置
        GLint   m_loc_pos;      //!< 頂点のattribute位置
        GLint   m_loc_col;      //!< 色のattribute位置

    public:
        //! デフォルトコンストラクタ
        Shader_12ShapeMVP();
        //! コンストラクタ
        Shader_12ShapeMVP(const GLuint progid, const GLint loc_model, const GLint loc_pos, const GLint loc_col);

    public:
        //! シェーダプログラムを取得
        GLuint getProgram() const;
        //! モデル変換行列のunifrom位置を取得
        GLint getModelLocation() const;
        //! 頂点のattribute位置を取得
        GLint getPositionLocation() const;
        //! 色のattribute位置を取得
        GLint getColorLocation() const;
    };
}

namespace my {
    /**
     * @class ShaderBuilder
     * @brief シェーダをビルドおよび管理するクラス
     */
    class ShaderBuilder {
        Shader_11ShapeSimple    m_11_shape_simple;  //!< 11_shape_simpleシェーダのプログラム
        Shader_12ShapeMVP       m_12_shape_mvp;     //!< 12_shape_mvpシェーダのプログラム

    public:
        //! デフォルトコンストラクタ
        ShaderBuilder();
        //! デストラクタ
        ~ShaderBuilder();
        //! コピーコンストラクタによるコピー禁止
        ShaderBuilder(const ShaderBuilder& org) = delete;
        //! 代入によるコピー禁止
        ShaderBuilder& operator=(const ShaderBuilder& org) = delete;

    public:
        //! 11_shape_simpleシェーダのプログラムの取得
        Shader_11ShapeSimple getShader_11ShapeSimple() const;
        //! 12_shape_mvpシェーダのプログラムの取得
        Shader_12ShapeMVP getShader_12ShapeMVP() const;

    private:
        //! 11_shape_simpleシェーダの読み込み
        void loadShader_11ShapeSimple();
        //! 12_shape_mvpシェーダの読み込み
        void loadShader_12ShapeMVP();

    private:
        //! シェーダソースをファイル読み込み
        std::string readShaderSource(const std::string srcpath);
        //! シェーダプログラムの作成
        GLuint createProgram(const std::string& vsrc, const std::string& fsrc);

    private:
        //! シェーダのコンパイルログを出力
        void printShaderLog(const GLuint shader);
    };
}

namespace my {
    /**
     * @class GlobalDrawer
     * @brief グローバルな描画資源を扱うクラス(シングルトン)
     */
    class GlobalDrawer {
        std::int32_t    m_width;            //!< 画面幅[pixel]
        std::int32_t    m_height;           //!< 画面高さ[pixel]
        std::int32_t    m_fbwidth;          //!< フレームバッファ幅[pixel]
        std::int32_t    m_fbHeight;         //!< フレームバッファ高さ[pixel]
        float           m_scale;            //!< 拡大率
        ShaderBuilder   m_shaderbuilder;    //!< シェーダビルダーインスタンス

    private:
        //! デフォルトコンストラクタ
        GlobalDrawer();
        //! デストラクタ
        ~GlobalDrawer() = default;
        //! コピーコンストラクタによるコピー禁止
        GlobalDrawer(const GlobalDrawer& org) = delete;
        //! 代入によるコピー禁止
        GlobalDrawer& operator=(const GlobalDrawer& org) = delete;

    public:
        //! インスタンスを取得
        static GlobalDrawer& instance();

    public:
        //! ShaderBuilderインスタンスを取得
        ShaderBuilder& getShaderBuilder();

    public:
        //! 画面サイズの変更
        void resize(const std::int32_t w, const std::int32_t h);
        //! フレームバッファサイズの変更
        void changeFramebufferSize(const std::int32_t w, const std::int32_t h);
        //! 拡大率の変更
        void changeScale(const float scale);

    public:
        //! フレームバッファサイズを取得
        void getFramebufferSize(std::int32_t* w, std::int32_t* h) const;
    };
}

#endif //INCLUDED_GLOBALDRAWER_HPP
