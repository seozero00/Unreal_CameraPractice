// MyCameraActor.cpp
#include "MyCameraActor.h"
#include "Engine/Console.h"

// 전역 변수 초기화
float DeltaRoll = 0.0f;
float DeltaPitch = 0.0f;
float DeltaYaw = 0.0f;
float DeltaX = 0.0f;
float DeltaY = 0.0f;
float DeltaZ = 0.0f;

AMyCameraActor::AMyCameraActor()
{
    PrimaryActorTick.bCanEverTick = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    RootComponent = CameraComponent;
}

void AMyCameraActor::BeginPlay()
{
    Super::BeginPlay();

    // 콘솔 명령어 처리를 위한 델리게이트 생성 및 AdjustCameraConsoleCommand 함수 바인딩
    FConsoleCommandWithArgsDelegate CameraCommandDelegate;
    CameraCommandDelegate.BindUObject(this, &AMyCameraActor::CameraConsoleCommand);

    IConsoleManager::Get().RegisterConsoleCommand(
        TEXT("Camera"),
        CameraCommandDelegate
    );
}

void AMyCameraActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyCameraActor::CameraConsoleCommand(const TArray<FString>& Args)
{
    if (Args.Num() != 6)
    {
        UE_LOG(LogTemp, Warning, TEXT("Camera <DeltaRoll> <DeltaPitch> <DeltaYaw> <DeltaX> <DeltaY> <DeltaZ>"));
        return;
    }

    DeltaRoll = FCString::Atof(*Args[0]) * 100;
    DeltaPitch = FCString::Atof(*Args[1]) * 100;
    DeltaYaw = FCString::Atof(*Args[2]) * 100;
    DeltaX = FCString::Atof(*Args[3]) * 100;
    DeltaY = FCString::Atof(*Args[4]) * 100;
    DeltaZ = FCString::Atof(*Args[5]) * 100;

    AdjustCamera();
}

void AMyCameraActor::AdjustCamera()
{
    FRotator CurrentRotation = CameraComponent->GetComponentRotation();
    FVector CurrentLocation = CameraComponent->GetComponentLocation();

    CurrentRotation.Roll += DeltaRoll;
    CurrentRotation.Pitch += DeltaPitch;
    CurrentRotation.Yaw += DeltaYaw;

    CurrentLocation.X += DeltaX;
    CurrentLocation.Y += DeltaY;
    CurrentLocation.Z += DeltaZ;

    CameraComponent->SetWorldRotation(CurrentRotation);
    CameraComponent->SetWorldLocation(CurrentLocation);
}
