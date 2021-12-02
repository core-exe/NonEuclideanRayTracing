CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(PROJECT CXX)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()

ADD_SUBDIRECTORY(deps/vecmath)

SET(PROJECT_SOURCES
        src/image.cpp
        src/main.cpp)

SET(PROJECT_INCLUDES
        include/camera.hpp
        include/christoffel.hpp
        include/geodesic.hpp
        include/geometry.hpp
        include/group.hpp
        include/hit.hpp
        include/image.hpp
        include/metric.hpp
        include/object.hpp
        include/observer.hpp
        include/ray.hpp
        include/scene.hpp
        include/texture.hpp
        include/trajectory.hpp
        include/utils.hpp
        )

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

ADD_EXECUTABLE(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_INCLUDES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} vecmath)
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE include)
