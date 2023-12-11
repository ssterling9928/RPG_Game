// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Aura_CharacterBase.h"

// Sets default values
AAura_CharacterBase::AAura_CharacterBase()

{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAura_CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


// Called when the game starts or when spawned
void AAura_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}