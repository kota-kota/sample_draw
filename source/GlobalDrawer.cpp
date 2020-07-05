/**
 * @file GlobalDrawer.cpp
 * @author kota-kota
 * @brief グローバルな描画資源を扱うクラスの実装
 * @version 0.1
 * @date 2020-05-19
 * 
 * @copyright Copyright (c) 2020
 */
#include "GlobalDrawer.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

namespace my {
    /**
     * @brief デフォルトコンストラクタ
     * 
     */
    ShapeShader::ShapeShader() :
        m_progid(0U), m_loc_modelview(-1), m_loc_projection(-1), m_loc_pointsize(-1), m_loc_pos(-1), m_loc_col(-1)
    {
    }

    /**
     * @brief コンストラクタ
     * 
     * @param [in] progid シェーダプログラムID
     * @param [in] loc_modelview モデルビュー変換行列のuniform位置
     * @param [in] loc_projection プロジェクション変換行列のuniform位置
     * @param [in] loc_pointsize ポイントサイズのuniform位置
     * @param [in] loc_pos 頂点のattribute位置
     * @param [in] loc_col 色のattribute位置
     */
    ShapeShader::ShapeShader(const GLuint progid, const GLint loc_modelview, const GLint loc_projection, const GLint loc_pointsize, const GLint loc_pos, const GLint loc_col) :
        m_progid(progid), m_loc_modelview(loc_modelview), m_loc_projection(loc_projection), m_loc_pointsize(loc_pointsize), m_loc_pos(loc_pos), m_loc_col(loc_col)
    {
        std::cout << "[ShapeShader::ShapeShader()] progId:" << progid << " loc_modelview:" << loc_modelview << " loc_projection:" << loc_projection << " loc_pointsize:" << loc_pointsize << " loc_pos:" << loc_pos << " loc_col:" << loc_col << std::endl;
    }

    /**
     * @brief シェーダプログラムを取得
     * 
     * @retval 0 異常
     * @retval >0 正常
     */
    GLuint ShapeShader::getProgram() const { return this->m_progid; }

    /**
     * @brief モデルビュー変換行列のunifrom位置を取得
     * 
     * @retval -1 異常
     * @retval >=0 正常
     */
    GLint ShapeShader::getModelViewLocation() const { return this->m_loc_modelview; }

    /**
     * @brief プロジェクション変換行列のunifrom位置を取得
     * 
     * @retval -1 異常
     * @retval >=0 正常
     */
    GLint ShapeShader::getProjectionLocation() const { return this->m_loc_projection; }

    /**
     * @brief ポイントサイズのunifrom位置を取得
     * 
     * @retval -1 異常
     * @retval >=0 正常
     */
    GLint ShapeShader::getPointSizeLocation() const { return this->m_loc_pointsize; }

    /**
     * @brief 頂点のattribute位置を取得
     * 
     * @retval -1 異常
     * @retval >=0 正常
     */
    GLint ShapeShader::getPositionLocation() const { return this->m_loc_pos; }

    /**
     * @brief 色のattribute位置を取得
     * 
     * @retval -1 異常
     * @retval >=0 正常
     */
    GLint ShapeShader::getColorLocation() const { return this->m_loc_col; }
}

namespace my {
    /**
     * @brief デフォルトコンストラクタ
     * 
     */
    TextShader::TextShader() :
        m_progid(0U), m_loc_modelview(-1), m_loc_projection(-1), m_loc_texture(-1), m_loc_texcolor(-1), m_loc_pos(-1), m_loc_uv(-1)
    {
    }

