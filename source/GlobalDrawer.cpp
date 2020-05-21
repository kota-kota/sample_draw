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
#include <vector>

namespace {
     //! バーテックスシェーダのソースプログラム
    constexpr GLchar VERT_SRC[] =
        "#version 100\n"
        "in vec3 position;\n"
        "in vec4 color;\n"
        "out vec4 vertex_color;\n"
        "void main()\n"
        "{\n"
        "  vertex_color = color / 255.0F;\n"
        "  gl_Position = vec4(position, 1.0);\n"
        "}\n";

    //! フラグメントシェーダのソースプログラム
    constexpr GLchar FRAG_SRC[] =
        "#version 100\n"
        "in vec4 vertex_color;\n"
        "out vec4 fragment;\n"
        "void main()\n"
        "{\n"
        " fragment = vertex_color;\n"
        "}\n";
}

namespace my {
    /**
     * @brief デフォルトコンストラクタ
     * 
     */
    Shader::Shader() :
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
    Shader::Shader(const GLuint progid, const GLint loc_pos, const GLint loc_col) :
        m_progid(progid), m_loc_pos(loc_pos), m_loc_col(loc_col)
    {
        std::cout << "Shader progId:" << progid << " loc_pos:" << loc_pos << " loc_col:" << loc_col << std::endl;
    }

    /**
     * @brief シェーダプログラムを取得
     * 
     * @retval 0 異常
     * @retval >0 正常
     */
    GLuint Shader::getProgram() const { return this->m_progid; }

    /**
     * @brief 頂点のattribute位置を取得
     * 
     * @retval -1 異常
     * @retval >=0 正常
     */
    GLint Shader::getPositionLocation() const { return this->m_loc_pos; }

    /**
     * @brief 色のattribute位置を取得
     * 
     * @retval -1 異常
     * @retval >=0 正常
     */
    GLint Shader::getColorLocation() const { return this->m_loc_col; }
}

namespace my {
    /**
     * @brief デフォルトコンストラクタ
     * 
     * @par 詳細
     *      シェーダプログラムを作成する。
     */
    ShaderCompiler::ShaderCompiler() :
        m_shader()
    {
        // シェーダプログラムを作成する
        GLuint progid = this->createProgram(VERT_SRC, FRAG_SRC);
        GLint loc_pos = glGetAttribLocation(progid, "position");
        GLint loc_col = glGetAttribLocation(progid, "color");
        this->m_shader = Shader(progid, loc_pos, loc_col);
    }

    /**
     * @brief デストラクタ
     * 
     * @par 詳細
     *      シェーダプログラムを破棄する。
     */
    ShaderCompiler::~ShaderCompiler()
    {
        glDeleteProgram(this->m_shader.getProgram());
    }

    /**
     * @brief シェーダプログラムの取得
     * 
     * @par 詳細
     *      シェーダプログラムを取得する。
     */
    Shader ShaderCompiler::getShader() const { return this->m_shader; }

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
    GLuint ShaderCompiler::createProgram(const char *vsrc, const char *fsrc)
    {
        // 空のプログラムオブジェクトを作成する
        const GLuint program = glCreateProgram();
        if (vsrc != NULL) {
            // バーテックスシェーダのシェーダオブジェクトを作成する
            const GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vobj, 1, &vsrc, NULL);
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
        if (fsrc != NULL) {
            //フラグメントシェーダのシェーダオブジェクトを作成する
            const GLuint fobj = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fobj, 1, &fsrc, NULL);
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
    //シェーダのコンパイル時のログを出力する
    void ShaderCompiler::printShaderLog(GLuint shader)
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
        m_width(0), m_height(0), m_shader()
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
     * @brief 画面幅高さを設定
     * 
     * @param [in] w 画面幅[pixel]
     * @param [in] h 画面高さ[pixel]
     */
    void GlobalDrawer::setScreen(const std::int32_t w, const std::int32_t h)
    {
        this->m_width = w;
        this->m_height = h;
    }

    /**
     * @brief シェーダプログラムを取得
     * 
     * @return Shader シェーダプログラム
     */
    Shader GlobalDrawer::getShader() const
    {
        return this->m_shader.getShader();
    }
}
