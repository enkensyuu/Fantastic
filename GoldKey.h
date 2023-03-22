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

class GoldKey
{
public:
	void Initialize(const Matrix4& position);

	void Update(Vector3 speed);

	void Draw(const ViewProjection& viewProjection);

	Vector3 GetWorldPosition();

	void MoveCollision();

	void GetCollision();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Model* model_ = nullptr;
	Vector3 velocity_;

	bool isMove_ = false;
	bool isGet_ = false;

	int stopTimer = 12 * 5;
};

