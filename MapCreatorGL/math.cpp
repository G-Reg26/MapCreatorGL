#include "math.h"


//VECTOR2
Vec2::Vec2()
{
	x = 0.0f;
	y = 0.0f;
}

Vec2::Vec2(const float & x, const float & y)
{
	this->x = x;
	this->y = y;
}


//VECTOR3
Vec3::Vec3()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vec3::Vec3(const float & x, const float & y, const float & z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3 Vec3::Add(const float & x, const float & y, const float & z)
{
	this->x += x;
	this->y += y;
	this->z += z;

	return *this;
}

Vec3 Vec3::Subtract(const float & x, const float & y, const float & z)
{
	this->x -= x;
	this->y -= y;
	this->z -= z;

	return *this;
}

Vec3 Vec3::Multiply(const float & x, const float & y, const float & z)
{
	this->x *= x;
	this->y *= y;
	this->z *= z;

	return *this;
}

Vec3 Vec3::Divide(const float & x, const float & y, const float & z)
{
	this->x /= x;
	this->y /= y;
	this->z /= z;

	return *this;
}

Vec3 Vec3::Add(const float & scalar)
{
	this->x += scalar;
	this->y += scalar;
	this->z += scalar;

	return *this;
}

Vec3 Vec3::Subtract(const float & scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	this->z -= scalar;

	return *this;
}

Vec3 Vec3::Multiply(const float & scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;

	return *this;
}

Vec3 Vec3::Divide(const float & scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;

	return *this;
}

Vec3 Vec3::Cross(const Vec3 & v) const
{
	const float _x = y * v.z - z * v.y;
	const float _y = z * v.x - x * v.z;
	const float _z = x * v.y - y * v.x;

	return Vec3(_x, _y, _z);
}

Vec3 & Vec3::Normalize()
{
	const float Length = sqrtf(x * x + y * y + z * z);

	x /= Length;
	y /= Length;
	z /= Length;

	return *this;
}

void Vec3::Rotate(float Angle, const Vec3 & Axe)
{
	const float SinHalfAngle = sinf(Functions::ToRadians(Angle / 2));
	const float CosHalfAngle = cosf(Functions::ToRadians(Angle / 2));

	const float Rx = Axe.x * SinHalfAngle;
	const float Ry = Axe.y * SinHalfAngle;
	const float Rz = Axe.z * SinHalfAngle;
	const float Rw = CosHalfAngle;

	Quaternion RotationQ(Rx, Ry, Rz, Rw);
	Quaternion ConjugateQ = RotationQ.Conjugate();

	Quaternion W = RotationQ * (*this) * ConjugateQ;

	x = W.x;
	y = W.y;
	z = W.z;
}

Vec3 operator+(Vec3 left, const Vec3& right)
{
	return left.Add(right.x, right.y, right.z);
}

Vec3 operator-(Vec3 left, const Vec3& right)
{
	return left.Subtract(right.x, right.y, right.z);
}

Vec3 operator*(Vec3 left, const Vec3& right)
{
	return left.Multiply(right.x, right.y, right.z);
}

Vec3 operator/(Vec3 left, const Vec3& right)
{
	return left.Divide(right.x, right.y, right.z);
}

Vec3 operator+(Vec3 left, const float & scalar)
{
	return left.Add(scalar);
}

Vec3 operator-(Vec3 left, const float & scalar)
{
	return left.Subtract(scalar);
}

Vec3 operator*(Vec3 left, const float & scalar)
{
	return left.Multiply(scalar);
}

Vec3 operator/(Vec3 left, const float & scalar)
{
	return left.Divide(scalar);;
}

Vec3 & Vec3::operator+=(const Vec3 & other)
{
	return Add(other.x, other.y, other.z);
}

Vec3 & Vec3::operator-=(const Vec3 & other)
{
	return Subtract(other.x, other.y, other.z);
}

Vec3 & Vec3::operator*=(const Vec3 & other)
{
	return Multiply(other.x, other.y, other.z);
}

Vec3 & Vec3::operator/=(const Vec3 & other)
{
	return Divide(other.x, other.y, other.z);
}

Vec3 & Vec3::operator+=(const float & scalar)
{
	return Add(scalar);
}

Vec3 & Vec3::operator-=(const float & scalar)
{
	return Subtract(scalar);
}

Vec3 & Vec3::operator*=(const float & scalar)
{
	return Multiply(scalar);
}

Vec3 & Vec3::operator/=(const float & scalar)
{
	return Divide(scalar);
}

bool Vec3::operator==(const Vec3 & other) const
{
	return x == other.x && y == other.y && z == other.z;
}

bool Vec3::operator!=(const Vec3 & other) const
{
	return !(*this == other);
}

bool Vec3::operator<(const Vec3 & other) const
{
	return x < other.x && y < other.y && z < other.z;
}

bool Vec3::operator>(const Vec3 & other) const
{
	return x > other.x && y > other.y && z > other.z;
}

bool Vec3::operator<=(const Vec3 & other) const
{
	return x <= other.x && y <= other.y && z <= other.z;
}

bool Vec3::operator>=(const Vec3 & other) const
{
	return x >= other.x && y >= other.y && z >= other.z;
}

Vec3 operator-(const Vec3& vector)
{
	return Vec3(-vector.x, -vector.y, -vector.z);
}


//MAT4
Mat4::Mat4()
{
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			if (i == j) 
			{
				matrix[i][j] = 1.0;
			}
			else 
			{
				matrix[i][j] = 0.0;
			}
		}
	}
}

