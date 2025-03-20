cmake_minimum_required(VERSION 3.18.1)
set(CMAKE_CXX_STANDARD 20)

project(JMBQ)

set(DobbyHome Dobby)
set(xdlHome xdl)

include_directories(
        ${DobbyHome}/include
        ${xdlHome}/include
)

aux_source_directory(xdl xdl-src)


message("Build type: ${CMAKE_BUILD_TYPE}")


set(LINKER_FLAGS "-ffixed-x18 -Wl,--hash-style=both")
set(C_FLAGS "-Werror=format -fdata-sections -ffunction-sections")
set(CXX_FLAGS "${CXX_FLAGS} -fno-exceptions -fno-rtti")


set(C_FLAGS "${C_FLAGS} -O2 -fvisibility=hidden -fvisibility-inlines-hidden")
set(LINKER_FLAGS "${LINKER_FLAGS} -Wl,-exclude-libs,ALL -Wl,--gc-sections -Wl,--strip-all")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${C_FLAGS} ${CXX_FLAGS}")

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${LINKER_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${LINKER_FLAGS}")

add_library(HI3 SHARED main.cpp hook.cpp
        ${xdl-src}
        )
target_link_libraries(HI3 log
        ${PROJECT_SOURCE_DIR}/Dobby/${ANDROID_ABI}/libdobby.a
        )