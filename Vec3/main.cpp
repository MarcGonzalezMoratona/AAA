#include <iostream>
#include "Vec3.cpp"
using namespace std;

int main() {
	Vec3<float> v(7, 6, 4);
	Vec3<float> c(2, 1, 3);
	cout << "Initial values:" << endl;
	cout << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")" << endl;
	cout << "(" << c.getX() << ", " << c.getY() << ", " << c.getZ() << ")" << endl;

	Vec3<float> cp = v.cross_product(c);
	cout << endl << "Cross product:"  << "(" << cp.getX() << ", " << cp.getY() << ", " << cp.getZ() << ")" << endl;
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

	float dp = v.dot_product(c);
	cout << endl << "Dot product: " << dp << endl;
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
	
	float distance = v.distance_to(c);
	cout << endl << "Distance: " << distance << endl;
	cout << "Expected output: 2.44949" << endl;

	cout << endl << "Setting new values:" << endl;
	v.setX(5);
	v.setY(7);
	v.setZ(9);
	cout << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")" << endl;


	cout << endl << "Normalisation: ";
	Vec3<float>n = v.Normalize();
	cout << "(" << n.getX() << ", " << n.getY() << ", " << n.getZ() << ")" << endl;
	cout << "Expected output: (0.40161, 0.562254, 0.722897)" << endl;

	cout << endl << "Setting new values:" << endl;
	v.setX(1);
	v.setY(2);
	v.setZ(3);
	c.setX(4);
	c.setY(5);
	c.setZ(6);

	cout << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")" << endl;
	cout << "(" << c.getX() << ", " << c.getY() << ", " << c.getZ() << ")" << endl;

	cout << endl << "Angle between" << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ") " << "and (" << c.getX() << ", " << c.getY() << ", " << c.getZ() << "): " << v.angle_between(c) << "°" << endl;
	cout << "Expected output: 12.9332°" << endl;

	
}
