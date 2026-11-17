#include <cmath>
#include <stdexcept>
#include "Vector3.h"
#include "Matrix4x4.h"

class Quaternion {
public:
	float x;
	float y;
	float z;
	float w;

public:
	Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	// 単位クォータニオン
	static Quaternion IdentityQuaternion();
	// 共役
	static Quaternion Conjugate(const Quaternion& q);

	// ノルム
	static float Norm(const Quaternion& q);

	// 正規化
	static Quaternion Normalize(const Quaternion& q);
	// 逆クォータニオン
	static Quaternion Inverse(const Quaternion& q);

	// クォータニオンの積
	static Quaternion Multiply(const Quaternion& q1, const Quaternion& q2);

	static Quaternion MakeRotateAxisAngleQuatenion(const Vector3& axis, float angle);

	static Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);

	static Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);

	// fromからtoへ回転させるQuaternion
	static Quaternion DirectionToDirection(const Vector3& from, const Vector3& to);

	// クォータニオンの内積
	static float Dot(const Quaternion& q1, const Quaternion& q2);
};

// fromからtoへ回転させる行列
Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to);

