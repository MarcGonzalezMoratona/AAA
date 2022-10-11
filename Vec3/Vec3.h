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
    void setX(T x);
	void setY(T y);
	void setZ(T z);
	Vec3<T> Normalize();
	float distance_to(Vec3<T> v);
	T dot_product(Vec3<T> v);
	Vec3<T> cross_product(Vec3<T> v);
	void angle_between(Vec3<T> v);

};
