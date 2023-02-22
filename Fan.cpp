#include "Fan.h"
#include <cassert>
#include "Procession.h"
#include <DirectXMath.h>

void Fan::Initialize()
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

		worldTransforms_[0].translation_ = { 0.0f,10.0f,0.0f };
		worldTransforms_[1].translation_ = { 10.0f,0.0f,0.0f };
		worldTransforms_[2].translation_ = { 0.0f,0.0f,10.0f };

		// 行列更新
		worldTransforms_[i].matWorld_ = Mat_Identity();
		worldTransforms_[i].matWorld_ = MatWorld(worldTransforms_[i].scale_, worldTransforms_[i].rotation_, worldTransforms_[i].translation_);

		worldTransforms_[i].TransferMatrix();

	}

	viewProjection_.Initialize();
}

void Fan::Update()
{
	Vector3 rotationSpeed = { 0.0f,0.0f,0.05f };
	for (size_t i = 0; i < _countof(worldTransforms_); i++)
	{
		for (size_t i = 0; i < _countof(isrotation_); i++)
		{

			if (input_->TriggerKey(DIK_1))
			{
				if (!isrotation_[0])
				{
					isrotation_[0] = true;
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
				}
				else
				{
					isrotation_[2] = false;
				}
			}

			if (isrotation_[0])
			{
				worldTransforms_[0].rotation_ += rotationSpeed;
			}

			if (isrotation_[1])
			{
				worldTransforms_[1].rotation_ += rotationSpeed;
			}

			if (isrotation_[2])
			{
				worldTransforms_[2].rotation_ += rotationSpeed;
			}
			// 行列更新
			worldTransforms_[i].matWorld_ = Mat_Identity();
			worldTransforms_[i].matWorld_ = MatWorld(worldTransforms_[i].scale_, worldTransforms_[i].rotation_, worldTransforms_[i].translation_);

			worldTransforms_[i].TransferMatrix();
		}
	}
}
void Fan::Draw()
{
	for (size_t i = 0; i < _countof(worldTransforms_); i++)
	{
		model_->Draw(worldTransforms_[i], viewProjection_, texture_);
	}
}
