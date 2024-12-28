project(shared_lib VERSION 1.0.0.0 DESCRIPTION "动态库文件")

# 如果是使用 MSVC 编译，则需要以 .in 文件为模板产生工程的版本信息
if(MSVC)
    set(VERSIONINFO_RC ${PROJECT_BINARY_DIR}/VersionInfo.rc)
    configure_file(${PROJECT_SOURCE_DIR}/VersionInfo.rc.in ${VERSIONINFO_RC})
endif() # endif MSVC

# 递归地查找 .def/.map 文件，并存放到 EXPORTS_FILES 变量中
file(GLOB_RECURSE EXPORTS_FILES
    ${PROJECT_SOURCE_DIR}/*.def
    ${PROJECT_SOURCE_DIR}/*.map
)

# 递归地查找头文件，并存放到 INCLUDE_FILES 变量中
file(GLOB_RECURSE INCLUDE_FILES
    ${PROJECT_SOURCE_DIR}/*.h
    ${PROJECT_SOURCE_DIR}/*.hpp
)

# 递归地查找 .c/.cpp 文件，并存放到 SOURCE_FILES 变量中
file(GLOB_RECURSE SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/*.c
    ${PROJECT_SOURCE_DIR}/*.cpp
)
    
# 将文件分组
source_group("Header Files" FILES "${INCLUDE_FILES}")
source_group("Source Files" FILES "${SOURCE_FILES}")

# 指定当前子工程是编译为动态库文件
if(BUILD_SHARED_LIBS)
    set(BUILD_TYPE SHARED)
    else()
    set(BUILD_TYPE STATIC)
endif() # endif BUILD_SHARED_LIBS
add_library(
    ${PROJECT_NAME}
    ${BUILD_TYPE}
    ${INCLUDE_FILES}
    ${SOURCE_FILES}
    ${EXPORTS_FILES}
    ${VERSIONINFO_RC}
)

# 如果有找到 cppcheck 可执行程序，则在编译前先进行静态代码检查
if(CMAKE_CXX_CPPCHECK)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        PRE_BUILD
        command ${CPPCHECK_COMMAND} ${PROJECT_SOURCE_DIR}
    )
endif() # endif `cppcheck` was found.

# 当前子工程要包含的头文件路径
include_directories(
    ${CMAKE_SOURCE_DIR}/src/static_lib
)

# 当前子工程要链接的库名称
target_link_libraries(
    ${PROJECT_NAME}
    static_lib # 例如这里需要依赖 static_lib 工程编译出来的库，如果你不需要，可以删除这行.
)

# 配置预编译头:
target_precompile_headers(
  ${PROJECT_NAME}
  PRIVATE
  "$<$<COMPILE_LANGUAGE:CXX>:${PROJECT_SOURCE_DIR}/pch.h>"
)

# 设置在 Linux 中编译时的版本信息
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})
if(UNIX)
    if(APPLE)
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Wl,-exported_symbols_list,${PROJECT_SOURCE_DIR}/exports.txt")
    ELSE()
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Wl,--version-script=${PROJECT_SOURCE_DIR}/exports.map")
    endif()
endif() # endif UNIX