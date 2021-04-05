// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"


using namespace std;

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetUp();
    
    //RECEPÇÃO
    PrintLine(TEXT("Bem vindo ao Bull Cown!"));
    PrintLine(TEXT("Pressione ENTER para comecar: "));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    //Checando a resposta do jogador
    if (!bPrimeiraVez) {
        processaResposta(Input);
        
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
    FString newWord[5] = { TEXT("agua"), TEXT("cadeira"), TEXT("palavra"), TEXT("vaca"), TEXT("lapis")};
    return newWord[rand() % 5];

}

void UBullCowCartridge::SetUp() {

    //VARIÁVEIS
    Lives = 10;
    HiddenWord = NovaPalavra();
    bPrimeiraVez = true;
    bGameOver = false;
}

void UBullCowCartridge::Dica(FString palavra) {
    PrintLine(TEXT("Tem %i letras."), HiddenWord.Len());

    if (palavra == "agua") {
        PrintLine(TEXT("Elemento da naturaza."));
    }
    if (palavra == "cadeira") {
        PrintLine(TEXT("Junto da mesa."));
    }
    if (palavra == "palavra") {
        PrintLine(TEXT("E uma palavra."));
    }
    if (palavra == "vaca") {
        PrintLine(TEXT("Marida do vaco."));
    }
    if (palavra == "lapis") {
        PrintLine(TEXT("E melhor que caneta"));
    }

}

void UBullCowCartridge::GameOver(bool bResultado, FString Palavra) {
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
    Dica(HiddenWord);
}

void UBullCowCartridge::processaResposta(FString input){
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

bool UBullCowCartridge::IsIsogram(FString palavra) const {
    /*for (size_t i = 0; i < length; i++) {

    }
    */
    return true;
}