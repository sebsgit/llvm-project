// RUN: %check_clang_tidy %s autosar-a2-13-5-hex-constants-upper-case %t

void func()
{
	const auto x1 = 0xFFff;
	// CHECK-MESSAGES: :[[@LINE-1]]:21: warning: A2-13-5: Hexadecimal constants should be upper case [autosar-a2-13-5-hex-constants-upper-case]

	const auto x2 = 0xab8F;
	// CHECK-MESSAGES: :[[@LINE-1]]:21: warning: A2-13-5: Hexadecimal constants should be upper case [autosar-a2-13-5-hex-constants-upper-case]
	
	const auto y = 0xFFAB;
}
