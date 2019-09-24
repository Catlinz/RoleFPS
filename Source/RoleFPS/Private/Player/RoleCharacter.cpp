// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RoleCharacter.h"

// Sets default values
ARoleCharacter::ARoleCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoleCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARoleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