    /**
     * @brief コンストラクタ
     * 
     * @param [in] progid シェーダプログラムID
     * @param [in] loc_modelview モデルビュー変換行列のuniform位置
     * @param [in] loc_projection プロジェクション変換行列のuniform位置
     * @param [in] loc_texture textureのuniform位置
     * @param [in] loc_texcolor texcolorのuniform位置
     * @param [in] loc_pos 頂点のattribute位置
     * @param [in] loc_uv UV座標のattribute位置
     */
    TextShader::TextShader(const GLuint progid, const GLint loc_modelview, const GLint loc_projection, const GLint loc_texture, const GLint loc_texcolor, const GLint loc_pos, const GLint loc_uv) :
        m_progid(progid), m_loc_modelview(loc_modelview), m_loc_projection(loc_projection), m_loc_texture(loc_texture), m_loc_texcolor(loc_texcolor), m_loc_pos(loc_pos), m_loc_uv(loc_uv)
    {
        std::cout << "[TextShader::TextShader()] progId:" << progid << " loc_modelview:" << loc_modelview << " loc_projection:" << loc_projection << " loc_texture:" << loc_texture << " loc_texcolor:" << loc_texcolor << " loc_pos:" << loc_pos << " loc_uv:" << loc_uv << std::endl;
    }

    /**
     * @brief シェーダプログラムを取得
     * 
     * @retval 0 異常
     * @retval >0 正常
     */
    GLuint TextShader::getProgram() const { return this->m_progid; }

    /**
     * @brief モデルビュー変換行列のunifrom位置を取得
     * 
     * @retval -1 異常
     * @retval >=0 正常
     */
    GLint TextShader::getModelViewLocation() const { return this->m_loc_modelview; }

    /**
     * @brief プロジェクション変換行列のunifrom位置を取得
     * 
     * @retval -1 異常
     * @retval >=0 正常
     */
    GLint TextShader::getProjectionLocation() const { return this->m_loc_projection; }

    /**
     * @brief textureのunifrom位置を取得
     * 
     * @retval -1 異常
     * @retval >=0 正常
     */
    GLint TextShader::getTextureLocation() const { return this->m_loc_texture; }

    /**
     * @brief texcolorのunifrom位置を取得
     * 
     * @retval -1 異常
     * @retval >=0 正常
     */
    GLint TextShader::getTexColorLocation() const { return this->m_loc_texcolor; }

    /**
     * @brief 頂点のattribute位置を取得
     * 
     * @retval -1 異常
     * @retval >=0 正常
     */
    GLint TextShader::getPositionLocation() const { return this->m_loc_pos; }

    /**
     * @brief UV座標のattribute位置を取得
     * 
     * @retval -1 異常
     * @retval >=0 正常
     */
    GLint TextShader::getUVLocation() const { return this->m_loc_uv; }
}

namespace my {
    /**
     * @brief デフォルトコンストラクタ
     * 
     * @par 詳細
     *      シェーダプログラムを作成する。
     */
    ShaderBuilder::ShaderBuilder() :
        m_shape_shader(), m_text_shader()
    {
        std::cout << "[ShaderBuilder::ShaderBuilder()] call" << std::endl;
        loadShapeShader();
        loadTextShader();
    }

    /**
     * @brief デストラクタ
     * 
     * @par 詳細
     *      シェーダプログラムを破棄する。
     */
    ShaderBuilder::~ShaderBuilder()
    {
        std::cout << "[ShaderBuilder::~ShaderBuilder()] call" << std::endl;
        glDeleteProgram(this->m_shape_shader.getProgram());
        glDeleteProgram(this->m_text_shader.getProgram());
    }

    /**
     * @brief shapeシェーダのプログラムの取得
     * 
     * @par 詳細
     *      shapeシェーダのプログラムを取得する。
     */
    ShapeShader ShaderBuilder::getShapeShader() const { return this->m_shape_shader; }

    /**
     * @brief textシェーダのプログラムの取得
     * 
     * @par 詳細
     *      textシェーダのプログラムを取得する。
     */
    TextShader ShaderBuilder::getTextShader() const { return this->m_text_shader; }

