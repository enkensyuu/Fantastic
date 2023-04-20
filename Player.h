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

	Vector3 GetWorldPosition();

	void Collision(Vector3 speed);

	void DethCollision();

	void GetStop();

	bool IsGetDead() { return isDead_; }


private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	uint32_t texture_ = 0;

	bool isMove_ = false;
	bool isMove2_ = false;
	bool isDead_ = false;

	Vector3 playerSpeed;
	Vector3 returnSpeed;
	Vector3 acc;

	int stoptimer;
	int stoptimer2;
};


