#include "stage.h"
#include <cassert>
#include <fstream>

stage::~stage() {
	delete modelGoal_;
}

void stage::Initialize(Model* model) {
	// ���f���ǂݍ���
	model_ = model;

	// �X�e�[�W�̏���������
	LoadFloorBlock();

	worldTransform.Initialize();
	worldTransform.TransferColorMatrix();
	worldTransform.TransferMatrix();
}

void stage::StageInitialize(const std::string stageNum) {
	// �ŏ��Ɏc���Ă���v�f���폜
	stageBlocks_.clear();

	isSwitchDrawR_ = false;
	isSwitchDrawB_ = false;

	// �o�b�t�@���N���A
	stageCommands.str("");
	// ��Ԃ��N���A
	stageCommands.clear(std::stringstream::goodbit);

	// �X�e�[�W�p�t�@�C���ǂݍ���
	LoadStageData(stageNum);
	// �X�e�[�W�t�@�C���Ŋe�v�f��ݒ�
	LoadStageCommands();

	isGoal_ = false;
}

void stage::Update() {
	isGoal_ = false;
}

void stage::Draw(ViewProjection viewProjection) {
	// �X�e�[�W�`��
	for (std::unique_ptr<StageData>& block : stageBlocks_) {
		if (block->type_ == BLOCK) {
			// �Ǖ`��
			model_->Draw(block->worldTransform_, viewProjection);
		}
	}
}

void stage::LoadStageData(const std::string stageNum) {
	// �t�@�C��
	std::ifstream file;
	// �p�X���擾
	const std::string name = "stage";
	const std::string filename = name + stageNum + ".csv";
	const std::string directoryPath = "Resources/" + name + "/";
	// �t�@�C�����J��
	file.open(directoryPath + filename);
	assert(file.is_open());
	// �t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	stageCommands << file.rdbuf();

	// �t�@�C�������
	file.close();
}

void stage::LoadStageCommands() {
	// 1�s���̕����������ϐ�
	std::string line;
	// �}�b�v�`�b�v�p�ϐ�
	int mapLine = 0;	// X
	int mapRow = 0;	// Y

	// �R�}���h���s���[�v
	while (getline(stageCommands, line)) {
		// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);
		// ������
		std::string word;
		// ,��؂�ōs�̐擪��������擾
		getline(line_stream, word, ',');

		// "//"����n�܂�s�̓R�����g
		if (word.find("//") == 0) {
			// �R�����g�s��ǂݔ�΂�
			continue;
		}

		while (mapLine != STAGE_WIDTH) {
			// �R�}���h�ǂݍ���
			if (word.find("NONE") == 0 || word.find("0") == 0) {
				// �X�e�[�W�̃u���b�N��ǉ�
				PushStageBlockList(stageBlocks_, NONE, mapLine, mapRow, -20.0f);
				// �C���N�������g
				mapLine++;
			}
			else if (word.find("BLOCK") == 0 || word.find("1") == 0) {
				// �X�e�[�W�̃u���b�N��ǉ�
				PushStageBlockList(stageBlocks_, BLOCK, mapLine, mapRow, -20.0f);
				// �C���N�������g
				mapLine++;
			}
			// ���̓��e��
			getline(line_stream, word, ',');
		}
		// �}�b�v�`�b�vLine��20�𒴂����烊�Z�b�g����Row���C���N�������g
		if (mapLine == STAGE_WIDTH) {
			mapLine = 0;
			mapRow++;
		}
	}
}

void stage::LoadFloorBlock() {
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			// �X�e�[�W�̃u���b�N��ǉ�
			PushStageBlockList(floorBlocks_, BLOCK, j, i, -20.0f);
		}
	}
}

void stage::InitializeStageBlock(std::unique_ptr<StageData>& block, Vector3 pos, int line, int row) {
	// ���[���h�g�����X�t�H�[���̏������ݒ�
	block->worldTransform_.Initialize();

	// �X�P�[���ݒ�
	block->worldTransform_.scale_ = { magnification_, magnification_, magnification_ };
	// ���W�ݒ�
	block->worldTransform_.translation_ = pos;

	// �s��X�V
	block->worldTransform_.matWorld_ = MyMathUtility::MySetMatrix4Identity();
	block->worldTransform_.matWorld_ *= MyMathUtility::MySynMatrix4WorldTransform(block->worldTransform_);
	block->worldTransform_.TransferMatrix();

	block->line_ = line;
	block->row_ = row;
}

void stage::PushStageBlockList(std::list<std::unique_ptr<StageData>>& blocks_, int type, int line, int row, float depth) {
	// ���X�g�ɓ���邽�߂ɐV�����錾
	std::unique_ptr<StageData> newBlock = std::make_unique<StageData>();
	// �u���b�N�̎��
	newBlock->type_ = type;
	// ���W
	Vector3 pos;
	pos.x = 2.0f + (4.0f * line);
	pos.y = 70.0f - (4.0f * row);
	pos.z = depth;

	// ����������
	InitializeStageBlock(newBlock, pos, line, row);
	// ���X�g�ɒǉ�
	blocks_.push_back(std::move(newBlock));
}

void stage::CheckBlock(int line, int row) {
	// �͈�for
	for (std::unique_ptr<StageData>& block : stageBlocks_) {
		if (block->type_ == GOAL) {
			// �w�肵���ԍ��ɍ��������W��Ԃ�
			if (block->line_ == line && block->row_ == row) {
				isGoal_ = true;
			}
		}
	}
}

bool stage::CheckFloorBlock(int line, int row) {
	if (line < 0 || line > 31 || row < 0 || row > 18) {
		return true;
	}
	return false;
}

Vector3 stage::GetBlockPosition(int line, int row) {
	// �͈�for
	for (std::unique_ptr<StageData>& block : stageBlocks_) {
		// �u���b�N�ƕǂ̎��͕Ԃ�
		if (block->type_ == BLOCK) {
			// �w�肵���ԍ��ɍ��������W��Ԃ�
			if (block->line_ == line && block->row_ == row) {
				return block->worldTransform_.translation_;
			}
		}
	}
	// �Ȃ�������0��Ԃ�
	return Vector3(0, 0, 0);
}