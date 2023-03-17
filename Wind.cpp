#include "Wind.h"
#include <cassert>
#include"Procession.h"

void Wind::Initialize(const Matrix4& position, const Vector3& velocity)
{
	//// NULL�|�C���^�`�F�b�N
	//assert(model);

	//model_ = model;

	debugText_ = DebugText::GetInstance();

	// �����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
	/*texture_ = TextureManager::Load("Red.png");
	model_ = Model::Create();*/
	model_ = Model::CreateFromOBJ("Wind");

	worldTransform_.Initialize();

	// �����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_.x = position.m[3][0];
	worldTransform_.translation_.y = position.m[3][1];
	worldTransform_.translation_.z = position.m[3][2];

	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();

}

void Wind::Update()
{
	// ���W���ړ�������(1�t���[�����̈ړ��ʂ𑫂�����)
	worldTransform_.translation_ += velocity_;

	// ���Ԍo�߂Ńf�X
	if (--deathTimer_ <= 0)
	{
		isDead_ = true;
	}
	worldTransform_.SetColor(color);

	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
	worldTransform_.TransferColorMatrix();
}

void Wind::Draw(const ViewProjection& viewProjection)
{
	// ���f���̕`��
	model_->Draw(worldTransform_, viewProjection);
}

Vector3 Wind::GetWorldPosition()
{
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void Wind::Collision()
{
	isDead_ = true;
}
