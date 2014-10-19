

#pragma once

#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOKYO_API APlayerCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	UFUNCTION()
	void OnStartJump();

	UFUNCTION()
	void OnStopJump();

	UFUNCTION()
	void MoveRight(float Val);

	UFUNCTION()
	void Turn();
	
	UFUNCTION()
	void OnFire();

public:

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	TSubobjectPtr<USkeletalMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

protected:

	//camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<UCameraComponent> CustomCameraComponent;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Change direction in which character is looking at
	void ChangeDirection();
};
