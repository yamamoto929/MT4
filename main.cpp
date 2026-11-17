#include <Novice.h>
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
const char kWindowTitle[] = "LE2B_30_ヤマモト_ルナ";
const int kRowHeight = 20;
// Quaternion表示
void QuaternionScreenPrintf(int x, int y, const Quaternion& q, const char* label);

// Matrix4x4表示
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

// Vector3表示
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result = {
	    vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0],

	    vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1],

	    vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2]};

	return result;
}

Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	
	Quaternion rotation0 = Quaternion::MakeRotateAxisAngleQuatenion({0.71f, 0.71f, 0.0f}, 0.3f);

	Quaternion rotation1 = Quaternion::MakeRotateAxisAngleQuatenion({0.71f, 0.0f, 0.71f}, 3.141592f);

	Quaternion interpolate0 = Slerp(rotation0, rotation1, 0.0f);
	Quaternion interpolate1 = Slerp(rotation0, rotation1, 0.3f);
	Quaternion interpolate2 = Slerp(rotation0, rotation1, 0.5f);
	Quaternion interpolate3 = Slerp(rotation0, rotation1, 0.7f);
	Quaternion interpolate4 = Slerp(rotation0, rotation1, 1.0f);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		QuaternionScreenPrintf(0, kRowHeight * 0, interpolate0, ": interpolate0, Slerp(q0, q1, 0.0f)");

		QuaternionScreenPrintf(0, kRowHeight * 1, interpolate1, ": interpolate1, Slerp(q0, q1, 0.3f)");

		QuaternionScreenPrintf(0, kRowHeight * 2, interpolate2, ": interpolate2, Slerp(q0, q1, 0.5f)");

		QuaternionScreenPrintf(0, kRowHeight * 3, interpolate3, ": interpolate3, Slerp(q0, q1, 0.7f)");

		QuaternionScreenPrintf(0, kRowHeight * 4, interpolate4, ": interpolate4, Slerp(q0, q1, 1.0f)");
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

// Quaternion表示
void QuaternionScreenPrintf(int x, int y, const Quaternion& q, const char* label) { Novice::ScreenPrintf(x, y, "%6.2f %6.2f %6.2f %6.2f %s", q.x, q.y, q.z, q.w, label); }

// Matrix4x4表示
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {

	Novice::ScreenPrintf(x, y, "%s", label);

	for (int row = 0; row < 4; row++) {
		Novice::ScreenPrintf(x, y + kRowHeight * (row + 1), "%7.3f %7.3f %7.3f %7.3f", matrix.m[row][0], matrix.m[row][1], matrix.m[row][2], matrix.m[row][3]);
	}
}

// Vector3表示
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) { Novice::ScreenPrintf(x, y, "%6.2f %6.2f %6.2f %s", vector.x, vector.y, vector.z, label); }

Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t) {
	Quaternion end = q1;
	float dot=Quaternion::Dot(q0,end);
	if (dot < 0.0f) {
		end=Quaternion::Conjugate(end);
		dot = -dot;
	}

	float theta = std::acos(dot);

	float scale0 = std::sin((1.0f - t) * theta) / std::sin(theta);
	float scale1 = std::sin(t * theta) / std::sin(theta);

	return {scale0 * q0.x + scale1 * end.x, scale0 * q0.y + scale1 * end.y, scale0 * q0.z + scale1 * end.z, scale0 * q0.w + scale1 * end.w};
}
