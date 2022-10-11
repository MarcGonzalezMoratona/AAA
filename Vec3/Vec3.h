#pragma once

template <class T>
class Vec3 {

private:
	T x;
	T y;
	T z;

public:
	Vec3();
	Vec3(T x, T y, T z);
	// Vec3(Vec3<T>& v);
	T getX();
	T getY();
	T getZ();
    T setX(T x);
	T setY(T y);
	T setZ(T z);
	Vec3<T> Normalize();
	float distance_to(Vec3<T> v);
	Vec3<T> dot_product(Vec3<T> v);
	void cross_product(Vec3<T> v);
	void angle_between(Vec3<T> v);

};

#pragma once