#include <iostream>
#include "Vec3.cpp"
using namespace std;

void main() {
	Vec3<float> v1(7, 6, 4);
	Vec3<float> v2(2, 1, 3);
	cout << "Initial values:" << endl;
	cout << "v1: (" << v1.getX() << ", " << v1.getY() << ", " << v1.getZ() << ")" << endl;
	cout << "v2: (" << v2.getX() << ", " << v2.getY() << ", " << v2.getZ() << ")" << endl;

	cout << endl << "Copy of the vector v1:" << endl;
	Vec3<float> v3 = Vec3<float>(v1);
	cout << "v3: (" << v3.getX() << ", " << v3.getY() << ", " << v3.getZ() << ")" << endl;


	Vec3<float> cp = v1.cross_product(v2);
	cout << endl << "Cross product:"  << "(" << cp.getX() << ", " << cp.getY() << ", " << cp.getZ() << ")" << endl;
	cout << "Expected output: (14, 13, -5)" << endl;

	cout << endl << "Setting new values:" << endl;
	v1.setX(2);
	v1.setY(7);
	v1.setZ(2);
	v2.setX(3);
	v2.setY(1);
	v2.setZ(5);

	cout << "(" << v1.getX() << ", " << v1.getY() << ", " << v1.getZ() << ")" << endl;
	cout << "(" << v2.getX() << ", " << v2.getY() << ", " << v2.getZ() << ")" << endl;

	float dp = v1.dot_product(v2);
	cout << endl << "Dot product: " << dp << endl;
	cout << "Expected output: 23" << endl;

	cout << endl << "Setting new values:" << endl;
	v1.setX(1);
	v1.setY(0);
	v1.setZ(5);
	v2.setX(0);
	v2.setY(2);
	v2.setZ(4);

	cout << "(" << v1.getX() << ", " << v1.getY() << ", " << v1.getZ() << ")" << endl;
	cout << "(" << v2.getX() << ", " << v2.getY() << ", " << v2.getZ() << ")" << endl;
	
	float distance = v1.distance_to(v2);
	cout << endl << "Distance: " << distance << endl;
	cout << "Expected output: 2.44949" << endl;

	cout << endl << "Setting new values:" << endl;
	v1.setX(5);
	v1.setY(7);
	v1.setZ(9);
	cout << "(" << v1.getX() << ", " << v1.getY() << ", " << v1.getZ() << ")" << endl;


	cout << endl << "Normalisation: ";
	Vec3<float>n = v1.Normalize();
	cout << "(" << n.getX() << ", " << n.getY() << ", " << n.getZ() << ")" << endl;
	cout << "Expected output: (0.40161, 0.562254, 0.722897)" << endl;

	cout << endl << "Setting new values:" << endl;
	v1.setX(1);
	v1.setY(2);
	v1.setZ(3);
	v2.setX(4);
	v2.setY(5);
	v2.setZ(6);

	cout << "(" << v1.getX() << ", " << v1.getY() << ", " << v1.getZ() << ")" << endl;
	cout << "(" << v2.getX() << ", " << v2.getY() << ", " << v2.getZ() << ")" << endl;

	cout << endl << "Angle between" << "(" << v1.getX() << ", " << v1.getY() << ", " << v1.getZ() << ") " << "and (" << v2.getX() << ", " << v2.getY() << ", " << v2.getZ() << "): " << v1.angle_between(v2) << "°" << endl;
	cout << "Expected output: 12.9332°" << endl;

	
}
