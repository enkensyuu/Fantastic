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

class Player
{
public:
	void Initialize();

	void Update();

	void Draw();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Model* model_ = nullptr;
	uint32_t texture_ = 0;

};

