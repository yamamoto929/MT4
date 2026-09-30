#include "Matrix4x4.h"
#include "Spherical.h"
#include "Vector3.h"
#include <Novice.h>
#include <cmath>
#include <imgui.h>
#include <numbers>

const char kWindowTitle[] = "LE2B_30_ヤマモト_ルナ";
Vector3 ToCartesian(const Spherical& s);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	const float halfPi = std::numbers::pi_v<float> / 2.0f;
	Spherical s{6.0f, 0.0f, -halfPi};

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

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
		Vector3 pos = ToCartesian(s);
		Vector3 target{};
		Vector3 eye = target + pos;
		Vector3 worldUp{0.0f, 1.0f, 0.0f};
		Vector3 forward = Normalize(target - eye);
		Vector3 right = Normalize(Cross(worldUp, forward));
		Vector3 up = Cross(forward, right);
		Matrix4x4 cameraMatrix{
		    {{right.x, right.y, right.z, 0.0f}, {up.x, up.y, up.z, 0.0f}, {forward.x, forward.y, forward.z, 0.0f}, {eye.x, eye.y, eye.z, 1.0f}}
        };
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		ImGui::Begin("Spherical Coordinates");
		ImGui::Text("Target: (0,0,0) / +Y up / Camera +Z forward");
		ImGui::Separator();
		ImGui::InputFloat("Radius", &s.radius, 0.01f);
		ImGui::InputFloat("Theta: elevation (rad)", &s.theta, 0.01f);
		ImGui::InputFloat("Phi (rad)", &s.phi, 0.01f);
		ImGui::Separator();
		ImGui::Text("Spherical: r = %.3f, theta = %.3f rad, phi = %.3f rad", s.radius, s.theta, s.radius);
		ImGui::Text("Cartesian: x = %.3f, y = %.3f, z = %.3f", pos.x, pos.y, pos.z);
		ImGui::Separator();
		ImGui::Text("Camera Matrix");
		for (int i = 0; i < 4; i++) {
			ImGui::Text("%.3f    %.3f    %.3f    %.3f", cameraMatrix.m[i][0], cameraMatrix.m[i][1], cameraMatrix.m[i][2], cameraMatrix.m[i][3]);
		}
		ImGui::End();
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

Vector3 ToCartesian(const Spherical& s) {
	float rho = s.radius * std::cos(s.theta);
	return {rho * std::cos(s.phi), s.radius * std::sin(s.theta), rho * std::sin(s.phi)};
}
