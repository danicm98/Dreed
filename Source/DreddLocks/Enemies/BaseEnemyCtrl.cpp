// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCtrl.h"

#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIWaypointGeneral.h"


void ABaseEnemyCtrl::BeginPlay()
{
	Super::BeginPlay();
	enemyPawn = Cast<ABaseEnemy>(GetPawn());
}

bool ABaseEnemyCtrl::DoBasicAttack(FVector targetPosition)
{
#if WITH_EDITOR 
	UE_LOG(LogTemp, Error, TEXT("ABaseEnemyCtlr. La funcion DoBasicAttack ha sido llamada pero no esta implementada "));
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, FString::Printf(TEXT("ABaseEnemyCtlr. La funcion DoBasicAttack ha sido llamada pero no esta implementada")));
#endif
	return false;
}

EPathFollowingRequestResult::Type ABaseEnemyCtrl::moveToPosition(FVector targetPosition)
{
#if WITH_EDITOR 
	UE_LOG(LogTemp, Error, TEXT("ABaseEnemyCtlr. La funcion moveToPosition ha sido llamada pero no esta implementada "));
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, FString::Printf(TEXT("ABaseEnemyCtlr. La funcion moveToPosition ha sido llamada pero no esta implementada")));
#endif
	return EPathFollowingRequestResult::Type::AlreadyAtGoal;
}

void ABaseEnemyCtrl::rotatePawnTowardsTargetXY(FVector targetPosition)
{
	if (enemyPawn != nullptr)
	{
		//To only rotate in the XY (horizontal) plane
		targetPosition.Z = enemyPawn->GetActorLocation().Z;
		enemyPawn->SetActorRotation((targetPosition - enemyPawn->GetActorLocation()).Rotation(), ETeleportType::None);
	}
}

void ABaseEnemyCtrl::UpdateNextTargetPoint()
{
	TArray<AAIWaypointGeneral*> aLista = enemyPawn->TargetPoints;
	UBlackboardComponent* pBlackBoardComponent = BrainComponent->GetBlackboardComponent();
	int32 iTargetPointOrder = pBlackBoardComponent->GetValueAsInt("TargetPointOrder");

	if (iTargetPointOrder >= aLista.Num())
	{
		iTargetPointOrder = 0;
		pBlackBoardComponent->SetValueAsInt("TargetPointOrder", iTargetPointOrder);
	}
	pBlackBoardComponent->SetValueAsVector("TargetPointPosition", aLista[iTargetPointOrder]->GetActorLocation());
	pBlackBoardComponent->SetValueAsInt("TargetPointOrder", (iTargetPointOrder + 1));
}
