//===--- A2135HexConstantsUpperCaseCheck.cpp - clang-tidy -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "A2135HexConstantsUpperCaseCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

struct HexConstantCheckResult {
  bool hasLowerCase{false};
  ptrdiff_t firstLowerCaseChar{0};
};

static HexConstantCheckResult
isHexConstantWithLowerCaseLetters(const clang::StringRef &Text) noexcept { 
  if (Text.startswith("0x")) {
    const auto it = std::find_if(Text.begin() + 2, Text.end(), [](auto c) { return isLowercase(c); });
    if (it != Text.end()) {
      return {true, std::distance(Text.begin(), it)};
    }
  }
  return {false, 0};
}

void A2135HexConstantsUpperCaseCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(integerLiteral().bind("int_lit"), this);
}

void A2135HexConstantsUpperCaseCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<IntegerLiteral>("int_lit");
  if (MatchedDecl) {
    const auto Text = clang::Lexer::getSourceText(CharSourceRange::getTokenRange(MatchedDecl->getLocation()), *Result.SourceManager, {});
    const auto CheckResult = isHexConstantWithLowerCaseLetters(Text);
    if (CheckResult.hasLowerCase) {
      diag(MatchedDecl->getLocation().getLocWithOffset(CheckResult.firstLowerCaseChar),
           "A2-13-5: Hexadecimal constants should be upper case");
    }
  }
}

} // namespace autosar
} // namespace tidy
} // namespace clang
