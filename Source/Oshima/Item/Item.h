// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Item.generated.h"

UENUM()
enum class Operator {ADD, SUBTRACT, DIVIDE, MODULO};

UCLASS()
class OSHIMA_API UItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int id;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString name;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString description;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool isConsumeable;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	Operator operationType;

public:
	UItem();
	void Use();

	FString GetItemName() { return name; }
};
