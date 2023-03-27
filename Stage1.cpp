#include "Stage1.h"
#include <cassert>
#include "Procession.h"
#include <DirectXMath.h>

using namespace DirectX;

void Stage1::Initialize()
{
	/*assert(model);
	model_ = model;*/
	debugText_ = DebugText::GetInstance();
	input_ = Input::GetInstance();
	texture_ = TextureManager::Load("white.png");
	model_ = Model::Create();

	for (size_t i = 0; i < _countof(isrotation_); i++)
	{
		isrotation_[i] = false;
	}

	for (size_t i = 0; i < _countof(worldTransforms_); i++)
	{
		worldTransforms_[i].Initialize();

		worldTransforms_[i].rotation_ = { 0,XMConvertToRadians(90),0 };

		worldTransforms_[0].translation_ = { 0.0f,10.0f,0.0f };
		worldTransforms_[1].translation_ = { 10.0f,0.0f,0.0f };
		worldTransforms_[2].translation_ = { 0.0f,0.0f,0.0f };

		// 行列更新
		worldTransforms_[i].matWorld_ = Mat_Identity();
		worldTransforms_[i].matWorld_ = MatWorld(worldTransforms_[i].scale_, worldTransforms_[i].rotation_, worldTransforms_[i].translation_);

		worldTransforms_[i].TransferMatrix();
		worldTransforms_[i].TransferColorMatrix();

	}

	viewProjection_.Initialize();
}

void Stage1::Update()
{
	// デスフラグの立った弾を削除
	winds_.remove_if([](std::unique_ptr<Wind>& wind)
		{
			return wind->IsDead();
		}
	);

	if (input_->TriggerKey(DIK_1))
	{
		if (!isrotation_[0])
		{
			isrotation_[0] = true;
			isrotation_[1] = false;
			isrotation_[2] = false;
		}
		else
		{
			isrotation_[0] = false;
		}
	}

	else if (input_->TriggerKey(DIK_2))
	{
		if (!isrotation_[1])
		{
			isrotation_[1] = true;
			isrotation_[0] = false;
			isrotation_[2] = false;
		}
		else
		{
			isrotation_[1] = false;
		}
	}

	else if (input_->TriggerKey(DIK_3))
	{
		if (!isrotation_[2])
		{
			isrotation_[2] = true;
			isrotation_[0] = false;
			isrotation_[1] = false;
		}
		else
		{
			isrotation_[2] = false;
		}
	}

	if (isrotation_[0])
	{
		WindOn();
		worldTransforms_[0].rotation_ += rotationSpeed;
	}

	if (isrotation_[1])
	{
		WindOn();
		worldTransforms_[1].rotation_ += rotationSpeed;
	}

	if (isrotation_[2])
	{
		WindOn();
		worldTransforms_[2].rotation_ += rotationSpeed;
	}

	for (size_t i = 0; i < _countof(worldTransforms_); i++)
	{
		// 行列更新
		worldTransforms_[i].matWorld_ = Mat_Identity();
		worldTransforms_[i].matWorld_ = MatWorld(worldTransforms_[i].scale_, worldTransforms_[i].rotation_, worldTransforms_[i].translation_);

		worldTransforms_[i].TransferMatrix();
	}

	for (std::unique_ptr<Wind>& wind : winds_)
	{
		wind->Update();
	}
}

void Stage1::Draw()
{
	for (size_t i = 0; i < _countof(worldTransforms_); i++)
	{
		model_->Draw(worldTransforms_[i], viewProjection_, texture_);
	}

	for (std::unique_ptr<Wind>& wind : winds_)
	{
		wind->Draw(viewProjection_);
	}
}

void Stage1::WindOn()
{
	// 弾の速度
	const float kBulletSpeed = 0.5f;
	velocity = { 0,+kBulletSpeed, 0 };

	// 弾を生成し、初期化
	std::unique_ptr < Wind> newWind = std::make_unique<Wind>();

	for (size_t i = 0; i < _countof(worldTransforms_); i++)
	{
		if (isrotation_[i])
		{
			newWind->Initialize(worldTransforms_[i].matWorld_, velocity);
		}

	}

	// 弾を登録する
	winds_.push_back(std::move(newWind));
}
