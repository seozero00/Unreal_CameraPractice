#include "MyCameraActor.h"
#include "Engine/Console.h"

// Sets default values
AMyCameraActor::AMyCameraActor()
{
    PrimaryActorTick.bCanEverTick = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    RootComponent = CameraComponent;
}

void AMyCameraActor::BeginPlay()
{
    Super::BeginPlay();

    FConsoleCommandWithArgsDelegate ConsoleCommandDelegate;
    ConsoleCommandDelegate.BindUObject(this, &AMyCameraActor::AdjustCameraRotationConsoleCommand);
    IConsoleManager::Get().RegisterConsoleCommand(
        TEXT("AdjustCamera"),
        TEXT("Adjust camera rotation with provided roll, pitch, yaw values."),
        ConsoleCommandDelegate
    );
}

void AMyCameraActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

FRotator AMyCameraActor::GetCameraRotation() const
{
    return CameraComponent->GetComponentRotation();
}

void AMyCameraActor::AdjustCameraRotationConsoleCommand(const TArray<FString>& Args)
{
    if (Args.Num() != 3)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid input. Usage: AdjustCamera <DeltaRoll> <DeltaPitch> <DeltaYaw>"));
        return;
    }

    float DeltaRoll = FCString::Atof(*Args[0]);
    float DeltaPitch = FCString::Atof(*Args[1]);
    float DeltaYaw = FCString::Atof(*Args[2]);

    AdjustCameraRotation(DeltaRoll, DeltaPitch, DeltaYaw);
}

void AMyCameraActor::AdjustCameraRotation(float DeltaRoll, float DeltaPitch, float DeltaYaw)
{
    FRotator CurrentRotation = CameraComponent->GetComponentRotation();

    CurrentRotation.Roll += DeltaRoll;
    CurrentRotation.Pitch += DeltaPitch;
    CurrentRotation.Yaw += DeltaYaw;

    CameraComponent->SetWorldRotation(CurrentRotation);
}