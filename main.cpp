#include "Quaternion.h"
#include <Novice.h>

const char kWindowTitle[] = "LE2B_30_ヤマモト_ルナ";
void ScreenPrintQuaternion(const char* label, const Quaternion& q, const float& textX, const float& textY);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Quaternion q1 = {2.0f, 3.0f, 4.0f, 1.0f};
	Quaternion q2 = {1.0f, 3.0f, 5.0f, 2.0f};
	Quaternion identity = IdentityQuaternion();
	Quaternion conj = Conjugate(q1);
	Quaternion inv = Inverse(q1);
	Quaternion normal = Normalize(q1);
	Quaternion mul1 = Multiply(q1, q2);
	Quaternion mul2 = Multiply(q2, q1);
	float norm = Norm(q1);
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
		ScreenPrintQuaternion("Identity", identity, 10, 10);
		ScreenPrintQuaternion("Conjugate", conj, 10, 30);
		ScreenPrintQuaternion("Inverse", inv, 10, 50);
		ScreenPrintQuaternion("Normalize", normal, 10, 70);
		ScreenPrintQuaternion("Multiply(q1,q2)", mul1, 10, 90);
		ScreenPrintQuaternion("Multiply(q2,q1)", mul2, 10, 110);
		Novice::ScreenPrintf(10, 130, "Norm : %.2f", norm);

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

void ScreenPrintQuaternion(const char* label, const Quaternion& q, const float& textX, const float& textY) {
	Novice::ScreenPrintf(static_cast<int>(textX), static_cast<int>(textY), "%s : %.2f, %.2f, %.2f, %.2f", label, q.x, q.y, q.z, q.w);
}
