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
	PauseScene_= Sprite::Create(textureHandle_[9], { 600,80 });
	PauseSelect_ = Sprite::Create(textureHandle_[10], { 770,330 });
	PauseSelect2_ = Sprite::Create(textureHandle_[10], { 770,425 });
	PauseSelect3_ = Sprite::Create(textureHandle_[10], { 615,515 });
	PauseSelect4_ = Sprite::Create(textureHandle_[10], { 615,615});
	PauseSelect5_ = Sprite::Create(textureHandle_[10], { 602,715 });
	PauseSelect6_ = Sprite::Create(textureHandle_[10], { 661,810 });
	Operation_= Sprite::Create(textureHandle_[12], {0,0});

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
	RingFlag = 0;
	PauseFlag = 0;
	SelectFlag = 0;
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
			scene_ = OPERATION;
			StageTimer = 0;
		}
		break;

	case OPERATION:
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene_ = STAGECHOICE;
			StageTimer = 0;
		}

	case STAGECHOICE:
		Select = 0;
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
			scene_ = THREE;
		}

		if (input_->TriggerKey(DIK_RETURN) && StageTimer == 2)
		{
			scene_ = FOUR;
		}

		if (input_->TriggerKey(DIK_RETURN) && StageTimer == 3)
		{
			scene_ = FIVE;
		}

		if (input_->TriggerKey(DIK_RETURN) && StageTimer == 4)
		{
			scene_ = SIX;
		}

		if (input_->TriggerKey(DIK_RETURN) && StageTimer == 5)
		{
			scene_ = SEVEN;
		}

		//マイナスに行かないようにする
		if (StageTimer < 1)
		{
			StageTimer = 5;
		}

		//ステージタイマーを初期化
		if (StageTimer > 5)
		{
			StageTimer = 1;
		}
		

	case THREE: //ステージ1//

		//ENTERキーを押したらステージ移動
		if (input_->TriggerKey(DIK_RETURN) && RingFlag == 1)
		{
			scene_ = THREE;
		}

		if (input_->TriggerKey(DIK_RETURN) && RingFlag == 2)
		{
			scene_ = FOUR;
		}

		if (input_->TriggerKey(DIK_RETURN) && RingFlag == 3)
		{
			scene_ = FIVE;
		}

		if (input_->TriggerKey(DIK_RETURN) && RingFlag == 4)
		{
			scene_ = SIX;
		}

		if (input_->TriggerKey(DIK_SPACE) && RingFlag == 5)
		{
			scene_ = SEVEN;
		}

		if(scene_ == THREE)
		 {
		    stage1_->Update();
		 }
		
		//Pause画面
		if (input_->PushKey(DIK_ESCAPE))
		{
			PauseFlag = 1;
		}

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

		if (Select <= 1)
		{
			Select = 1;
		}

		if (Select > 6)
		{
			Select = 1;
		}

		//Pauseの処理//
		
		//ゲームを続ける
		if (input_->TriggerKey(DIK_RETURN) && Select == 1)
		{
			PauseFlag = 0;
		}

		//リセット
		if (input_->TriggerKey(DIK_RETURN) && Select == 2)
		{
			stage1_->Initialize();
			PauseFlag = 0;
		}

		//画面の大きさ変更
		/*if (input_->TriggerKey(DIK_RETURN) && Select == 3)
		{

		}*/

		//ゲーム説明の戻る
		if (input_->TriggerKey(DIK_RETURN)&& Select == 4)
		{
			scene_ = EXPLANATION;
			PauseFlag = 0;
		}

		//ステージ選択に戻る
		if (input_->TriggerKey(DIK_RETURN) && Select == 5)
		{
			scene_ = STAGECHOICE;
			PauseFlag = 0;
		}

		//ゲームをやめる
		/*if (input_->TriggerKey(DIK_RETURN) && Select == 6)
		{

		}*/
		break;

	case FOUR: //ステージ2

			stage2_->Update();

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

			if (Select <= 1)
			{
				Select = 1;
			}

			if (Select > 6)
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

			//画面の大きさ変更
			/*if (input_->TriggerKey(DIK_RETURN) && Select == 3)
			{

			}*/

			//ゲーム説明の戻る
			if (input_->TriggerKey(DIK_RETURN) && Select == 4)
			{
				scene_ = EXPLANATION;
			}

			//ステージ選択に戻る
			if (input_->TriggerKey(DIK_RETURN) && Select == 5)
			{
				scene_ = STAGECHOICE;
			}

			//ゲームをやめる
			/*if (input_->TriggerKey(DIK_RETURN) && Select == 6)
			{

			}*/
			break;
		

	case FIVE: //ステージ3//

			stage3_->Update();

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

			if (Select <= 1)
			{
				Select = 1;
			}

			if (Select > 6)
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

			//画面の大きさ変更
			/*if (input_->TriggerKey(DIK_RETURN) && Select == 3)
			{

			}*/

			//ゲーム説明の戻る
			if (input_->TriggerKey(DIK_RETURN) && Select == 4)
			{
				scene_ = EXPLANATION;
			}

			//ステージ選択に戻る
			if (input_->TriggerKey(DIK_RETURN) && Select == 5)
			{
				scene_ = STAGECHOICE;
			}

			//ゲームをやめる
			/*if (input_->TriggerKey(DIK_RETURN) && Select == 6)
			{

			}*/
			break;
	

	case SIX: //ステージ4//
		
			stage4_->Update();

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

			if (Select <= 1)
			{
				Select = 1;
			}

			if (Select > 6)
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

			//画面の大きさ変更
			/*if (input_->TriggerKey(DIK_RETURN) && Select == 3)
			{

			}*/

			//ゲーム説明の戻る
			if (input_->TriggerKey(DIK_RETURN) && Select == 4)
			{
				scene_ = EXPLANATION;
			}

			//ステージ選択に戻る
			if (input_->TriggerKey(DIK_RETURN) && Select == 5)
			{
				scene_ = STAGECHOICE;
			}

			//ゲームをやめる
			/*if (input_->TriggerKey(DIK_RETURN) && Select == 6)
			{

			}*/
		break;

	case SEVEN: //ステージ5//
		
			stage5_->Update();

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

			if (Select <= 1)
			{
				Select = 1;
			}

			if (Select > 6)
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

			//画面の大きさ変更
			/*if (input_->TriggerKey(DIK_RETURN) && Select == 3)
			{

			}*/

			//ゲーム説明の戻る
			if (input_->TriggerKey(DIK_RETURN) && Select == 4)
			{
				scene_ = EXPLANATION;
			}

			//ステージ選択に戻る
			if (input_->TriggerKey(DIK_RETURN) && Select == 5)
			{
				scene_ = STAGECHOICE;
			}

			//ゲームをやめる
			/*if (input_->TriggerKey(DIK_RETURN) && Select == 6)
			{

			}*/
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
	case EXPLANATION:
		Explanation_->Draw();
		break;
	case OPERATION:
		Operation_->Draw();
		break;
	case STAGECHOICE:
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
	case THREE:
		if (scene_ == THREE)
		{
			BackGroudStage1_->Draw();
			Pause_->Draw();

			DebugText::GetInstance()->SetPos(1700, 30);
			DebugText::GetInstance()->Printf("Select:%d", Select);
	    }
		break;
	case FOUR:
		if (scene_ == FOUR)
		{
			BackGroudStage2_->Draw();
			Pause_->Draw();
		}
		break;
	case FIVE:
		if (scene_ == FIVE)
		{
			BackGroudStage3_->Draw();
			Pause_->Draw();
		}
		break;
	case SIX:
		if (scene_ == SIX)
		{
			BackGroudStage4_->Draw();
			Pause_->Draw();
		}
	case SEVEN:
		if (scene_ == SEVEN)
		{
			BackGroudStage5_->Draw();
			Pause_->Draw();
		}
		break;
	}
	/*DebugText::GetInstance()->SetPos(200, 180);
	DebugText::GetInstance()->Printf("scene:%d", scene_);*/

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
	switch (scene_)
	{
	case TITLE:
		break;
	case EXPLANATION:
		break;
	case STAGECHOICE:
		break;
	case THREE:
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

				if (Select == 6)
				{
					PauseSelect6_->Draw();
				}
			}
		}
		break;

	case FOUR:
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

				if (Select == 6)
				{
					PauseSelect6_->Draw();
				}
			}
		}
		break;

	case FIVE:
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

				if (Select == 6)
				{
					PauseSelect6_->Draw();
				}
			}
		}
		break;

	case SIX:
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

				if (Select == 6)
				{
					PauseSelect6_->Draw();
				}
			}
		}
		break;

	case SEVEN:
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

				if (Select == 6)
				{
					PauseSelect6_->Draw();
				}
			}
		}
		break;
	}

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}