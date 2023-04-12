cmake_minimum_required(VERSION 3.5)
project(cm-tool)

set(CMAKE_CXX_STANDARD 14)

find_package(tinyxml2 CONFIG REQUIRED)

# interface
set(INTERFACE_INCLUDE interface)

# xmlparser
set(XMLPARSER_INCLUDE implementation/xmlparser/include)
set(XMLPARSER_SOURCES
    implementation/xmlparser/src/XmlParser.cpp
    implementation/xmlparser/src/XmlParserCommon.cpp
)
add_library(xmlparser OBJECT ${XMLPARSER_SOURCES})
target_link_libraries(xmlparser PRIVATE tinyxml2::tinyxml2)
target_include_directories(xmlparser PUBLIC ${INTERFACE_INCLUDE} ${XMLPARSER_INCLUDE})

# codegen
set(GEN_INCLUDE implementation/codegen/include)
set(GEN_SOURCES 
    implementation/codegen/src/CodeGen.cpp
    implementation/codegen/src/CommonGen.cpp
    implementation/codegen/src/CommonVectorGen.cpp
)
add_library(codegen OBJECT ${GEN_SOURCES})
target_include_directories(codegen PUBLIC ${INTERFACE_INCLUDE} ${GEN_INCLUDE})

# app
set(APP_SOURCES
    app/main.cpp
)
add_executable(cm-tool ${APP_SOURCES})
target_link_libraries(cm-tool PRIVATE codegen xmlparser)

# install
install (TARGETS cm-tool
    DESTINATION bin
)
install (DIRECTORY implementation/templates/
    DESTINATION etc
)