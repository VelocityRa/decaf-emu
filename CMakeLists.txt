cmake_minimum_required(VERSION 2.8.4)
include(ExternalProject)

project(wiiu-emu)

set(PUGIXML_DIR "libraries/pugixml")
include_directories("${PUGIXML_DIR}/src")
add_library(pugixml STATIC "${PUGIXML_DIR}/src/pugixml.cpp")
set(PUGIXML_LIBRARIES pugixml)

set(DOCOPT_DIR "libraries/docopt")
include_directories("${DOCOPT_DIR}")
externalproject_add(docopt
	SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${DOCOPT_DIR}"
	INSTALL_COMMAND ""
	)
externalproject_get_property(docopt BINARY_DIR)
set(DOCOPT_LIBRARIES "${BINARY_DIR}/${CMAKE_FIND_LIBRARY_PREFIXES}docopt_s.a")

set(SPDLOG_DIR "libraries/spdlog")
include_directories("${SPDLOG_DIR}/include")

set(GSL_DIR "libraries/gsl")
include_directories("${GSL_DIR}/include")

set(CEREAL_DIR "libraries/cereal")
include_directories("${CEREAL_DIR}/include")

set(ASMJIT_DIR "libraries/asmjit")
include_directories("${ASMJIT_DIR}/src")
externalproject_add(asmjit
	SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${ASMJIT_DIR}"
	CMAKE_CACHE_ARGS "-DASMJIT_STATIC:string=on"
	INSTALL_COMMAND ""
	)
externalproject_get_property(asmjit BINARY_DIR)
set(ASMJIT_LIBRARIES "${BINARY_DIR}/${CMAKE_FIND_LIBRARY_PREFIXES}asmjit.a")

set(GLBINDING_DIR "libraries/glbinding")
include_directories("${GLBINDING_DIR}/source/glbinding/include")
externalproject_add(glbinding
	SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${GLBINDING_DIR}"
	CMAKE_CACHE_ARGS "-DOPTION_BUILD_STATIC:string=on"
	INSTALL_COMMAND ""
	)
externalproject_get_property(glbinding BINARY_DIR)
set(GLBINDING_LIBRARIES "${BINARY_DIR}/${CMAKE_FIND_LIBRARY_PREFIXES}glbinding.a")

if (NOT MSVC)
	set(CMAKE_CXX_COMPILER "clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    if (APPLE)
    	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif()
endif()

add_subdirectory("src")