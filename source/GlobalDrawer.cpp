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
        m_progid(0U), m_loc_modelview(-1), m_loc_projection(-1), m_loc_pos(-1), m_loc_col(-1)
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
     * @par 詳細
     *      シェーダプログラムを作成する。
     */
    ShaderBuilder::ShaderBuilder() :
        m_shape_shader()
    {
        std::cout << "[ShaderBuilder::ShaderBuilder()] call" << std::endl;
        loadShapeShader();
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
    }

    /**
     * @brief shapeシェーダのプログラムの取得
     * 
     * @par 詳細
     *      shapeシェーダのプログラムを取得する。
     */
    ShapeShader ShaderBuilder::getShapeShader() const { return this->m_shape_shader; }

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
     */
    GlobalDrawer::GlobalDrawer() :
        m_shaderbuilder()
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
}
