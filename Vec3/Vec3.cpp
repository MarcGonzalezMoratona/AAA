#include "Vec3.h"
#include <iostream>
#include <cmath>

using namespace std;

template <class T>
Vec3<T>::Vec3() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

template <class T>
Vec3<T>::Vec3(const T x, const T y, const T z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

 template <class T>
 Vec3<T>::Vec3(const Vec3<T>& v) {
 	this->x = v.getX();
 	this->y = v.getY();
 	this->z = v.getZ();
 }

template <class T>
T Vec3<T>::getX() const{
	return this->x;
}

template <class T>
T Vec3<T>::getY() const{
	return this->y;
}

template <class T>
T Vec3<T>::getZ() const{
	return this->z;
}

template <class T>
void Vec3<T>::setX(T x) {
	this->x = x;
}

template <class T>
void Vec3<T>::setY(T y) {
	this->y = y;
}

template <class T>
void Vec3<T>::setZ(T z) {
	this->z = z;
}

template <class T>
Vec3<T> Vec3<T>::Normalize() {
	float length = sqrt((pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)));
	return Vec3<T>(this->x / length, this->y / length, this->z / length);
}

template <class T>
float Vec3<T>::distance_to(Vec3<T> v) {
	Vec3<T> r(pow(this->x - v.x, 2), pow(this->y - v.y, 2), pow(this->z - v.z, 2));
	return sqrt(r.getX() + r.getY() + r.getZ());
}

template <class T>
T Vec3<T>::dot_product(Vec3<T> v) {
	return (this->x * v.x + this->y * v.y + this->z * v.z);
}


template <class T>
Vec3<T> Vec3<T>::cross_product(Vec3<T> v) {
	return Vec3<T>((this->y * v.z - this->z * v.y), (this->x * v.z - this->z * v.x), (this->x * v.y - this->y * v.x));
}

template <class T>
float Vec3<T>::angle_between(Vec3<T> v) {
	return 180*(acos(dot_product(v) / 
		(sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)) * 
		sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)))))/M_PI;
}
