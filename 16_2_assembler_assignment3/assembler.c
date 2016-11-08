#include"ass_header.h"

/*
* DATE   : 2016.10.30
* AUTHOR : JEON JONG CHAN
*/
void injection(FILE *machine, int line, int ret)
{
	FILE * injection_code;
	char temp,asm_opcode[3];
	int i = 0, j = 0, operand = 0;
	/*
	 * �Ǽ��ڵ� ù��°�� �ǵ�ġ �ʰ� ����ɶ� �ٷ� �����Ű�� ��.
	 *			�ι�°�� ���� ac ���������� ���� �����ϴ� �޸�
	 */
	fprintf(machine, "%03d\n", OUT);
	fprintf(machine, "%03d\n", 0);
	fprintf(machine, "%03d\n", STA + line + 2);

	//�Ǽ��ڵ� ���� INLINE ���� ����
	//fprintf(fp, "%03d\n", LDA + 81);
	//fprintf(fp, "%03d\n", ADD + 82);
	//fprintf(fp, "%03d\n", STA + 83);

	fopen_s(&injection_code, "injection_code.txt", "r");
	if (injection_code == -1)
	{
		printf("asm �ҽ��ڵ� ���� ����� ����");
	}

	//������ ������������ �ݺ�
	while(1)
	{
		/*
		* injection_code���Ͽ��� ������ ���� �� ���� �Է¹޴´�.
		*/
		while (1)
		{
			temp = fgetc(injection_code);
			if (temp == 32 || temp == 9)//������ ���.
			{	
				//������ ���� �� ���� �Է¹޴´�. �̸� operand�� �ѹ� �ҷ���
				while (temp == 32) temp = fgetc(injection_code);
				/*
				* temp�� �����̽��� �ƴϸ� �ݺ����� �����⿡ ������ġ�� ��ĭ�ǵ����ش�.
				* �̶� �빮���� ��� ���๮�ڰ� ���� �����ٷ� �Ѿ ���̱⿡ break
				*/
				if ((temp >= 65 && temp <= 90))
				{
					fseek(injection_code, -1, SEEK_CUR);
					break;
				}
				else if (temp == 10)//����߽߰� ����
				{
					break;
				}
				else//���๮�ڵ� �߰� ���ϸ� ���ڶ�� �Ǵ�.
				{
					fseek(injection_code, -1, SEEK_CUR);
					fscanf_s(injection_code, "%d", &operand, sizeof(operand));
					//�����ε� �������ڰ� ������ ���๮�ڵ� ���ٸ� break
				}
			}
			//���๮��
			else if (temp == 10)
			{
				break;
			}
			else if (temp >= 65 && temp <= 90)//������ �ƴϸ� ��ɾ� �迭�� �ѱ��ھ� ����.�빮�ڸ� �ν�
			{
				asm_opcode[i] = temp;
			}
			else if (feof(injection_code))
			{
				break;
			}
			else if (i > 2)// ��ɾ 3���� �̻����� �Ǵ�.����
			{
				printf("����");
				return 0;
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
			fclose(injection_code);
			fclose(machine);
			return 0;
		}
		//�Է¹��� �������� ��ɾ�κ��� �˾Ƴ���.
		for (j = 0; j < 10; j++)
		{
			//strncmp �� ���ڿ��� ���� �� 0�� ��ȯ. strcmp�� �ٸ��� ����ں����� ���ϴ°� ����.
			if (!strncmp(opcode[j], asm_opcode, 3))
			{
				break;
			}
		}

		switch (j)
		{
		case 0:
			// operand �� ����� �ϴ� ��ɾ�
			if (operand == 0)
			{
				operand += HTL;
				fprintf(machine, "%03d\n", operand);
				break;
			}
			else
			{
				printf(" file exit!");
				fclose(injection_code);
				fclose(machine);
				return 0;
			}
		case 1:
			//operand�� ������ �ȵǴ� ��ɾ�� case 1~7
			if (operand != 0)
			{
				operand += ADD;
				fprintf(machine, "%03d\n", operand);
				break;
			}
			else
			{
				printf(" file exit!");
				fclose(injection_code);
				fclose(machine);
				return 0;
			}
		case 2:
			if (operand != 0)
			{
				operand += SUB;
				fprintf(machine, "%03d\n", operand);
				break;
			}
			else
			{
				printf(" file exit!");
				fclose(injection_code);
				fclose(machine);
				return 0;
			}
		case 3:
			if (operand != 0)
			{
				operand += STA;
				fprintf(machine, "%03d\n", operand);
				break;
			}
			else
			{
				printf(" file exit!");
				fclose(injection_code);
				fclose(machine);
				return 0;
			}
		case 4:
			if (operand != 0)
			{
				operand += LDA;
				fprintf(machine, "%03d\n", operand);
				break;
			}
			else
			{
				printf(" file exit!");
				fclose(injection_code);
				fclose(machine);
				return 0;
			}
		case 5:
			if (operand != 0)
			{
				operand += BRA;
				fprintf(machine, "%03d\n", operand);
				break;
			}
			else
			{
				printf(" file exit!");
				fclose(injection_code);
				fclose(machine);
				return 0;
			}
		case 6:
			if (operand != 0)
			{
				operand += BRZ;
				fprintf(machine, "%03d\n", operand);
				break;
			}
			else
			{
				printf(" file exit!");
				fclose(injection_code);
				fclose(machine);
				return 0;
			}
		case 7:
			if (operand != 0)
			{
				operand += BRP;
				fprintf(machine, "%03d\n", operand);
				break;
			}
			else
			{
				printf(" file exit!");
				fclose(injection_code);
				fclose(machine);
				return 0;
			}
		case 8:
			// operand �� ����� �ϴ� ��ɾ�
			if (operand == 0)
			{
				operand += INP;
				fprintf(machine, "%03d\n", operand);
				break;
			}
			else
			{
				printf(" file exit!");
				fclose(injection_code);
				fclose(machine);
				return 0;
			}
		case 9:
			// operand �� ����� �ϴ� ��ɾ�
			if (operand == 0)
			{
				operand += OUT;
				fprintf(machine, "%03d\n", operand);
				break;
			}
			else
			{
				printf(" file exit!");
				fclose(injection_code);
				fclose(machine);
				return 0;
			}
		}
		i = 0;
		if (feof(injection_code)) break;
		operand = 0;
	}

	//���� ���� �������Ϳ� �ҷ��´�.
	fprintf(machine, "%03d\n", LDA + line + 2);
	//���� �����ؾ� �� �ڵ�� ����
	fprintf(machine, "%03d\n", BRA + ret + 1);

	fclose(injection_code);
}
int main(int argc, char* argv[])
{
	FILE * asm,* machine;
	char asm_opcode[3] = { 0 }, temp, *Ctemp[256] = { 0, };
	int  operand = 0;
	int i = 0, j = 0, select = 0, count = 0, asm_line = 0, ret = 0;
	/*
	 * ����� �Է¹��� ���ڿ���� ������ ����.
	 * ���������� ����Ŭ���Ͽ� ������ �� �ٸ���� �ʿ�.
	 */
	fopen_s(&asm,argv[1], "r");
	fopen_s(&machine,argv[2], "w+");

	//fopen_s(&asm, "test.txt", "r");
	//fopen_s(&machine, "asm_test.txt", "w+");

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
	for (asm_line = 0; !feof(asm); asm_line++)	fgets(Ctemp, 256, asm);
	printf("line �� : %d\n", asm_line);
	//���� �������� �ʱ�ȭ ���ش�.
	rewind(asm);

	//������ ������������ �ݺ�
	for(count = 0;;count++)
	{
		/*
		 * �Ǽ��ڵ� ������ �����Ű�� ���� �������� 3������ �����Ѵ�.
		 * ��Ȯ���� 4��° �ڵ忡 ������ ����.
		 * ����Ű�� operand �� ��ü ���μ��� ����� ��ü����+3������ ����.
		 */
		if (count == 3)
		{
			fprintf(machine, "%03d\n", BRA + asm_line + 3);
			//���� ��ġ�� �����Ѵ�
			ret = count;
		}
		/*
		 * asm���Ͽ��� ������ ���� �� ���� �Է¹޴´�.
		 */
		while (1)
		{
			temp = fgetc(asm);
			printf("%c", temp);
			if (temp == 32 || temp == 9)//������ ���.
			{	
				//������ ���� �� ���� �Է¹޴´�. �̸� operand�� �ѹ� �ҷ���
				while (temp == 32) temp = fgetc(asm);
				/*
				* temp�� �����̽��� �ƴϸ� �ݺ����� �����⿡ ������ġ�� ��ĭ�ǵ����ش�.
				* �̶� �빮���� ��� ���๮�ڰ� ���� �����ٷ� �Ѿ ���̱⿡ break
				*/
				if ((temp >= 65 && temp <= 90))
				{
					fseek(asm, -1, SEEK_CUR);
					break;
				}
				else if (temp == 10)//����߽߰� ����
				{
					printf("%c", temp);
					break;
				}
				else//���๮�ڵ� �߰� ���ϸ� ���ڶ�� �Ǵ�.
				{
					fseek(asm, -1, SEEK_CUR);
					fscanf_s(asm, "%d", &operand, sizeof(operand));
					//�����ε� �������ڰ� ������ ���๮�ڵ� ���ٸ� break
					printf("	%d", operand);
				}
			}
			//���๮��
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
		//�޸𸮹����� �����ʰ� ������ ����
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
			// operand �� ����� �ϴ� ��ɾ�
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
			//operand�� ������ �ȵǴ� ��ɾ�� case 1~7
			if (operand != 0)
			{
				operand += ADD;
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
		case 2:
			if (operand != 0)
			{
				operand += SUB;
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
		case 3:
			if (operand != 0)
			{
				operand += STA;
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
		case 4:
			if (operand != 0)
			{
				operand += LDA;
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
		case 5:
			if (operand != 0)
			{
				operand += BRA;
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
		case 6:
			if (operand != 0)
			{
				operand += BRZ;
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
		case 7:
			if (operand != 0)
			{
				operand += BRP;
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
		case 8:
			// operand �� ����� �ϴ� ��ɾ�
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
			// operand �� ����� �ϴ� ��ɾ�
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
	//�Ǽ��ڵ� �����Լ��� ȣ��
	injection(machine, asm_line, ret);
	//������ ��ü ���μ��� ���Ѵ�.
	rewind(machine);
	for (asm_line = 0; !feof(machine); asm_line++)	fgets(Ctemp, 256, machine);
	
	if (asm_line > 99)
	{
		printf("�޸� �ʰ�");
	}
	else
	{
		printf("�������ϴ�.");
	}
	fclose(asm);
	fclose(machine);

	return 0;
}