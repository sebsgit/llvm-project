//===--- AndroidTidyModule.cpp - clang-tidy--------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "A391FixedWidthTypesCheck.h"
#include "A5101PointerToVirtMemberCheck.h"
#include "A524ReinterpretCastCheck.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

class AutosarModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<A391FixedWidthTypesCheck>(
        "autosar-a3-9-1-fixed-width-types");
    CheckFactories.registerCheck<A5101PointerToVirtMemberCheck>(
        "autosar-a5-10-1-pointer-to-virt-member");
    CheckFactories.registerCheck<A524ReinterpretCastCheck>(
        "autosar-a5-2-4-reinterpret-cast");
  }
};

static ClangTidyModuleRegistry::Add<AutosarModule>
    X("autosar-module", "Adds autosar lint checks.");

} // namespace autosar
    
volatile int AutosarModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang
