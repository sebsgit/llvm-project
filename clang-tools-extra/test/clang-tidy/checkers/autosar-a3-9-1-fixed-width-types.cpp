// RUN: %check_clang_tidy %s autosar-a3-9-1-fixed-width-types %t

#include <cstdint>

template <typename T = short>
class X
{
public:
		T var;
		short var2;
		uint8_t var3;
};

struct S
{
	int x;
	int32_t x0;
};

void func()
{
	char a0;
	signed char a1;
	unsigned char a2;
	short a3;
	short int a4;
	signed short a5;
	signed short int a6;
	unsigned short a7;
	unsigned short int a8;
	int a9;
	const signed a10 = 0;
	signed int a11;
	unsigned a12;
	unsigned int a13;
	long a14;
	const long int a15 = 0;
	signed long a16;
	signed long int a17;
	unsigned long a18;
	unsigned long int a19;
	long long a20;
	long long int a21;
	signed long long a22;
	signed long long int a23;
	unsigned long long a24;
	unsigned long long int a25;
	
	auto lambda_i = []() -> int { return -1; };
}

int f_return_int()
{
	X<unsigned> x;
	return static_cast<const long>(1);
}

// CHECK-MESSAGES: :5:24: warning: A3-9-1: Use the fixed width integer types from <cstdint> [autosar-a3-9-1-fixed-width-types]
