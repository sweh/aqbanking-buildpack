
# Macros cmake's CONFIGURE_PACKAGE_CONFIG_FILE() would create

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        message( WARNING "${_name} required component \"${comp}\" not found")
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

set_and_check(prefix "/tmp/aqbanking/gwenhywfar")
set_and_check(exec_prefix "${prefix}")
set_and_check(includedir "${prefix}/include")
set_and_check(GWENHYWFAR_INCLUDE_DIRS "${includedir}/gwenhywfar4")
set_and_check(GWENHYWFAR_LIBRARIES "${exec_prefix}/lib/libgwenhywfar.so.60")

# find components

# find QT4 or cpp
list(FIND GWENHYWFAR_FIND_COMPONENTS "qt4" FIND_GWEN_COMPONENT_QT4)
list(FIND GWENHYWFAR_FIND_COMPONENTS "cpp" FIND_GWEN_COMPONENT_CPP)

if ( NOT ${FIND_GWEN_COMPONENT_QT4} EQUAL -1 OR NOT ${FIND_GWEN_COMPONENT_CPP} EQUAL -1 )
  find_package(gwengui-qt4)
  if ( gwengui-qt4_FOUND )
    set( GWENHYWFAR_INCLUDE_DIRS ${GWENHYWFAR_INCLUDE_DIRS} ${GWENGUI_QT4_INCLUDE_DIRS} )
    set( GWENHYWFAR_LIBRARIES ${GWENHYWFAR_LIBRARIES} ${GWENGUI_QT4_LIBRARIES} )
    set( GWENHYWFAR_qt4_FOUND true )
    set( GWENHYWFAR_cpp_FOUND true ) # this is included into qt4 as has no own configuration file
  endif()
endif()

check_required_components(GWENHYWFAR)
mark_as_advanced( GWENHYWFAR_INCLUDE_DIRS GWENHYWFAR_LIBRARIES )
