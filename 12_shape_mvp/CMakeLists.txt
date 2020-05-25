cmake_minimum_required(VERSION 2.8)

#CMakeで設定されている全ての変数を出力する
function(DumpCMakeVariables)
	message(STATUS "*** dump start cmake variables ***")
	get_cmake_property(_variableNames VARIABLES)
	foreach(_variableName ${_variableNames})
		message(STATUS "* ${_variableName}=${${_variableName}}")
	endforeach()
	message(STATUS "*** dump end ***")
endfunction()

#プロジェクト名
set(PROJECT_NAME "12_shape_mvp")
project(${PROJECT_NAME})

#ソース
set(SRCS
	${CMAKE_SOURCE_DIR}/source/12_shape_mvp.cpp
	${CMAKE_SOURCE_DIR}/source/GlobalDrawer.hpp
	${CMAKE_SOURCE_DIR}/source/GlobalDrawer.cpp
	${CMAKE_SOURCE_DIR}/source/Matrix.hpp
	${CMAKE_SOURCE_DIR}/source/Matrix.cpp
	${CMAKE_SOURCE_DIR}/source/Vertex.hpp
	${CMAKE_SOURCE_DIR}/source/Vertex.cpp
)
#インクルードパス
set(INC_PATH
	${CMAKE_SOURCE_DIR}/source
	${CMAKE_SOURCE_DIR}/library/include/GLFW
	${CMAKE_SOURCE_DIR}/library/include/GLEW
)
#ライブラリパス
set(LIB_PATH
	${CMAKE_SOURCE_DIR}/library/lib
)
#ライブラリ
set(LIBS
	opengl32.lib
	glfw3.lib
	libglew32.lib
)
#プリプロセッサ
add_definitions(
	-DGLEW_STATIC
)

#インクルードパス設定
include_directories(${INC_PATH})
#ライブラリパス設定
link_directories(${LIB_PATH})
#実行ファイル
add_executable(${PROJECT_NAME} ${SRCS})
#リンク
target_link_libraries(${PROJECT_NAME} ${LIBS})

#ビルド後イベント
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/source/shader/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/shader
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/source/shader/ ${CMAKE_CURRENT_BINARY_DIR}/shader
  COMMENT "Copy shader sources"
)

#CMakeで設定されている全ての変数を出力する
#DumpCMakeVariables()
