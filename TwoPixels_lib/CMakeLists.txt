project(TwoPixels_lib)

set(HEADER_FILES
        twopixels.h
        )

set(SOURCE_FILES
        twopixels.cpp)

add_library(TwoPixels_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})