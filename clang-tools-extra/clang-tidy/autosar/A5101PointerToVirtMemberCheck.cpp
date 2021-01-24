//===--- A5101PointerToVirtMemberCheck.cpp - clang-tidy -------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "A5101PointerToVirtMemberCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace autosar {

static bool isPointerToVirtMember(const clang::Expr* Expr) noexcept {
  if (Expr->getType()->isMemberFunctionPointerType()) {
    if (auto MatchedUnary = dyn_cast<UnaryOperator>(Expr)) {
      if (MatchedUnary->getOpcode() == UnaryOperator::Opcode::UO_AddrOf) {
        auto SubExpr = MatchedUnary->getSubExpr();
        if (auto DeclRef = dyn_cast<DeclRefExpr>(SubExpr)) {
          if (auto CxxMethod = dyn_cast<CXXMethodDecl>(DeclRef->getDecl())) {
            if (CxxMethod->isVirtual()) {
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

void A5101PointerToVirtMemberCheck::registerMatchers(MatchFinder *Finder) {
  auto MemOnLeftNullOnRight = 
      allOf(hasLHS(allOf(unaryOperator(), hasType(memberPointerType()))),
                                    unless(hasRHS(hasDescendant(cxxNullPtrLiteralExpr()))));
  auto MemOnRightNullOnLeft =
      allOf(unless(hasRHS(allOf(unaryOperator(), hasType(memberPointerType())))),
            hasLHS(hasDescendant(cxxNullPtrLiteralExpr())));
  Finder->addMatcher(binaryOperator(anyOf(MemOnLeftNullOnRight, MemOnRightNullOnLeft)).bind("op"), this);
}

void A5101PointerToVirtMemberCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<BinaryOperator>("op");
  const auto OperatorName = MatchedDecl->getOpcode();
  if (OperatorName == BinaryOperator::Opcode::BO_EQ || OperatorName == BinaryOperator::Opcode::BO_NE)
  {
    const auto Lhs = MatchedDecl->getLHS();
    const auto Rhs = MatchedDecl->getRHS();
    if (isPointerToVirtMember(Lhs) || isPointerToVirtMember(Rhs))
    {
      diag(MatchedDecl->getOperatorLoc(),
           "A5-10-1: A pointer to member virtual function shall only be tested for equality with null-pointer-constant");
    }
  }
  
}

} // namespace autosar
} // namespace tidy
} // namespace clang