    /**
     * @brief shapeシェーダの読み込み
     * 
     */
    void ShaderBuilder::loadShapeShader()
    {
        std::cout << "[ShaderBuilder::loadShapeShader()] call" << std::endl;
        const std::string vsrc = readShaderSource(".\\shader\\shape.vert");
        const std::string fsrc = readShaderSource(".\\shader\\shape.frag");
        if ((!vsrc.empty()) && (!fsrc.empty())) {
            GLuint progid = createProgram(vsrc, fsrc);
            GLint loc_modelview = glGetUniformLocation(progid, "modelview");
            GLint loc_projection = glGetUniformLocation(progid, "projection");
            GLint loc_pointsize = glGetUniformLocation(progid, "pointSize");
            GLint loc_pos = glGetAttribLocation(progid, "position");
            GLint loc_col = glGetAttribLocation(progid, "color");
            this->m_shape_shader = ShapeShader(progid, loc_modelview, loc_projection, loc_pointsize, loc_pos, loc_col);
        }
    }

    /**
     * @brief textシェーダの読み込み
     * 
     */
    void ShaderBuilder::loadTextShader()
    {
        std::cout << "[ShaderBuilder::loadTextShader()] call" << std::endl;
        const std::string vsrc = readShaderSource(".\\shader\\text.vert");
        const std::string fsrc = readShaderSource(".\\shader\\text.frag");
        if ((!vsrc.empty()) && (!fsrc.empty())) {
            GLuint progid = createProgram(vsrc, fsrc);
            GLint loc_modelview = glGetUniformLocation(progid, "modelview");
            GLint loc_projection = glGetUniformLocation(progid, "projection");
            GLint loc_texture = glGetUniformLocation(progid, "texture");
            GLint loc_texcolor = glGetUniformLocation(progid, "texcolor");
            GLint loc_pos = glGetAttribLocation(progid, "position");
            GLint loc_uv = glGetAttribLocation(progid, "uv");
            this->m_text_shader = TextShader(progid, loc_modelview, loc_projection, loc_texture, loc_texcolor, loc_pos, loc_uv);
        }
    }

    /**
     * @brief シェーダソースをファイル読み込み
     * 
     * @param [in] name シェーダのソースファイルパス
     * 
     * @return std::string シェーダのソースファイルの文字列
     * 
     * @par 詳細
     *      シェーダのソースファイルを読み込んみ、ソース文字列を返す。
     */
    std::string ShaderBuilder::readShaderSource(const std::string srcpath)
    {
        std::cout << "[ShaderBuilder::readShaderSource()] call" << std::endl;
        if (srcpath.empty()) {
            return std::string();
        }
        // ソースファイルを開く
        std::ifstream file(srcpath);
        if (file.fail()) {
            // 開けなかった
            std::cerr << "* Open " << srcpath << " .. NG" << std::endl;
            return std::string();
        }
        // 読み込み成功
        std::cerr << "* Open " << srcpath << " .. OK" << std::endl;
        return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    }

