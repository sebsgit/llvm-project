//===--- A391FixedWidthTypesCheck.cpp - clang-tidy ------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "A391FixedWidthTypesCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/TypeLoc.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

static const std::initializer_list<std::string> restricted_types{
    "char",
    "signed char",
    "unsigned char",
    "short",
    "short int",
    "signed short",
    "signed short int",
    "unsigned short",
    "unsigned short int",
    "int",
    "signed",
    "signed int",
    "unsigned",
    "unsigned int",
    "long",
    "long int",
    "signed long",
    "signed long int",
    "unsigned long",
    "unsigned long int",
    "long long",
    "long long int",
    "signed long long",
    "signed long long int",
    "unsigned long long",
    "unsigned long long int "
};

void A391FixedWidthTypesCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(typeLoc().bind("t_loc"), this);
}

void A391FixedWidthTypesCheck::check(const MatchFinder::MatchResult &Result) {
  const auto MatchedDecl = Result.Nodes.getNodeAs<TypeLoc>("t_loc");
  if (MatchedDecl && MatchedDecl->getBeginLoc().isValid()) {
    for (auto t : restricted_types) {
      if (MatchedDecl->getType().getUnqualifiedType().getAsString() == t) {
          diag(MatchedDecl->getBeginLoc(),
                 "A3-9-1: Use the fixed width integer types from <cstdint>");
      }
    }
  }
}

} // namespace autosar
} // namespace tidy
} // namespace clang
