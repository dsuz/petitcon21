#include "StageSequenceData.h"

#include "IPropertyTable.h"
#if WITH_EDITOR
#include "Misc/MessageDialog.h"
#include "UObject/Package.h"
#include "EditorReimportHandler.h"
#include "FileHelpers.h"
#endif

#define LOCTEXT_NAMESPACE "TEST"

void UStageSequenceDataAsset::Build()
{
#if WITH_EDITORONLY_DATA

	// データテーブルの設定チェック
	if( DataTable == nullptr )
	{
		const FText TitleText = LOCTEXT( "Title", "WarningMassege" );
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT( "Message", "DataTable is Null !!" ), &TitleText );
		return;
	}

	// データテーブルの型チェック
	if( !DataTable->GetRowStruct()->IsChildOf( FStageSequenceData_TableRow::StaticStruct() ) )
	{
		const FText TitleText = LOCTEXT( "Title", "WarningMassege" );
		FMessageDialog::Open( EAppMsgType::Ok, LOCTEXT( "Message", "DataTable type does not match !!" ), &TitleText );
		return;
	}

	TArray<UPackage*> PackagesToSave;

	// データテーブルをリインポート
	if( FReimportManager::Instance()->Reimport( DataTable, false, true ) )
	{
		// リインポートに成功したデータテーブルを保存対象に追加
		PackagesToSave.Add( DataTable->GetOutermost() );
	}

	StageSequenceMap.Empty();

	// データテーブルの行の要素を配列で取得
	TArray RowNames = DataTable->GetRowNames();
	
	// 行の数だけループ
	for (int i = 0; i < RowNames.Num(); i++)
	{
		// １行分の構造体を取得
		FStageSequenceData_TableRow* TableRow = DataTable->FindRow<FStageSequenceData_TableRow>(RowNames[i], FString());

		// 実際にゲーム上で使いやすいようにデータを加工する
		FStageSequenceData StageSequenceData;
		StageSequenceData.StageNumber = TableRow->StageNumber;
		StageSequenceData.TimeSecond = TableRow->TimeSecond;
		StageSequenceData.SpawnLocation = TableRow->SpawnLocation;
		StageSequenceData.ShootDirection = TableRow->ShootDirection;
		StageSequenceData.ShootSpeed = TableRow->ShootSpeed;

		// Mapに追加する
		StageSequenceMap.Add(i, StageSequenceData);
	}

	// データアセットに編集フラグを追加
	MarkPackageDirty();

	// データアセットを保存対象に追加
	PackagesToSave.Add( GetOutermost() );

	// 関連アセットを全て保存（SourceControl使用時はチェックアウトするかメッセージウィンドウを出す）
	// ファイル編集フラグ（Dirty)が付いてるもののみを保存対象にしたいので第一引数はtrue
	// 保存する際に確認のメッセージウィンドウを出さない場合は第二引数をfalseにする
	FEditorFileUtils::PromptForCheckoutAndSave( PackagesToSave, true, true );

#endif
}
#undef LOCTEXT_NAMESPACE
