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

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ftsynth.h>
#include <freetype/ftglyph.h>

#include <cstdint>
#include <vector>
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
        GLint   m_loc_pointsize;    //!< ポイントサイズのunifrom位置
        GLint   m_loc_pos;          //!< 頂点のattribute位置
        GLint   m_loc_col;          //!< 色のattribute位置

    public:
        //! デフォルトコンストラクタ
        ShapeShader();
        //! コンストラクタ
        ShapeShader(const GLuint progid, const GLint loc_modelview, const GLint loc_projection, const GLint loc_pointsize, const GLint loc_pos, const GLint loc_col);

    public:
        //! シェーダプログラムを取得
        GLuint getProgram() const;
        //! モデルビュー変換行列のunifrom位置を取得
        GLint getModelViewLocation() const;
        //! プロジェクション変換行列のunifrom位置を取得
        GLint getProjectionLocation() const;
        //! ポイントサイズのunifrom位置を取得
        GLint getPointSizeLocation() const;
        //! 頂点のattribute位置を取得
        GLint getPositionLocation() const;
        //! 色のattribute位置を取得
        GLint getColorLocation() const;
    };
}

namespace my {
    /**
     * @class TextShader
     * @brief textシェーダのプログラムを扱うクラス
     * 
     */
    class TextShader {
        GLuint  m_progid;           //!< シェーダプログラムID
        GLint   m_loc_modelview;    //!< モデルビュー変換行列のunifrom位置
        GLint   m_loc_projection;   //!< プロジェクション変換行列のunifrom位置
        GLint   m_loc_texture;      //!< textureのuniform位置
        GLint   m_loc_texcolor;     //!< texcolorのuniform位置
        GLint   m_loc_pos;          //!< 頂点のattribute位置
        GLint   m_loc_uv;           //!< UV座標のattribute位置

    public:
        //! デフォルトコンストラクタ
        TextShader();
        //! コンストラクタ
        TextShader(const GLuint progid, const GLint loc_modelview, const GLint loc_projection, const GLint loc_texture, const GLint loc_texcolor, const GLint loc_pos, const GLint loc_uv);

    public:
        //! シェーダプログラムを取得
        GLuint getProgram() const;
        //! モデルビュー変換行列のunifrom位置を取得
        GLint getModelViewLocation() const;
        //! プロジェクション変換行列のunifrom位置を取得
        GLint getProjectionLocation() const;
        //! textureのunifrom位置を取得
        GLint getTextureLocation() const;
        //! texcolorのunifrom位置を取得
        GLint getTexColorLocation() const;
        //! 頂点のattribute位置を取得
        GLint getPositionLocation() const;
        //! UV座標のattribute位置を取得
        GLint getUVLocation() const;
    };
}

namespace my {
    /**
     * @class ShaderBuilder
     * @brief シェーダをビルドおよび管理するクラス
     */
    class ShaderBuilder {
        ShapeShader     m_shape_shader;     //!< shapeシェーダのプログラム
        TextShader      m_text_shader;      //!< textシェーダのプログラム

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
        //! textシェーダのプログラムの取得
        TextShader getTextShader() const;

    private:
        //! shapeシェーダの読み込み
        void loadShapeShader();
        //! textシェーダの読み込み
        void loadTextShader();

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
    using Binary = std::vector<std::uint8_t>;

    /**
     * @class Image
     * @brief 画像
     * 
     */
    class Image : public Binary {
        std::int32_t    m_width;    //!< 画像の幅[pixel]
        std::int32_t    m_height;   //!< 画像の高さ[pixel]
        std::int32_t    m_channel;  //!< 画像のチャンネル数

    public:
        //! デフォルトコンストラクタ
        Image();
        //! コンストラクタ
        Image(const std::int32_t width, const std::int32_t height, const std::int32_t channel);
        //! デストラクタ
        ~Image() = default;
        //! コピーコンストラクタ
        Image(const Image& org) = default;
        //! 代入によるコピー
        Image& operator=(const Image& org) = default;

    public:
        //! 画像の幅を取得
        std::int32_t width() const;
        //! 画像の高さを取得
        std::int32_t height() const;
        //! 画像のチャンネル数を取得
        std::int32_t channel() const;
    };
}

namespace my {
    /**
     * @class TextBuilder
     * @brief テキスト画像を生成するクラス
     */
    class TextBuilder {
        FT_Library              m_ft_library;   //!< FreeTypeインスタンスハンドル
        FT_Face	                m_ft_face;      //!< FreeTypeフェイスオブジェクトハンドル

    public:
        //! デフォルトコンストラクタ
        TextBuilder();
        //! デストラクタ
        ~TextBuilder();
        //! コピーコンストラクタによるコピー禁止
        TextBuilder(const TextBuilder& org) = delete;
        //! 代入によるコピー禁止
        TextBuilder& operator=(const TextBuilder& org) = delete;

    public:
        //! テキスト画像を作成
        Image build(const std::wstring& text, const std::int32_t size, const bool isBold);
    };
}

namespace my {
    /**
     * @class GlobalDrawer
     * @brief グローバルな描画資源を扱うクラス(シングルトン)
     */
    class GlobalDrawer {
        ShaderBuilder   m_shaderbuilder;    //!< シェーダビルダーインスタンス
        TextBuilder     m_textbuilder;      //!< テキストビルダーインスタンス

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
        //! TextBuilderインスタンスを取得
        TextBuilder& getTextBuilder();
    };
}

#endif //INCLUDED_GLOBALDRAWER_HPP
