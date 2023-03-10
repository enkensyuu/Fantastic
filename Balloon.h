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

class Balloon
{
public:
	void Initialize();

	void Update(Vector3 speed);

	void Draw();

	void Collision();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Model* model_ = nullptr;

	bool isMove_ = false;
	Vector3 balloonSpeed;

};

