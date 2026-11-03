
void ADialogueManager::StartDialogue(UDialogueData* Data)
{
	if (!Data || Data->DialogueLines.Num() == 0) return;
	
	CurrentDialogue = Data;
	CurrentLineIndex = 0;
	
	if (DialogueWidgetClass && !DialogueWidget)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (!PC) return;
	
		DialogueWidget = CreateWidget<UDialogueWidget>(PC, DialogueWidgetClass);
		if (!DialogueWidget) return;
		
		DialogueWidget->SetDialogueManager(this);
		DialogueWidget->AddToViewport();
	}
	ShowLine(0);
}

void ADialogueManager::ShowLine(int32 Index)
{
	
	if (!CurrentDialogue || !CurrentDialogue->DialogueLines.IsValidIndex(Index))
	{
		EndDialogue();
		return;
	}

	CurrentLineIndex = Index;
	const FDialogueLine& Line = CurrentDialogue->DialogueLines[Index];

	if (DialogueWidget)
	{
		DialogueWidget->UpdateDialogue(
			Line.SpeakerName, 
			Line.DialogueText, 
			Line.Choices, 
			!Line.Choices.IsEmpty());
	}
}

void ADialogueManager::Continue()
{
	if (!CurrentDialogue || !CurrentDialogue->DialogueLines.IsValidIndex(CurrentLineIndex)) return;

	const FDialogueLine& Line = CurrentDialogue->DialogueLines[CurrentLineIndex];

	if (Line.NextLineIndex == -1)
		EndDialogue();
	else
		ShowLine(Line.NextLineIndex);
}

void ADialogueManager::SelectChoice(int32 ChoiceIndex)
{
	if (!CurrentDialogue || !CurrentDialogue->DialogueLines.IsValidIndex(CurrentLineIndex)) return;

	const FDialogueLine& Line = CurrentDialogue->DialogueLines[CurrentLineIndex];

	if (!Line.Choices.IsValidIndex(ChoiceIndex)) return;

	int32 Next = Line.Choices[ChoiceIndex].NextLineIndex;

	if (Next == -1)
		EndDialogue();
	else
		ShowLine(Next);
}

void ADialogueManager::EndDialogue()
{
	if (DialogueWidget)
	{
		DialogueWidget->RemoveFromParent();
		DialogueWidget = nullptr;
	}
	CurrentDialogue = nullptr;
	CurrentLineIndex = INDEX_NONE;
	OnDialogueEnd.Broadcast();
}