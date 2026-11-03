
void UBrawlManager::StartTurn()
{
	if (!IsValid(Player) || !IsValid(Enemy) || !IsValid(TurnManager)) 
	{
		UE_LOG(LogTemp, Error, TEXT("BrawlManager: Player, Enemy or TurnManager is not valid."));
		return;
	}

	if (bIsNewEnemy)
	{
		bIsPlayerFirst = FMath::RandBool();
		TurnManager->WhoseFirst(bIsPlayerFirst);
	}

	if (TurnManager->IsPlayerTurn())
	{
		SetPlacement(true, false, true);
		UE_LOG(LogTemp, Warning, TEXT("BrawlManager: Player First"));
	}
	else
	{
		SetPlacement(false, true, false );
		UE_LOG(LogTemp, Warning, TEXT("BrawlManager: Enemy First"));
	}
	CurrentState = ECurrentState::DicePlacement;
}

bool UBrawlManager::IsBoardFull() const
{
	if (!IsValid(Player) || !IsValid(Enemy)) return false;
	if (Player->PlayerDicesOnTable.Num() != BoardSize || Enemy->EnemyDicesOnTable.Num() != BoardSize) return false;

	for (int32 i = 0; i < BoardSize; i++)
	{
		if (!IsValid(Player->PlayerDicesOnTable[i]) || !IsValid(Enemy->EnemyDicesOnTable[i]))
		{
			return false;
		}
	}
	return true;
}

void UBrawlManager::DicesPlacementSequence(ABaseDice* PlacedDice)
{
	if (CurrentState != ECurrentState::DicePlacement) return;
	if (!IsValid(PlacedDice) || !IsValid(Player) || !IsValid(Enemy) || !IsValid(TurnManager)) return;

	if (Player->PlayerDicesOnTable.Num() != BoardSize 
		|| Enemy->EnemyDicesOnTable.Num() != BoardSize 
		|| Enemy->PlayerDicesOnTable.Num() != BoardSize)
	{
		UE_LOG(LogTemp, Error, TEXT("BrawlManager: Invalid board size"));
		return;
	}

	static const FName BigDice(TEXT("BigDice"));
	DicePlaced += PlacedDice->ActorHasTag(BigDice) ? 2 : 1;
	
	for (int32 i = 0; i < BoardSize; i++)
	{
		Enemy->PlayerDicesOnTable[i] = Player->PlayerDicesOnTable[i];
		if (Enemy->EnemyDicesOnTable[i])
		{
			EnemyResults[i] = (Enemy->EnemyDicesOnTable[i]->Sum());
		}
		if (Player->PlayerDicesOnTable[i])
		{
			PlayerResults[i] = (Player->PlayerDicesOnTable[i]->Sum());
		}
	}
	
	if (IsBoardFull())
	{
		SetPlacement(false, false, true);
		bIsPlayerFirst = !bIsPlayerFirst;
		CurrentState = ECurrentState::ScoreResolve;
		return;
	}

	if (SwapPoints.Contains(DicePlaced))
	{
		TurnManager->SwapOrder();
		UE_LOG(LogTemp, Warning, TEXT("BrawlManager: Swap Order"));
		if (TurnManager->IsPlayerTurn())
		{
			SetPlacement(true, false, true);
			UE_LOG(LogTemp, Warning, TEXT("BrawlManager: Player turn"));
		}
		else
		{
			SetPlacement(false, true, false);
			UE_LOG(LogTemp, Warning, TEXT("BrawlManager: Enemy turn"));
		}
	}
}

void UBrawlManager::CheckingResults()
{
	if (CurrentState != ECurrentState::ScoreResolve) return;
	if (!IsValid(Player) || !IsValid(Enemy) || !IsValid(GameState)) return;
	
	if (Player->PlayerDicesOnTable.Num() != BoardSize
		|| Enemy->EnemyDicesOnTable.Num() != BoardSize)
	{
		UE_LOG(LogTemp, Error, TEXT("BrawlManager: Invalid board size"));
		return;
	}

	int32 PlayerPoints = 0;
	int32 EnemyPoints = 0;
	static const FName Fang(TEXT("Fang"));

	for (int32 i = 0; i < BoardSize; i++)
	{
		ABaseDice* PlayerDice = Player->PlayerDicesOnTable[i];
		ABaseDice* EnemyDice = Enemy->EnemyDicesOnTable[i];

		if (!IsValid(PlayerDice) || !IsValid(EnemyDice)) continue;
		if (!PlayerDice->bIsVisible && !EnemyDice->bIsVisible) continue;
		if (PlayerDice->ActorHasTag(Fang) || EnemyDice->ActorHasTag(Fang)) continue;
		
		const int32 Difference = PlayerDice->Sum() - EnemyDice->Sum();
		if (Difference <= -2) EnemyPoints++;
		else if (Difference >= 2) PlayerPoints++;
	}

	if (PlayerPoints > EnemyPoints) BigPlayerPoints++;
	else if (EnemyPoints > PlayerPoints) BigEnemyPoints++;
	
	GameState->TurnCountIncrease();
	bIsNewEnemy = false;
}
