// Fill out your copyright notice in the Description page of Project Settings.


#include "RoleFPS.h"

// Sets default values
ARoleCharacter::ARoleCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	const auto CapsuleComponent = GetCapsuleComponent();

	// Setup the First person mesh for the character.
	// The third person mesh is accessed via GetMesh() since it is the default 
	// mesh for the actor.
	Mesh1P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("PawnMesh1P"));
	Mesh1P->SetupAttachment(CapsuleComponent);
	Mesh1P->bOnlyOwnerSee = true;
	Mesh1P->bOwnerNoSee = false;
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->bReceivesDecals = false;
	Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh1P->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	Mesh1P->SetCollisionObjectType(ECC_Pawn);
	Mesh1P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh1P->SetCollisionResponseToAllChannels(ECR_Ignore);

	// Setup the Third person mesh for the character.  This is the 
	// default mesh on the Actor.
	const auto Mesh3P = GetMesh();
	
	Mesh3P->bOnlyOwnerSee = false;
	Mesh3P->bOwnerNoSee = true;
	Mesh3P->bReceivesDecals = false;
	Mesh3P->SetCollisionObjectType(ECC_Pawn);
	Mesh3P->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh3P->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	Mesh3P->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	Mesh3P->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// Set the collision responses for the capsule bounds component
	CapsuleComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	CapsuleComponent->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	CapsuleComponent->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Ignore);

}

bool ARoleCharacter::IsAlive() const {
	return true;
}

bool ARoleCharacter::IsFirstPerson() const {
	return IsAlive() && Controller && Controller->IsLocalPlayerController();
}

void ARoleCharacter::PostInitializeComponents() {
	Super::PostInitializeComponents();

	UpdatePawnMeshesForView();
}

void ARoleCharacter::UpdatePawnMeshesForView() {
	bool const bFirstPerson = IsFirstPerson();

	const auto Mesh3P = GetMesh();

	if (bFirstPerson) {
		// Make sure only the first person mesh will be updating animations and bones.
		Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
		Mesh3P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	}
	else {
		// Make sure only the third person mesh will be updating animations and bones.
		Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
		Mesh3P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	}

	// Make sure we display only the correct mesh.
	Mesh1P->SetOwnerNoSee(!bFirstPerson);
	Mesh3P->SetOnlyOwnerSee(bFirstPerson);
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

