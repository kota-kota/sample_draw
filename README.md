# sample_draw

## 概要

基本描画をいろいろ試すためのサンプルアプリケーション
- GLFW を使用したウィンドウ制御
- GLEW + OpenGL ES 3.2 を使用した形状（点、線、面）描画
- FreeTypeを使用した文字描画【未対応】
- Bitmap画像描画【未対応】
- libpngを使用したPNG画像描画【未対応】

## 依存関係

GLFW：3.3.2
GLEW：2.1.0

## 詳細

GLFW

- ウィンドウを生成し、イベントループを実施する。
- ウインドウリサイズイベントを処理する。
- マウス入力イベントを処理する。
- キー入力イベントを処理する。
- 描画APIとして、OpenGL ES 3.2 を指定する。

GLEW

- GLFWウィンドウ生成後に初期化する。
- 初期化するだけで、OpenGLの拡張が使用可能となる。

イベントループ処理

- Timerクラスを使用して、一定周期（30FPS）で処理を実行する。
- Screenクラスの描画処理を実行する。

Screen

- 画面を生成するクラス。
- ウィンドウリサイズイベントで、ウィンドウのサイズを変更する。
- OpenGLを使用した画面描画を実行する。
    - 画面のクリア
    - ビューポート
    - ビュー変換、投影変換
    - 描画物の描画実行
    - 画面更新

GlobalDrawer

- グローバルな描画資源を保持するクラス。

ShaderBuilder

- シェーダの生成および管理するクラス。
- 各種シェーダを取り扱う。
    - shapeシェーダ

Shape

- 形状を扱うクラス。
- shapeシェーダプログラムを使用する。
- 頂点バッファ（VBO, VAO）を使用する。

Vertex, Index, Color

- 頂点に関するクラス。

Vector, Matrix, Degree, Radian

- ベクトルおよび行列に関するクラス。
