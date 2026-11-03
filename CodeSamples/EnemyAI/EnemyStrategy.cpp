
void UEnemyStrategy::InitNameAndData(FName Name)
{
	StrategyName = Name;
	Data = nullptr;

	StrategyScoreDataTable = LoadObject<UDataTable>(nullptr,TEXT("/Game/Dynamic/Enemies/StrategyTable.StrategyTable"));
	if (!IsValid(StrategyScoreDataTable))
	{
		UE_LOG(LogTemp, Error, TEXT("StrategyScoreDataTable not found"));
		return;
	}
	Data = StrategyScoreDataTable->FindRow<FStrategyScoreData>(StrategyName, TEXT(""));
	if (!Data)
	{
		UE_LOG(LogTemp, Error, TEXT("Strategy %s not found"), *StrategyName.ToString());
	}
}

int UEnemyStrategy::ResultsScore(const int32 PlayerResult, const int32 EnemyResult)
{
	if (!Data) return 0;
	
	const int32 Difference =  FMath::Clamp(EnemyResult - PlayerResult, -5, 5);
	
	switch (Difference)
	{
	case  5: return Data->Diff_Plus_5;
	case  4: return Data->Diff_Plus_4;
	case  3: return Data->Diff_Plus_3;
	case  2: return Data->Diff_Plus_2;
	case  1: return Data->Diff_Plus_1;
	case  0: return Data->Diff_0;
	case -1: return Data->Diff_Minus_1;
	case -2: return Data->Diff_Minus_2;
	case -3: return Data->Diff_Minus_3;
	case -4: return Data->Diff_Minus_4;
	case -5: return Data->Diff_Minus_5;
	default: return 0;
	}
}

int UEnemyStrategy::BlindScore(const int32 EnemyResult)
{
	if (!Data) return 0;
	
	switch (EnemyResult)
	{
	case 6: return Data->Blind_6;
	case 5: return Data->Blind_5;
	case 4: return Data->Blind_4;
	case 3: return Data->Blind_3;
	case 2: return Data->Blind_2;
	case 1: return Data->Blind_1;
	default: return 0;
	}
}
