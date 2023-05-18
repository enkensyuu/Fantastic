#include "GameScene.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "Procession.h"
#include <cassert>
#include <iomanip>
#include <random>
#include <sstream>

GameScene::GameScene() {}

void GameScene::CheckAllCollisions()
{
	Vector3 posA, posB;

	const std::list<std::unique_ptr<Wind>>& wind_ = stage1_->GetBullets();
	const std::list<std::unique_ptr<GoldKey>>& goldKey_ = balloon_->GetGoldKey();

#pragma region Player&Wind
	posA = player_->GetWorldPosition();

	for (const std::unique_ptr<Wind>& wind : wind_) {
		posB = wind->GetWorldPosition();

		if (
			(posA.x - posB.x) * (posA.x - posB.x) +
			(posA.y - posB.y) * (posA.y - posB.y) +
			(posA.z - posB.z) * (posA.z - posB.z)
			<= (2.0f + 1.0f) * (1.0f + 1.0f)
			) {
			player_->Collision(wind->GetVelocity());
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
			balloon_->MoveCollision(wind->GetVelocity());
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

#pragma region GoldKey&Wind
	for (const std::unique_ptr<Wind>& wind : wind_) {
		for (const std::unique_ptr<GoldKey>& goldKey : goldKey_) {

			posA = wind->GetWorldPosition();
			posB = goldKey->GetWorldPosition();

			if (
				(posA.x - posB.x) * (posA.x - posB.x) +
				(posA.y - posB.y) * (posA.y - posB.y) +
				(posA.z - posB.z) * (posA.z - posB.z)
				<= (1.0f + 1.0f) * (1.0f + 1.0f)
				) {
				goldKey->MoveCollision(wind->GetVelocity());
			}
		}
	}
#pragma endregion

#pragma region Player&GoldKey

	posA = player_->GetWorldPosition();

	for (const std::unique_ptr<GoldKey>& goldKey : goldKey_) {

		posB = goldKey->GetWorldPosition();

		if (
			(posA.x - posB.x) * (posA.x - posB.x) +
			(posA.y - posB.y) * (posA.y - posB.y) +
			(posA.z - posB.z) * (posA.z - posB.z)
			<= (1.0f + 0.5f) * (1.0f + 1.0f)
			) {
			goldKey->GetCollision();
			isGetKey_ = true;
			isKeyOpen_ = true;
		}
	}
#pragma endregion

#pragma region SilverKey&Wind
	for (const std::unique_ptr<Wind>& wind : wind_) {

		posA = wind->GetWorldPosition();
		posB = silverKey_->GetWorldPosition();

		if (
			(posA.x - posB.x) * (posA.x - posB.x) +
			(posA.y - posB.y) * (posA.y - posB.y) +
			(posA.z - posB.z) * (posA.z - posB.z)
			<= (2.0f + 1.0f) * (1.0f + 1.0f)
			) {
			silverKey_->MoveCollision(wind->GetVelocity());
		}
	}
#pragma endregion

#pragma region Player&SilverKey

	posA = player_->GetWorldPosition();
	posB = silverKey_->GetWorldPosition();

	if (
		(posA.x - posB.x) * (posA.x - posB.x) +
		(posA.y - posB.y) * (posA.y - posB.y) +
		(posA.z - posB.z) * (posA.z - posB.z)
		<= (2.0f + 1.0f) * (1.0f + 1.0f)
		) {
		silverKey_->GetCollision();
		isGetKey_ = true;
		isKeyOpen_ = true;
	}
#pragma endregion

#pragma region WindPower&Wind
	posA = windPower_->GetPosition();

	for (const std::unique_ptr<Wind>& wind : wind_) {
		posB = wind->GetWorldPosition();

		if (
			(posA.x - posB.x) * (posA.x - posB.x) +
			(posA.y - posB.y) * (posA.y - posB.y) +
			(posA.z - posB.z) * (posA.z - posB.z)
			<= (1.0f + 1.0f) * (1.0f + 1.0f)
			) {
			windPower_->Collision();
			wind->Collision();
			isOpen_ = true;
		}
	}

	if (!windPower_->IsStop())
	{
		isOpen_ = false;
	}
#pragma endregion

#pragma region Magma&Wind
	posA = magmaBlock_->GetPosition();

	for (const std::unique_ptr<Wind>& wind : wind_) {
		posB = wind->GetWorldPosition();

		if (
			(posA.x - posB.x) * (posA.x - posB.x) +
			(posA.y - posB.y) * (posA.y - posB.y) +
			(posA.z - posB.z) * (posA.z - posB.z)
			<= (1.0f + 1.0f) * (1.0f + 1.0f)
			) {
			magmaBlock_->Collision();
			wind->Collision();
		}
	}
#pragma endregion

#pragma region Player&MagmaBlock

	posA = player_->GetWorldPosition();
	posB = magmaBlock_->GetPosition();

	if (
		(posA.x - posB.x) * (posA.x - posB.x) +
		(posA.y - posB.y) * (posA.y - posB.y) +
		(posA.z - posB.z) * (posA.z - posB.z)
		<= (1.0f + 1.0f) * (1.0f + 1.0f)
		) {
		if (!magmaBlock_->IsGetCool())
		{
			player_->DethCollision();
		}
	}

#pragma endregion

#pragma region Player&Door
	posA = player_->GetWorldPosition();
	posB = door_->GetPosition();

	if (posA.x - 2 < posB.x + 1.5f && posA.x + 2 > posB.x - 1.5f)
	{
		if (posA.y - 1 < posB.y + 1.5f && posA.y + 1 > posB.y - 1.5f)
		{
			player_->GetStop();
		}
	}
#pragma endregion

#pragma region Wind&Door

	posA = door_->GetPosition();

	for (const std::unique_ptr<Wind>& wind : wind_) {
		posB = wind->GetWorldPosition();

		if (posA.x - 2 < posB.x + 1.5f && posA.x + 2 > posB.x - 1.5f)
		{
			if (posA.y - 1 < posB.y + 1.5f && posA.y + 1 > posB.y - 1.5f)
			{
				wind->Collision();
			}
		}
	}

#pragma endregion

#pragma region Player&Goal

	posA = player_->GetWorldPosition();

	posB = goal_->GetPosition();

	if (
		(posA.x - posB.x) * (posA.x - posB.x) +
		(posA.y - posB.y) * (posA.y - posB.y) +
		(posA.z - posB.z) * (posA.z - posB.z)
		<= (1.0f + 1.0f) * (1.0f + 1.0f)
		) {
		isGoal_ = true;
	}
#pragma endregion

}

GameScene::~GameScene() {
	delete model_;
	// BGM解放
	// 自キャラの解放
	delete player_;
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
}

void GameScene::Initialize() {
	// インスタンス取得
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	isGetKey_ = false;
	isOpen_ = false;
	isKeyOpen_ = false;

	gameOverTexture_ = TextureManager::Load("Game_Over.png");
	gameClearTexture_ = TextureManager::Load("GameClear.png");
	backGroundStage1 = TextureManager::Load("Stage1.png");

	gameOver_ = Sprite::Create(gameOverTexture_, { 0,0 });
	gameClear_ = Sprite::Create(gameClearTexture_, { 0,0 });
	backGround1_ = Sprite::Create(backGroundStage1, { 0,0 });

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

	balloon_ = new Balloon;
	balloon_->Initialize(-5, 10);

	silverKey_ = new SilverKey;
	silverKey_->Initialize(65, 60);

	windPower_ = new WindPower;
	windPower_->Initialize(-5, -5);

	magmaBlock_ = new MagmaBlock;
	magmaBlock_->Initialize(0, -10);

	door_ = new Door;
	door_->Initialize(110, 55);

	goal_ = new Goal;
	goal_->Initialize(114, 7);

	scene_ = TITLE;

	// 3Dモデルの生成
	model_ = Model::Create();

	// ステージ
	stage_ = new stage();
	stage_->Initialize(model_);

	// ステージフラグ
	stageFlag = 0;

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	viewProjection_.eye = { 74.0f, 35.0f, -125.0f };
	viewProjection_.target = { 74.0f,35.0f, 0.0f };
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
}

void GameScene::Update() {
	switch (scene_)
	{
		case TITLE:

			Initialize();
			isGoal_ = false;

			debugText_->SetPos(50, 50);
			debugText_->Printf("PUSH_SPACE");

			if (input_->TriggerKey(DIK_SPACE))
			{
				Parameter({ 10.0f,7.0f,-20.0f }, stageFlag);
				scene_ = ONE;
			}

			break;

		case ONE:

			// プレイヤー
			player_->Update(CollisionStageFlag(player_, stage_));
			player_->OnCollisionStage(CollisionStageFlag(player_, stage_));
			player_->IsDead();

			// ステージ
			stage_->Update();
			stage1_->Update();

			// ギミック
			silverKey_->Update();
			silverKey_->OnCollisionStage(CollisionKeyFlag(silverKey_, stage_));

			door_->Update(isOpen_, isKeyOpen_);

			CheckAllCollisions();

			// クリア
			if (isGoal_)
			{
				scene_ = GameClear;
			}

			// ゲームオーバー
			if (player_->IsGetDead())
			{
				scene_ = GameOver;
			}

			// リセット
			if (input_->TriggerKey(DIK_R))
			{
				stage1_->Initialize();
				silverKey_->Initialize(65, 60);
				door_->Initialize(110, 55);
				isGetKey_ = false;
				isKeyOpen_ = false;
			}

			// スキップ(後で消す)
			if (input_->TriggerKey(DIK_SPACE)) 
			{
				scene_ = GameClear;
			}

			break;

		case TWO:

			// プレイヤー
			player_->Update(CollisionStageFlag(player_, stage_));
			player_->OnCollisionStage(CollisionStageFlag(player_, stage_));
			player_->IsDead();

			// ステージ
			stage_->Update();
			stage1_->Update();

			// ギミック
			silverKey_->Update();
			silverKey_->OnCollisionStage(CollisionKeyFlag(silverKey_, stage_));

			door_->Update(isOpen_, isKeyOpen_);

			CheckAllCollisions();

			// クリア
			if (isGoal_)
			{
				scene_ = GameClear;
			}

			// ゲームオーバー
			if (player_->IsGetDead())
			{
				scene_ = GameOver;
			}

			// リセット
			if (input_->TriggerKey(DIK_R))
			{
				stage1_->Initialize();
				silverKey_->Initialize(65, 60);
				door_->Initialize(110, 55);
				isGetKey_ = false;
				isKeyOpen_ = false;
			}

			// スキップ(後で消す)
			if (input_->TriggerKey(DIK_SPACE))
			{
				scene_ = GameClear;
			}

			debugText_->SetPos(50, 120);
			debugText_->Printf("stageFlag_:%d", stageFlag);

			break;

		case THREE:

			// プレイヤー
			player_->Update(CollisionStageFlag(player_, stage_));
			player_->OnCollisionStage(CollisionStageFlag(player_, stage_));
			player_->IsDead();

			// ステージ
			stage_->Update();
			stage1_->Update();

			// ギミック
			silverKey_->Update();
			silverKey_->OnCollisionStage(CollisionKeyFlag(silverKey_, stage_));

			door_->Update(isOpen_, isKeyOpen_);

			CheckAllCollisions();

			// クリア
			if (isGoal_)
			{
				scene_ = GameClear;
			}

			// ゲームオーバー
			if (player_->IsGetDead())
			{
				scene_ = GameOver;
			}

			// リセット
			if (input_->TriggerKey(DIK_R))
			{
				stage1_->Initialize();
				silverKey_->Initialize(65, 60);
				door_->Initialize(110, 55);
				isGetKey_ = false;
				isKeyOpen_ = false;
			}

			// スキップ(後で消す)
			if (input_->TriggerKey(DIK_SPACE))
			{
				scene_ = GameClear;
			}

			break;

		case FOUR:

			// プレイヤー
			player_->Update(CollisionStageFlag(player_, stage_));
			player_->OnCollisionStage(CollisionStageFlag(player_, stage_));
			player_->IsDead();

			// ステージ
			stage_->Update();
			stage1_->Update();

			// ギミック
			silverKey_->Update();
			silverKey_->OnCollisionStage(CollisionKeyFlag(silverKey_, stage_));

			door_->Update(isOpen_, isKeyOpen_);

			CheckAllCollisions();

			// クリア
			if (isGoal_)
			{
				scene_ = GameClear;
			}

			// ゲームオーバー
			if (player_->IsGetDead())
			{
				scene_ = GameOver;
			}

			// リセット
			if (input_->TriggerKey(DIK_R))
			{
				stage1_->Initialize();
				silverKey_->Initialize(65, 60);
				door_->Initialize(110, 55);
				isGetKey_ = false;
				isKeyOpen_ = false;
			}

			// スキップ(後で消す)
			if (input_->TriggerKey(DIK_SPACE))
			{
				scene_ = GameClear;
			}

			break;

		case FIVE:

			// プレイヤー
			player_->Update(CollisionStageFlag(player_, stage_));
			player_->OnCollisionStage(CollisionStageFlag(player_, stage_));
			player_->IsDead();

			// ステージ
			stage_->Update();
			stage1_->Update();

			// ギミック
			silverKey_->Update();
			silverKey_->OnCollisionStage(CollisionKeyFlag(silverKey_, stage_));

			door_->Update(isOpen_, isKeyOpen_);

			CheckAllCollisions();

			// クリア
			if (isGoal_)
			{
				scene_ = GameClear;
			}

			// ゲームオーバー
			if (player_->IsGetDead())
			{
				scene_ = GameOver;
			}

			// リセット
			if (input_->TriggerKey(DIK_R))
			{
				stage1_->Initialize();
				silverKey_->Initialize(65, 60);
				door_->Initialize(110, 55);
				isGetKey_ = false;
				isKeyOpen_ = false;
			}

			// スキップ(後で消す)
			if (input_->TriggerKey(DIK_SPACE))
			{
				scene_ = GameClear;
			}

			break;

		case GameOver:

			if (input_->TriggerKey(DIK_SPACE))
			{
				scene_ = TITLE;
			}

			break;

		case GameClear:

			if (input_->TriggerKey(DIK_SPACE) && stageFlag == 0)
			{
				Initialize();
				isGoal_ = false;

				stageFlag = 1;

				Parameter({ 0.0f, 0.0f, -20.0f }, stageFlag);

				scene_ = TWO;
			}
			else if (input_->TriggerKey(DIK_SPACE) && stageFlag == 1)
			{
				Initialize();
				isGoal_ = false;

				stageFlag = 2;

				Parameter({ 0.0f, 0.0f, -20.0f }, stageFlag);

				scene_ = THREE;
			}
			else if (input_->TriggerKey(DIK_SPACE) && stageFlag == 2)
			{
				Initialize();
				isGoal_ = false;

				stageFlag = 3;

				Parameter({ 0.0f, 0.0f, -20.0f }, stageFlag);

				scene_ = FOUR;
			}
			else if (input_->TriggerKey(DIK_SPACE) && stageFlag == 3)
			{
				Initialize();
				isGoal_ = false;

				stageFlag = 4;

				Parameter({ 0.0f, 0.0f, -20.0f }, stageFlag);

				scene_ = FIVE;
			}
			else if (input_->TriggerKey(DIK_SPACE) && stageFlag == 4)
			{
				scene_ = TITLE;
			}

			break;
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

	switch (scene_)
	{
		case TITLE:

			break;

		case ONE:

			backGround1_->Draw();

			break;

		case TWO:

			backGround1_->Draw();

			break;

		case THREE:

			break;

		case FOUR:

			break;

		case FIVE:

			break;

		case GameOver:

			gameOver_->Draw();

			break;

		case GameClear:

			gameClear_->Draw();

			break;
	}

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

		case ONE:

			stage_->Draw(viewProjection_);
			stage1_->Draw(viewProjection_);
			player_->Draw(viewProjection_);
			silverKey_->Draw(viewProjection_);
			door_->Draw(viewProjection_);
			goal_->Draw(viewProjection_);

			break;

		case TWO:

			stage_->Draw(viewProjection_);
			stage1_->Draw(viewProjection_);
			player_->Draw(viewProjection_);
			silverKey_->Draw(viewProjection_);
			door_->Draw(viewProjection_);
			goal_->Draw(viewProjection_);

			break;

		case THREE:

			stage_->Draw(viewProjection_);
			stage1_->Draw(viewProjection_);
			player_->Draw(viewProjection_);
			silverKey_->Draw(viewProjection_);
			door_->Draw(viewProjection_);
			goal_->Draw(viewProjection_);

			break;

		case FOUR:

			stage_->Draw(viewProjection_);
			stage1_->Draw(viewProjection_);
			player_->Draw(viewProjection_);
			silverKey_->Draw(viewProjection_);
			door_->Draw(viewProjection_);
			goal_->Draw(viewProjection_);

			break;

		case FIVE:

			stage_->Draw(viewProjection_);
			stage1_->Draw(viewProjection_);
			player_->Draw(viewProjection_);
			silverKey_->Draw(viewProjection_);
			door_->Draw(viewProjection_);
			goal_->Draw(viewProjection_);

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

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Parameter(
	const Vector3& playerPos1, const int& stageNum) {
	// 自キャラの初期化
	Vector3 pos1 = playerPos1;
	player_->Initialize(pos1);
	// ステージの初期化
	stage_->StageInitialize(filename_[stageNum]); // ステージ読み込み(1)

	isClear = false;
}

bool GameScene::CollisionStageFlag(Player* p, stage* s) {
	// 各座標変数の宣言
	Vector3 pPos = p->GetWorldPosition();
	float pRadius = p->GetRadius();
	float pX1, pX2, pY1, pY2;
	// プレイヤーの矩形座標
	pX1 = pPos.x - pRadius;
	pX2 = pPos.x + pRadius;
	pY1 = pPos.y - pRadius;
	pY2 = pPos.y + pRadius;

	// プレイヤーLeftTop座標
	int pLT[2] = { static_cast<int>(pX1 / 4), static_cast<int>(((pY1 / 4) - 17) * -1) };
	int isFloor = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
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

bool GameScene::CollisionKeyFlag(SilverKey* p, stage* s)
{
	// 各座標変数の宣言
	Vector3 pPos = p->GetWorldPosition();
	float pRadius = 3.0f;
	float pX1, pX2, pY1, pY2;
	// プレイヤーの矩形座標
	pX1 = pPos.x - pRadius;
	pX2 = pPos.x + pRadius;
	pY1 = pPos.y - pRadius;
	pY2 = pPos.y + pRadius;

	// プレイヤーLeftTop座標
	int pLT[2] = { static_cast<int>(pX1 / 4), static_cast<int>(((pY1 / 4) - 17) * -1) };
	int isFloor = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
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
