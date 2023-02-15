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

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(C_FLAGS "${C_FLAGS} -O2 -fvisibility=hidden -fvisibility-inlines-hidden")
    set(LINKER_FLAGS "${LINKER_FLAGS} -Wl,-exclude-libs,ALL -Wl,--gc-sections -Wl,--strip-all")
else ()
    set(C_FLAGS "${C_FLAGS} -O0")
endif ()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${C_FLAGS} ${CXX_FLAGS}")

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${LINKER_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${LINKER_FLAGS}")

add_library(JMBQ SHARED main.cpp hook.cpp jni.cpp
        ${xdl-src}
        )
target_link_libraries(JMBQ log
        ${PROJECT_SOURCE_DIR}/Dobby/${ANDROID_ABI}/libdobby.a
        )

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(TARGET JMBQ POST_BUILD
            COMMAND ${CMAKE_STRIP} --strip-all --remove-section=.comment "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libJMBQ.so")
endif ()