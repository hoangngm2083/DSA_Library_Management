cmake_minimum_required(VERSION 3.16)

project(Library VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt (default to Qt6, fallback to Qt5)
find_package(Qt6 COMPONENTS Core Widgets QUIET)
if(NOT Qt6_FOUND)
    find_package(Qt5 5.15 COMPONENTS Core Widgets REQUIRED)
endif()

# Enable automatic processing for Qt (moc, uic, rcc)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/models
    ${CMAKE_CURRENT_SOURCE_DIR}/include/repositories
    ${CMAKE_CURRENT_SOURCE_DIR}/include/data_structures
    ${CMAKE_CURRENT_SOURCE_DIR}/include/view
)

# Collect all .cpp recursively
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    main.cpp
)

# Collect all headers (not strictly required, but useful for IDEs + AUTOMOC)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    include/*.h
)

# Collect all Qt UI files
file(GLOB_RECURSE UI_FILES CONFIGURE_DEPENDS
    src/view/*.ui
)

# Collect all resources
file(GLOB_RECURSE RESOURCES CONFIGURE_DEPENDS
    resources/*.qrc
)

# Create executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}   # optional: helps IDE, AUTOMOC auto-detects Q_OBJECT anyway
    ${UI_FILES}
    ${RESOURCES}
)

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)

# Output dir
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Debug flags
if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR}/bin)
