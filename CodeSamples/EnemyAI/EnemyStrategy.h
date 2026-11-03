
#pragma once

#include "CoreMinimal.h"
#include "StrategyScoreData.h"
#include "EnemyStrategy.generated.h"

UCLASS()
class DICES_API UEnemyStrategy : public UObject
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION()
	void InitNameAndData(FName Name);
	UFUNCTION(BlueprintCallable)
	virtual int32 ResultsScore(const int32 PlayerResult, const int32 EnemyResult);
	UFUNCTION(BlueprintCallable)
	virtual int32 BlindScore(const int32 EnemyResult);
	
	
private:
	
	UPROPERTY()
	FName StrategyName;
	UPROPERTY()
	TObjectPtr<UDataTable> StrategyScoreDataTable;
	FStrategyScoreData* Data = nullptr;
};
