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

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Quaternion rotation = Quaternion::MakeRotateAxisAngleQuatenion({1.0f, 0.4f, -0.2f}, 0.45f);

	Vector3 pointY = {2.1f, -0.9f, 1.3f};

	Matrix4x4 rotateMatrix = Quaternion::MakeRotateMatrix(rotation);

	Vector3 rotateByQuaternion = Quaternion::RotateVector(pointY, rotation);
	Vector3 rotateByMatrix = Transform(pointY, rotateMatrix);


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
		// 画面に表示
		QuaternionScreenPrintf(0, kRowHeight * 0, rotation, ": rotation");

		MatrixScreenPrintf(0, kRowHeight * 1, rotateMatrix, "rotateMatrix");

		VectorScreenPrintf(0, kRowHeight * 6, rotateByQuaternion, ": rotateByQuaternion");

		VectorScreenPrintf(0, kRowHeight * 7, rotateByMatrix, ": rotateByMatrix");
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