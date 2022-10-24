#include "String.h"
#include <iostream>
using namespace std;

void main() {
	String a;
	a = "hello";
	cout << a.str << endl;

	String b("world");
	cout << b.str << endl;

	String c = std::move(a + std::move(b)); 
}