    /**
     * @brief シェーダプログラムの作成
     * 
     * @param [in] vsrc バーテックスシェーダのソースプログラムの文字列
     * @param [in] fsrc フラグメントシェーダのソースプログラムの文字列
     * 
     * @retval 0 作成失敗
     * @retval >0 作成成功（シェーダプログラムID）
     * 
     * @par 詳細
     *      なし
     */
    GLuint ShaderBuilder::createProgram(const std::string& vsrc, const std::string& fsrc)
    {
        std::cout << "[ShaderBuilder::createProgram()] call" << std::endl;
        // 空のプログラムオブジェクトを作成する
        const GLuint program = glCreateProgram();
        if (!vsrc.empty()) {
            const GLchar* pvsrc = vsrc.c_str();
            // バーテックスシェーダのシェーダオブジェクトを作成する
            const GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vobj, 1, &pvsrc, NULL);
            glCompileShader(vobj);
            //作成できたかチェックする
            GLint retCompiled = 0;
            glGetShaderiv(vobj, GL_COMPILE_STATUS, &retCompiled);
            if(retCompiled == GL_FALSE) {
                //作成失敗
                std::cerr << "* glCompileShader() vobj:" << vobj << " .. NG" << std::endl;
                printShaderLog(vobj);
                glDeleteProgram(program);
                return 0;
            }
            std::cout << "* glCompileShader() vobj:" << vobj << " .. OK" << std::endl;
            // バーテックスシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
            glAttachShader(program, vobj);
            glDeleteShader(vobj);
        }
        if (!fsrc.empty()) {
            const GLchar* pfsrc = fsrc.c_str();
            //フラグメントシェーダのシェーダオブジェクトを作成する
            const GLuint fobj = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fobj, 1, &pfsrc, NULL);
            glCompileShader(fobj);
            //作成できたかチェックする
            GLint retCompiled = 0;
            glGetShaderiv(fobj, GL_COMPILE_STATUS, &retCompiled);
            if(retCompiled == GL_FALSE) {
                //作成失敗
                std::cerr << "* glCompileShader() fobj:" << fobj << " .. NG" << std::endl;
                printShaderLog(fobj);
                glDeleteProgram(program);
                return 0;
            }
            std::cout << "* glCompileShader() fobj:" << fobj << " .. OK" << std::endl;
            // フラグメントシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
            glAttachShader(program, fobj);
            glDeleteShader(fobj);
        }
        //プログラムオブジェクトをリンクする
        glLinkProgram(program);
        //リンクできたかチェックする
        GLint retLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &retLinked);
        if(retLinked == GL_FALSE) {
            //失敗
            std::cerr << "* glLinkProgram() program:" << program << " .. NG" << std::endl;
            printShaderLog(program);
            glDeleteProgram(program);
            return 0;
        }
        std::cout << "* glLinkProgram() program:" << program << " .. OK" << std::endl;

        // 作成したプログラムオブジェクトを返す
        return program;
    }

    /**
     * @brief シェーダのコンパイルログを出力
     * 
     * @param [in] shader シェーダオブジェクトID
     * 
     * @par 詳細
     *      なし
     */
    void ShaderBuilder::printShaderLog(const GLuint shader)
    {
        // シェーダのコンパイル時のログの長さを取得する
        GLsizei bufSize = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &bufSize);
        if (bufSize > 1) {
            // シェーダのコンパイル時のログの内容を取得する
            std::vector<GLchar> infoLog(bufSize);
            GLsizei length;
            glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
            std::cerr << &infoLog[0] << std::endl;
        }
    }
}


namespace my {
    /**
     * @brief デフォルトコンストラクタ
     * 
     * @par 詳細
     *      なし
     */
    Image::Image() :
        Binary(),
        m_width(0), m_height(0), m_channel(0)
    {
    }

    /**
     * @brief コンストラクタ
     * 
     * @param [in] width 画像の幅[pixel]
     * @param [in] height 画像の高さ[pixel]
     * @param [in] channel 画像のチャンネル数
     * 
     * @par 詳細
     *      なし
     */
    Image::Image(const std::int32_t width, const std::int32_t height, const std::int32_t channel) :
        Binary(width * height * channel, 0),
        m_width(width), m_height(height), m_channel(channel)
    {
    }

    /**
     * @brief 画像の幅を取得
     * 
     * @retval <=0 取得失敗
     * @retval >0 取得成功（画像の幅）
     */
    std::int32_t Image::width() const { return this->m_width; }

    /**
     * @brief 画像の高さを取得
     * 
     * @retval <=0 取得失敗
     * @retval >0 取得成功（画像の高さ）
     */
    std::int32_t Image::height() const { return this->m_height; }

    /**
     * @brief 画像のチャンネル数を取得
     * 
     * @retval <=0 取得失敗
     * @retval >0 取得成功（画像のチャンネル数）
     */
    std::int32_t Image::channel() const { return this->m_channel; }
}


