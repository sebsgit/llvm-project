// RUN: %check_clang_tidy %s autosar-a5-10-1-pointer-to-virt-member %t

namespace
{
class A
{
public:
    virtual ~A() = default;
    void f1() noexcept {}
    void f2() noexcept {}
    virtual void f3() noexcept {}
};
} // namespace

void f()
{
    bool B1 = (&A::f1 == &A::f2); // Compliant
    bool B2 = (&A::f1 == nullptr); // Compliant
    bool B3 = (&A::f3 == nullptr); // Compliant
    bool B4 = (&A::f3 != nullptr); // Compliant
    bool B5 = (&A::f3 == &A::f1); // Non-compliant
    bool B51 = (&A::f1 == &A::f3); // Non-compliant
    bool B6 = (0 == 1);
    bool B7 = (nullptr == nullptr);
}
//TODO fix tests
// CHECK-MESSAGES: :[[@LINE-1]]:6: warning: A pointer to member virtual function shall only be tested for equality with null pointer constant. [autosar-a5-10-1-pointer-to-virt-member]
