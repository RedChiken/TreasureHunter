// Fill out your copyright notice in the Description page of Project Settings.

#include "Limbus.h"
#include "LimbusGameModeBase.h"

void ALimbusGameModeBase::startGame() {
	playerChange();
	renewPawnStates();
	
	waitSubjectSelect();
	selectSubject();
	
	/*
	waitSubjectSelect()에서 특정 폰의 값을 반환
	selectSubject에서 이 값을 받아 폰을 지정
	*/
	
	menu();
	// subject를 입력받아 그에 대한 메뉴 출력

	exitGame();

}

void ALimbusGameModeBase::playerChange() {

}

void ALimbusGameModeBase::renewPawnStates(/*subject*/){
	
	// 폰들의 상태 갱신
	
	if (checkDead(/*subject*/)) {
		implementDead(/*subject*/);
	}
}

bool ALimbusGameModeBase::checkDead(/*subject*/) {
	
}

void ALimbusGameModeBase::implementDead(/*subject*/) {

}

void ALimbusGameModeBase::waitSubjectSelect() {
	/*subject 반환*/
	//클릭 이벤트 받아야 함
}

void ALimbusGameModeBase::selectSubject() {
	//subject 지정
}

void ALimbusGameModeBase::menu(/*subject*/) {
	
	//subject에 대한 정보 기반으로 정보 제공.
	//클릭 이벤트 받아야 함

	if (checkReinforcement(/*subject*/)) {
		implementReinforcement(/*subject*/);
	}
	else if (checkMove(/*subject, object area*/)) {
		implementMove(/*subject, object area*/);
	}
	else if (1 < 2) {		//더미값
		waitAttackObjectSelect();	//object 반환값 저장
		if (checkAttack(/*object*/)) {
			implementAttack(/*subject, object*/);
		}
	}
	else if (2 < 3) {		//더미값
		skillMenu();
	}
}

bool ALimbusGameModeBase::checkReinforcement(/*subject*/) {

}

void ALimbusGameModeBase::implementReinforcement(/*subject*/) {
	//강화 적용
}

bool ALimbusGameModeBase::checkMove(/*subject, object area*/) {

}

void ALimbusGameModeBase::implementMove(/*subject, object*/) {
	//subject를 object area로 이동
	if (checkTrap(/*object area*/)) {
		implementTrap/*subject, trap*/();
	}
	if (checkSacred(/*object area*/)) {
		getSacred(/*subject*/);
	}
}

bool ALimbusGameModeBase::checkTrap(/*object*/) {

}

void ALimbusGameModeBase::implementTrap(/*subject, trap*/) {
	//함정효과 적용
	if (checkDead(/*object*/)) {
		implementDead(/*object*/);
	}
}

bool ALimbusGameModeBase::checkSacred(/*object*/) {

}

void ALimbusGameModeBase::getSacred(/*subject*/) {
	//성물효과 적용
}

void ALimbusGameModeBase::waitAttackObjectSelect() {
	//object 지정
	//외부로부터 이벤트 대기
	//object 반환
}

bool ALimbusGameModeBase::checkAttack(/*subject, object*/) {

}

void ALimbusGameModeBase::implementAttack() {
	//공격 영향 적용
	if (checkDead(/*subject, object*/)) {
		implementDead(/*subject, object*/);
	}
}

void ALimbusGameModeBase::skillMenu() {
	waitSkillObjectSelect();
	if (checkSkill(/*subject, object*/)) {
		implementSkill(/*subject, object*/);
	}
}

void ALimbusGameModeBase::waitSkillObjectSelect() {
	//외부로부터 이벤트 받음
	//object 반환
}

bool ALimbusGameModeBase::checkSkill(/*subject, object*/) {

}

void ALimbusGameModeBase::implementSkill(/*subject, object*/) {
	//스킬 효과 적용
	if (checkDead(/*object*/)) {
		implementDead(/*object*/);
	}
}

void ALimbusGameModeBase::exitGame() {

}