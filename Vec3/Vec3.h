#pragma once

template <class T>
class Vec3 {

private:
	T x;
	T y;
	T z;

public:
	Vec3();
	Vec3(const T x, const T y, const T z);
	Vec3(const Vec3<T>& v);
	T getX() const;
	T getY() const;
	T getZ() const;
    void setX(T x);
	void setY(T y);
	void setZ(T z);
	Vec3<T> Normalize();
	float distance_to(Vec3<T> v);
	T dot_product(Vec3<T> v);
	Vec3<T> cross_product(Vec3<T> v);
	float angle_between(Vec3<T> v);

};
