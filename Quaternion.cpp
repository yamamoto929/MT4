#include "Quaternion.h"
// 単位クォータニオン
Quaternion IdentityQuaternion() { return {0.0f, 0.0f, 0.0f, 1.0f}; }

// 共役
Quaternion Conjugate(const Quaternion& q) { return {-q.x, -q.y, -q.z, q.w}; }

// ノルム
float Norm(const Quaternion& q) { return std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w); }

// 正規化
Quaternion Normalize(const Quaternion& q) {
	float norm = Norm(q);
	return {q.x / norm, q.y / norm, q.z / norm, q.w / norm};
}

// 逆クォータニオン
Quaternion Inverse(const Quaternion& q) {
	float normSquared = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;

	if (normSquared == 0.0f) {
		throw std::domain_error("Cannot invert zero quaternion");
	}

	Quaternion conjugate = Conjugate(q);

	return {conjugate.x / normSquared, conjugate.y / normSquared, conjugate.z / normSquared, conjugate.w / normSquared};
}

// クォータニオンの積
Quaternion Multiply(const Quaternion& q1, const Quaternion& q2) {
	return {
	    q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y, q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x, q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
	    q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z};
}