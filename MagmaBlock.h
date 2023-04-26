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
	void Initialize(float x, float y);

	void Update();

	void Draw(ViewProjection& viewProjection);

	Vector3 GetPosition();

	void Collision();

	bool IsGetCool() { return isCool_; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	bool isCool_ = false;

	Model* model_ = nullptr;
	uint32_t texture_ = 0;

	float color_ = 1;
	XMFLOAT4 color;
};