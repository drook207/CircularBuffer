set(TARGET_NAME circularbuffer)

if(BUILD_SHARED)
message(STATUS "Building shared lib")
add_library(${TARGET_NAME} SHARED inc/circularbuffer.hpp)
else()
message(STATUS "Building static lib")
add_library(${TARGET_NAME} STATIC inc/circularbuffer.hpp)
endif()


set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)


if(QT_IMPLEMANTATION)
target_link_libraries( ${TARGET_NAME} PRIVATE Qt6::Core)
target_compile_definitions(${TARGET_NAME} QT_IMPLEMANTATION)
endif()