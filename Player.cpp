#include "Player.h"
#include <cassert>
#include "Procession.h"

void Player::Initialize()
{
	input_ = Input::GetInstance();

	texture_ = TextureManager::Load("yellow.png");
	model_ = Model::Create();

	worldTransform_.Initialize();

	worldTransform_.translation_ = { 0,0,55 };
	isMove_ = false;
	isMove2_ = false;

	// �s��X�V
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();

	viewProjection_.Initialize();
}

void Player::Update(Vector3 speed)
{
	playerSpeed = speed;
	returnSpeed = speed;
	returnSpeed /= 2;

	if (isMove_)
	{
		worldTransform_.translation_ += playerSpeed;
		stoptimer--;
	}
	if (stoptimer <= 0)
	{
		isMove_ = false;
		isMove2_ = true;
		stoptimer = 6 * 5;
	}

	if (isMove2_)
	{
		worldTransform_.translation_ += returnSpeed;
		stoptimer2--;
	}

	if (stoptimer2 <= 0)
	{
		isMove2_ = false;
		stoptimer2 = 8 * 5;
	}

	if (input_->TriggerKey(DIK_R))
	{
		Initialize();
	}

	// �����͐V���ɏ����������Ƃ���
	if (input_->PushKey(DIK_W))
	{
		worldTransform_.translation_ += {0, 1, 0};
	}

	if (input_->PushKey(DIK_A))
	{
		worldTransform_.translation_ += {-1, 0, 0};
	}

	if (input_->PushKey(DIK_S))
	{
		worldTransform_.translation_ += {0, -1, 0};
	}

	if (input_->PushKey(DIK_D))
	{
		worldTransform_.translation_ += {1, 0, 0};
	}

	if (input_->PushKey(DIK_U))
	{
		worldTransform_.translation_ += {0, 0, 1};
	}

	if (input_->PushKey(DIK_J))
	{
		worldTransform_.translation_ += {0, 0, -1};
	}
	// �����܂ŏ����������Ƃ���

	// �s��X�V
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
	worldTransform_.TransferColorMatrix();
}

void Player::Draw()
{
	model_->Draw(worldTransform_, viewProjection_, texture_);
}

Vector3 Player::GetWorldPosition()
{
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void Player::Collision()
{
	isMove_ = true;
}
