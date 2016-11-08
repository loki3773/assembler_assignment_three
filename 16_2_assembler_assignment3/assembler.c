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
	 * 악성코드 첫번째는 의도치 않게 실행될때 바로 종료시키는 행.
	 *			두번째는 현재 ac 레지스터의 값을 저장하는 메모리
	 */
	fprintf(machine, "%03d\n", OUT);
	fprintf(machine, "%03d\n", 0);
	fprintf(machine, "%03d\n", STA + line + 2);

	//악성코드 시작 INLINE 으로 주입
	//fprintf(fp, "%03d\n", LDA + 81);
	//fprintf(fp, "%03d\n", ADD + 82);
	//fprintf(fp, "%03d\n", STA + 83);

	fopen_s(&injection_code, "injection_code.txt", "r");
	if (injection_code == -1)
	{
		printf("asm 소스코드 파일 입출력 실패");
	}

	//파일이 끝나기전까지 반복
	while(1)
	{
		/*
		* injection_code파일에서 한줄이 끝날 때 까지 입력받는다.
		*/
		while (1)
		{
			temp = fgetc(injection_code);
			if (temp == 32 || temp == 9)//공백일 경우.
			{	
				//공백이 없을 때 까지 입력받는다. 미리 operand에 한번 불러옴
				while (temp == 32) temp = fgetc(injection_code);
				/*
				* temp가 스페이스가 아니면 반복문이 끝나기에 파일위치를 한칸되돌려준다.
				* 이때 대문자일 경우 개행문자가 없이 다음줄로 넘어간 것이기에 break
				*/
				if ((temp >= 65 && temp <= 90))
				{
					fseek(injection_code, -1, SEEK_CUR);
					break;
				}
				else if (temp == 10)//개행발견시 점프
				{
					break;
				}
				else//개행문자도 발견 못하면 숫자라고 판단.
				{
					fseek(injection_code, -1, SEEK_CUR);
					fscanf_s(injection_code, "%d", &operand, sizeof(operand));
					//공백인데 다음숫자가 없으며 개행문자도 없다면 break
				}
			}
			//개행문자
			else if (temp == 10)
			{
				break;
			}
			else if (temp >= 65 && temp <= 90)//공백이 아니면 명령어 배열에 한글자씩 저장.대문자만 인식
			{
				asm_opcode[i] = temp;
			}
			else if (feof(injection_code))
			{
				break;
			}
			else if (i > 2)// 명령어가 3글자 이상으로 판단.빼액
			{
				printf("빼액");
				return 0;
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
			fclose(injection_code);
			fclose(machine);
			return 0;
		}
		//입력받은 데이터중 명령어부분을 알아낸다.
		for (j = 0; j < 10; j++)
		{
			//strncmp 는 문자열이 같을 때 0을 반환. strcmp와 다르게 몇글자비교할지 정하는게 가능.
			if (!strncmp(opcode[j], asm_opcode, 3))
			{
				break;
			}
		}

		switch (j)
		{
		case 0:
			// operand 가 없어야 하는 명령어
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
			//operand가 없으면 안되는 명령어들 case 1~7
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
			// operand 가 없어야 하는 명령어
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
			// operand 가 없어야 하는 명령어
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

	//원래 값을 레지스터에 불러온다.
	fprintf(machine, "%03d\n", LDA + line + 2);
	//본래 시작해야 될 코드로 리턴
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
	 * 실행시 입력받은 문자열들로 파일을 연다.
	 * 실행파일을 더블클릭하여 열었을 땐 다른방법 필요.
	 */
	fopen_s(&asm,argv[1], "r");
	fopen_s(&machine,argv[2], "w+");

	//fopen_s(&asm, "test.txt", "r");
	//fopen_s(&machine, "asm_test.txt", "w+");

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
	for (asm_line = 0; !feof(asm); asm_line++)	fgets(Ctemp, 256, asm);
	printf("line 수 : %d\n", asm_line);
	//파일 읽은것을 초기화 해준다.
	rewind(asm);

	//파일이 끝나기전까지 반복
	for(count = 0;;count++)
	{
		/*
		 * 악성코드 구문을 실행시키기 위해 점프문을 3번지에 삽입한다.
		 * 정확히는 4번째 코드에 점프문 삽입.
		 * 가리키는 operand 는 전체 라인수를 계산후 전체라인+3번지를 지정.
		 */
		if (count == 3)
		{
			fprintf(machine, "%03d\n", BRA + asm_line + 3);
			//현재 위치를 저장한다
			ret = count;
		}
		/*
		 * asm파일에서 한줄이 끝날 때 까지 입력받는다.
		 */
		while (1)
		{
			temp = fgetc(asm);
			printf("%c", temp);
			if (temp == 32 || temp == 9)//공백일 경우.
			{	
				//공백이 없을 때 까지 입력받는다. 미리 operand에 한번 불러옴
				while (temp == 32) temp = fgetc(asm);
				/*
				* temp가 스페이스가 아니면 반복문이 끝나기에 파일위치를 한칸되돌려준다.
				* 이때 대문자일 경우 개행문자가 없이 다음줄로 넘어간 것이기에 break
				*/
				if ((temp >= 65 && temp <= 90))
				{
					fseek(asm, -1, SEEK_CUR);
					break;
				}
				else if (temp == 10)//개행발견시 점프
				{
					printf("%c", temp);
					break;
				}
				else//개행문자도 발견 못하면 숫자라고 판단.
				{
					fseek(asm, -1, SEEK_CUR);
					fscanf_s(asm, "%d", &operand, sizeof(operand));
					//공백인데 다음숫자가 없으며 개행문자도 없다면 break
					printf("	%d", operand);
				}
			}
			//개행문자
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
		//메모리번지를 범위초과 지정시 종료
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
			// operand 가 없어야 하는 명령어
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
			//operand가 없으면 안되는 명령어들 case 1~7
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
			// operand 가 없어야 하는 명령어
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
			// operand 가 없어야 하는 명령어
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
	//악성코드 주입함수를 호출
	injection(machine, asm_line, ret);
	//파일의 전체 라인수를 구한다.
	rewind(machine);
	for (asm_line = 0; !feof(machine); asm_line++)	fgets(Ctemp, 256, machine);
	
	if (asm_line > 99)
	{
		printf("메모리 초과");
	}
	else
	{
		printf("끝났습니다.");
	}
	fclose(asm);
	fclose(machine);

	return 0;
}