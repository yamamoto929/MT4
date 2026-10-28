#include <cmath>
#include <stdexcept>
#include "Vector3.h"
#include "Matrix4x4.h"

class Quaternion {
	float x;
	float y;
	float z;
	float w;

public:
	Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	// 単位クォータニオン
	Quaternion IdentityQuaternion();
	// 共役
	Quaternion Conjugate(const Quaternion& q);

	// ノルム
	float Norm(const Quaternion& q);

	// 正規化
	Quaternion Normalize(const Quaternion& q);
	// 逆クォータニオン
	Quaternion Inverse(const Quaternion& q);

	// クォータニオンの積
	Quaternion Multiply(const Quaternion& q1, const Quaternion& q2);

	Quaternion MakeRotateAxisAngleQuatenion(const Vector3& axis, float angle);

	Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);

	Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);
};

