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
	 * 실행시 입력받은 문자열들로 파일을 연다.
	 * 실행파일을 더블클릭하여 열었을 땐 다른방법 필요.
	 */
	//fopen_s(&asm,argv[0], "r");
	//fopen_s(&machine,argv[1], "w");

	fopen_s(&asm,"test.txt","r");
	fopen_s(&machine, "asm_test.txt", "w");

	//파일입출력 실패시 콘솔창에 메세지 출력
	if (asm == -1)
	{
		printf("asm 소스코드 파일 입출력 실패");
	}
	else if (machine == -1)
	{
		printf("machine 소스코드 파일 입출력 실패");
	}
	//파일의 전체 라인수를 구한다.
	for (asm_line = 0; !feof(asm); asm_line++)	fgets(temp, 256, asm);
	printf("line 수 : %d\n", asm_line);
	rewind(asm);

	//파일이 끝나기전까지 반복
	for(count = 0;;count++)
	{

		/*
		 * asm파일에서 한줄이 끝날 때 까지 입력받는다.
		 */
		while (1)
		{
			temp = fgetc(asm);
			printf("%c", temp);
			if (temp == 32 )//공백일 경우.
			{	//공백이 없을 때 까지 입력받는다. 미리 operand에 한번 불러옴
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
			else if(temp >= 65 && temp <= 90)//공백이 아니면 명령어 배열에 한글자씩 저장.대문자만 인식
			{
				asm_opcode[i] = temp;
			}
			else if (feof(asm))
			{
				break;
			}
			else if( i > 2)// 명령어가 3글자 이상으로 판단.빼액
			{
				printf("빼액");
			}
			else// 오류.빼빼액
			{
				printf("빼빼액");
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
		//입력받은 데이터중 명령어부분을 알아낸다.
		for (j = 0; j < 10; j++)
		{
			//strncmp 는 문자열이 같을 때 0을 반환. strcmp와 다르게 몇글자비교할지 정하는게 가능.
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
	printf("끝났습니다.");
	fclose(asm);
	fclose(machine);
}