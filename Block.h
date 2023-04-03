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

class Block
{
public:
	void Initialize();

	void Draw();

	Vector3 GetPosition();

private:
	WorldTransform worldTransform_[28];
	ViewProjection viewProjection_;

	Model* model_ = nullptr;

	uint32_t texture_ = 0;

};
