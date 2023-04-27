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
#include "DirectXMath.h"

using namespace DirectX;

class Goal
{
public:
	void Initialize(float x,float y);

	void Draw(ViewProjection& viewProjection);

	Vector3 GetPosition();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Model* model_ = nullptr;

	uint32_t texture_ = 0;

};

