
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogueData.h"
#include "DialogueManager.generated.h"

class UDialogueWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnd);

UCLASS()
class DICES_API ADialogueManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ADialogueManager();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	TSubclassOf<UUserWidget> DialogueWidgetClass;
	
	UPROPERTY(BlueprintAssignable)
	FOnDialogueEnd OnDialogueEnd;
	
	UFUNCTION(BlueprintCallable)
	void StartDialogue(UDialogueData* Data);
	
	UFUNCTION(BlueprintCallable)
	void Continue();
	
	UFUNCTION(BlueprintCallable)
	void SelectChoice(int32 ChoiceIndex);
	
private:
	UPROPERTY()
	TObjectPtr<UDialogueData> CurrentDialogue;
	
	UPROPERTY()
	TObjectPtr<UDialogueWidget> DialogueWidget;
	
	int32 CurrentLineIndex;
	
	void ShowLine(int32 Index);
	void EndDialogue();
	
protected:
	virtual void BeginPlay() override;

public:	

};
