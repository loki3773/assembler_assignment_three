#pragma once
#include<stdio.h>
#include<string.h>
/*
 * DATE   : 2016.10.30
 * AUTHOR : JEON JONG CHAN
 */

//���� OPCODE
#define HTL	000
//���ϱ� OPCODE
#define ADD	100
//���� OPCODE
#define SUB	200
//���� OPCODE
#define STA	300
//�ҷ�����(LOAD) OPCODE
#define LDA	500
//������ ���� OPCODE
#define BRA	600
//0�� ���� ���� OPCODE
#define BRZ	700
//0���� ���ų� ũ�ų� OPCODE
#define BRP	800
//��� OPCODE
#define INP	901
//�Է� OPCODE
#define OUT	902

//�Է¹޴� ��ɾ �����ϱ� ���� ��ɾ ������ �迭
char opcode[10][3] = {
	 {'H','L','T'}
	,{'A','D','D'}
	,{'S','U','B'}
	,{'S','T','A'}
	,{'L','D','A'}
	,{'B','R','A'}
	,{'B','R','Z'}
	,{'B','R','P'}
	,{'I','N','P'}
	,{'O','U','T'}
};