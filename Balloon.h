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
#include "GoldKey.h"
#include <list>

class Balloon
{
public:
	void Initialize(float x, float y);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void MoveCollision(Vector3 speed);

	void DeadCollision();

	Vector3 GetWorldPosition();

	void KeyShot();

	std::list<std::unique_ptr<GoldKey>>goldKey_;
	const std::list<std::unique_ptr<GoldKey>>& GetGoldKey() { return goldKeys_; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Model* model_ = nullptr;

	bool isMove_ = false;
	bool isUpDown_ = true;
	bool isUp_ = true;
	bool isDown_ = false;
	bool isShotStop = true;
	bool isDead_ = false;
	bool isLockShot = false;

	int changeTime;

	Vector3 balloonSpeed;
	Vector3 UpDownSpeed;

	std::list<std::unique_ptr<GoldKey>> goldKeys_;

};

