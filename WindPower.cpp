#include "WindPower.h"
#include "Procession.h"

void WindPower::Initialize()
{
	texture_ = TextureManager::Load("white.png");
	model_ = Model::Create();
	isMove_ = false;
	stopTimer_ = 4 * 5;

	worldTransform_.Initialize();

	worldTransform_.translation_ = { 10,10,0 };

	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferColorMatrix();
	worldTransform_.TransferMatrix();

	viewProjection_.Initialize();
}

void WindPower::Update()
{
	Vector3 RotationSpeed = { 0,0,0.1f };

	if (isMove_)
	{
		worldTransform_.rotation_ -= RotationSpeed;
		stopTimer_--;
	}

	if (stopTimer_<=0)
	{
		isMove_ = false;
	}

	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void WindPower::Draw()
{
	model_->Draw(worldTransform_, viewProjection_, texture_);
}

void WindPower::Collision()
{
	isMove_ = true;
	stopTimer_ = 12 * 5;
}

Vector3 WindPower::GetPosition()
{
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}
