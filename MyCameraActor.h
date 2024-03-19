#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "MyCameraActor.generated.h"

extern float RollAdjustment;
extern float PitchAdjustment;
extern float YawAdjustment;
extern float XAdjustment;
extern float YAdjustment;
extern float ZAdjustment;

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

private:
    void AdjustAndUpdateCamera(float DeltaTime);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
        UCameraComponent* CameraComponent;

    float TimeSinceStart; // 시작 이후 경과 시간(절대시간이라고 생각하면 ㄷ편함)
    float Psi; // psi 값 (각도)
    float InitialSpeedMPS; // 이동 속도를 저장할 변수 추가)
};
