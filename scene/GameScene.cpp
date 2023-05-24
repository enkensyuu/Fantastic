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

	gameOver_ = Sprite::Create(gameOverTexture_, { 0,0 });
	gameClear_ = Sprite::Create(gameClearTexture_, { 0,0 });

	closeGame_ = false;

	StageTimer = 1;
	Select = 0;
	RingFlag = 0;
	PauseFlag = false;
	SelectFlag = 0;
	SceneStageFlag1 = 0;
	PauseFlag = 0;
	changScene = false;
	stopPlay = false;

	//テクスチャを入れ込む
	textureHandle_[0] = TextureManager::Load("exchange.png"); //ゲーム説明
	textureHandle_[1] = TextureManager::Load("Title.png"); //タイトル
	textureHandle_[2] = TextureManager::Load("space.png"); //Space文字
	textureHandle_[3] = TextureManager::Load("Stage.png"); //ステージ選択
	textureHandle_[4] = TextureManager::Load("waku.png"); //ステージ選択(枠)
	textureHandle_[5] = TextureManager::Load("1.png"); //背景1
	textureHandle_[6] = TextureManager::Load("2.png"); //背景2
	textureHandle_[7] = TextureManager::Load("3.png"); //背景3
	textureHandle_[8] = TextureManager::Load("Pause.png"); //Pause
	textureHandle_[9] = TextureManager::Load("ScenePause.png");//Pause画面
	textureHandle_[10] = TextureManager::Load("Yazirushi.png");//Pause画面(Select)
	textureHandle_[11] = TextureManager::Load("4.png"); //背景4
	textureHandle_[12] = TextureManager::Load("Operation.png"); //操作説明
	textureHandle_[13] = TextureManager::Load("5.png"); //背景5
	textureHandle_[14] = TextureManager::Load("Game_Over.png"); //ゲームオーバー文字



	//スプライトを生成
	Explanation_ = Sprite::Create(textureHandle_[0], { 0,0 });
	Title_ = Sprite::Create(textureHandle_[1], { 0,0 });
	Space_ = Sprite::Create(textureHandle_[2], { 550,600 });
	StageChoice_ = Sprite::Create(textureHandle_[3], { 0,0 });
	Waku_ = Sprite::Create(textureHandle_[4], { 102,200 });
	Waku2_ = Sprite::Create(textureHandle_[4], { 700,200 });
	Waku3_ = Sprite::Create(textureHandle_[4], { 1300,200 });
	Waku4_ = Sprite::Create(textureHandle_[4], { 104,604 });
	Waku5_ = Sprite::Create(textureHandle_[4], { 705,600 });
	BackGroudStage1_ = Sprite::Create(textureHandle_[5], { 0,0 });
	BackGroudStage2_ = Sprite::Create(textureHandle_[6], { 0,0 });
	BackGroudStage3_ = Sprite::Create(textureHandle_[7], { 0,0 });
	BackGroudStage4_ = Sprite::Create(textureHandle_[11], { 0,0 });
	BackGroudStage5_ = Sprite::Create(textureHandle_[13], { 0,0 });
	Pause_ = Sprite::Create(textureHandle_[8], { 10,10 });
	PauseScene_ = Sprite::Create(textureHandle_[9], { 600,80 });
	PauseSelect_ = Sprite::Create(textureHandle_[10], { 770,290 });
	PauseSelect2_ = Sprite::Create(textureHandle_[10], { 770,403 });
	PauseSelect3_ = Sprite::Create(textureHandle_[10], { 610,530 });
	PauseSelect4_ = Sprite::Create(textureHandle_[10], { 600,655 });
	PauseSelect5_ = Sprite::Create(textureHandle_[10], { 660,791 });
	//PauseSelect6_ = Sprite::Create(textureHandle_[10], { 661,830 });
	Operation_ = Sprite::Create(textureHandle_[12], { 0,0 });
	GameOver_ = Sprite::Create(textureHandle_[14], { 0,0 });

	//SEデータ
	StageSelectSE_ = audio_->LoadWave("SE/StageSelection.mp3");

	//BGM(ステージ1,2,3,4,5,タイトル)
	TitleBGM_ = audio_->LoadWave("BGM/Title.mp3");
	Stage1BGM_ = audio_->LoadWave("BGM/Stage1BGM.mp3");
	Stage2BGM_ = audio_->LoadWave("BGM/Stage2BGM.mp3");
	Stage3BGM_ = audio_->LoadWave("BGM/Stage3BGM.mp3");
	Stage4BGM_ = audio_->LoadWave("BGM/Stage4BGM.mp3");
	Stage5BGM_ = audio_->LoadWave("BGM/Stage5BGM.mp3");

	// 3Dモデルの生成
	model_ = Model::Create();

	// ステージ
	stage_ = new stage();
	stage_->Initialize(model_);

	stage1_ = new Stage1;

	stage2_ = new Stage2;

	stage3_ = new Stage3;

	stage4_ = new Stage4;

	stage5_ = new Stage5;

	player_ = new Player;

	balloon_ = new Balloon;

	silverKey_ = new SilverKey;

	windPower_ = new WindPower;

	magmaBlock_ = new MagmaBlock;

	door_ = new Door;

	goal_ = new Goal;

	scene_ = TITLE;

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

		if (input_->TriggerKey(DIK_SPACE))
		{
			scene_ = INSTRUCTIONS;
			StageTimer = 0;
		}

		break;

	case INSTRUCTIONS:


		if (input_->TriggerKey(DIK_SPACE))
		{
			if (!changScene)
			{
				changScene = true;
			}
			else
			{
				scene_ = SELECT;
				PauseFlag = 0;
				StageTimer = 1;
				if (SceneStageFlag1 == 1)
				{
					scene_ = STAGE1;
					SceneStageFlag1 = 0;
				}

				else if (SceneStageFlag2 == 1)
				{
					scene_ = STAGE2;
					SceneStageFlag2 = 0;
				}

				else if (SceneStageFlag3 == 1)
				{
					scene_ = STAGE3;
					SceneStageFlag3 = 0;
				}

				else if (SceneStageFlag4 == 1)
				{
					scene_ = STAGE4;
					SceneStageFlag4 = 0;
				}

				else if (SceneStageFlag5 == 1)
				{
					scene_ = STAGE5;
					SceneStageFlag5 = 0;
				}
			}
		}

		break;

	case SELECT:
		if (input_->TriggerKey(DIK_RIGHT))
		{
			StageTimer += 1;
		}

		if (input_->TriggerKey(DIK_LEFT))
		{
			StageTimer -= 1;
		}

		if (input_->TriggerKey(DIK_D))
		{
			StageTimer += 1;
		}

		if (input_->TriggerKey(DIK_A))
		{
			StageTimer -= 1;
		}

		if (input_->TriggerKey(DIK_RETURN) && StageTimer == 1)
		{
			STage1Initialize();
			StageSEHandle_ = audio_->PlayWave(StageSelectSE_, false);
			Stage1BGMHandle_ = audio_->PlayWave(Stage1BGM_, true);
			scene_ = STAGE1;
		}

		if (input_->TriggerKey(DIK_RETURN) && StageTimer == 2)
		{
			StageSEHandle_ = audio_->PlayWave(StageSelectSE_, false);
			Stage2BGMHandle_ = audio_->PlayWave(Stage2BGM_, true);
			scene_ = STAGE2;
		}

		if (input_->TriggerKey(DIK_RETURN) && StageTimer == 3)
		{
			StageSEHandle_ = audio_->PlayWave(StageSelectSE_, false);
			Stage3BGMHandle_ = audio_->PlayWave(Stage3BGM_, true);
			scene_ = STAGE3;
		}

		if (input_->TriggerKey(DIK_RETURN) && StageTimer == 4)
		{
			StageSEHandle_ = audio_->PlayWave(StageSelectSE_, false);
			Stage4BGMHandle_ = audio_->PlayWave(Stage4BGM_, true);
			scene_ = STAGE4;
		}

		if (input_->TriggerKey(DIK_RETURN) && StageTimer == 5)
		{
			StageSEHandle_ = audio_->PlayWave(StageSelectSE_, false);
			Stage5BGMHandle_ = audio_->PlayWave(Stage5BGM_, true);
			scene_ = STAGE5;
		}

		//マイナスに行かないようにする
		if (StageTimer < 1)
		{
			StageTimer = 5;
		}

		//右端まで行ったら1に戻す
		if (StageTimer > 5)
		{
			StageTimer = 1;
		}

		Select = 1;
		PauseFlag = 0;
		break;

	case STAGE1:
		Stage1Update();
		CheckAllCollisions();

		if (isGoal_)
		{
			stopPlay = true;
		}

		break;

	case STAGE2:
		CheckAllCollisions();
		break;

	case STAGE3:
		CheckAllCollisions();
		break;

	case STAGE4:
		CheckAllCollisions();
		break;

	case STAGE5:
		CheckAllCollisions();
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
	/// 
	switch (scene_)
	{
	case TITLE:
		Title_->Draw();
		if (GameTimer_ % 30 >= 20)
		{
			Space_->Draw();
		}

		break;
	case INSTRUCTIONS:
		if (!changScene)
		{
			Explanation_->Draw();
		}
		else
		{
			Operation_->Draw();
		}

		break;

	case SELECT:
		StageChoice_->Draw();
		if (StageTimer == 1)
		{
			Waku_->Draw();
		}
		if (StageTimer == 2)
		{
			Waku2_->Draw();
		}
		if (StageTimer == 3)
		{
			Waku3_->Draw();
		}
		if (StageTimer == 4)
		{
			Waku4_->Draw();
		}
		if (StageTimer == 5)
		{
			Waku5_->Draw();
		}
		break;
	case STAGE1:
		if (scene_ == STAGE1)
		{

			BackGroudStage1_->Draw();
			Pause_->Draw();

			/*DebugText::GetInstance()->SetPos(1700, 30);
			DebugText::GetInstance()->Printf("Select:%d", Select);*/
		}
		break;
	case STAGE2:
		if (scene_ == STAGE2)
		{
			BackGroudStage2_->Draw();
			Pause_->Draw();
		}
		break;
	case STAGE3:
		if (scene_ == STAGE3)
		{
			BackGroudStage3_->Draw();
			Pause_->Draw();
		}
		break;
	case STAGE4:
		if (scene_ == STAGE4)
		{
			BackGroudStage4_->Draw();
			Pause_->Draw();
		}
	case STAGE5:
		if (scene_ == STAGE5)
		{
			BackGroudStage5_->Draw();
			Pause_->Draw();
		}
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

	case INSTRUCTIONS:
		break;

	case SELECT:
		break;

	case STAGE1:

		stage_->Draw(viewProjection_);
		stage1_->Draw(viewProjection_);
		player_->Draw(viewProjection_);
		silverKey_->Draw(viewProjection_);
		door_->Draw(viewProjection_);
		goal_->Draw(viewProjection_);

		break;

	case STAGE2:

		stage_->Draw(viewProjection_);
		stage1_->Draw(viewProjection_);
		player_->Draw(viewProjection_);
		silverKey_->Draw(viewProjection_);
		door_->Draw(viewProjection_);
		goal_->Draw(viewProjection_);

		break;

	case STAGE3:

		stage_->Draw(viewProjection_);
		stage1_->Draw(viewProjection_);
		player_->Draw(viewProjection_);
		silverKey_->Draw(viewProjection_);
		door_->Draw(viewProjection_);
		goal_->Draw(viewProjection_);

		break;

	case STAGE4:

		stage_->Draw(viewProjection_);
		stage1_->Draw(viewProjection_);
		player_->Draw(viewProjection_);
		silverKey_->Draw(viewProjection_);
		door_->Draw(viewProjection_);
		goal_->Draw(viewProjection_);

		break;

	case STAGE5:

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
	switch (scene_)
	{
	case TITLE:
		break;
	case INSTRUCTIONS:
		break;
	case SELECT:
		break;
	case STAGE1:
		//GameOver_->Draw();
		if (PauseFlag == 1)
		{
			PauseScene_->Draw();
		}
		if (PauseFlag == 1)
		{
			if (SelectFlag == 1)
			{
				if (Select == 1)
				{
					PauseSelect_->Draw();
				}

				if (Select == 2)
				{
					PauseSelect2_->Draw();
				}

				if (Select == 3)
				{
					PauseSelect3_->Draw();
				}

				if (Select == 4)
				{
					PauseSelect4_->Draw();
				}

				if (Select == 5)
				{
					PauseSelect5_->Draw();
				}

				/*if (Select == 6)
				{
					PauseSelect6_->Draw();
				}*/
			}
		}
		break;

	case STAGE2:
		if (PauseFlag == 1)
		{
			PauseScene_->Draw();
		}
		if (PauseFlag == 1)
		{
			if (SelectFlag == 1)
			{
				if (Select == 1)
				{
					PauseSelect_->Draw();
				}

				if (Select == 2)
				{
					PauseSelect2_->Draw();
				}

				if (Select == 3)
				{
					PauseSelect3_->Draw();
				}

				if (Select == 4)
				{
					PauseSelect4_->Draw();
				}

				if (Select == 5)
				{
					PauseSelect5_->Draw();
				}

				/*if (Select == 6)
				{
					PauseSelect6_->Draw();
				}*/
			}
		}
		break;

	case STAGE3:
		if (PauseFlag == 1)
		{
			PauseScene_->Draw();
		}
		if (PauseFlag == 1)
		{
			if (SelectFlag == 1)
			{
				if (Select == 1)
				{
					PauseSelect_->Draw();
				}

				if (Select == 2)
				{
					PauseSelect2_->Draw();
				}

				if (Select == 3)
				{
					PauseSelect3_->Draw();
				}

				if (Select == 4)
				{
					PauseSelect4_->Draw();
				}

				if (Select == 5)
				{
					PauseSelect5_->Draw();
				}

				/*if (Select == 6)
				{
					PauseSelect6_->Draw();
				}*/
			}
		}
		break;

	case STAGE4:
		if (PauseFlag == 1)
		{
			PauseScene_->Draw();
		}
		if (PauseFlag == 1)
		{
			if (SelectFlag == 1)
			{
				if (Select == 1)
				{
					PauseSelect_->Draw();
				}

				if (Select == 2)
				{
					PauseSelect2_->Draw();
				}

				if (Select == 3)
				{
					PauseSelect3_->Draw();
				}

				if (Select == 4)
				{
					PauseSelect4_->Draw();
				}

				if (Select == 5)
				{
					PauseSelect5_->Draw();
				}

				/*if (Select == 6)
				{
					PauseSelect6_->Draw();
				}*/
			}
		}
		break;

	case STAGE5:
		if (PauseFlag == 1)
		{
			PauseScene_->Draw();
		}
		if (PauseFlag == 1)
		{
			if (SelectFlag == 1)
			{
				if (Select == 1)
				{
					PauseSelect_->Draw();
				}

				if (Select == 2)
				{
					PauseSelect2_->Draw();
				}

				if (Select == 3)
				{
					PauseSelect3_->Draw();
				}

				if (Select == 4)
				{
					PauseSelect4_->Draw();
				}

				if (Select == 5)
				{
					PauseSelect5_->Draw();
				}
			}
		}
		break;
	}

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Parameter(const Vector3& playerPos1, const int& stageNum) {
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



void GameScene::STage1Initialize()
{
	isGetKey_ = false;
	isKeyOpen_ = false;

	stage1_->Initialize();

	Parameter({ 10.0f,7.0f,-20.0f }, stageFlag);

	silverKey_->Initialize(65, 60);

	door_->Initialize(110, 55);

	goal_->Initialize(114, 7);

	isGoal_ = false;
}
void GameScene::STage2Initialize()
{
	stage2_->Initialize();

	balloon_->Initialize(-5, 10);

	silverKey_->Initialize(65, 60);

	windPower_->Initialize(-5, -5);

	magmaBlock_->Initialize(0, -10);

	door_->Initialize(110, 55);

	goal_->Initialize(114, 7);

	isGoal_ = false;

}
void GameScene::STage3Initialize()
{
	stage3_->Initialize();

	balloon_->Initialize(-5, 10);

	silverKey_->Initialize(65, 60);

	windPower_->Initialize(-5, -5);

	magmaBlock_->Initialize(0, -10);

	door_->Initialize(110, 55);

	goal_->Initialize(114, 7);

	isGoal_ = false;

}
void GameScene::STage4Initialize()
{
	isGoal_ = false;
}
void GameScene::STage5Initialize()
{
	isGoal_ = false;
}

void GameScene::Stage1Update()
{
	if (!stopPlay)
	{
		if (!PauseFlag)
		{
			// プレイヤー
			player_->Update(CollisionStageFlag(player_, stage_));
			player_->OnCollisionStage(CollisionStageFlag(player_, stage_));
			player_->IsDead();

			// ステージ
			stage_->Update();

			// ギミック
			silverKey_->Update();
			silverKey_->OnCollisionStage(CollisionKeyFlag(silverKey_, stage_));

			door_->Update(isOpen_, isKeyOpen_);

			stage1_->Update();
		}

		audio_->SetVolume(Stage1BGMHandle_, 0.25f);
	}



	//Pause画面
	if (input_->PushKey(DIK_ESCAPE))
	{
		PauseFlag = true;
	}

	if (PauseFlag)
	{
		//Pause画面の下移動
		if (input_->TriggerKey(DIK_DOWN) || input_->TriggerKey(DIK_S))
		{
			Select++;
			SelectFlag = 1;
		}

		//Pause画面の上移動
		if (input_->TriggerKey(DIK_UP) || input_->TriggerKey(DIK_W))
		{
			Select--;
			SelectFlag = 1;
		}
	}

	if (Select < 1)
	{
		Select = 5;
	}

	if (Select > 5)
	{
		Select = 1;
	}

	//Pauseの処理//

	//ゲームを続ける
	if (input_->TriggerKey(DIK_RETURN) && Select == 1)
	{
		PauseFlag = false;
	}

	//リセット
	if (input_->TriggerKey(DIK_RETURN) && Select == 2)
	{
		STage1Initialize();
		PauseFlag = false;
		isGoal_ = false;
		stopPlay = false;
	}

	//ゲーム説明の戻る
	if (input_->TriggerKey(DIK_RETURN) && Select == 3)
	{
		scene_ = INSTRUCTIONS;
		SceneStageFlag1 = 1;
		PauseFlag = false;
	}

	//ステージ選択に戻る
	if (input_->TriggerKey(DIK_RETURN) && Select == 4)
	{
		scene_ = SELECT;
		audio_->StopWave(Stage1BGMHandle_);
		PauseFlag = false;
	}

	//ゲームをやめる
	if (input_->TriggerKey(DIK_RETURN) && Select == 5)
	{
		closeGame_ = true;
	}
}

void GameScene::Stage2Update()
{
	stage2_->Update();

	audio_->SetVolume(Stage2BGMHandle_, 0.15f);

	//Pause画面の下移動
	if (input_->TriggerKey(DIK_DOWN))
	{
		if (PauseFlag == 1)
		{
			Select++;
			SelectFlag = 1;
		}
	}

	if (input_->TriggerKey(DIK_S))
	{
		if (PauseFlag == 1)
		{
			Select++;
			SelectFlag = 1;
		}
	}

	//Pause画面の上移動
	if (input_->TriggerKey(DIK_UP))
	{
		if (PauseFlag == 1)
		{
			Select--;
			SelectFlag = 1;
		}
	}

	if (input_->TriggerKey(DIK_W))
	{
		if (PauseFlag == 1)
		{
			Select--;
			SelectFlag = 1;
		}
	}

	if (Select < 1)
	{
		Select = 5;
	}

	if (Select > 5)
	{
		Select = 1;
	}

	//Pauseの処理//

		//Pause画面
	if (input_->PushKey(DIK_ESCAPE))
	{
		PauseFlag = 1;
	}

	//ゲームを続ける
	if (input_->TriggerKey(DIK_RETURN) && Select == 1)
	{
		PauseFlag = 0;
	}

	//リセット
	if (input_->TriggerKey(DIK_RETURN) && Select == 2)
	{
		stage2_->Initialize();
		PauseFlag = 0;
	}

	//ゲーム説明の戻る
	if (input_->TriggerKey(DIK_RETURN) && Select == 3)
	{
		SceneStageFlag2 = 1;
		scene_ = INSTRUCTIONS;
	}

	//ステージ選択に戻る
	if (input_->TriggerKey(DIK_RETURN) && Select == 4)
	{
		audio_->StopWave(Stage2BGMHandle_);
		scene_ = SELECT;
	}

	//ゲームをやめる
	if (input_->TriggerKey(DIK_RETURN) && Select == 5)
	{
		closeGame_ = true;
	}
}

void GameScene::Stage3Update()
{
	stage3_->Update();

	audio_->SetVolume(Stage3BGMHandle_, 0.15f);

	//Pause画面の下移動
	if (input_->TriggerKey(DIK_DOWN))
	{
		if (PauseFlag == 1)
		{
			Select++;
			SelectFlag = 1;
		}
	}

	if (input_->TriggerKey(DIK_S))
	{
		if (PauseFlag == 1)
		{
			Select++;
			SelectFlag = 1;
		}
	}

	//Pause画面の上移動
	if (input_->TriggerKey(DIK_UP))
	{
		if (PauseFlag == 1)
		{
			Select--;
			SelectFlag = 1;
		}
	}

	if (input_->TriggerKey(DIK_W))
	{
		if (PauseFlag == 1)
		{
			Select--;
			SelectFlag = 1;
		}
	}

	if (Select < 1)
	{
		Select = 5;
	}

	if (Select > 5)
	{
		Select = 1;
	}

	//Pauseの処理//

	//Pause画面
	if (input_->PushKey(DIK_ESCAPE))
	{
		PauseFlag = 1;
	}

	//ゲームを続ける
	if (input_->TriggerKey(DIK_RETURN) && Select == 1)
	{
		PauseFlag = 0;
	}

	//リセット
	if (input_->TriggerKey(DIK_RETURN) && Select == 2)
	{
		stage3_->Initialize();
		PauseFlag = 0;
	}

	//ゲーム説明の戻る
	if (input_->TriggerKey(DIK_RETURN) && Select == 3)
	{
		scene_ = INSTRUCTIONS;
		SceneStageFlag3 = 1;
	}

	//ステージ選択に戻る
	if (input_->TriggerKey(DIK_RETURN) && Select == 4)
	{
		audio_->StopWave(Stage3BGMHandle_);
		scene_ = SELECT;
	}

	//ゲームをやめる
	if (input_->TriggerKey(DIK_RETURN) && Select == 5)
	{
		closeGame_ = true;
	}
}

void GameScene::Stage4Update()
{
	stage4_->Update();

	audio_->SetVolume(Stage4BGMHandle_, 0.15f);

	//Pause画面の下移動
	if (input_->TriggerKey(DIK_DOWN))
	{
		if (PauseFlag == 1)
		{
			Select++;
			SelectFlag = 1;
		}
	}

	if (input_->TriggerKey(DIK_S))
	{
		if (PauseFlag == 1)
		{
			Select++;
			SelectFlag = 1;
		}
	}

	//Pause画面の上移動
	if (input_->TriggerKey(DIK_UP))
	{
		if (PauseFlag == 1)
		{
			Select--;
			SelectFlag = 1;
		}
	}

	if (input_->TriggerKey(DIK_W))
	{
		if (PauseFlag == 1)
		{
			Select--;
			SelectFlag = 1;
		}
	}

	if (Select < 1)
	{
		Select = 5;
	}

	if (Select > 5)
	{
		Select = 1;
	}

	//Pauseの処理//

		//Pause画面
	if (input_->PushKey(DIK_ESCAPE))
	{
		PauseFlag = 1;
	}

	//ゲームを続ける
	if (input_->TriggerKey(DIK_RETURN) && Select == 1)
	{
		PauseFlag = 0;
	}

	//リセット
	if (input_->TriggerKey(DIK_RETURN) && Select == 2)
	{
		stage4_->Initialize();
		PauseFlag = 0;
	}

	//ゲーム説明の戻る
	if (input_->TriggerKey(DIK_RETURN) && Select == 3)
	{
		scene_ = INSTRUCTIONS;
		SceneStageFlag4 = 1;
	}

	//ステージ選択に戻る
	if (input_->TriggerKey(DIK_RETURN) && Select == 4)
	{
		audio_->StopWave(Stage4BGMHandle_);
		scene_ = SELECT;
	}

	//ゲームをやめる
	if (input_->TriggerKey(DIK_RETURN) && Select == 5)
	{
		closeGame_ = true;
	}

}

void GameScene::Stage5Update()
{
	stage5_->Update();

	audio_->SetVolume(Stage5BGMHandle_, 0.15f);

	//Pause画面の下移動
	if (input_->TriggerKey(DIK_DOWN))
	{
		if (PauseFlag == 1)
		{
			Select++;
			SelectFlag = 1;
		}
	}

	if (input_->TriggerKey(DIK_S))
	{
		if (PauseFlag == 1)
		{
			Select++;
			SelectFlag = 1;
		}
	}

	//Pause画面の上移動
	if (input_->TriggerKey(DIK_UP))
	{
		if (PauseFlag == 1)
		{
			Select--;
			SelectFlag = 1;
		}
	}

	if (input_->TriggerKey(DIK_W))
	{
		if (PauseFlag == 1)
		{
			Select--;
			SelectFlag = 1;
		}
	}

	if (Select < 1)
	{
		Select = 5;
	}

	if (Select > 5)
	{
		Select = 1;
	}

	//Pauseの処理//

		//Pause画面
	if (input_->PushKey(DIK_ESCAPE))
	{
		PauseFlag = 1;
	}

	//ゲームを続ける
	if (input_->TriggerKey(DIK_RETURN) && Select == 1)
	{
		PauseFlag = 0;
	}

	//リセット
	if (input_->TriggerKey(DIK_RETURN) && Select == 2)
	{
		stage5_->Initialize();
		PauseFlag = 0;
	}

	//ゲーム説明の戻る
	if (input_->TriggerKey(DIK_RETURN) && Select == 3)
	{
		scene_ = INSTRUCTIONS;
		SceneStageFlag5 = 1;
	}

	//ステージ選択に戻る
	if (input_->TriggerKey(DIK_RETURN) && Select == 4)
	{
		audio_->StopWave(Stage5BGMHandle_);
		scene_ = SELECT;
	}

	//ゲームをやめる
	if (input_->TriggerKey(DIK_RETURN) && Select == 5)
	{
		closeGame_ = true;
	}
}