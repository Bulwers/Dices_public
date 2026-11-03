
USTRUCT(BlueprintType)
struct FDialogueChoice
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ChoiceText;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 NextLineIndex;
};

USTRUCT(BlueprintType)
struct FDialogueLine
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SpeakerName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DialogueText;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FDialogueChoice> Choices;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 NextLineIndex = -1;
};

UCLASS(BlueprintType)
class DICES_API UDialogueData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FDialogueLine> DialogueLines;
	
};
