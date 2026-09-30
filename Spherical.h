#pragma once
// 球面座標系
struct Spherical {
	float radius; // 動径
	float theta;  // 仰角
	float phi;    // 方位角
};

/* 初期値の例
#include <numbers>

Spherical s{
	6.0f,
	0.0f,
	-std::numbers::pi_v<float> / 2.0f};
*/