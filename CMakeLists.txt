CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(TEST_SCMETRIC_DG CXX)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()

ADD_SUBDIRECTORY(deps/vecmath)

SET(PROJECT_SOURCES
        src/camera.cpp
        src/christoffel.cpp
        src/geodesic.cpp
        src/geometry.cpp
        src/group.cpp
        src/hit.cpp
        src/image.cpp
        src/metric.cpp
        src/object.cpp
        src/observer.cpp
        src/ray.cpp
        src/scene.cpp
        src/texture.cpp
        src/trajectory.cpp
        src/utils.cpp
        executable_src/test_scmetric_dg.cpp
        )

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
