# CMakeList.txt: проект CMake для onnx_demo; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)


set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

project ("onnx_demo")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(onnx_DIR "${CMAKE_SOURCE_DIR}/vcpkg/packages/onnx_x64-windows/share/onnx")
set(protobuf_DIR "${CMAKE_SOURCE_DIR}/vcpkg/packages/protobuf_x64-windows/share/protobuf")



find_package(onnx CONFIG REQUIRED)

add_executable (onnx_demo "onnx_demo.cpp" "onnx_demo.h")

target_link_libraries(onnx_demo PRIVATE onnx)

target_compile_definitions(onnx_demo PRIVATE ONNX_ML)


# target_include_directories(onnx_demo PRIVATE "${PROJECT_SOURCE_DIR}/contrib/onnxruntime/include")
# target_link_directories(onnx_demo PRIVATE "${CMAKE_SOURCE_DIR}/contrib/onnxruntime/lib")
# target_link_libraries(onnx_demo PRIVATE onnxruntime onnxruntime_providers_shared)
