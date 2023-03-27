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

class WindPower
{
public:
	void Initialize();

	void Update();

	void Draw();

	void Collision();

	Vector3 GetPosition();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Model* model_ = nullptr;
	uint32_t texture_ = 0;

	bool isMove_ = false;

	int stopTimer_;
};
