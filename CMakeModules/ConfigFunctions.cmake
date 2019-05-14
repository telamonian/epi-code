function(chooseToolchain)
    # set the toolchain and corresponding default compiler paths
    if(${CMAKE_TOOLCHAIN} STREQUAL gnu)
        set(CMAKE_C_COMPILER gcc-9)
        set(CMAKE_CXX_COMPILER g++-9)
    elseif(${CMAKE_TOOLCHAIN} STREQUAL clang)
        set(CMAKE_C_COMPILER clang)
        set(CMAKE_CXX_COMPILER clang++)
    elseif(${CMAKE_TOOLCHAIN} STREQUAL intel)
        set(CMAKE_C_COMPILER icc)
        set(CMAKE_CXX_COMPILER icpc)
    else(${CMAKE_TOOLCHAIN} STREQUAL gnu)
        # warn if CMAKE_TOOLCHAIN has been set to an unrecognized value
        message(WARNING "No support for specified CMAKE_TOOLCHAIN: ${CMAKE_TOOLCHAIN}. Compilers set to CMake default.")
    endif(${CMAKE_TOOLCHAIN} STREQUAL gnu)

    # allow for specific compiler path overrides
    foreach(lang C;CXX)
        if(DEFINED CMAKE_${lang}_COMPILER)
            # SetConfigDefault(CMAKE_${lang}_COMPILER CUSTOM_${lang}_COMPILER ${CMAKE_${lang}_COMPILER})
            set(CMAKE_${lang}_COMPILER ${CMAKE_${lang}_COMPILER} PARENT_SCOPE)
        endif(DEFINED CMAKE_${lang}_COMPILER)
    endforeach(lang)
endfunction()
