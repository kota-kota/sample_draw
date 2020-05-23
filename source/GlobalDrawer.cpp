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
    Shader_11ShapeSimple::Shader_11ShapeSimple() :
        m_progid(0U), m_loc_pos(-1), m_loc_col(-1)
    {
    }

    /**
     * @brief コンストラクタ
     * 
     * @param [in] progid シェーダプログラムID
     * @param [in] loc_pos 頂点のattribute位置
     * @param [in] loc_col 色のattribute位置
     */
    Shader_11ShapeSimple::Shader_11ShapeSimple(const GLuint progid, const GLint loc_pos, const GLint loc_col) :
        m_progid(progid), m_loc_pos(loc_pos), m_loc_col(loc_col)
    {
        std::cout << "Shader_11ShapeSimple progId:" << progid << " loc_pos:" << loc_pos << " loc_col:" << loc_col << std::endl;
    }

    /**
     * @brief シェーダプログラムを取得
     * 
     * @retval 0 異常
     * @retval >0 正常
     */
    GLuint Shader_11ShapeSimple::getProgram() const { return this->m_progid; }

    /**
     * @brief 頂点のattribute位置を取得
     * 
     * @retval -1 異常
     * @retval >=0 正常
     */
    GLint Shader_11ShapeSimple::getPositionLocation() const { return this->m_loc_pos; }

    /**
     * @brief 色のattribute位置を取得
     * 
     * @retval -1 異常
     * @retval >=0 正常
     */
    GLint Shader_11ShapeSimple::getColorLocation() const { return this->m_loc_col; }
}

namespace my {
    /**
     * @brief デフォルトコンストラクタ
     * 
     * @par 詳細
     *      シェーダプログラムを作成する。
     */
    ShaderBuilder::ShaderBuilder() :
        m_11_shape_simple()
    {
        loadShader_11ShapeSimple();
    }

    /**
     * @brief デストラクタ
     * 
     * @par 詳細
     *      シェーダプログラムを破棄する。
     */
    ShaderBuilder::~ShaderBuilder()
    {
        glDeleteProgram(this->m_11_shape_simple.getProgram());
    }

    /**
     * @brief 11_shape_simpleシェーダのプログラムの取得
     * 
     * @par 詳細
     *      11_shape_simpleシェーダのプログラムを取得する。
     */
    Shader_11ShapeSimple ShaderBuilder::getShader_11ShapeSimple() const { return this->m_11_shape_simple; }

    /**
     * @brief 11_shape_simpleシェーダの読み込み
     * 
     */
    void ShaderBuilder::loadShader_11ShapeSimple()
    {
        const std::string vsrc = readShaderSource("C:\\workspace\\sample_draw\\source\\shader\\11_shape_simple.vert");
        const std::string fsrc = readShaderSource("C:\\workspace\\sample_draw\\source\\shader\\11_shape_simple.frag");
        if ((!vsrc.empty()) && (!fsrc.empty())) {
            GLuint progid = createProgram(vsrc, fsrc);
            GLint loc_pos = glGetAttribLocation(progid, "position");
            GLint loc_col = glGetAttribLocation(progid, "color");
            this->m_11_shape_simple = Shader_11ShapeSimple(progid, loc_pos, loc_col);
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
        if (srcpath.empty()) {
            return std::string();
        }
        // ソースファイルを開く
        std::ifstream file(srcpath);
        if (file.fail()) {
            // 開けなかった
            std::cerr << "Shader::readShaderSource() .. Failed to open " << srcpath << std::endl;
            return std::string();
        }
        // 読み込み成功
        return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    }

    /**
     * @brief シェーダプログラムの作成
     * 
     * @param [in] vsrc バーテックスシェーダのソースプログラムの文字列
     * @param [in] fsrc フラグメントシェーダのソースプログラムの文字列
     * @retval 0 作成失敗
     * @retval >0 作成成功（シェーダプログラムID）
     * 
     * @par 詳細
     *      なし
     */
    GLuint ShaderBuilder::createProgram(const std::string& vsrc, const std::string& fsrc)
    {
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
                std::cerr << "glCompileShader() vobj:" << vobj << " .. NG" << std::endl;
                printShaderLog(vobj);
                glDeleteProgram(program);
                return 0;
            }
            std::cout << "glCompileShader() vobj:" << vobj << " .. OK" << std::endl;
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
                std::cerr << "glCompileShader() fobj:" << fobj << " .. NG" << std::endl;
                printShaderLog(fobj);
                glDeleteProgram(program);
                return 0;
            }
            std::cout << "glCompileShader() fobj:" << fobj << " .. OK" << std::endl;
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
            std::cerr << "glLinkProgram() program:" << program << " .. NG" << std::endl;
            printShaderLog(program);
            glDeleteProgram(program);
            return 0;
        }
        std::cout << "glLinkProgram() program:" << program << " .. OK" << std::endl;

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
     */
    GlobalDrawer::GlobalDrawer() :
        m_width(0), m_height(0), m_fbwidth(0), m_fbHeight(0), m_scale(0.0F), m_shaderbuilder()
    {
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
     * @brief 11_shape_simpleシェーダのプログラムを取得
     * 
     * @return Shader_11ShapeSimple 11_shape_simpleシェーダのプログラム
     */
    Shader_11ShapeSimple GlobalDrawer::getShader_11ShapeSimple() const
    {
        return this->m_shaderbuilder.getShader_11ShapeSimple();
    }

    /**
     * @brief 画面サイズの変更
     * 
     * @param [in] w 画面幅[pixel]
     * @param [in] h 画面高さ[pixel]
     */
    void GlobalDrawer::resize(const std::int32_t w, const std::int32_t h)
    {
        this->m_width = w;
        this->m_height = h;
    }

    /**
     * @brief フレームバッファサイズの変更
     * 
     * @param [in] w フレームバッファ幅[pixel]
     * @param [in] h フレームバッファ高さ[pixel]
     */
    void GlobalDrawer::changeFramebufferSize(const std::int32_t w, const std::int32_t h)
    {
        this->m_fbwidth = w;
        this->m_fbHeight = h;
    }

    /**
     * @brief 拡大率の変更
     * 
     * @param [in] scale 拡大率
     */
    void GlobalDrawer::changeScale(const float scale)
    {
        this->m_scale = scale;
    }

    /**
     * @brief フレームバッファサイズを取得
     * 
     * @param [out] w フレームバッファ幅[pixel]
     * @param [out] h フレームバッファ高さ[pixel]
     */
    void GlobalDrawer::getFramebufferSize(std::int32_t* w, std::int32_t* h) const
    {
        *w = this->m_fbwidth;
        *h = this->m_fbHeight;
    }
}
