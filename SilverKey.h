#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DirectXMath.h>

using namespace DirectX;

class SilverKey
{
public:
	void Initialize(float x, float y);

	void Update();

	void Draw(ViewProjection& viewProjection);

	Vector3 GetWorldPosition();
	
	void MoveCollision(Vector3 speed);

	void GetCollision();
	void OnCollisionStage(bool collisionFlag);

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Model* model_ = nullptr;
	Vector3 Speed;

	// 前フレーム座標
	Vector3 prePos_{};
	bool stopG_;
	bool isMove_ = false;;
	bool isGet_ = false;

	int stopTimer = 6 * 5;
};

