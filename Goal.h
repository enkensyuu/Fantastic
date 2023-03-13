#pragma once
#include "WorldTransform.h"
#include "TextureManager.h"
#include "Model.h"
#include "ViewProjection.h"

class Goal
{
public:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	const float Y_POS = -20.0f;
	const float Y_RAD = fabs(Y_POS) * 2.0f;
	bool isGoal = 0;
	void Initialize(); // ê›íËílÇÕx,zÇÃÇ›,yílÇÕå≈íË
	void Draw(ViewProjection viewProjection);
	bool IsGoal() { return isGoal; }

	void OnCollision() { isGoal = true; }
	const Vector3 GetWorldPosition() { return worldTransform_.translation_; }
	const Vector3 GetRadius() { return worldTransform_.scale_; }
};