// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Aura_CharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"


/**
 * 
 */
UCLASS()
class RPG_GAME_API AAuraEnemy : public AAura_CharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

	AAuraEnemy();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	
};
