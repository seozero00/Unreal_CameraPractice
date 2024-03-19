#include "MyCameraActor.h"

// 변수 초기화
float InitialX = 0.0f;  // 초기 x 좌표
float InitialY = 0.0f;  // 초기 y 좌표
float XSpeed = 1.0f;    // x 방향 속도 (1 m/s)
float YSpeed = 1.0f;    // y 방향 속도 (1 m/s)
float MovementFrequency = 10.0f; // 주기 10hz

// Psi 값 설정 (라디안 단위, 여기서는 0도)
float Psi = 0.0f;

void AMyCameraActor::BeginPlay()
{
    Super::BeginPlay();
    TimeSinceStart = GetWorld()->GetTimeSeconds();
}

AMyCameraActor::AMyCameraActor()
{
    // 이 액터를 매 프레임마다 Tick() 호출하도록 설정
    PrimaryActorTick.bCanEverTick = true;

    // 카메라 컴포넌트 생성
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    RootComponent = CameraComponent;

    // 초기 위치 설정
    FVector InitialPosition(InitialX, InitialY, 500.0f); // 초기 위치 설정

    // 현재 카메라의 위치 설정
    CameraComponent->SetWorldLocation(InitialPosition);
}

void AMyCameraActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 값에 따라 위치 조정 및 카메라 위치 업데이트
    AdjustAndUpdateCamera(DeltaTime);
}

void AMyCameraActor::AdjustAndUpdateCamera(float DeltaTime)
{
    // 현재 경과 시간 (현재시간 - 시작 이후 경과 시간)
    float CurrentTime = GetWorld()->GetTimeSeconds() - TimeSinceStart;

    // x, y 좌표 계산 psi 이용
    float CurrentX = InitialX + XSpeed * CurrentTime * FMath::Sin(Psi);
    float CurrentY = InitialY + YSpeed * CurrentTime * FMath::Cos(Psi);

    // 현재 카메라의 위치 설정
    FVector CurrentPosition(CurrentX, CurrentY, 500.0f); // z 좌표는 고도라서 걍,,,일단 500으로 설정

    // 카메라 컴포넌트에 새로운 위치 설정
    CameraComponent->SetWorldLocation(CurrentPosition);
}
