// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "LIFE_GAME.generated.h"

UCLASS()
class T01LIFE_API ALIFE_GAME : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALIFE_GAME();

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Width in blocks")
  int W;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Height in blocks")
  int H;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration File")
  FName FN;

  UFUNCTION(BlueprintCallable, Category = "LIFE")
  void PutPoint(int X, int Y)
  {
    Frame1[Y * W + X] = 1;
    return;
  }

  UFUNCTION(BlueprintCallable, Category = "LIFE")
  void GetFrame(TArray<FVector> &a_out, TArray<FVector> &b_out)
  {
    Frame2.clear();
    Frame2.resize(W * H);
    for (int i = 0; i < H; i++)
      for (int j = 0; j < W; j++)
      {
        int ck = CheckNear(j, i);
        if (ck < 2)
          Frame2[i * W + j] = 0;
        else if (ck > 3)
          Frame2[i * W + j] = 0;
        else if (ck == 3)
          Frame2[i * W + j] = 1;
        else if (Frame1[i * W + j] == 1 && ck == 2)
          Frame2[i * W + j] = 1;
        else
          Frame2[i * W + j] = 0;
      }
    for (int i = 0; i < H * W; i++)
      if (Frame2[i] == 1)
        Frame1[i] = 1;
      else if (Frame2[i] == 0 && Frame1[i] != 1)
        Frame1[i] = 0;
      else
        Frame1[i] = 2;
    TArray<FVector> Vec;
    TArray<FVector> Vec2;
    for (int i = 0; i < H; i++)
      for (int j = 0; j < W; j++)
        if (Frame1[i * W + j] == 1)
          Vec.Push(FVector(j, i, 0));
        else if (Frame1[i * W + j] == 2)
          Vec2.Push(FVector(j, i, 0));
    a_out = Vec;
    b_out = Vec2;
    return;
  }

  std::vector<int> Frame1; // show
  std::vector<int> Frame2; // change

  int GetEl(int y, int x)
  {
    x = (x + W) % W;
    y = (y + H) % H;
    return Frame1[y * W + x] == 1;
  }

  int CheckNear(int x, int y)
  {
    int k = 0;
    if (GetEl(y - 1, x - 1))
      ++k;
    if (GetEl(y, x - 1))
      ++k;
    if (GetEl(y - 1, x))
      ++k;
    if (GetEl(y - 1, x + 1))
      ++k;
    if (GetEl(y + 1, x - 1))
      ++k;
    if (GetEl(y + 1, x))
      ++k;
    if (GetEl(y, x + 1))
      ++k;
    if (GetEl(y + 1, x + 1))
      ++k;
    return k;
  }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
