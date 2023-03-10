#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "Procession.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
}

void GameScene::CheckAllCollisions()
{
	Vector3 posA, posB;

	const std::list<std::unique_ptr<Wind>>& wind_ = stage1_->GetBullets();

#pragma region Player&Wind
	posA = player_->GetWorldPosition();

	for (const std::unique_ptr<Wind>& wind : wind_) {
		posB = wind->GetWorldPosition();

		if (
			(posA.x - posB.x) * (posA.x - posB.x) +
			(posA.y - posB.y) * (posA.y - posB.y) +
			(posA.z - posB.z) * (posA.z - posB.z)
			<= (1.0f + 1.0f) * (1.0f + 1.0f)
			) {
			player_->Collision();
			wind->Collision();
		}
	}
#pragma endregion

#pragma region Balloon&Wind
	posA = balloon_->GetWorldPosition();

	for (const std::unique_ptr<Wind>& wind : wind_) {
		posB = wind->GetWorldPosition();

		if (
			(posA.x - posB.x) * (posA.x - posB.x) +
			(posA.y - posB.y) * (posA.y - posB.y) +
			(posA.z - posB.z) * (posA.z - posB.z)
			<= (1.0f + 1.0f) * (1.0f + 1.0f)
			) {
			balloon_->MoveCollision();
			wind->Collision();
		}
	}
#pragma endregion

#pragma region Balloon&Wind

	posA = player_->GetWorldPosition();

	posB = balloon_->GetWorldPosition();

	if (
		(posA.x - posB.x) * (posA.x - posB.x) +
		(posA.y - posB.y) * (posA.y - posB.y) +
		(posA.z - posB.z) * (posA.z - posB.z)
		<= (1.0f + 1.0f) * (1.0f + 1.0f)
		) {
		balloon_->DeadCollision();
	}
#pragma endregion

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	stage1_ = new Stage1;
	stage1_->Initialize();

	stage2_ = new Stage2;
	stage2_->Initialize();

	stage3_ = new Stage3;
	stage3_->Initialize();

	stage4_ = new Stage4;
	stage4_->Initialize();

	stage5_ = new Stage5;
	stage5_->Initialize();

	player_ = new Player;
	player_->Initialize();

	balloon_ = new Balloon;
	balloon_->Initialize();

	scene_ = TITLE;
}

void GameScene::Update() {
	switch (scene_)
	{
	case TITLE:
		Initialize();
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene_ = THREE;
		}
		break;
	case THREE:
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene_ = FOUR;
		}
		CheckAllCollisions();
		stage1_->Update();
		player_->Update(stage1_->GetSpeed());
		balloon_->Update(stage1_->GetSpeed());
		break;
	case FOUR:
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene_ = FIVE;
		}
		stage2_->Update();
		break;
	case FIVE:
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene_ = SIX;
		}
		stage3_->Update();
		break;
	case SIX:
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene_ = SEVEN;
		}
		stage4_->Update();
		break;
	case SEVEN:
		stage5_->Update();
	}

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
	switch (scene_)
	{
	case TITLE:
		break;
	case THREE:
		stage1_->Draw();
		player_->Draw();
		balloon_->Draw();
		break;
	case FOUR:
		stage2_->Draw();
		break;
	case FIVE:
		stage3_->Draw();
		break;
	case SIX:
		stage4_->Draw();
		break;
	case SEVEN:
		stage5_->Draw();
		break;
	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

