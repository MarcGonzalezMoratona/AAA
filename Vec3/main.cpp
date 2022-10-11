#include <iostream>
#include "Vec3.cpp"
using namespace std;

int main() {
	Vec3<int> v(7, 6, 4);
	Vec3<int> c(2, 1, 3);
	cout << "Initial values:" << endl;
	cout << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")" << endl;
	cout << "(" << c.getX() << ", " << c.getY() << ", " << c.getZ() << ")" << endl;

	Vec3<int> r2 = v.cross_product(c);
	cout << endl << "Cross product:"  << "(" << r2.getX() << ", " << r2.getY() << ", " << r2.getZ() << ")" << endl;
	cout << "Expected output: (14, 13, -5)" << endl;

	cout << endl << "Setting new values:" << endl;
	v.setX(2);
	v.setY(7);
	v.setZ(2);
	c.setX(3);
	c.setY(1);
	c.setZ(5);

	cout << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")" << endl;
	cout << "(" << c.getX() << ", " << c.getY() << ", " << c.getZ() << ")" << endl;

	float r1 = v.dot_product(c);
	cout << endl << "Dot product: " << r1 << endl;
	cout << "Expected output: 23" << endl;

	cout << endl << "Setting new values:" << endl;
	v.setX(1);
	v.setY(0);
	v.setZ(5);
	c.setX(0);
	c.setY(2);
	c.setZ(4);

	cout << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")" << endl;
	cout << "(" << c.getX() << ", " << c.getY() << ", " << c.getZ() << ")" << endl;
	
	cout << endl << "Distance:" << endl;
	float distance = v.distance_to(c);
	cout << distance << endl;

	cout << endl << "Normalisation:" << endl;
	Vec3<float> n(5, 6, 10);
	Vec3<float>r3 = n.Normalize();
	cout << "(" << r3.getX() << ", " << r3.getY() << ", " << r3.getZ() << ")" << endl;
}
