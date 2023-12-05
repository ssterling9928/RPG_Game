// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Aura_CharacterBase.generated.h"

UCLASS(Abstract)
class RPG_GAME_API AAura_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	
	AAura_CharacterBase();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

};
