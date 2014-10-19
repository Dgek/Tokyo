

#include "Tokyo.h"
#include "PlayerCharacter.h"

#include "Projectile.h"

APlayerCharacter::APlayerCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	CustomCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	CustomCameraComponent->AttachParent = CapsuleComponent;

	//create mesh
	MeshComponent = PCIP.CreateDefaultSubobject <USkeletalMeshComponent>(this, TEXT("MeshComponent"));
	MeshComponent->SetOnlyOwnerSee(true);
	MeshComponent->AttachParent = CustomCameraComponent;
	MeshComponent->bCastDynamicShadow = true;
	MeshComponent->CastShadow = true;
}
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::OnStopJump);
	InputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::OnFire);
	InputComponent->BindAction("Turn", IE_Pressed, this, &APlayerCharacter::Turn);
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::OnStartJump()
{
	bPressedJump = true;
}

void APlayerCharacter::OnStopJump()
{
	bPressedJump = false;
}

void APlayerCharacter::OnFire()
{
	UWorld* World = GetWorld();
	if (World)
	{
		const FVector SpawnPos = GetActorLocation();
		FRotator SpawnRot = Controller->GetControlRotation();
		SpawnRot.Pitch += 15.0f;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		AProjectile* const Projectile = World->SpawnActor<AProjectile>(ProjectileClass, SpawnPos, SpawnRot, SpawnParams);
		if (Projectile)
		{
			const FVector LaunchDir = SpawnRot.Vector();
			Projectile->InitVelocity(LaunchDir);
		}
	}
}

void APlayerCharacter::Turn()
{

}