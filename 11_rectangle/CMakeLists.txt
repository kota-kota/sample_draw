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
set(PROJECT_NAME "11_rectangle")
project(${PROJECT_NAME})

#ソース
set(SRCS
	${CMAKE_SOURCE_DIR}/source/11_rectangle.cpp
	${CMAKE_SOURCE_DIR}/source/GlobalDrawer.hpp
	${CMAKE_SOURCE_DIR}/source/GlobalDrawer.cpp
	${CMAKE_SOURCE_DIR}/source/Object.hpp
	${CMAKE_SOURCE_DIR}/source/Object.cpp
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

#CMakeで設定されている全ての変数を出力する
#DumpCMakeVariables()
