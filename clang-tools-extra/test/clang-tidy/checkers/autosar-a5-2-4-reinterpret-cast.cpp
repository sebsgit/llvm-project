// RUN: %check_clang_tidy %s autosar-a5-2-4-reinterpret-cast %t

#include <cinttypes>
#include <string>

void f()
{
  std::string Str = "Hello";
  std::int32_t* Ptr = reinterpret_cast<std::int32_t*>(&Str);
}
// CHECK-MESSAGES: :[[@LINE-1]]:23: warning: A5-2-4: reinterpret_cast shall not be used [autosar-a5-2-4-reinterpret-cast]
