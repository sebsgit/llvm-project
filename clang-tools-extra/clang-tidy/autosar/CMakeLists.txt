set(LLVM_LINK_COMPONENTS
  support
  FrontendOpenMP
  )

add_clang_library(clangTidyAutosarModule
  A2135HexConstantsUpperCaseCheck.cpp
  A391FixedWidthTypesCheck.cpp
  A5101PointerToVirtMemberCheck.cpp
  A524ReinterpretCastCheck.cpp
  AutosarTidyModule.cpp

  LINK_LIBS
  clangTidy
  clangTidyUtils

  DEPENDS
  omp_gen
  )

clang_target_link_libraries(clangTidyAutosarModule
  PRIVATE
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  )
