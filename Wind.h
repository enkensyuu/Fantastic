#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include"ViewProjection.h"
#include "DebugText.h"

///	<summary>
///	���L�����̒e
/// </summary>
class Wind
{
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="position">�������W</param>
	void Initialize(const Matrix4& position, const Vector3& velocity);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection">�r���[�v���W�F�N�V����</param>
	void Draw(const ViewProjection& viewProjection);

	Vector3 GetWorldPosition();

	bool IsDead() const { return isDead_; }

	void Collision();

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	// ���f��
	Model* model_ = nullptr;
	DebugText* debugText_ = nullptr;

	// �e�N�X�`���n���h��
	uint32_t texture_ = 0u;

	// ���x
	Vector3 velocity_;

	// ����<frm>
	static const int32_t kLifeTime = 4 * 5;

	// �f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	// �f�X�t���O
	bool isDead_ = false;

	XMFLOAT4 color = { 1,1,1,0.5f };
};