namespace my {
    /**
     * @brief デフォルトコンストラクタ
     * 
     * @par 詳細
     *      なし
     */
    TextBuilder::TextBuilder() :
        m_ft_library(nullptr), m_ft_face(nullptr)
    {
        std::cout << "[TextBuilder::TextBuilder()] call" << std::endl;
        // FreeTypeインスタンスハンドルの初期化
        FT_Error fterr;
        fterr = FT_Init_FreeType(&m_ft_library);
        if(fterr != 0) { std::cout << "* FT_Init_FreeType() .. NG (" << fterr << ")" << std::endl; return; }
        std::cout << "* FT_Init_FreeType() .. OK" << std::endl;
        // FreeTypeフェイスオブジェクトハンドルの生成
        fterr = FT_New_Face(m_ft_library, "C:\\Windows\\Fonts\\meiryo.ttc", 0, &m_ft_face);
        //fterr = FT_New_Face(m_ft_library, "C:\\Windows\\Fonts\\msgothic.ttc", 0, &m_ft_face);
        if(fterr != 0) { std::cout << "* FT_New_Face() .. NG (" << fterr << ")" << std::endl; return; }
        std::cout << "* FT_New_Face() .. OK" << std::endl;
    }

    /**
     * @brief デストラクタ
     * 
     * @par 詳細
     *      なし
     */
    TextBuilder::~TextBuilder()
    {
        std::cout << "[TextBuilder::~TextBuilder()] call" << std::endl;
        // FreeTypeフェイスオブジェクトハンドルの破棄
        (void)FT_Done_Face(m_ft_face);
        // FreeTypeインスタンスハンドルの破棄
        (void)FT_Done_FreeType(m_ft_library);
    }

