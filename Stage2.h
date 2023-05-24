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
#include"Audio.h"

class Stage2
{
public:

	void Initialize();

	void Update();

	void Draw(ViewProjection& viewProjection);

	std::list<std::unique_ptr<Wind>>wind_;
	const std::list<std::unique_ptr<Wind>>& GetBullets() { return winds_; }

	void WindOn(const Matrix4& position, const Vector3& velocity);


private:
	static const int num = 5;
	WorldTransform worldTransforms_[num];

	Vector3 rotationSpeedX = { 1.0f,0.0f,0.0f };
	Vector3 rotationSpeedY = { 0.0f,1.0f,0.0f };

	//uint32_t textureHandle2_[10];

	ViewProjection viewProjection_;
	DebugText* debugText_ = nullptr;
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	Audio* audio_ = nullptr;
	uint32_t texture_ = 0;
	//Sprite* BackGroud_ = nullptr; 

	int DebugText;


	// �e�̑��x
	const float kBulletSpeed = 0.5f;

	bool isLflag;
	bool isRflag;
	bool isUflag;
	bool isDflag;

	Vector3 Lvelocity;
	Vector3 Rvelocity;
	Vector3 Uvelocity;
	Vector3 Dvelocity;

	std::list<std::unique_ptr<Wind>> winds_;
};

