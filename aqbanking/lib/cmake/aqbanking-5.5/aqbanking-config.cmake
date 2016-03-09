
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
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

find_package(Gwenhywfar "4.10.0.0" REQUIRED)

set_and_check(prefix "/tmp/aqbanking")
set_and_check(exec_prefix "${prefix}")
set_and_check(AQBANKING_INCLUDE_DIRS "${prefix}/include/aqbanking5")
set_and_check(AQBANKING_LIBRARIES "${exec_prefix}/lib/libaqbanking.so")
set(AQBANKING_LIBRARIES ${AQBANKING_LIBRARIES} ${GWENHYWFAR_LIBRARIES})

mark_as_advanced( AQBANKING_INCLUDE_DIRS AQBANKING_LIBRARIES )
