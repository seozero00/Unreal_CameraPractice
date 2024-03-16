#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "MyCameraActor.generated.h"

UCLASS()
class FSIM_API AMyCameraActor : public AActor
{
    GENERATED_BODY()

public:
    AMyCameraActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    FRotator GetCameraRotation() const;

    void AdjustCameraRotationConsoleCommand(const TArray<FString>& Args);

    void AdjustCameraRotation(float DeltaRoll, float DeltaPitch, float DeltaYaw);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
        UCameraComponent* CameraComponent;
};