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

	void MoveCollision();

	void DeadCollision();

	Vector3 GetWorldPosition();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Model* model_ = nullptr;

	bool isMove_ = false;
	bool isUpDown_ = true;
	bool isUp_ = true;
	bool isDown_ = false;

	int changeTime;

	Vector3 balloonSpeed;
	Vector3 UpDownSpeed;

	// �f�X�t���O
	bool isDead_ = false;

};

