#include "Stage2.h"
#include <cassert>
#include "Procession.h"
#include <DirectXMath.h>

using namespace DirectX;

void Stage2::Initialize()
{
	/*assert(model);
	model_ = model;*/
	debugText_ = DebugText::GetInstance();
	input_ = Input::GetInstance();
	texture_ = TextureManager::Load("white.png");
	model_ = Model::Create();

	Lvelocity = { -kBulletSpeed,0,0 };
	Rvelocity = { +kBulletSpeed,0,0 };
	Uvelocity = { 0,+kBulletSpeed,0 };
	Dvelocity = { 0,-kBulletSpeed,0 };

	for (size_t i = 0; i < _countof(isrotation_); i++)
	{
		isrotation_[i] = false;
	}

	for (size_t i = 0; i < _countof(worldTransforms_); i++)
	{
		worldTransforms_[i].Initialize();

		worldTransforms_[0].rotation_ = { XMConvertToRadians(90),0,0 };
		worldTransforms_[1].rotation_ = { XMConvertToRadians(90),0,0 };
		worldTransforms_[2].rotation_ = { 0,XMConvertToRadians(90),0 };
		worldTransforms_[3].rotation_ = { 0,XMConvertToRadians(90),0 };
		worldTransforms_[4].rotation_ = { 0,XMConvertToRadians(270),0 };
		worldTransforms_[5].rotation_ = { 0,XMConvertToRadians(270),0 };
		worldTransforms_[6].rotation_ = { XMConvertToRadians(270),0,0 };
		worldTransforms_[7].rotation_ = { XMConvertToRadians(270),0,0 };

		worldTransforms_[0].translation_ = { -5.0f,-10.0f,0.0f };
		worldTransforms_[1].translation_ = { -25.0f,-15.0f,0.0f };
		worldTransforms_[2].translation_ = { -5.0f,-7.0f,0.0f };
		worldTransforms_[3].translation_ = { -10.0f,0.0f,0.0f };
		worldTransforms_[4].translation_ = { 15.0f,0.0f,0.0f };
		worldTransforms_[5].translation_ = { -15.0f,-7.0f,0.0f };
		worldTransforms_[6].translation_ = { 0.0f,-7.0f,0.0f };
		worldTransforms_[7].translation_ = { -5.0f,7.0f,0.0f };

		// 行列更新
		worldTransforms_[i].matWorld_ = Mat_Identity();
		worldTransforms_[i].matWorld_ = MatWorld(worldTransforms_[i].scale_, worldTransforms_[i].rotation_, worldTransforms_[i].translation_);

		worldTransforms_[i].TransferMatrix();
		worldTransforms_[i].TransferColorMatrix();

	}
	viewProjection_.Initialize();
}

void Stage2::Update()
{
	// デスフラグの立った弾を削除
	winds_.remove_if([](std::unique_ptr<Wind>& wind)
		{
			return wind->IsDead();
		}
	);

	if (input_->TriggerKey(DIK_UP))
	{
		if (!isrotation_[0] && !isrotation_[1])
		{
			isrotation_[0] = true;
			isrotation_[1] = true;
			isrotation_[2] = false;
			isrotation_[3] = false;
			isrotation_[4] = false;
			isrotation_[5] = false;
			isrotation_[6] = false;
			isrotation_[7] = false;
			velocity = Uvelocity;
		}
		else
		{
			isrotation_[0] = false;
			isrotation_[1] = false;
		}
	}

	else if (input_->TriggerKey(DIK_RIGHT))
	{
		if (!isrotation_[2] && !isrotation_[3])
		{
			isrotation_[0] = false;
			isrotation_[1] = false;
			isrotation_[2] = true;
			isrotation_[3] = true;
			isrotation_[4] = false;
			isrotation_[5] = false;
			isrotation_[6] = false;
			isrotation_[7] = false;
			velocity = Rvelocity;
		}
		else
		{
			isrotation_[2] = false;
			isrotation_[3] = false;
		}
	}

	else if (input_->TriggerKey(DIK_LEFT))
	{
		if (!isrotation_[4] && !isrotation_[5])
		{
			isrotation_[0] = false;
			isrotation_[1] = false;
			isrotation_[2] = false;
			isrotation_[3] = false;
			isrotation_[4] = true;
			isrotation_[5] = true;
			isrotation_[6] = false;
			isrotation_[7] = false;
			velocity = Lvelocity;
		}
		else
		{
			isrotation_[4] = false;
			isrotation_[5] = false;
		}
	}

	else if (input_->TriggerKey(DIK_DOWN))
	{
		if (!isrotation_[6] && !isrotation_[7])
		{
			isrotation_[0] = false;
			isrotation_[1] = false;
			isrotation_[2] = false;
			isrotation_[3] = false;
			isrotation_[4] = false;
			isrotation_[5] = false;
			isrotation_[6] = true;
			isrotation_[7] = true;
			velocity = Dvelocity;
		}
		else
		{
			isrotation_[6] = false;
			isrotation_[7] = false;
		}
	}

	if (isrotation_[0])
	{
		WindOn(worldTransforms_[0].matWorld_, Uvelocity);
		worldTransforms_[0].rotation_ += rotationSpeed;
	}

	if (isrotation_[1])
	{
		WindOn(worldTransforms_[1].matWorld_, Uvelocity);
		worldTransforms_[1].rotation_ += rotationSpeed;
	}

	if (isrotation_[2])
	{
		WindOn(worldTransforms_[2].matWorld_, Rvelocity);
		worldTransforms_[2].rotation_ += rotationSpeed;
	}

	if (isrotation_[3])
	{
		WindOn(worldTransforms_[3].matWorld_, Rvelocity);
		worldTransforms_[3].rotation_ += rotationSpeed;
	}

	if (isrotation_[4])
	{
		WindOn(worldTransforms_[4].matWorld_, Lvelocity);
		worldTransforms_[4].rotation_ += rotationSpeed;
	}

	if (isrotation_[5])
	{
		WindOn(worldTransforms_[5].matWorld_, Lvelocity);
		worldTransforms_[5].rotation_ += rotationSpeed;
	}

	if (isrotation_[6])
	{
		WindOn(worldTransforms_[6].matWorld_, Dvelocity);
		worldTransforms_[6].rotation_ += rotationSpeed;
	}

	if (isrotation_[7])
	{
		WindOn(worldTransforms_[7].matWorld_, Dvelocity);
		worldTransforms_[7].rotation_ += rotationSpeed;
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

void Stage2::Draw(ViewProjection& viewProjection)
{
	for (size_t i = 0; i < _countof(worldTransforms_); i++)
	{
		model_->Draw(worldTransforms_[i], viewProjection, texture_);
	}

	for (std::unique_ptr<Wind>& wind : winds_)
	{
		wind->Draw(viewProjection);
	}
}

void Stage2::WindOn(const Matrix4& position, const Vector3& velocity)
{

	// 弾を生成し、初期化
	std::unique_ptr < Wind> newWind = std::make_unique<Wind>();

	newWind->Initialize(position, velocity);

	// 弾を登録する
	winds_.push_back(std::move(newWind));
}