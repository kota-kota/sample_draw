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

namespace my {
    /**
     * @class Shader
     * @brief シェーダプログラムを扱うクラス
     * 
     */
    class Shader {
        GLuint  m_progid;   //!< シェーダプログラムID
        GLint   m_loc_pos;  //!< 頂点のattribute位置
        GLint   m_loc_col;  //!< 色のattribute位置

    public:
        //! デフォルトコンストラクタ
        Shader();
        //! コンストラクタ
        Shader(const GLuint progid, const GLint loc_pos, const GLint loc_col);

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
     * @class ShaderCompiler
     * @brief シェーダをコンパイルするクラス
     */
    class ShaderCompiler {
        Shader  m_shader;   //!< シェーダプログラム

    public:
        //! デフォルトコンストラクタ
        ShaderCompiler();
        //! デストラクタ
        ~ShaderCompiler();
        //! コピーコンストラクタによるコピー禁止
        ShaderCompiler(const ShaderCompiler& org) = delete;
        //! 代入によるコピー禁止
        ShaderCompiler& operator=(const ShaderCompiler& org) = delete;

    public:
        //! シェーダプログラムの取得
        Shader getShader() const;

    private:
        //! シェーダプログラムの作成
        GLuint createProgram(const char *vsrc, const char *fsrc);

    private:
        //! シェーダのコンパイルログを出力
        void printShaderLog(GLuint shader);
    };
}

namespace my {
    /**
     * @class GlobalDrawer
     * @brief グローバルな描画資源を扱うクラス(シングルトン)
     */
    class GlobalDrawer {
        std::int32_t    m_width;    //!< 画面幅[pixel]
        std::int32_t    m_height;   //!< 画面高さ[pixel]
        ShaderCompiler  m_shader;   //!< シェーダ

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
        //! 画面幅高さを設定
        void setScreen(const std::int32_t w, const std::int32_t h);

    public:
        //! シェーダプログラムを取得
        Shader getShader() const;
    };
}

#endif //INCLUDED_GLOBALDRAWER_HPP
