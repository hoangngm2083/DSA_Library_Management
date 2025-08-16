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

# Source files
set(SOURCES
    main.cpp
    src/models/DanhMucSach.cpp
    src/models/DauSach.cpp
    src/models/MuonTra.cpp
    src/models/TheDocGia.cpp
    src/library.cpp
)

# View sources
set(VIEW_SOURCES
    src/view/MainWindow.cpp
    src/view/BorrowBookWindow.cpp
)

# Headers that need moc (with Q_OBJECT)
set(VIEW_HEADERS
    include/view/MainWindow.h
    include/view/BorrowBookWindow.h
)

# Qt UI files
set(UI_FILES
    src/view/MainWindow.ui
)

# Resources (if any, e.g., .qrc)
set(RESOURCES
    # resources/resources.qrc
)

# Combine all sources
set(ALL_SOURCES
    ${SOURCES}
    ${VIEW_SOURCES}
    ${VIEW_HEADERS}
    ${UI_FILES}
    ${RESOURCES}
)

# Create executable
add_executable(${PROJECT_NAME} ${ALL_SOURCES})

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
