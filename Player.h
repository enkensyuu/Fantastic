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

	int stoptimer;
	int stoptimer2;

	// 半径
	float radius_ = 1.5f;

	//死亡フラグ
	bool isDead_;

public: //アクセッサ、インライン関数
	bool IsDead() const { return isDead_; }
	Vector3 GetPosition() const { return worldTransform_.translation_; }
	float GetRadius() const { return radius_; }
};