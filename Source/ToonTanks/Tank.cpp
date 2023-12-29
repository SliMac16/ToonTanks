// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"



ATank::ATank()
{
    
    Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	Arm->SetupAttachment(RootComponent);


    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Arm);

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("Move"), this, &ATank::Move);
}

void ATank::Move(float Value)
{
    UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);

    FVector DeltaLocation = FVector::ZeroVector;

    DeltaLocation.X = Value;

    AddActorLocalOffset(DeltaLocation);
    
}

