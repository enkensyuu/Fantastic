#include "Stage5.h"
#include <cassert>
#include "Procession.h"

void Stage5::Initialize()
{
	/*assert(model);
	model_ = model;*/
	debugText_ = DebugText::GetInstance();
	input_ = Input::GetInstance();
	texture_ = TextureManager::Load("white.png");
	model_ = Model::Create();
	audio_ = Audio::GetInstance();

	//SEデータ
	PropellerSE_ = audio_->LoadWave("SE/Wind.wav");

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
		worldTransforms_[3].translation_ = { 0.0f,-10.0f,0.0f };
		worldTransforms_[4].translation_ = { -10.0f,0.0f,0.0f };
		worldTransforms_[5].translation_ = { -10.0f,10.0f,0.0f };
		worldTransforms_[6].translation_ = { -10.0f,-10.0f,0.0f };

		// 行列更新
		worldTransforms_[i].matWorld_ = Mat_Identity();
		worldTransforms_[i].matWorld_ = MatWorld(worldTransforms_[i].scale_, worldTransforms_[i].rotation_, worldTransforms_[i].translation_);

		worldTransforms_[i].TransferMatrix();

	}

	viewProjection_.Initialize();

}

void Stage5::Update()
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

	else if (input_->TriggerKey(DIK_4))
	{
		if (!isrotation_[3])
		{
			isrotation_[3] = true;
		}
		else
		{
			isrotation_[3] = false;
		}
	}

	else if (input_->TriggerKey(DIK_5))
	{
		if (!isrotation_[4])
		{
			isrotation_[4] = true;
		}
		else
		{
			isrotation_[4] = false;
		}
	}

	else if (input_->TriggerKey(DIK_6))
	{
		if (!isrotation_[5])
		{
			isrotation_[5] = true;
		}
		else
		{
			isrotation_[5] = false;
		}
	}

	else if (input_->TriggerKey(DIK_7))
	{
		if (!isrotation_[6])
		{
			isrotation_[6] = true;
		}
		else
		{
			isrotation_[6] = false;
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

	if (isrotation_[3])
	{
		worldTransforms_[3].rotation_ += rotationSpeed;
	}

	if (isrotation_[4])
	{
		worldTransforms_[4].rotation_ += rotationSpeed;
	}

	if (isrotation_[5])
	{
		worldTransforms_[5].rotation_ += rotationSpeed;
	}

	if (isrotation_[6])
	{
		worldTransforms_[6].rotation_ += rotationSpeed;
	}

	//プロペラSE
	if (isrotation_[0] || isrotation_[1] || isrotation_[2] || isrotation_[3] || isrotation_[4] || isrotation_[5]||isrotation_[6])
	{
		if (HandleFlag5 == false)
		{
			if (isrotation_[0] || isrotation_[1] || isrotation_[2] || isrotation_[3] || isrotation_[4] || isrotation_[5]||isrotation_[6])
			{
				if (HandleFlag5 == false)
				{
					SEHandle_ = audio_->PlayWave(PropellerSE_, false);
					HandleFlag5 = true;
				}
			}
		}
	}

	if (!isrotation_[0] && !isrotation_[1] && !isrotation_[2] && !isrotation_[3] && !isrotation_[4] && !isrotation_[5]&&!isrotation_[6])
	{
		audio_->StopWave(SEHandle_);
		HandleFlag5 = false;
	}

	for (size_t i = 0; i < _countof(worldTransforms_); i++)
	{
		// 行列更新
		worldTransforms_[i].matWorld_ = Mat_Identity();
		worldTransforms_[i].matWorld_ = MatWorld(worldTransforms_[i].scale_, worldTransforms_[i].rotation_, worldTransforms_[i].translation_);

		worldTransforms_[i].TransferMatrix();
	}
}

void Stage5::Draw()
{
	for (size_t i = 0; i < _countof(worldTransforms_); i++)
	{
		model_->Draw(worldTransforms_[i], viewProjection_, texture_);
	}

	DebugText::GetInstance()->SetPos(900, 180);
	DebugText::GetInstance()->Printf("Stage5", DebugText5);
}