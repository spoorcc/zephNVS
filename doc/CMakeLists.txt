IF (BUILD_ZEPH_NVS_DOC)

    FIND_PACKAGE(Doxygen)

    IF(DOXYGEN_FOUND)
        SET(DOXYGEN_LANGUAGE "English" CACHE STRING "Language used by doxygen")
        MARK_AS_ADVANCED(DOXYGEN_LANGUAGE)

        # Images
        SET( CMAKE_DOXYGEN_IMAGE_PATH   "${CMAKE_CURRENT_SOURCE_DIR}/img"  )
        SET( CMAKE_DOXYGEN_PROJECT_LOGO "${CMAKE_CURRENT_SOURCE_DIR}/img/logo_small.png" )

        # Examples
        SET( CMAKE_DOXYGEN_EXAMPLE_PATH "${PROJECT_SOURCE_DIR}/test" )

        SET( CMAKE_DOXYGEN_LAYOUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/DoxygenLayout.xml" )

        # Inputs
        SET( DOXYGEN_SOURCE_DIR         "${CMAKE_SOURCE_DIR}/src/core
                                         ${CMAKE_SOURCE_DIR}/inc
                                         ${CMAKE_SOURCE_DIR}/doc/pages
                                         ${PROJECT_SOURCE_DIR}/README.md"  )
        STRING(REGEX REPLACE "[\n ]+" " " CMAKE_DOXYGEN_INPUT_LIST "${DOXYGEN_SOURCE_DIR}")

        # Output
        SET( CMAKE_DOXYGEN_HTML_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/public" )
        SET( CMAKE_DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/doc" )

        # Html settings
        SET( CMAKE_DOXYGEN_HTML_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/doxygen-bootstrapped/header.html"  )
        SET( CMAKE_DOXYGEN_HTML_FOOTER "${CMAKE_CURRENT_SOURCE_DIR}/doxygen-bootstrapped/footer.html"  )
        SET( CMAKE_DOXYGEN_HTML_CSS "${CMAKE_CURRENT_SOURCE_DIR}/doxygen-bootstrapped/customdoxygen.css"  )

        SET( CMAKE_DOXYGEN_HTML_EXTRA   "${CMAKE_CURRENT_SOURCE_DIR}/doxygen-bootstrapped/doxy-boot.js
                                         ${CMAKE_CURRENT_SOURCE_DIR}/doxygen-bootstrapped/jquery.smartmenus.js
                                         ${CMAKE_CURRENT_SOURCE_DIR}/doxygen-bootstrapped/jquery.smartmenus.min.js
                                         ${CMAKE_CURRENT_SOURCE_DIR}/doxygen-bootstrapped/addons/bootstrap/jquery.smartmenus.bootstrap.css
                                         ${CMAKE_CURRENT_SOURCE_DIR}/doxygen-bootstrapped/addons/bootstrap/jquery.smartmenus.bootstrap.js
                                         ${CMAKE_CURRENT_SOURCE_DIR}/doxygen-bootstrapped/addons/bootstrap/jquery.smartmenus.bootstrap.min.js
                                         ${CMAKE_CURRENT_SOURCE_DIR}/doxygen-bootstrapped/addons/keyboard/jquery.smartmenus.keyboard.js
                                         ${CMAKE_CURRENT_SOURCE_DIR}/doxygen-bootstrapped/addons/keyboard/jquery.smartmenus.keyboard.min.js" )
        STRING(REGEX REPLACE "[\n ]+" " " CMAKE_DOXYGEN_HTML_EXTRA_LIST "${CMAKE_DOXYGEN_HTML_EXTRA}")        

        # Latex settings
        SET( CMAKE_DOXYGEN_LATEX_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/conf/header.tex"  )
        SET( CMAKE_DOXYGEN_LATEX_FOOTER "${CMAKE_CURRENT_SOURCE_DIR}/conf/footer.tex"  )

        CONFIGURE_FILE(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        # Use 'make doc' to build the documentation
        SET( DOC_TARGET "doc" )

        ADD_CUSTOM_TARGET(${DOC_TARGET} ALL
                ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    ELSE(DOXYGEN_FOUND)
        MESSAGE (FATAL_ERROR "To build documentation Doxygen is needed, could not find doxygen binary")
    ENDIF(DOXYGEN_FOUND)

ENDIF (BUILD_ZEPH_NVS_DOC)

