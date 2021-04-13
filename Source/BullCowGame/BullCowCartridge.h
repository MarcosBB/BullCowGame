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
	FString NovaPalavra() const;
	void GameOver(const bool& bResultado, const FString& palavra);
	void Header(const FString& Input) const;
	void processaResposta(const FString& input);
	TArray<FString> achaPalavrasValidas(const TArray<FString>& Lista) const;
	bool IsIsogram(const FString& palavra) const;
	void GetBullCows(const FString& Input, int32& ContadorDeBulls, int32& ContadorDeCows) const;

 	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 Lives;
	bool bGanhou;
	bool bPrimeiraVez;
	bool bGameOver;
	TArray<FString> PalavrasValidas;
};

