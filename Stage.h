#pragma once
#include <sstream>
#include <WorldTransform.h>
#include <Model.h>
#include <MyMathUtility.h>

class Stage {
private: // �萔
	static const int STAGE_WIDTH = 20;
	static const int STAGE_HEIGHT = 20;

public:
	// ��
	enum STAGE {
		NONE,		// ��
		BLOCK,		// �n��, ��

		NONE2,
		NONE3,
	};

	// �\����
	struct StageData {
		WorldTransform worldTransform_;	// ���W
		int type_;	// �u���b�N�̎��
		int line_;
		int row_;
	};

public:
	// �f�X�g���N�^
	~Stage();

	// ������
	void Initialize(Model* model);

	// �X�e�[�W������
	void StageInitialize(const std::string stageNum);

	// �X�V
	void Update();

	// �`��
	void Draw(ViewProjection viewProjection);

	// ���W�Q�b�^�[
	Vector3 GetBlockPosition(int line, int row);

private:
	// �X�e�[�W���̓ǂݍ���
	void LoadFloorBlock();

	// �X�e�[�W�t�@�C���ǂݍ���
	void LoadStageData(const std::string stageNum);

	// �X�e�[�W�ǂݍ���
	void LoadStageCommands();

	// �u���b�N������
	void InitializeStageBlock(std::unique_ptr<StageData>& block, Vector3 pos, int line, int row);

	// ���X�g�Ƀu���b�N��ǉ�
	void PushStageBlockList(std::list<std::unique_ptr<StageData>>& blocks_, int type, int line, int row, float depth);

private:
	// ���f��
	Model* model_ = nullptr;
	Model* modelFloor_ = nullptr;
	// �e�N�X�`���n���h��
	int32_t textureHandle_ = 0u;

	// �t�@�C���R�}���h
	std::stringstream stageCommands;
	// ���[���h�ϊ��f�[�^
	std::list<std::unique_ptr<StageData>> stageBlocks_;
	std::list<std::unique_ptr<StageData>> floorBlocks_;

	// �u���b�N�̔{��(Scale)
	float magnification_ = 2.0f;
	// �u���b�N�̔��a���a
	float radius_ = 2.0f;

public: // �A�N�Z�b�T
	float GetRadius() { return radius_; }
};