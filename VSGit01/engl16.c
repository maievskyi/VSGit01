// engl16 ������ ���������� ��� git 21.01.2021
// ����� ������ - ������ ���������� ��� git 26.01.
// 29 01 21  commit visual
//.............
//...............................



//24/09/20 ����� RRRengl09 ��������� ������ � ininame.dat
// 31/07/20 ��������� �� ������ �-��� sepmini()
// extensmem()
// ������ ��������
// ���� ��������� ������ ���������� ( �� ��������)
//
#define _CRT_SECURE_NO_WARNINGS  //   ?? ��������� �� ��������������� ??
//#define VARTOKEN nodebug
//#define RENAME ok
//#define ALPHABET ok
#define DEBUG 
#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include"engl16.h"  //
#include"time.h"
#include"conio.h"


FILE *ptxtfile; //---> ����� ������� ������ - argv[1] ������ �������� ��� ������ "txt2.txt"
FILE *pmyfile;	//---> ��������� �� ������. ���� � ������� ��������� ���� ���� - argv[2].dat"
FILE *pinifile;	//---> ��������� �� ������. ���� � ������� ��������� ������ ininame.dat
FILE *pnosortfile;	//---> ��������� �� ������. � � ����� ���� ������ ���� ���� - argv[1]_nosort.dat"
FILE *psortfile;	//---> ��������� �� ������. � � ������� ���� ���� ���� ���� - argv[1]_sort.dat"

char *pnamenosort;		//������ �� ��� �-�� � ����� ������ ���� ��� 
struct word *pmemword;		//���� ������ -> � main()�� ��������� �������� ��� ������ 
							//��� ������ �������� (word) ��� ��������������� token()
							//����� ������ ����� �������������� �� ����� ���������
struct word *pmemsortword;  // ���� �� � ��� ������� � ���������������� �������
struct word *palphabetword;  // ���� �� � ��� ���-� � ������-�� � ������������ �������
long amountmem = 0;		//--- ������ � ������ ��� ��� ����-��� ��� ��������� word
long *pamountmem;		//--->��� ���� � �-��� ��� ��� ����-��� ��� ������ ������ word
int countnumword = 0;	//---������� ���������� ���� � ������ � ��� ��� �����-�
int *pcountnumword;		//--->��������� �� ����� ����
struct ininame *pmemininame;			//--->���� �� ��� ��� � ����� ��� ���������
int flagtext = NEWTEXT;	//���������� -���� ������ ������ �� ���� ��� ��� �������
						//� � ����� �� �������������� �� ����� � �������� � ����� ���� ���� 

						//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%       main     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
