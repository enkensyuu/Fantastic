#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class MagmaBlock
{
public:
	void Initialize(float x,float y);

	void Update();

	void Draw();

	Vector3 GetPosition();

	void Collision();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Model* model_ = nullptr;
	uint32_t texture_ = 0;
};