Mat4::Mat4(const float matrix[4][4])
{
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			this->matrix[i][j] = matrix[i][j];
		}
	}
}

Mat4 Mat4::Multiply(const Mat4 & mat4)
{
	float newMat[4][4] = 
	{
		{ 0.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f },
	};

	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			for (int k = 0; k < 4; k++)
			{
				newMat[j][i] += (matrix[j][k] * mat4.matrix[k][i]);
			}
		}
	}

	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			this->matrix[i][j] = newMat[i][j];
		}
	}

	return *this;
}

Mat4 operator*(Mat4 left, const Mat4& right)
{
	return left.Multiply(right);
}

Mat4 & Mat4::operator*=(const Mat4 & other) 
{
	return Multiply(other);
}


//QUATERNION
Quaternion::Quaternion()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

Quaternion::Quaternion(const float x, const float y, const float z, const float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion Quaternion::Multiply(const Quaternion & quaternion)
{
	const float _w = (w * quaternion.w) - (x * quaternion.x) - (y * quaternion.y) - (z * quaternion.z);
	const float _x = (x * quaternion.w) + (w * quaternion.x) + (y * quaternion.z) - (z * quaternion.y);
	const float _y = (y * quaternion.w) + (w * quaternion.y) + (z * quaternion.x) - (x * quaternion.z);
	const float _z = (z * quaternion.w) + (w * quaternion.z) + (x * quaternion.y) - (y * quaternion.x);

	Quaternion q(_x, _y, _z, _w);

	return q;
}

Quaternion Quaternion::Multiply(const Vec3 & vec)
{
	const float _w =-(x * vec.x) - (y * vec.y) - (z * vec.z);
	const float _x = (w * vec.x) + (y * vec.z) - (z * vec.y);
	const float _y = (w * vec.y) + (z * vec.x) - (x * vec.z);
	const float _z = (w * vec.z) + (x * vec.y) - (y * vec.x);

	Quaternion q(_x, _y, _z, _w);

	return q;
}

Quaternion Quaternion::Conjugate()
{
	Quaternion q(-x, -y, -z, w);

	return q;
}

Quaternion operator*(Quaternion left, const Quaternion & right)
{
	return left.Multiply(right);
}

Quaternion operator*(Quaternion left, const Vec3 & right)
{
	return left.Multiply(right);
}

Quaternion & Quaternion::operator*=(const Quaternion & other)
{
	return Multiply(other);
}

Quaternion & Quaternion::operator*=(const Vec3 & other)
{
	return Multiply(other);
}
