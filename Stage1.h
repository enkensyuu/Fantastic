#pragma once
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <list>
#include "Wind.h"

class Stage1
{
public:

	void Initialize();

	void Update();

	void Draw();

	std::list<std::unique_ptr<Wind>>wind_;
	const std::list<std::unique_ptr<Wind>>& GetBullets() { return winds_; }

	void WindOn(const Matrix4& position, const Vector3& velocity);

	Vector3 GetSpeed() { return velocity; }

private:
	static const int num = 8;
	WorldTransform worldTransforms_[num];
	bool isrotation_[num];

	Vector3 rotationSpeedX = { 1.0f,0.0f,0.0f };
	Vector3 rotationSpeedY = { 0.0f,1.0f,0.0f };

	ViewProjection viewProjection_;
	DebugText* debugText_ = nullptr;
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	uint32_t texture_ = 0;

	// ’e‚Ì‘¬“x
	const float kBulletSpeed = 0.5f;

	Vector3 velocity;
	Vector3 Lvelocity;
	Vector3 Rvelocity;
	Vector3 Uvelocity;
	Vector3 Dvelocity;

	std::list<std::unique_ptr<Wind>> winds_;
};

