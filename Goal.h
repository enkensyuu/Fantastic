#pragma once
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <list>

class Goal
{
public:
	void Initialize();

	void Draw();

	Vector3 GetPosition();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Model* model_ = nullptr;

	uint32_t texture_ = 0;

};

