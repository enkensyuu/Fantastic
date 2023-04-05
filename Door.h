#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Door
{
public:
	void Initialize(float x, float y);

	void Update(bool flag);

	void Draw();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Input* input_ = nullptr;

	Model* model_ = nullptr;
	uint32_t texture_ = 0;

	float startY;


};