#include "Quaternion.h"
#include <cmath>
// 単位クォータニオン
Quaternion Quaternion::IdentityQuaternion() { return {0.0f, 0.0f, 0.0f, 1.0f}; }

// 共役
Quaternion Quaternion::Conjugate(const Quaternion& q) { return {-q.x, -q.y, -q.z, q.w}; }

// ノルム
float Quaternion::Norm(const Quaternion& q) { return std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w); }

// 正規化
Quaternion Quaternion::Normalize(const Quaternion& q) {
	float norm = Norm(q);
	return {q.x / norm, q.y / norm, q.z / norm, q.w / norm};
}

// 逆クォータニオン
Quaternion Quaternion::Inverse(const Quaternion& q) {
	float normSquared = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;

	if (normSquared == 0.0f) {
		throw std::domain_error("Cannot invert zero quaternion");
	}

	Quaternion conjugate = Conjugate(q);

	return {conjugate.x / normSquared, conjugate.y / normSquared, conjugate.z / normSquared, conjugate.w / normSquared};
}

// クォータニオンの積
Quaternion Quaternion::Multiply(const Quaternion& q1, const Quaternion& q2) {
	return {
	    q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y, q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x, q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
	    q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z};
}

Quaternion Quaternion::MakeRotateAxisAngleQuatenion(const Vector3& axis, float angle) {
	float length = std::sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
	if (length == 0.0f) {
		throw std::domain_error("Cannot normalize zero axis");
	}
	Vector3 normalizedAxis = {axis.x / length, axis.y / length, axis.z / length};
	float sinHalfAngle = std::sin(angle / 2.0f);
	float cosHalfAngle = std::cos(angle / 2.0f);
	
	Quaternion result = {normalizedAxis.x * sinHalfAngle, normalizedAxis.y * sinHalfAngle, normalizedAxis.z * sinHalfAngle, cosHalfAngle};
	return result;
}

Vector3 Quaternion::RotateVector(const Vector3& vector, const Quaternion& quaternion) {
	Quaternion qVector = {vector.x, vector.y, vector.z, 0.0f};
	Quaternion rotated = Multiply(Multiply(quaternion, qVector), Inverse(quaternion));
	return {rotated.x, rotated.y, rotated.z};
}
Matrix4x4 Quaternion::MakeRotateMatrix(const Quaternion& q) {
	float x = q.x;
	float y = q.y;
	float z = q.z;
	float w = q.w;
	float w2 = q.w * q.w;
	float x2 = q.x * q.x;
	float y2 = q.y * q.y;
	float z2 = q.z * q.z;

	Matrix4x4 result = {
	    {{w2 + x2 - y2 - z2, 2.0f * (x * y + w * z), 2.0f * (x * z - w * y), 0.0f},
	     {2.0f * (x * y - w * z), w2 - x2 + y2 - z2, 2.0f * (y * z + w * x), 0.0f},
	     {2.0f * (x * z + w * y), 2.0f * (y * z - w * x), w2 - x2 - y2 + z2, 0.0f},
	     {0.0f, 0.0f, 0.0f, 1.0f}}
    };

	return result;
}


Quaternion Quaternion::DirectionToDirection(const Vector3& from, const Vector3& to) {

	// fromとtoは正規化済みを前提とする

	// 内積
	float dot = from.x * to.x + from.y * to.y + from.z * to.z;

	// 同じ向き
	if (dot >= 0.999999f) {
		return IdentityQuaternion();
	}

	// 真逆の向き
	if (dot <= -0.999999f) {

		// fromに垂直な回転軸を作成
		Vector3 axis = {-from.y, from.x, 0.0f};

		float length = std::sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);

		// fromがZ軸に近い場合
		if (length < 0.000001f) {
			axis = {0.0f, -from.z, from.y};

			length = std::sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
		}

		axis.x /= length;
		axis.y /= length;
		axis.z /= length;

		// 180度回転
		return {axis.x, axis.y, axis.z, 0.0f};
	}

	// 通常の向き：外積から回転軸を計算
	Vector3 cross = {from.y * to.z - from.z * to.y, from.z * to.x - from.x * to.z, from.x * to.y - from.y * to.x};

	Quaternion result = {cross.x, cross.y, cross.z, 1.0f + dot};

	return Normalize(result);
}

Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to) {

	Quaternion rotation = Quaternion::DirectionToDirection(from, to);

	return Quaternion::MakeRotateMatrix(rotation);
}

// クォータニオンの内積
float Quaternion::Dot(const Quaternion& q1, const Quaternion& q2) { return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w; }