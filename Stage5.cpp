#include "Stage5.h"
#include <cassert>
#include "Procession.h"
#include <DirectXMath.h>

using namespace DirectX;

void Stage5::Initialize()
{
	/*assert(model);
	model_ = model;*/
	debugText_ = DebugText::GetInstance();
	input_ = Input::GetInstance();
	texture_ = TextureManager::Load("white.png");
	model_ = Model::CreateFromOBJ("fan");
	//model_ = Model::Create();
	audio_ = Audio::GetInstance();

	//BackGroud_ = Sprite::Create(textureHandle2_[0], { 0,0 });

	Lvelocity = { -kBulletSpeed,0,0 };
	Rvelocity = { +kBulletSpeed,0,0 };
	Uvelocity = { 0,+kBulletSpeed,0 };
	Dvelocity = { 0,-kBulletSpeed,0 };

	isLflag = false;
	isRflag = false;
	isUflag = false;
	isDflag = false;

	for (size_t i = 0; i < _countof(worldTransforms_); i++)
	{
		worldTransforms_[i].Initialize();

		worldTransforms_[i].scale_ = { 2.0f,2.0f,2.0f };

		worldTransforms_[0].rotation_ = { 0,0,XMConvertToRadians(90) };
		worldTransforms_[1].rotation_ = { 0,0,XMConvertToRadians(90) };
		worldTransforms_[2].rotation_ = { 0,0,XMConvertToRadians(90) };

		worldTransforms_[0].translation_ = { 2.0f,7.0f,-20.0f };
		worldTransforms_[1].translation_ = { 38.0f,32.0f,-20.0f };
		worldTransforms_[2].translation_ = { 58.0f,55.0f,-20.0f };
		worldTransforms_[3].translation_ = { 42.0f,3.0f,-20.0f };
		worldTransforms_[4].translation_ = { 82.0f,27.0f,-20.0f };

		// 行列更新
		worldTransforms_[i].matWorld_ = Mat_Identity();
		worldTransforms_[i].matWorld_ = MatWorld(worldTransforms_[i].scale_, worldTransforms_[i].rotation_, worldTransforms_[i].translation_);

		worldTransforms_[i].TransferMatrix();
		worldTransforms_[i].TransferColorMatrix();

	}
	viewProjection_.Initialize();
}

void Stage5::Update()
{
	//SEHandle_ = audio_->PlayWave(PropellerSE_, true);
	// デスフラグの立った弾を削除
	winds_.remove_if([](std::unique_ptr<Wind>& wind)
		{
			return wind->IsDead();
		}
	);

	if (input_->TriggerKey(DIK_UP) || input_->TriggerKey(DIK_W))
	{
		if (!isUflag)
		{
			isRflag = false;
			isUflag = true;
		}

		else
		{
			isUflag = false;
		}
	}

	else if (input_->TriggerKey(DIK_RIGHT) || input_->TriggerKey(DIK_D))
	{
		if (!isRflag)
		{
			isRflag = true;
			isUflag = false;
		}

		else
		{
			isRflag = false;
		}
	}

	if (isRflag)
	{
		WindOn(worldTransforms_[0].matWorld_, Rvelocity);
		worldTransforms_[0].rotation_ += rotationSpeedX;

		WindOn(worldTransforms_[1].matWorld_, Rvelocity);
		worldTransforms_[1].rotation_ += rotationSpeedX;

	}

	if (isUflag)
	{
		WindOn(worldTransforms_[3].matWorld_, Uvelocity);
		worldTransforms_[3].rotation_ += rotationSpeedY;
		WindOn(worldTransforms_[4].matWorld_, Uvelocity);
		worldTransforms_[4].rotation_ += rotationSpeedY;
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

void Stage5::Draw(ViewProjection& viewProjection)
{
	for (size_t i = 0; i < _countof(worldTransforms_); i++)
	{
		model_->Draw(worldTransforms_[i], viewProjection);
	}

	for (std::unique_ptr<Wind>& wind : winds_)
	{
		wind->Draw(viewProjection);
	}

	/*DebugText::GetInstance()->SetPos(900, 180);
	DebugText::GetInstance()->Printf("Stage1", DebugText);*/
}

void Stage5::WindOn(const Matrix4& position, const Vector3& velocity)
{

	// 弾を生成し、初期化
	std::unique_ptr < Wind> newWind = std::make_unique<Wind>();

	newWind->Initialize(position, velocity);

	// 弾を登録する
	winds_.push_back(std::move(newWind));
}