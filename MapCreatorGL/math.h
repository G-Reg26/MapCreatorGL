#pragma once

#include <iostream>

#define PI 3.14159f

struct Vec2
{
	Vec2();
	Vec2(const float &x, const float &y);

	float x, y;
};

struct  Vec3
{
	Vec3();
	Vec3(const float &x, const float &y, const float &z);

	Vec3 Add(const float &x, const float& y, const float &z);
	Vec3 Subtract(const float &x, const float& y, const float &z);
	Vec3 Multiply(const float &x, const float& y, const float &z);
	Vec3 Divide(const float &x, const float& y, const float &z);

	Vec3 Add(const float &scalar);
	Vec3 Subtract(const float &scalar);
	Vec3 Multiply(const float &scalar);
	Vec3 Divide(const float &scalar);

	Vec3 Cross(const Vec3& v) const;
	Vec3& Normalize();
	void Rotate(float Angle, const Vec3& Axe);

	friend Vec3 operator+(Vec3 left, const Vec3& right);
	friend Vec3 operator-(Vec3 left, const Vec3& right);
	friend Vec3 operator*(Vec3 left, const Vec3& right);
	friend Vec3 operator/(Vec3 left, const Vec3& right);

	friend Vec3 operator+(Vec3 left, const float& scalar);
	friend Vec3 operator-(Vec3 left, const float& scalar);
	friend Vec3 operator*(Vec3 left, const float& scalar);
	friend Vec3 operator/(Vec3 left, const float& scalar);

	Vec3& operator+=(const Vec3& other);
	Vec3& operator-=(const Vec3& other);
	Vec3& operator*=(const Vec3& other);
	Vec3& operator/=(const Vec3& other);

	Vec3& operator+=(const float& scalar);
	Vec3& operator-=(const float& scalar);
	Vec3& operator*=(const float& scalar);
	Vec3& operator/=(const float& scalar);

	bool operator==(const Vec3& other) const;
	bool operator!=(const Vec3& other) const;

	bool operator<(const Vec3& other) const;
	bool operator>(const Vec3& other) const;
	bool operator<=(const Vec3& other) const;
	bool operator>=(const Vec3& other) const;

	friend Vec3 operator-(const Vec3& vector);

	float x, y, z;
};

struct Mat4 
{
	Mat4();
	Mat4(const float matrix[4][4]);

	Mat4 Multiply(const Mat4 &mat4);

	friend Mat4 operator*(Mat4 left, const Mat4& right);

	Mat4& operator*=(const Mat4& other);

	float matrix[4][4];
};

struct Quaternion 
{
	Quaternion();
	Quaternion(const float x, const float y, const float z, const float w);

	Quaternion Multiply(const Quaternion &quaternion);
	Quaternion Multiply(const Vec3 &vec);
	Quaternion Conjugate();

	friend Quaternion operator*(Quaternion left, const Quaternion& right);
	friend Quaternion operator*(Quaternion left, const Vec3& right);

	Quaternion& operator*=(const Quaternion& other);
	Quaternion& operator*=(const Vec3& other);

	float x, y, z, w;
};

struct Functions
{
	static float ToRadians(const float &degree) 
	{
		return (degree * PI) / 180.0f;
	}

	static Vec3 ToRadians(const Vec3 &degree) 
	{
		return Vec3(((degree.x * PI) / 180.0f), ((degree.y * PI) / 180.0f), ((degree.z * PI) / 180.0f));
	}

	static float ToDegrees(const float &radian) 
	{
		return (radian * 180.0f) / PI;
	}

	static Vec3 ToDegrees(const Vec3 &radian) 
	{
		return Vec3(((radian.x * 180.0f) / PI), ((radian.y * 180.0f) / PI), ((radian.z * 180.0f) / PI));
	}

	static float Distance(const Vec3 &point1, const Vec3 &point2) 
	{
		return sqrtf(Square(point2.x - point1.x) + Square(point2.y - point1.y) + Square(point2.z - point1.z));
	}

	static float Square(const float &x) 
	{
		return x * x;
	}

	static float C(const float &a, const float &b) 
	{
		return sqrtf(Square(a) + Square(b));
	}

	static float r(float x, float y)
	{
		return sqrtf((x * x) + (y * y));
	}

	static float GetTheta(float x, float y)
	{
		if (x == 0 && y != 0)
		{
			if (y > 0)
			{
				return 3.14159f / 2.0f;
			}
			else
			{
				return (3 * 3.14159f) / 2.0f;
			}
		}
		else if (x != 0 && y == 0)
		{
			if (x > 0)
			{
				return 0.0f;
			}
			else
			{
				return 3.14159f;
			}
		}
		else if (x == 0 && y == 0)
		{
			return 0.0f;
		}
		else
		{
			if (y / x > 0)
			{
				if (y > 0)
				{
					return atanf(y / x);
				}
				else
				{
					return atanf(y / x) + 3.14159f;
				}
			}
			else
			{
				if (x < 0)
				{
					return acosf(x / r(x, y));
				}
				else
				{
					return asinf(y / r(x, y)) + (2.0f * 3.14159f);
				}
			}
		}
	}


};