#pragma once

#include "CoreMinimal.h"
#include "StrategyScoreData.generated.h"

USTRUCT(BlueprintType)
struct FStrategyScoreData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Diff_Plus_5 = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Diff_Plus_4 = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Diff_Plus_3 = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Diff_Plus_2 = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Diff_Plus_1 = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Diff_0 = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Diff_Minus_1 = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Diff_Minus_2 = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Diff_Minus_3 = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Diff_Minus_4 = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Diff_Minus_5 = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Blind_6 = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Blind_5 = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Blind_4 = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Blind_3 = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Blind_2 = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Blind_1 = 0;
};
