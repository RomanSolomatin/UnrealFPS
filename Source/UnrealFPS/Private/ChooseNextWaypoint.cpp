// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "../Public/ChooseNextWaypoint.h"

//IWYU

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	///Get the patrol points.
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto Guard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = Guard->PatrolPointsCPP;

	///Set Next Waypoint.
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]); //TODO protect against empty array.
	
	//UE_LOG(LogTemp, Warning, TEXT("Waypoint Index: %i"), Index);
	

	///Cycle index
	auto NewIndex = (Index+1) % (PatrolPoints.Num());
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NewIndex);

	return EBTNodeResult::Succeeded;
}
