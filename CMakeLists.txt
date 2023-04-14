cmake_minimum_required(VERSION 3.5)
project(cm-tool)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.81.0 REQUIRED COMPONENTS filesystem program_options)
if (Boost_FOUND)
    message("Boost found")
else()
    message(FATAL_ERROR "Cannot find Boost")
endif()

# interface
set(INTERFACE_INCLUDE interface)

# xmlparser
set(XMLPARSER_INCLUDE implementation/xmlparser/include)
set(XMLPARSER_SOURCES
    implementation/xmlparser/src/XmlParser.cpp
)
add_library(xmlparser OBJECT ${XMLPARSER_SOURCES})
target_link_libraries(xmlparser PRIVATE Boost::boost Boost::filesystem)
target_include_directories(xmlparser PUBLIC ${INTERFACE_INCLUDE} ${XMLPARSER_INCLUDE})

# codegen
set(GEN_INCLUDE implementation/codegen/include)
set(GEN_SOURCES
    implementation/codegen/src/CodeGen.cpp
    implementation/codegen/src/CommonGen.cpp
    implementation/codegen/src/DataTypeGen.cpp
)
add_library(codegen OBJECT ${GEN_SOURCES})
target_link_libraries(codegen PRIVATE Boost::boost Boost::filesystem)
target_include_directories(codegen PUBLIC ${INTERFACE_INCLUDE} ${GEN_INCLUDE})

# app
set(APP_SOURCES
    app/main.cpp
    app/Options.cpp
)
add_executable(cm-tool ${APP_SOURCES})
target_link_libraries(cm-tool PRIVATE xmlparser codegen Boost::boost Boost::program_options)

# install
install (TARGETS cm-tool
    DESTINATION bin
)
install (DIRECTORY implementation/templates/
    DESTINATION etc
)