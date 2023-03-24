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

	void Update(Vector3 speed);

	void Draw();

	Vector3 GetWorldPosition();
	
	void MoveCollision();

	void GetCollision();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Model* model_ = nullptr;

	bool isMove_ = false;;
	bool isGet_ = false;

	int stopTimer = 6 * 5;
};

