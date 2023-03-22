#pragma once
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"Audio.h"

class Stage2
{
public:

	void Initialize();

	void Update();

	void Draw();

	//void WindOn();

private:
	static const int num = 4;

	WorldTransform worldTransforms_[num];
	bool isrotation_[num];

	Vector3 rotationSpeed = { 0.0f,0.0f,1.0f };

	ViewProjection viewProjection_;
	DebugText* debugText_ = nullptr;
	Input* input_ = nullptr;
	Model* model_ = nullptr;
	Audio* audio_ = nullptr;
	uint32_t texture_ = 0;

	//SE
	uint32_t PropellerSE_ = 0;
	uint32_t SEHandle_ = 0;
	uint32_t HandleFlag2 = false;

	/*std::list<std::unique_ptr<Wind>> winds2_;
	const std::list<std::unique_ptr<Wind>>& GetBullets() { return winds2_; }*/
};

