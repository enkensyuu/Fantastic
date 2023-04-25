#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DirectXMath.h"

using namespace DirectX;

class WindPower
{
public:
	void Initialize(float x,float y);

	void Update();

	void Draw();

	void Collision();

	Vector3 GetPosition();

	bool IsStop() { return isMove_; }

private:
	WorldTransform worldTransform_[2];
	ViewProjection viewProjection_;

	Model* model_ = nullptr;
	Model* model2_ = nullptr;
	uint32_t texture_ = 0;
	uint32_t texture2_ = 0;

	bool isMove_ = false;

	int stopTimer_;
};
