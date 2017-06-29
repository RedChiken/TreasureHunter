// Fill out your copyseright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "LimbusGameModeBase.generated.h"

/**
 * 
 */


UCLASS()
class LIMBUS_API ALimbusGameModeBase : public AGameMode
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
		void startGame();

	UFUNCTION(BlueprintImplementableEvent)
		void playerChange();

	UFUNCTION(BlueprintImplementableEvent)
		void renewPawnStates();

	UFUNCTION(BlueprintImplementableEvent)
		bool checkDead();

	UFUNCTION(BlueprintImplementableEvent)
		void implementDead();

	UFUNCTION(BlueprintImplementableEvent)
		void waitSubjectSelect();

	UFUNCTION(BlueprintImplementableEvent)
		void selectSubject();

	UFUNCTION(BlueprintImplementableEvent)
		void menu();

	UFUNCTION(BlueprintImplementableEvent)
		bool checkReinforcement();

	UFUNCTION(BlueprintImplementableEvent)
		void implementReinforcement();

	UFUNCTION(BlueprintImplementableEvent)
		bool checkMove();

	UFUNCTION(BlueprintImplementableEvent)
		void implementMove();

	UFUNCTION(BlueprintImplementableEvent)
		bool checkTrap();

	UFUNCTION(BlueprintImplementableEvent)
		void implementTrap();

	UFUNCTION(BlueprintImplementableEvent)
		bool checkSacred();

	UFUNCTION(BlueprintImplementableEvent)
		void getSacred();

	UFUNCTION(BlueprintImplementableEvent)
		void waitAttackObjectSelect();

	UFUNCTION(BlueprintImplementableEvent)
		bool checkAttack();

	UFUNCTION(BlueprintImplementableEvent)
		void implementAttack();

	UFUNCTION(BlueprintImplementableEvent)
		void skillMenu();

	UFUNCTION(BlueprintImplementableEvent)
		void waitSkillObjectSelect();

	UFUNCTION(BlueprintImplementableEvent)
		bool checkSkill();

	UFUNCTION(BlueprintImplementableEvent)
		void implementSkill();

	UFUNCTION(BlueprintImplementableEvent)
		void exitGame();

};
