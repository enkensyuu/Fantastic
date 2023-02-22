#pragma once
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Fan
{
public:

	void Initialize();

	void Update();

	void Draw();

private:
	static const int fannam = 3;

	WorldTransform worldTransforms_[fannam];

	bool isrotation_[fannam];

	ViewProjection viewProjection_;
	DebugText* debugText_ = nullptr;
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	uint32_t texture_ = 0;
};
