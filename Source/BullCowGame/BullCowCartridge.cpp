// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    PalavrasValidas = achaPalavrasValidas(todasAsPalavras);
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
        Header(PlayerInput);
        bPrimeiraVez = false;
    }

    if (bGameOver) {
        GameOver(bGanhou, HiddenWord);
    }
    else {  //Se não for gameOver
        Header(PlayerInput);
    }
}

FString UBullCowCartridge::NovaPalavra() const {
    return PalavrasValidas[FMath::RandRange(0, PalavrasValidas.Num() - 1)];
}

void UBullCowCartridge::SetUp() {

    //VARIÁVEIS
    Lives = 20;
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

void UBullCowCartridge::Header(const FString& Input) const {
    ClearScreen();
    //PrintLine(TEXT("Palavra: %s"), *HiddenWord);
    PrintLine(TEXT("A palavra tem %i letras."), HiddenWord.Len());

    FBullCowCount Pontuacao = GetBullCows(Input);
    if (IsIsogram(Input)) {
        PrintLine(TEXT("Vidas: %i       Bulls: %i      Cows: %i"), Lives, Pontuacao.Bulls, Pontuacao.Cows);
    }
    else {
        PrintLine(TEXT("Vidas: %i       !!!DEVE ser um isograma!!!"), Lives);
    }

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
    TArray<FString> ListaDePalavrasValidas;
    for (int32 i = 0; i < Lista.Num(); i++) {
        if (Lista[i].Len() >= 4 && Lista[i].Len() <=8 && IsIsogram(Lista[i])) {
            ListaDePalavrasValidas.Emplace(Lista[i]);
        }
    }
    return ListaDePalavrasValidas;
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

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Input) const {
    //Cow = letra que existe na palavra mas não está na posição certa
    //Bull = letra que existe na palavra e está na posição correta
    
    FBullCowCount Contador;

    for (int32 IndiceInput = 0; IndiceInput < Input.Len(); IndiceInput++) {
        if (Input[IndiceInput] == HiddenWord[IndiceInput]) {
            Contador.Bulls++;
            continue;
        }

        for (size_t IndiceHidden = 0; IndiceHidden < HiddenWord.Len(); IndiceHidden++) {
            if (Input[IndiceInput] == HiddenWord[IndiceHidden]) {
                Contador.Cows++;
                break;
            }
        }
    }
    return Contador;
}