    /**
     * @brief テキスト画像を作成
     * 
     * @param [in] text テキスト文字列（ワイド文字）
     * @param [in] size テキストサイズ
     * @param [in] isBold 太字
     * 
     * @par 詳細
     *      なし
     */
    Image TextBuilder::build(const std::wstring& text, const std::int32_t size, const bool isBold)
    {
        // フォント寸法情報
        struct FontMetrics {
            std::int32_t    width_;     // フォント幅[pixel]
            std::int32_t    height_;    // フォント高さ[pixel]
            std::int32_t    offsetX_;   // グリフ原点(0,0)からグリフイメージの左端までの水平方向オフセット[pixel]
            std::int32_t    offsetY_;   // グリフ原点(0,0)からグリフイメージの上端までの垂直方向オフセット[pixel]
            std::int32_t    nextX_;     // 次グリフへの水平方向オフセット[pixel]
            std::int32_t    nextY_;     // 次グリフへの垂直方向オフセット[pixel]
            std::int32_t    kerningX_;  // 水平方向カーニング
            std::int32_t    kerningY_;  // 垂直方向カーニング
        };
        // フォントグリフ
        struct FontGlyph {
            FT_UInt         index_;     // グリフインデックス
            FT_Glyph        image_;     // グリフイメージ
            FontMetrics     metrics_;   // 寸法情報
        };

        // テキスト文字列のフォントグリフ保持用
        const std::int32_t MAX_GLYPHS = 32;
        FontGlyph glyphs[MAX_GLYPHS];
        std::int32_t numGlyphs = 0;

        // 文字列のバウンディングボックス
        FT_BBox stringBBox;

        std::cout << "[TextBuilder::build()] call" << std::endl;

        // 入力値チェック
        if(text.empty()) { std::cout << "* text is empty .. NG" << std::endl; return Image(); }
        if(size <= 0) { std::cout << "* size is negative value .. NG (" << size << ")" << std::endl; return Image(); }

        // フォントサイズ設定
        FT_Set_Char_Size(m_ft_face, size * 64, 0, 96, 0);

        // 文字列の長さ分ループ
        const std::size_t len = text.size();
        for (std::size_t i = 0; i < len; i++) {
            // 処理対象文字
            const std::uint16_t c = static_cast<std::uint16_t>(text[i]);

            // 処理対象文字のグリフ格納用
            FontGlyph* glyph = &glyphs[numGlyphs];

            // グリフインデックスを取得
            glyph->index_ = FT_Get_Char_Index(m_ft_face, c);

            // グリフをロード
            FT_Load_Glyph(m_ft_face, glyph->index_, FT_LOAD_DEFAULT);

            // ボールド加工
            if(isBold) {
                FT_GlyphSlot_Embolden(m_ft_face->glyph);
            }

            // グリフを描画
            FT_Get_Glyph(m_ft_face->glyph, &glyph->image_);
            FT_Glyph_To_Bitmap(&glyph->image_, FT_RENDER_MODE_NORMAL, nullptr, 1);

            // 寸法情報を取得
            FT_BitmapGlyph bit = (FT_BitmapGlyph)glyph->image_;
            glyph->metrics_.width_ = bit->bitmap.width;
            glyph->metrics_.height_ = bit->bitmap.rows;
            glyph->metrics_.offsetX_ = bit->left;
            glyph->metrics_.offsetY_ = bit->top;
            glyph->metrics_.nextX_ = m_ft_face->glyph->advance.x >> 6;
            glyph->metrics_.nextY_ = m_ft_face->glyph->advance.y >> 6;

            // 処理対象文字のバウンディングボックスを取得
            FT_BBox bbox;
            FT_Glyph_Get_CBox(glyph->image_, ft_glyph_bbox_pixels, &bbox);

            if (i == 0) {
                stringBBox.xMin = 0;
                stringBBox.xMax = glyph->metrics_.nextX_;
                stringBBox.yMin = bbox.yMin;
                stringBBox.yMax = bbox.yMax;
            }
            else {
                stringBBox.xMin = 0;
                stringBBox.xMax += glyph->metrics_.nextX_;
                if (bbox.yMin < stringBBox.yMin) { stringBBox.yMin = bbox.yMin; }
                if (bbox.yMax > stringBBox.yMax) { stringBBox.yMax = bbox.yMax; }
            }
            
            // 次文字へ
            numGlyphs++;
        }

        // 文字列の幅高さ
        const std::int32_t stringW = stringBBox.xMax - stringBBox.xMin;
        const std::int32_t stringH = stringBBox.yMax - stringBBox.yMin;

        // 文字列画像の領域を確保
        Image image(stringW, stringH, 1);

        // 文字列画像を生成
        FT_Vector pen = { 0, stringBBox.yMax };
        for (std::int32_t i = 0; i < numGlyphs; i++) {
            // 処理対象文字のグリフを取得
            FontGlyph* glyph = &glyphs[i];
            FT_BitmapGlyph bit = (FT_BitmapGlyph)glyph->image_;

            const std::int32_t xoffset = pen.x + glyph->metrics_.offsetX_;
            const std::int32_t yoffset = pen.y - glyph->metrics_.offsetY_;
            std::int32_t readOffset = 0;
            std::int32_t writeOffset = xoffset + (yoffset * stringW);
            for (std::int32_t h = 0; h < glyph->metrics_.height_; h++) {
                (void)memcpy_s(&image[writeOffset], stringW, bit->bitmap.buffer + readOffset, glyph->metrics_.width_);
                readOffset += glyph->metrics_.width_;
                writeOffset += stringW;
            }

            pen.x += glyph->metrics_.nextX_;

            // グリフイメージ破棄
            FT_Done_Glyph(glyph->image_);
        }

        return image;
    }
}

namespace my {
    /**
     * @brief デフォルトコンストラクタ
     * 
     */
    GlobalDrawer::GlobalDrawer() :
        m_shaderbuilder(), m_textbuilder()
    {
        std::cout << "[GlobalDrawer::GlobalDrawer()] call" << std::endl;
    }

    /**
     * @brief インスタンスを取得
     * 
     */
    GlobalDrawer& GlobalDrawer::instance()
    {
        static GlobalDrawer ins;
        return ins;
    }

    /**
     * @brief ShaderBuilderインスタンスを取得
     * 
     * @return ShaderBuilder ShaderBuilderインスタンス
     */
    ShaderBuilder& GlobalDrawer::getShaderBuilder()
    {
        return this->m_shaderbuilder;
    }

    /**
     * @brief TextBuilderインスタンスを取得
     * 
     * @return TextBuilder TextBuilderインスタンス
     */
    TextBuilder& GlobalDrawer::getTextBuilder()
    {
        return this->m_textbuilder;
    }
}
