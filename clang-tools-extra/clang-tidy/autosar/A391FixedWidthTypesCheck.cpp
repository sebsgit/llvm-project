//===--- A391FixedWidthTypesCheck.cpp - clang-tidy ------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "A391FixedWidthTypesCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

static const std::initializer_list<const char*> restricted_types{
    "int", "short", "long", "char"
};

void A391FixedWidthTypesCheck::registerMatchers(MatchFinder *Finder) {
  auto build_matcher_for_type = [](const std::string &type_name) { 
      return varDecl(anyOf(hasType(asString(type_name)), hasType(asString("unsigned " + type_name))));
  };

  for (auto t : restricted_types) 
  {
    Finder->addMatcher(build_matcher_for_type(t).bind(t), this);
  }
}

void A391FixedWidthTypesCheck::check(const MatchFinder::MatchResult &Result) {
  for (auto t : restricted_types) {
    const auto *MatchedDecl = Result.Nodes.getNodeAs<VarDecl>(t);
    if (!MatchedDecl) {
      continue;
    }
    diag(MatchedDecl->getLocation(), "A3-9-1: Use the fixed width integer types from <cstdint>")
        << MatchedDecl;
  }
}

} // namespace autosar
} // namespace tidy
} // namespace clang
