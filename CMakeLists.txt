CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(PROJECT CXX)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()

ADD_SUBDIRECTORY(deps/vecmath)

SET(RAY_TRACING_SOURCES
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
        src/plane.cpp
        src/ray.cpp
        src/scene.cpp
        src/texture.cpp
        src/trajectory.cpp
        src/utils.cpp
        )

SET(RAY_TRACING_INCLUDES
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
        include/plane.hpp
        include/ray.hpp
        include/scene.hpp
        include/texture.hpp
        include/trajectory.hpp
        include/utils.hpp
        )

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

SET(TEST_SCMETRIC_DG_SOURCES ${RAY_TRACING_SOURCES}
        executable_src/test_scmetric_dg.cpp)
ADD_EXECUTABLE(TEST_SCMETRIC_DG ${TEST_SCMETRIC_DG_SOURCES} ${RAY_TRACING_INCLUDES})
TARGET_LINK_LIBRARIES(TEST_SCMETRIC_DG vecmath)
TARGET_INCLUDE_DIRECTORIES(TEST_SCMETRIC_DG PRIVATE include)

SET(TEST_SC_GEOMETRY_SOURCES ${RAY_TRACING_SOURCES}
        executable_src/test_sc_geometry.cpp)
ADD_EXECUTABLE(TEST_SC_GEOMETRY ${TEST_SC_GEOMETRY_SOURCES} ${RAY_TRACING_INCLUDES})
TARGET_LINK_LIBRARIES(TEST_SC_GEOMETRY vecmath)
TARGET_INCLUDE_DIRECTORIES(TEST_SC_GEOMETRY PRIVATE include)

SET(TEST_CAMERA_SOURCES ${RAY_TRACING_SOURCES}
        executable_src/test_camera.cpp)
ADD_EXECUTABLE(TEST_CAMERA ${TEST_CAMERA_SOURCES} ${RAY_TRACING_INCLUDES})
TARGET_LINK_LIBRARIES(TEST_CAMERA vecmath)
TARGET_INCLUDE_DIRECTORIES(TEST_CAMERA PRIVATE include)
