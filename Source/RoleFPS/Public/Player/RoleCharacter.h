// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RoleCharacter.generated.h"

UCLASS()
class ROLEFPS_API ARoleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARoleCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Update which meshes are used based on third or first person view. */
	void UpdatePawnMeshesForView();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Do things like spawn inventory and update pawn meshes. */
	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Check if the pawn is still alive. */
	bool isAlive() const;

	/** Get the camera view type (First or Third person) */
	UFUNCTION(BlueprintCallable, Category = Mesh)
	virtual bool IsFirstPerson() const;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;
};
