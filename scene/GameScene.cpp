#include "GameScene.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "Procession.h"
#include <cassert>
#include <iomanip>
#include <random>
#include <sstream>

GameScene::~GameScene() {
	delete model_;
	// BGM解放
	// 自キャラの解放
	delete modelPlayer_;
	delete modelPlayer2_;
	// 天球データ解放
	delete modelSkydome_;
	// ステージ
	delete stage_;
	// スプライト
	delete title_;
	delete howtoplay_;
	delete stageClear_;
	delete gameOver_;
	delete gameClear_;
	// 背景スプライト
	delete backGround1_;
	delete backGround2_;
	delete backGround3_;
	delete backGround4_;
	delete backGround5_;
	delete backGround6_;
}
void GameScene::Initialize() {
	// インスタンス取得
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデルの生成
	model_ = Model::Create();

	// ステージ
	stage_ = new stage();
	stage_->Initialize(model_);

	// プレイヤー
	player_ = new Player;

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	viewProjection_.eye = { 40.0f, 80.0f, -125.0f};
	viewProjection_.target = { 40.0f, 40.0f, 0.0f };
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();

	//初期化
	Parameter({ 14.0f, -10.0f, 54.0f }, { 38.0f, -10.0f, 26.0f }, 0);
}

void GameScene::Update() {
	stage_->Update();
	player_->Update();
	CollisionStageFlag(player_, stage_);
	player_->OnCollisionStage(CollisionStageFlag(player_, stage_));
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	stage_->Draw(viewProjection_);
	player_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Parameter(
	const Vector3& playerPos1, const Vector3& playerPos2, const int& stageNum) {
	// 自キャラの初期化
	Vector3 pos1 = playerPos1;
	Vector3 pos2 = playerPos2;
	// ステージの初期化
	stage_->StageInitialize(filename_[stageNum]); // ステージ読み込み(1)

	isClear = false;
}

bool GameScene::CollisionStageFlag(Player* p, stage* s) {
	// 各座標変数の宣言
	Vector3 pPos = p->GetPosition();
	float pRadius = p->GetRadius();
	float pX1, pX2, pY1, pY2;
	// プレイヤーの矩形座標
	pX1 = pPos.x - pRadius;
	pX2 = pPos.x + pRadius;
	pY1 = pPos.y - pRadius;
	pY2 = pPos.y + pRadius;

	// プレイヤーLeftTop座標
	int pLT[2] = { static_cast<int>(pX1 / 4), static_cast<int>(((pY1 / 4) - 19) * -1) };
	int isFloor = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			// 足元のブロックを判別
			if (s->CheckFloorBlock(pLT[0] + i, pLT[1] + j)) {
				isFloor++;
			}
			if (isFloor == 4) {
				p->IsDead();
			}
			s->CheckBlock(pLT[0] + i, pLT[1] + j);
			// 各座標変数の宣言
			Vector3 bPos = s->GetBlockPosition(pLT[0] + i, pLT[1] + j);
			float bRadius = s->GetRadius();
			float bX1, bX2, bY1, bY2;
			// ブロックの矩形座標
			bX1 = bPos.x - bRadius;
			bX2 = bPos.x + bRadius;
			bY1 = bPos.y - bRadius;
			bY2 = bPos.y + bRadius;

			// 当たり判定
			if (pX1 < bX2 && pX2 > bX1 && pY1 < bY2 && pY2 > bY1) {
				return true;
			}
		}
	}
	return false;
}