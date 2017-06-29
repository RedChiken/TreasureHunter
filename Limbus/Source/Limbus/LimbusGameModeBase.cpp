// Fill out your copyright notice in the Description page of Project Settings.

#include "Limbus.h"
#include "LimbusGameModeBase.h"

void ALimbusGameModeBase::startGame() {
	playerChange();
	renewPawnStates();
	
	waitSubjectSelect();
	selectSubject();
	
	/*
	waitSubjectSelect()���� Ư�� ���� ���� ��ȯ
	selectSubject���� �� ���� �޾� ���� ����
	*/
	
	menu();
	// subject�� �Է¹޾� �׿� ���� �޴� ���

	exitGame();

}

void ALimbusGameModeBase::playerChange() {

}

void ALimbusGameModeBase::renewPawnStates(/*subject*/){
	
	// ������ ���� ����
	
	if (checkDead(/*subject*/)) {
		implementDead(/*subject*/);
	}
}

bool ALimbusGameModeBase::checkDead(/*subject*/) {
	
}

void ALimbusGameModeBase::implementDead(/*subject*/) {

}

void ALimbusGameModeBase::waitSubjectSelect() {
	/*subject ��ȯ*/
	//Ŭ�� �̺�Ʈ �޾ƾ� ��
}

void ALimbusGameModeBase::selectSubject() {
	//subject ����
}

void ALimbusGameModeBase::menu(/*subject*/) {
	
	//subject�� ���� ���� ������� ���� ����.
	//Ŭ�� �̺�Ʈ �޾ƾ� ��

	if (checkReinforcement(/*subject*/)) {
		implementReinforcement(/*subject*/);
	}
	else if (checkMove(/*subject, object area*/)) {
		implementMove(/*subject, object area*/);
	}
	else if (1 < 2) {		//���̰�
		waitAttackObjectSelect();	//object ��ȯ�� ����
		if (checkAttack(/*object*/)) {
			implementAttack(/*subject, object*/);
		}
	}
	else if (2 < 3) {		//���̰�
		skillMenu();
	}
}

bool ALimbusGameModeBase::checkReinforcement(/*subject*/) {

}

void ALimbusGameModeBase::implementReinforcement(/*subject*/) {
	//��ȭ ����
}

bool ALimbusGameModeBase::checkMove(/*subject, object area*/) {

}

void ALimbusGameModeBase::implementMove(/*subject, object*/) {
	//subject�� object area�� �̵�
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
	//����ȿ�� ����
	if (checkDead(/*object*/)) {
		implementDead(/*object*/);
	}
}

bool ALimbusGameModeBase::checkSacred(/*object*/) {

}

void ALimbusGameModeBase::getSacred(/*subject*/) {
	//����ȿ�� ����
}

void ALimbusGameModeBase::waitAttackObjectSelect() {
	//object ����
	//�ܺηκ��� �̺�Ʈ ���
	//object ��ȯ
}

bool ALimbusGameModeBase::checkAttack(/*subject, object*/) {

}

void ALimbusGameModeBase::implementAttack() {
	//���� ���� ����
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
	//�ܺηκ��� �̺�Ʈ ����
	//object ��ȯ
}

bool ALimbusGameModeBase::checkSkill(/*subject, object*/) {

}

void ALimbusGameModeBase::implementSkill(/*subject, object*/) {
	//��ų ȿ�� ����
	if (checkDead(/*object*/)) {
		implementDead(/*object*/);
	}
}

void ALimbusGameModeBase::exitGame() {

}