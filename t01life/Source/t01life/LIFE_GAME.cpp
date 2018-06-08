// Fill out your copyright notice in the Description page of Project Settings.

#include "LIFE_GAME.h"
#include <iostream>
#include <fstream>
#include <string>

// Sets default values
ALIFE_GAME::ALIFE_GAME()
{
  // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void ALIFE_GAME::BeginPlay()
{
  Super::BeginPlay();
  Frame1.resize(W * H);
  FString Us = FN.ToString();
  std::string S(TCHAR_TO_UTF8(*Us));
  std::ifstream File(S);
  if (File.bad() || !File.good() || File.fail() || !File.is_open())
  {
    std::ofstream F2(S);
    for (int i = 0; i < H * W; i++)
      if (rand() % 2 == 0)
        Frame1[i] = 1;
      else
        Frame1[i] = 0;
    int32 w, h;
    w = W;
    h = H;
    F2.write((char *)&w, sizeof(int32));
    F2.write((char *)&h, sizeof(int32));
    F2.write((char *)Frame1.data(), W * H * sizeof(int32));
    F2.close();
  }
  else
  {
    int32 w, h;
    File.read((char *)&w, sizeof(int32));
    File.read((char *)&h, sizeof(int32));
    W = w;
    H = h;
    int32 *Buf = new int32[W * H];
    File.read((char *)Buf, W * H * sizeof(int32));
    for (int i = 0; i < W * H; i++)
      Frame1[i] = Buf[i];
    delete[] Buf;
    File.close();
  }
}

// Called every frame
void ALIFE_GAME::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ALIFE_GAME::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

