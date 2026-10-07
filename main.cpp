#include <Novice.h>
#ifdef USE_IMGUI
#include <imgui.h>
#endif

const char kWindowTitle[] = "LE2B_30_ヤマモト_ルナ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	float mousePositionX = 0.0f;
	float mousePositionY = 0.0f;

	float lerpCirclePosX = 640.0f;
	float lerpCirclePosY = 360.0f;

	float deltaTime = 1.0f / 60.0f;
	float speed = 1.0f;


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
		ImGui::Begin("Debug");
		ImGui::SliderFloat("speed", &speed, 0.1f, 30.0f);
		ImGui::End();
		int intMouseX = 0;
		int intMouseY = 0;
		Novice::GetMousePosition(&intMouseX, &intMouseY);
		mousePositionX = static_cast<float>(intMouseX);
		mousePositionY = static_cast<float>(intMouseY);
		lerpCirclePosX += (speed * deltaTime) * (mousePositionX - lerpCirclePosX);
		lerpCirclePosY += (speed * deltaTime) * (mousePositionY - lerpCirclePosY);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawEllipse(static_cast<int>(mousePositionX), static_cast<int>(mousePositionY), 12, 12, 0.0f, 0xFF0000FF, kFillModeSolid);
		Novice::DrawEllipse(static_cast<int>(lerpCirclePosX), static_cast<int>(lerpCirclePosY), 20, 20, 0.0f, 0x00FF00FF, kFillModeSolid);
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
