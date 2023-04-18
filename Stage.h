#pragma once
#include <sstream>
#include "Model.h"
#include "MyMathUtility.h"

class stage {
private: // �萔
	static const int STAGE_WIDTH = 32;
	static const int STAGE_HEIGHT = 18;

public:
	// ��
	enum STAGE {
		NONE,		// ��
		BLOCK,		// �n��, ��
		GOAL,		// �S�[��
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
	~stage();

	// ������
	void Initialize(Model* model);

	// �X�e�[�W������
	void StageInitialize(const std::string stageNum);

	// �X�V
	void Update();

	// �`��
	void Draw(ViewProjection viewProjection);

	// �����̃u���b�N�𔻕ʂ���
	void CheckBlock(int line, int row);

	// ������͂ݏo���Ă��邩
	bool CheckFloorBlock(int line, int row);

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

	WorldTransform worldTransform;

	// ���f��
	Model* model_ = nullptr;
	Model* modelFloor_ = nullptr;
	Model* modelGoal_ = nullptr;
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
	// �S�[���t���O
	bool isGoal_ = false;
	bool isSwitchDrawR_ = false;
	bool isSwitchDrawB_ = false;

public: // �A�N�Z�b�T
	float GetRadius() { return radius_; }
	bool GetIsGoal() { return isGoal_; }
};