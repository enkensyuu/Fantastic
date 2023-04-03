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

	void Update(Vector3 speed);

	void Draw();

	Vector3 GetWorldPosition();

	void Collision();

	void StopCollision();
	void StopCollision2();

	bool GetG() { return g_; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	uint32_t texture_ = 0;

	bool isMove_ = false;
	bool isMove2_ = false;

	Vector3 playerSpeed;
	Vector3 returnSpeed;

	bool g_ = true;

	int stoptimer;
	int stoptimer2;
};


