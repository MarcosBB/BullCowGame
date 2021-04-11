// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetUp();
	void Dica(FString palavra);
	FString NovaPalavra();
	void GameOver(bool bResultado, FString palavra);
	void Header();
	void processaResposta(FString input);
	//bool IsIsogram(FString palavra) const;

 	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 Lives;
	bool bGanhou;
	bool bPrimeiraVez;
	bool bGameOver;
};

