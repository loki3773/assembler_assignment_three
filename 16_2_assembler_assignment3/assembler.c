#include"ass_header.h"

/*
* DATE   : 2016.10.30
* AUTHOR : JEON JONG CHAN
*/
int main(int argc, char* argv[])
{
	FILE * asm,* machine;
	char asm_opcode[3] = { 0 }, temp;
	int  operand = 0;
	int i = 0, j = 0, select = 0, count = 0, asm_line = 0;
	/*
	 * ����� �Է¹��� ���ڿ���� ������ ����.
	 * ���������� ����Ŭ���Ͽ� ������ �� �ٸ���� �ʿ�.
	 */
	//fopen_s(&asm,argv[0], "r");
	//fopen_s(&machine,argv[1], "w");

	fopen_s(&asm,"test.txt","r");
	fopen_s(&machine, "asm_test.txt", "w");

	//��������� ���н� �ܼ�â�� �޼��� ���
	if (asm == -1)
	{
		printf("asm �ҽ��ڵ� ���� ����� ����");
	}
	else if (machine == -1)
	{
		printf("machine �ҽ��ڵ� ���� ����� ����");
	}
	//������ ��ü ���μ��� ���Ѵ�.
	for (asm_line = 0; !feof(asm); asm_line++)	fgets(temp, 256, asm);
	printf("line �� : %d\n", asm_line);
	rewind(asm);

	//������ ������������ �ݺ�
	for(count = 0;;count++)
	{

		/*
		 * asm���Ͽ��� ������ ���� �� ���� �Է¹޴´�.
		 */
		while (1)
		{
			temp = fgetc(asm);
			printf("%c", temp);
			if (temp == 32 )//������ ���.
			{	//������ ���� �� ���� �Է¹޴´�. �̸� operand�� �ѹ� �ҷ���
				fscanf_s(asm, "%d", &operand, sizeof(operand));
				while (operand == 32)
				{
					fscanf_s(asm, "%d", &operand, sizeof(operand));
				}
				printf("	%d", operand);
			}
			else if (temp == 10)
			{
				break;
			}
			else if(temp >= 65 && temp <= 90)//������ �ƴϸ� ��ɾ� �迭�� �ѱ��ھ� ����.�빮�ڸ� �ν�
			{
				asm_opcode[i] = temp;
			}
			else if (feof(asm))
			{
				break;
			}
			else if( i > 2)// ��ɾ 3���� �̻����� �Ǵ�.����
			{
				printf("����");
			}
			else// ����.������
			{
				printf("������");
				return 0;
			}
			i++;
		}
		if (operand > 99 && operand < 0)
		{
			printf("memory out");
			fclose(asm);
			fclose(machine);
			return 0;
		}
		//�Է¹��� �������� ��ɾ�κ��� �˾Ƴ���.
		for (j = 0; j < 10; j++)
		{
			//strncmp �� ���ڿ��� ���� �� 0�� ��ȯ. strcmp�� �ٸ��� ����ں����� ���ϴ°� ����.
			if(!strncmp(opcode[j], asm_opcode, 3))
			{
				break;
			}
		}

		switch (j)
		{
		case 0:
			if (operand == 0)
			{
				operand += HTL;
				fprintf(machine, "%03d\n", operand);
				break;
			}
			else
			{
				printf(" file exit!");
				fclose(asm);
				fclose(machine);
				return 0;
			}
		case 1:
			operand += ADD;
			fprintf(machine, "%03d\n", operand);
			break;
		case 2:
			operand += SUB;
			fprintf(machine, "%03d\n", operand);
			break;
		case 3:
			operand += STA;
			fprintf(machine, "%03d\n", operand);
			break;
		case 4:
			operand += LDA;
			fprintf(machine, "%03d\n", operand);
			break;
		case 5:
			operand += BRA;
			fprintf(machine, "%03d\n", operand);
			break;
		case 6:
			operand += BRZ;
			fprintf(machine, "%03d\n", operand);
			break;
		case 7:
			operand += BRP;
			fprintf(machine, "%03d\n", operand);
			break;
		case 8:
			if (operand == 0)
			{
				operand += INP;
				fprintf(machine, "%03d\n", operand);
				break;
			}
			else
			{
				printf(" file exit!");
				fclose(asm);
				fclose(machine);
				return 0;
			}
		case 9:
			if (operand == 0)
			{
				operand += OUT;
				fprintf(machine, "%03d\n", operand);
				break;
			}
			else
			{
				printf(" file exit!");
				fclose(asm);
				fclose(machine);
				return 0;
			}
		}
		i = 0;
		if (feof(asm)) break;
		operand = 0;
	}
	printf("�������ϴ�.");
	fclose(asm);
	fclose(machine);
}