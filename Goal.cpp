#include "Goal.h"
#include "Procession.h"

void Goal::Initialize()
{
	model_ = Model::Create();
	texture_ = TextureManager::Load("red.png");

		worldTransform_.Initialize();

		worldTransform_.translation_ = { -27,-13,0 };


		// �s��X�V
		worldTransform_.matWorld_ = Mat_Identity();
		worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

		worldTransform_.TransferMatrix();
		worldTransform_.TransferColorMatrix();

	viewProjection_.Initialize();
}

void Goal::Draw()
{
	model_->Draw(worldTransform_, viewProjection_, texture_);
}

Vector3 Goal::GetPosition()
{
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}