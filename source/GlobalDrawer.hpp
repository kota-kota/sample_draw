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
     * @class ShapeShader
     * @brief shapeシェーダのプログラムを扱うクラス
     * 
     */
    class ShapeShader {
        GLuint  m_progid;           //!< シェーダプログラムID
        GLint   m_loc_modelview;    //!< モデルビュー変換行列のunifrom位置
        GLint   m_loc_projection;   //!< プロジェクション変換行列のunifrom位置
        GLint   m_loc_pos;          //!< 頂点のattribute位置
        GLint   m_loc_col;          //!< 色のattribute位置

    public:
        //! デフォルトコンストラクタ
        ShapeShader();
        //! コンストラクタ
        ShapeShader(const GLuint progid, const GLint loc_modelview, const GLint loc_projection, const GLint loc_pos, const GLint loc_col);

    public:
        //! シェーダプログラムを取得
        GLuint getProgram() const;
        //! モデルビュー変換行列のunifrom位置を取得
        GLint getModelViewLocation() const;
        //! プロジェクション変換行列のunifrom位置を取得
        GLint getProjectionLocation() const;
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
        ShapeShader       m_shape_shader;     //!< shapeシェーダのプログラム

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
        //! shapeシェーダのプログラムの取得
        ShapeShader getShapeShader() const;

    private:
        //! shapeシェーダの読み込み
        void loadShapeShader();

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
    };
}

#endif //INCLUDED_GLOBALDRAWER_HPP
