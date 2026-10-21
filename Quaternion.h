#include <cmath>
#include <stdexcept>

struct Quaternion {
	float x;
	float y;
	float z;
	float w;
};

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