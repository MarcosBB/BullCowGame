// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    
    SetUp();
    
    //RECEPÇÃO
    PrintLine(TEXT("Bem vindo ao Bull Cown!"));
    PrintLine(TEXT("Pressione ENTER para comecar:  "));
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    //Checando a resposta do jogador
    if (!bPrimeiraVez) {
        processaResposta(PlayerInput);

    }
    else {  //Se for a primeira vez
        Header();
        bPrimeiraVez = false;
    }

    if (bGameOver) {
        GameOver(bGanhou, HiddenWord);
    }
    else {  //Se não for gameOver
        Header();
    }
}

FString UBullCowCartridge::NovaPalavra() {
    return achaPalavrasValidas(todasAsPalavras)[FMath::RandRange(0, achaPalavrasValidas(todasAsPalavras).Num() - 1)];
}

void UBullCowCartridge::SetUp() {

    //VARIÁVEIS
    Lives = 10;
    HiddenWord = NovaPalavra();
    bPrimeiraVez = true;
    bGameOver = false;
}

void UBullCowCartridge::GameOver(const bool& bResultado, const FString& Palavra) {
    ClearScreen();

    if (!bResultado){
        PrintLine(TEXT("Perdeu"));
        PrintLine(TEXT("A palavra era %s."), *Palavra);
        PrintLine(TEXT("Digite ENTER para tentar de novo..."));
    }

    if (bResultado) {
        PrintLine(TEXT("Ganhou"));
        PrintLine(TEXT("Digite ENTER para continuar..."));
    }

    SetUp();
}

void UBullCowCartridge::Header() {
    ClearScreen();
    PrintLine(TEXT("Voce tem %i vidas."), Lives);
    PrintLine(TEXT("Tem %i letras."), HiddenWord.Len());
}

void UBullCowCartridge::processaResposta(const FString& input){
    if (input == HiddenWord) {
        bGanhou = true;
        bGameOver = true;
    }
    else {
        if (Lives > 0) {
            Lives = Lives - 1;
        }

        if (Lives <= 0) {
            bGanhou = false;
            bGameOver = true;
        }
    }
}

TArray<FString> UBullCowCartridge::achaPalavrasValidas(const TArray<FString>& Lista) const {
    TArray<FString> palavrasValidas;
    for (int32 i = 0; i < Lista.Num(); i++) {
        if (Lista[i].Len() >= 4 && Lista[i].Len() <=8 && IsIsogram(Lista[i])) {
            palavrasValidas.Emplace(Lista[i]);
        }
    }
    return palavrasValidas;
}

bool UBullCowCartridge::IsIsogram(const FString& palavra) const {
    for (int32 i = 0; i < palavra.Len(); i++) {
        for (int32 comparacao = i + 1; comparacao < palavra.Len(); comparacao++) {
            if (palavra[i] == palavra[comparacao]) {
                return false;
            }
        }
    }
    
    return true;
}
