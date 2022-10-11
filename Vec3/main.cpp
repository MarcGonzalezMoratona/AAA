#include <iostream>
#include "Vec3.cpp"
using namespace std;

int main() {
	Vec3<int> v(7,6,4);
	Vec3<int> c(2,1,3);
	cout << v.getX() << endl;
	cout << v.getY() << endl;
	cout << v.getZ() << endl;

	Vec3<int> r = v.dot_product(c);
	cout << r.getX() << endl;
	cout << r.getY() << endl;
	cout << r.getZ() << endl;

	Vec3<int> d(1,0,5);
	Vec3<int> t(0,2,4);
	float distance = d.distance_to(t);
    cout << distance << endl;

	Vec3<float> n(5,6,10);
	Vec3<float>r2 = n.Normalize();
	cout << r2.getX() << endl;
	cout << r2.getY() << endl;
	cout << r2.getZ() << endl;


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file