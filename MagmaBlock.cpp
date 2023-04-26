#include "MagmaBlock.h"
#include "Procession.h"

void MagmaBlock::Initialize(float x, float y)
{
	model_ = Model::CreateFromOBJ("MagmaBlock");

	color_ = 1;

	isCool_ = false;
	color = { color_,color_,color_,1 };

	worldTransform_.Initialize();

	worldTransform_.translation_ = { x,y,0 };

	// �s��X�V
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
	worldTransform_.TransferColorMatrix();

	viewProjection_.Initialize();
}

void MagmaBlock::Update()
{
	if (isCool_)
	{
		color_ -= 0.01f;
	}
	color = { color_,color_,color_,1 };
	worldTransform_.SetColor(color);
	// �s��X�V
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferColorMatrix();
	worldTransform_.TransferMatrix();
}

void MagmaBlock::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}

Vector3 MagmaBlock::GetPosition()
{
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void MagmaBlock::Collision()
{
	isCool_ = true;
}