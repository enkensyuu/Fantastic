#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene()
{
	delete Title_;
	delete Explanation_;
	delete StageChoice_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//テクスチャを入れ込む
	textureHandle_[0] = TextureManager::Load("exchange.png"); //操作説明
	textureHandle_[1] = TextureManager::Load("Title.png"); //タイトル
	textureHandle_[2] = TextureManager::Load("space.png"); //Space文字
	textureHandle_[3] = TextureManager::Load("Stage.png"); //ステージ選択
	textureHandle_[4] = TextureManager::Load("waku.png"); //ステージ選択(枠)

	//スプライトを生成
	Explanation_ = Sprite::Create(textureHandle_[0], { 0,0 });
	Title_ = Sprite::Create(textureHandle_[1], { 0,0 });
	Space_ = Sprite::Create(textureHandle_[2], { 550,800 });
	StageChoice_= Sprite::Create(textureHandle_[3], { 0,0 });
	Waku_ = Sprite::Create(textureHandle_[4], {100,200});

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

	scene_ = TITLE;
}

void GameScene::Update() {
	switch (scene_)
	{
	case TITLE:
		Initialize();
		GameTimer_ += 1;
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene_ = EXPLANATION;
		}
		break;
	case EXPLANATION:
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene_ = STAGECHOICE;
		}
		break;
	case STAGECHOICE:
		if (input_->TriggerKey(DIK_1))
		{
			WakuFlag = 1;
			if (input_->TriggerKey(DIK_RETURN))
			{
				scene_ = THREE;
			}
		}
		if (input_->TriggerKey(DIK_B) && WakuFlag == 1)
		{
			WakuFlag = 0;
		}

		if (input_->TriggerKey(DIK_2))
		{
			if (input_->TriggerKey(DIK_RETURN))
			{
				scene_ = FOUR;
			}
		}
		if (input_->TriggerKey(DIK_3))
		{
			if (input_->TriggerKey(DIK_RETURN))
			{
				scene_ = FIVE;
			}
		}
		if (input_->TriggerKey(DIK_4))
		{
			if (input_->TriggerKey(DIK_RETURN))
			{
				scene_ = SIX;
			}
		}
		if (input_->TriggerKey(DIK_5))
		{
			if (input_->TriggerKey(DIK_RETURN))
			{
				scene_ = SEVEN;
			}
		}
	case THREE:
		if (input_->TriggerKey(DIK_RETURN))
		{
			scene_ = FOUR;
		}
		stage1_->Update();
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
	case EXPLANATION:
		Explanation_->Draw();
		break;
	case STAGECHOICE:
		StageChoice_->Draw();
		if (WakuFlag == 1)
		{
         Waku_->Draw();
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
	case EXPLANATION:
		break;
	case STAGECHOICE:
		break;
	case THREE:
		stage1_->Draw();
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
