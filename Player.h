#pragma once
#include "Audio.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include <memory>

class Player {
public:
	//������
	void Initialize(Model* model, Vector3 pos = { 0.0f, 0.0f, 0.0f });

	//�X�V
	void Update();

	//�`��
	void Draw(ViewProjection& viewProjection);

	// ���S
	void IsDead() { isDead_ = true; }

	// �����蔻��
	void OnCollisionStage(bool collisionFlag);

private:
	//�C���v�b�g
	Input* input_ = nullptr;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// �O�t���[�����W
	Vector3 prePos_{};
	// ���a
	float radius_ = 2.0f;
	//���S�t���O
	bool isDead_;
	static bool isDeads_;

public: //�A�N�Z�b�T�A�C�����C���֐�
	bool IsDead() const { return isDead_; }
	Vector3 GetPosition() const { return worldTransform_.translation_; }
	float GetRadius() const { return radius_; }

};