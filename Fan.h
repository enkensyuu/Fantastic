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
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	DebugText* debugText_ = nullptr;
	Input* input_ = nullptr;
	Model* model_ = nullptr;
};