int main(int argc, const char ** argv, const char** env)
{
	system("chcp 1251 > nul");

	//==== �������� �����-� ���� ��� - ������ ��� ��� ��� � ����� ���������,===
	errno_t err;	//  ���������� (int?) ��� ������ ������ ? ����� ���������� (int?)
					// �������� ���� �� ininame.dat ���� � ����� ����-�� ����� �-��� "ininame.dat"=======				
	err = fopen_s(&pinifile, "ininame.dat", "r+b");// ������� �� �� � �����

												   //�� ���������� ����� ��� - ������ ���� �� ������================
	if (err != 0)//�� ���������� ����� ��� - ������ ���� �� �����

	{//%%%%% � � ������ ���� ��� ������ ������  ==%%%%%%%%%%%%%%%%%%%%%%%
	 //char * ptempin = (char*)malloc(NAMEENGLTEXT);


		puts("\n !!!  �� ����������� ���� ������������ \
 inname.dat � ������� ��� ������� \n");
		printf("\n    ������� ��� ����� � ���������� ������� \n\
 ___ ___________, ������ �� ������ %d �������� \n", NAMEENGLTEXT);
#ifndef DEBUG
		char tempin[NAMEENGLTEXT + 1];	//���� ��� ���������� ������ �� ���� �-��
		fgets(tempin, NAMEENGLTEXT, stdin);
#endif // DEBUG
#ifdef DEBUG						//�� ����� �������
		char tempin[] = "text00.txt";	//���� ���� ���� ��� ������ �� �� ����
#endif // DEBUG

		int namesize = strlen(tempin);//���� ������ � ������ �� �-�� ������
#ifndef DEBUG
		tempin[strlen(tempin) - 1] = '\0';
#endif // !DEBUG
#ifdef DEBUG
		tempin[strlen(tempin)] = '\0';
#endif // DEBUG

		struct ininame memininame;  //������ ��� ��������� �����
		strcpy(memininame.textname, tempin);  // ��� ���� ������ � ���������

		printf("\n    ��������� ��� ����� � ���������� ������� \n\
 � ������ tempin - %s \n ������ ����� ������ = %d ����\n\n", tempin, namesize);
		//===========// ��������� ��� ��� ���� ���� - .dat ����� //===================//
		char *pnamewordnosort;  //���� ��� ������ ��� ��������. ��� ���� �����_nosort.dat"
		pnamewordnosort = rename2(tempin, "_nosort.dat", 5);
		printf("\n  ��� �����  ������� �� ������ ���� \ - %s \n", pnamewordnosort);

		//======// �������� �� ��� pmemininame ��� ��� � ����� ��� ��������� //==========
		pmemininame = (struct ininame*)malloc(sizeof(struct ininame));//���� ����
		pmemininame = &memininame;// ������������� ��� ������ ininame ��������� (pdat1name)
		if (pmemininame == NULL)
			printf("�� �������� ������ ��� ���� ��� ��������� \n");
		else
			printf("  �������� ��� ��� pmemininame = %d Bytes \n \
��� ���� ��� ��������� \n", sizeof(struct ininame));
		//=====// ����� tempkey �� ����� ����� msek ��� ����� ��� ���� //=========	
		printf("\n  ���� ���� ������� ��������� ����� ������� ����� �����\n");
		// 
		char tempkey = '0';
		tempkey = delayorkey(5000, tempkey);
		if (tempkey == '0')//����������� ����
		{	//��� ����� ��������� �� ����� � pmemininame
			printf("\n  ������ ����������� ���� \n");

		}
		else//��� �������������� �������� ����� � pmemininame
		{
			printf("\n  ��������������  ������������� ��������� �����\n");

		};

		//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

		// ����� ��� �������� �� ������������� ������ ������ ������� ���� ===================
		{
			// �������� �������� txt ����� ==============================================
			char* pintextname; //���� �� ��������� � ������ ����� ������ �����?
			pintextname = (char*)malloc(strlen(tempin));//����������� �� ������ �������
			int ttt = strlen(tempin);
			strcpy(pintextname, tempin, strlen(tempin));  // ��� ���� ������ �

			err = fopen_s(&ptxtfile, pintextname, "r+b");// ���������������� ��������� FILE *ptxtfile 
														 //�� ��-�� txt �-� (argv[1])
														 //  � ����������� � ������ (rb)-  "txt2.txt" 
			if (err) {
				puts("��� ����� �������� �-�� \n");
				perror("��� ���������� - ����� �������� �-�� \n");
				system("pause");
				exit(1);
			};  // puts("��� ���������� ��� ������� �-�� \n"); 

				//~~~~~~  ������� �-�� ������ � ����������� ����� ������, ��� �����  ---> ================

				//~~~~~~~  ���������� ������ ����� � ������  ------------------------------------------
			long txtSize = 0;		//--- ������ � ������ ����� ����� ����� ������ � ��� ������
									// ������������� ����� ������� � ����� �����, � � (���� �� 0 ����� ����� �-��)	 
			fseek(ptxtfile, 0, SEEK_END);
			txtSize = ftell(ptxtfile);                       // �������� ������ � ������ 
															 // � ���������� � txtSize
															 //rewind(ptxtfile);  //+ ������� ������      														
			fseek(ptxtfile, 0, SEEK_SET);	// ��������� ������� ��� �� ������ �����
											//
			printf("������ ������ �������� ������ = %d Bytes \n", txtSize);

			//~~~~~~  ��������� ��� ������ ����p *ptxtbuf---------------------------------
			char * ptxtbuf;			//--->  ������� ��������� �� ��� ���. ptxtbuf 
									//		��� �������� ������-�� �� ��-�� �����...........
			ptxtbuf = (char*)malloc(sizeof(char) * txtSize); // �������� ��� ������ ptxtbuf ��� ����-� ������-�� �� �-� �
															 // ����� ����������� ��������� ��������
			if (ptxtbuf == NULL)
			{
				fputs("������ ������", stderr);
				exit(2);
			}
			printf("~~ �������� ��� ���. ptxtbuf ��� �������� ������ �� ����� ~~\n");

			// ------�� ptxtfile ��������� ���� � �����	ptxtbuf!!!------------------------------------
			size_t result = fread(ptxtbuf, sizeof(char), txtSize, ptxtfile);  // ��������� ���� � �����!!!
			if (result != txtSize)  //���� �� ������� ����� ��������� ����
			{
				if (feof(ptxtfile)) printf("��������������� ���������� ����� �����.\n");
				else printf("������ ��� ������ �����.\n");
				exit(3);
			}
			fclose(ptxtfile);	//��������� � ������ )) �������� ���� �� �������� �������� ������� �����

#ifdef TEXT	//~~~~~~  ����� ���-�� � �����. ����� ������ ������� �� ����� (���  �������)===================
			if (puts(ptxtbuf) == EOF) {
				printf("������ ��� ������ �� ������� ����� \n");
			}  // -> -> -> 
			else {
				printf("���� ������  ������-������� � �-��� main ���������\n");
				printf("		~~~ !!!!!����� ���� - ��� ������������ � ����� %s ~~~       \n \
	!!!!!!!!�� ������� ��������� ��� ������, ����� ������������� \n", argv[1]);	//  ???*
			}
#endif//     ~~~~~~~~~~~~~~~~~~~~~ ����� ��� ������ ������  ~~~~~~~~~~~~~~~

			//~~~~~   ����� ������ ����� ����� *pmemword ��� ������������� �������� ����� ���� =======================
			{
				printf("  ������ ������ ��� ���� ��������� %d ����\n", sizeof(struct word));
				amountmem = MAX_WORD * sizeof(struct word);  //������ �������� ���-��� ������ (����)
				pmemword = (struct word *) malloc(amountmem);   //����� ������ ��������� ������ 
																//  ��� ��������� � ��������� ����� � ��������� 
																//�������� - ��������� ���������� MAX_WORD 
				if (pmemword == NULL)printf("�� ��������� ������ ��� punsort \n");
				else printf("  ��������� ������ punsort = %d Bytes \n  ��� %d ����������������� �������� \
  � �������! ������������\n",
					MAX_WORD * sizeof(struct word), MAX_WORD);				//    �������
			}

			//~~~~~~~~~    ����� (���������� ����������?) ����� �-��� ������������ - sepmini() ------   
			pamountmem = &amountmem;  // ���� �� ���� ��� ��� ���� ��� ������� ���-�(����= 8 ���)
			pcountnumword = &countnumword; //���� �� ����� ����-�� ���� = ������ ��� �����-� 
										   // pmemword - ���� �� ������ �������� (word) ��� ��������������� token()
										   //ptxtbuf - ���� �� ��� ������ ����������� ������ - ����� ����� �����
										   //argv[1] - �� ��� ������ ��� ��� ������� printf
										   // ����� �������������  long amountword = *pcountnumword / sizeof(struct word); 
			pmemword = sepmini(pmemword, pamountmem, ptxtbuf, pcountnumword, argv[1]);


			//~~~~~~~~~~~~   ����� ������ � ���� ���� �������������� �� ��������������� �������� =================				
			//char *pnamewordnosort;  //���� ��� ������ ��� ��������. ��� ����� "argv[1]_nosort.dat"
			// ~~~~~~~���������� ����� - ���[1] ��� ��������-�� ���� *_nosort.dat ������� � - � rename2()
			{//~~~~~~~  ���������� ����� - ��� [1] ��� ��� � ��� ��� *_nosort.dat ������� �-� rename2()
			 //pnamewordnosort = rename2(argv[1], "_nosort.dat", 4);
			}
			//~~~~~~~~~~~~ ������ � hdd ����(������� ����������) ���� �������� ��������  ---///////////////  
			writebase2(pnosortfile, pnamewordnosort, pmemword, countnumword);//
																			 //pnosortfile - ���� �� ���� ����� �-��� hdd ���� � ������� ��������� ���� ���� 
																			 //pnamewordnosort - ��� �������������� ����� ��� �-�� ��� hdd ("argv[1]_nosort.dat")
																			 // pmemword - ���� �� ��� ������ ������ ��������, 
																			 // countnumword - ����� ������ ��������
																			 //,?? ������� ���� ��� ����� �  ����������� ( ----- )????
			puts(pnamewordnosort);		//debug


										//~~~~~~~~~~  ������ �  ��� ��� pdat1name ����� ����� ������-��� ������ word    ~~~~~~~~~
			pmemininame->idname = 0;
			strncpy(pmemininame->name, pnamewordnosort, EN1);


			//~~~~~~~~~~   ������ ��� ������ � 1-� ������  XXX_nosort.dat � ���� ��� "ininame.dat"   	
			err = fopen_s(&pinifile, "ininame.dat", "w+b");//XXX_nosrt.dat ���� � �-� "ininame.dat"
			if (err)
			{
				puts("\n ������! \n ������� ������ ����� ���������� �-�� ��� ������������ \n");
				system("pause");
				exit(1);
			}
			fwrite(pmemininame, sizeof(struct ininame), QUANTITYNAME, pinifile);//ininame.dat
																				//fwrite()
																				//~~~~~~~~~~   �������������� ����� ��� ������������� �������  _sort.dat





			free(ptxtbuf); //��� ��� ptxtbuf ��� �������� ������ �� �����
			free(pmemword);
		}// ����� ���� �������� �� ������������� � ���������� ������ ������ ������� ����
		 // ����� ���� �������� �� ������������� � ���������� ������ ������ ������� ����





		 //..................................................................


		free(pnamewordnosort); //��� ���� - ������ ��� ������������ �� ���� �.._nosort.dat
							   // � ���� - pdat1name ????
		system("pause");

	}//end if ....�� ���������� ����� ��� - ������ ���� �� �����

	 //...else ������� � ��� � ����� ��������� inname.dat � ������ �������
	else//...else ������� � ��� � ����� ��������� inname.dat � ������ �������
	{	// � � ��������� ���� ������������ ����� ������
		puts("\n !!!  ��� ����������� ���� ������������ \n\
 inname.dat � ������� ��� ������� \n");








		system("pause");

	}//end else ....��� � ����� ��������� inname.dat � ������ �������



	printf("\n\n             The END!   -     ����� �����! \n\n\n");
	system("pause");
}  //end main