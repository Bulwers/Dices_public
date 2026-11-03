
void UEnemyDecisionComponent::SetStrategy(const FName StrategyName)
{
	Strategy = NewObject<UEnemyStrategy>(this);

	if (!IsValid(Strategy))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create Strategy"));
		return;
	}
	Strategy->InitNameAndData(StrategyName);
}

int UEnemyDecisionComponent::FindSlotToPlaceDice(
	const TArray<ABaseDice*>& PlayerDicesOnTable,
	const TArray<ABaseDice*>& EnemyDicesOnTable)
{
	const int32 SlotsNum = FMath::Min(PlayerDicesOnTable.Num(), EnemyDicesOnTable.Num());
	for (int32 i = 0; i < SlotsNum; i++)
	{
		if (PlayerDicesOnTable[i] == nullptr && EnemyDicesOnTable[i] == nullptr)
		{
			EEnemyPlacementDecision = EDicePlacementDecision::BlindPlacement;
			return i;
		}
		if (PlayerDicesOnTable[i] != nullptr && EnemyDicesOnTable[i] == nullptr)
		{
			EEnemyPlacementDecision = EDicePlacementDecision::KnowingPlacement;
			return i;
		}
	}
	
	return INDEX_NONE;
}

ABaseDice* UEnemyDecisionComponent::ChoosingDiceToPutOnTable(
	const TArray<ABaseDice*>& PlayerDicesOnTable,
	const TArray<ABaseDice*>& EnemyDices,
	const int32 Slot)
{
	if (!IsValid(Strategy))
	{
		return nullptr;
	}
	
	TArray<int32> EnemyAvailableDices;
	for (int32 i = 0; i < EnemyDices.Num(); i++)
	{
		if (IsValid(EnemyDices[i]) && !EnemyDices[i]->bIsEnemyChosen)
		{
			EnemyAvailableDices.Add(i);
		}
	}
	if (EnemyAvailableDices.IsEmpty())
	{
		return nullptr;
	}
	
	int32 BestResultScore = -1;
	int32 BestResultIndex = INDEX_NONE;
	
	switch (EEnemyPlacementDecision)
	{
	case EDicePlacementDecision::KnowingPlacement:
		if (!PlayerDicesOnTable.IsValidIndex(Slot) ||
			!IsValid(PlayerDicesOnTable[Slot]))
		{
			return nullptr;
		}
		for (const int32 Index : EnemyAvailableDices)
		{
			int32 Score = Strategy->ResultsScore(PlayerDicesOnTable[Slot]->Result(), EnemyDices[Index]->Result());
			if (Score > BestResultScore)
			{
				BestResultScore = Score;
				BestResultIndex = Index;
			}
		}
		break;
	case EDicePlacementDecision::BlindPlacement:
		for (const int32 Index : EnemyAvailableDices)
		{
			int32 Score = Strategy->BlindScore(EnemyDices[Index]->Result());
			if (Score > BestResultScore)
			{
				BestResultScore = Score;
				BestResultIndex = Index;
			}
		}
		break;
	}

	if (BestResultIndex == INDEX_NONE)
	{
		return nullptr;
	}
	return EnemyDices[BestResultIndex];
}

TPair<ABaseDice*, int32> UEnemyDecisionComponent::GetDiceToPlace(
	const TArray<ABaseDice*>& PlayerDicesOnTable,
	const TArray<ABaseDice*>& EnemyDicesOnTable,
	const TArray<ABaseDice*>& EnemyDicesOnHand)
{
	const int32 Slot = FindSlotToPlaceDice(PlayerDicesOnTable,EnemyDicesOnTable);
	if (Slot == INDEX_NONE)
	{
		return TPair<ABaseDice*, int32>(nullptr, INDEX_NONE);
	}
	ABaseDice* Dice = ChoosingDiceToPutOnTable(PlayerDicesOnTable, EnemyDicesOnHand, Slot);
	return TPair<ABaseDice*, int32>(Dice, Slot);
}
