//
#define _CRT_SECURE_NO_WARNINGS  //   ?? ��������� �� ��������������� ??
#define TOKENDEBUG nodebug
//#define ALPHABET ok
#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include"engl16.h"  //

extern flagtext;

//////////-------  ����� �-���  ------///////////////////////////////////////////////////////////////
// ���������� �������� ��� ������ ptxtbuf[] (��� ������������� �� �-��) �  ������ �������� word
// ��� ������ � (������� �������) �� ���� ��� �-� extensmem()
struct word * sepmini(struct word *pmemword, long *pamountmem, char * ptxtbuf, int * pcountnumword, char const * argv)
	//����� ��������� �� � ������ � ������� ������� - str word *pmemword
	// ������� ��������� � ���������� � �-�,
	// pamountmem ���� �� ������ � ��� str word � �-���
	//multipl ����� ����� ��� ������ ��� ������ ��� token() 
	//ptxtbuf ����. �� ��� ������ ����������� ������ - ����� ����� �����
	//pcount - ��������� ����� ������������ ���� ��� �������
	// ����� ��� ������� ������� ������� (����������������) �������� � ���� �������
	// arv1 ��� ������������� ����� ��� ������ �������� ����� - ����� ������ ��� fprint()????
{
	printf("~~   �������� �������� �-��� sepmini()  ~~\n");
	printf("Tokens - ���������� ��������������� ����\n\n");
	printf(" ~~ ��������� ������� �������� �� �-�� - ��������� ��� ������ ( %s ): ~~\
		 ~~ � ���������� � ������� �������� � ����� � �������  ~~~\n", argv);
	//int count = 0;  // ��� �������� �������� ????
	//printf("Tokens:\n");

	int countstr = 0;				// ��������� ������� ����������� �������� � ����� token
	long maxmemstr = MAX_WORD;		// ��������� ������� ������� �������� ��� ��������� = 8
									//����� �������� � ���������� ������ � ����� token ��� ��������
	int * pmaxmemstr = &maxmemstr;		//--> ���� �� ����� ���� ����� ��� �������� � ����-�� ������ 
	struct word *plocseptempstr2 = NULL;		//--> ���� ���� �� ����������� ��� ������

	printf("��������� ��������� ������ = %d Bytes ���  %d \
���������������� ������� \n", (*pamountmem), (*pamountmem) / sizeof(struct word));	// 

																					//11
	char seps[] = " ][()/,.\t\n\r\v\xA0\"\'\\?!-+*/<>=_:;0123456789#$%^&";	// ������ �������� - �����������
	char *token1 = NULL;		//--->char *token1 - ��� ���� ���� �� ������ �����   
								//����������  char ������ � \0 � �����
	char *next_token1 = NULL;	//--->����� ?? ����� ��� �������� ����������� ������
								//22														//															Establish string and get the first token:
	token1 = strtok_s(ptxtbuf, seps, &next_token1);	//������ ����� � �������������
	char tokenbuf[EN];			//---> ��� �������� ������ ��� �������� �� token1 english
								//� ������ ������� = 32 ?��� ����� ��� ����������???
								// !������ ������ ����� strtok_s() ����� ������������� \0
								//33
	while (token1 != NULL)
	{
		//*pcountnumword += 1;     // ???????????????????????????????????????
		///_______________________________________________________________________________________________________

		// Get next token:
		//  �������� ������� � ���� �������� ==================================
		int ix = 0;				// ������� � 0 , ��� �������� ��������  (� ���� > 32 ???)
								// ������� � ������ ����� ����� ������������ � 0
		while (token1[ix])					// ������� � ������� ������� �� ������ (char-������) 
											//  ���� �  token1[ix] �� ���������� \0
		{									//  �������� ������� � ���� �������� 
			tokenbuf[ix] = (char)tolower(token1[ix]);  //����������� ��������-� �����  ������� ��-�� � ��������
			ix++;                                   // ��������� ������� �������� � ������
		}
		tokenbuf[ix] = (char)tolower(token1[ix]);		// ������  ���������� =/0 ������� ?
														//- end - ������� ��������� � ���� �������� 
														//*pcountnumword += 1;     // ???????????????????????????????????????

														// ��! ���� ����� ���� ������ ������� ���� ������ ������� ��� ������ ����� ========================
		if (*pcountnumword == maxmemstr - 1)  //pcount - �������� �-��� sepmini ??????????=========================
											  // ������� ���� ������ ������� ��������� � ����� ������� MAX_WORD
											  // ��� ����������� ��������� maxmemstr = maxmemstr * MULT_DIN_MEM;
											  // ��� ����� ������ ������ ������� extensmem() !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
											  //maxmemstr = maxmemstr * MULT_DIN_MEM; //
		{
			long newamountword = maxmemstr * MULT_DIN_MEM; //
			maxmemstr = newamountword; //?? ����� ������ ������������ ������ ������� �������
									   // ����� �-�� ???? � � �
			printf("~~   ����� �-��� extensmem()  ~~\n");
			pmemword = extensmem(pmemword, pamountmem, newamountword, pcountnumword);


		} // end if	4 .............................................................
		if (ix > 1)
		{
			strcpy_s((pmemword + *(pcountnumword))->en, EN, tokenbuf);	// ���������� ���� 
																		// ��������� �� ! ���� �������� �� ������ ?
			((pmemword + *(pcountnumword)))->id = (int)(*(pcountnumword)+1); //���������� id
																			 // id ���������� �� countnumword �� 1 ---   id=1   countnumword=0
			((pmemword + *(pcountnumword)))->repeat = 0;   // ������� temp ??
#ifdef SEPARATED
			printf("%4d. r=%d  id= %4d. - { %s }  ->  [ %s ]\n", *pcountnumword, \
				pmemword[(*pcountnumword)].repeat, *pcountnumword + 1, token1, tokenbuf);// ���������� ������ 
																						 //- ����� ��� ����˨����� ����� -temp-  pmemword[(*pcountnumword)].repeat,
																						 //*(plocsep + *pcount)->en = "NULL"; // ���������� ���� ���������
#endif			 //55
			*pcountnumword += 1;     // ???????????????????????????????????????

		}


#ifndef TOKENDEBUG
		//printf("string1----------%s \n", buf);		//temp ��� ��������� ������ strtok_s(string1, seps, &next_token1)
		// ����� �������˨����� ������
		printf("next_token1======%s \n\n", next_token1);//temp ��� ��������� ������ strtok_s(string1, seps, &next_token1)
#endif


														//66								// ���  ���� ������ token  ??????????????? 
		token1 = strtok_s(NULL, seps, &next_token1);
		//����-��  ����� �� strtok ���������� ���������� �����-�
	}	// end while (token1 != NULL)

		// "���������" ������ ������ � ������� �������
	long realamountword = *pcountnumword;
	pmemword = extensmem(pmemword, pamountmem, realamountword, pcountnumword);
	printf("��������� ������ = %d Bytes ���  %d \
�������� ����� ���������������� ������� word \n",
(realamountword) * sizeof(struct word), (realamountword));			//   


																	//=================================================================================
																	//=================================================================================
																	//=================================================================================
	return pmemword;
}//    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END sepmini()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 //////////////==== ������ ������ ��� ������ � ������� � ������ ������ ���  ======/////////////////////
struct word *extensmem(struct word *pmemword, long *pamountmem, long newamountword, int *pcountnumword)//
																									   //��� ���������� �������� ���������� struct word �������� ����������� ���� ������ size ���������� �-�
																									   // ������ ������ ������ *pamountmem ��� ������ struct word * �� ������� *pnewsize  � ������ � ���� ������ 
																									   // ������ ������ struct word *pmemword � ����� ?????????????????????? ��������� �� ��� ������
{
	printf("~~   �������� �������� �-��� extensmem()  ~~\n");
	printf("��������� *pamountmem-%d;  newamountword - { %d }; *pcountnumword - [ %d ]\n", *pamountmem, newamountword, *pcountnumword);   // ����������
																																		  // ~~~~~~~~~~~~~~~~~~~~~~~  ��������� ��� ���� ��� ������   ~~~~~~~~~~~~~~~~~~~~~~~~~
	struct word *ptempstrmemword = (struct word *) malloc((newamountword) * sizeof(struct word));
	//ptempstrmemword - ��������� ������ �� ��������� ������� ������� ������ ��� ��������� 
	if (ptempstrmemword == NULL)printf("�� ��������� ������ ��� ���������� struct word[] \n");
	else printf("��������� ��������� ������ = %d Bytes ���  %d \
���������������� ������� word \n",
(newamountword) * sizeof(struct word), (newamountword));			//
	*pamountmem = newamountword * sizeof(struct word);       //��� �������� ������� � �� �-����
	if (newamountword < *pcountnumword)
	{
		printf("���������� ������ ��� struct word[] ������ \n ��� ������� ������� ���� \n");
		//return (NULL);
	}
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ����������� �� ������� ������    ~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (int z = 0; z < *pcountnumword; z++)	// ������������ ����������� �� ������� ������
	{											// ������� � ������ �� ��������� ������ + ...
		*(ptempstrmemword + z) = *(pmemword + z);	// ���� ���������  ...

	}
	printf("���������� ������ ���� �������� � ������ ������\n");
	//*pcountnumword += 1;  // ...
	free(pmemword);										// ���������� ������ �������� plocsep
	pmemword = ptempstrmemword;			 		// ����� plocsep ����� ������ ����������� plocseptempstr2
	return pmemword;
}//    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END extensmem()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 /*
 /////////////////// ========  ������ � ����(�� ��� ���) ���� ������-� ������ � ��� ���� =======/////////////
 char* writebase(const char **argv, struct word *pmemword, int countnumword)	//argv[0] -��� �������
 // pmemword - ���� �� ������ ������ ��������, countnumword - ����� ������ ��������
 //, ������� ���� ��� ����� � ������ �������� ( pnamenosort )
 {
 printf("   ~~~ ������ � ���� ���������������� ������� �������� �� ������: ~~~  \n");
 puts(argv[0]);  // ���������� � ����������� ����� ������ stdout ������     //temp
 //printf("~~ argv[0] �������� ����������� ��� ��� �-��: ( %s )~~\n", argv[0]);  // temp


 //~~~~~~~~~~   ���������� ����� - ��� [1] ��� ��� � ��� ��� *_nosort.dat ������� �-� rename2()  ~~~~~~~
 char *pnamewordnosort;  // ������ �� ��� ������-��� ��������� ����� "argv[1]_nosort.dat"
 pnamewordnosort = rename2(argv[1], "_nosort.dat",4);
 //.....................................................................................................

 //~~~~~~~~~~~~~~ �������� ��� ���� � ������� ��������� ���� ����- "argv[1]_nosort.dat"  ~~~~~~~~~~~~~~~
 errno_t err = 1;   // ����� 1 -  ?????????????????????????????????? ������ �������
 FILE *nosortfile;		// ��� ���� � ������� ��������� ���� ����- "argv[1]_nosort.dat"
 err = fopen_s(&nosortfile, pnamewordnosort, "w+b");	// ���� ��� ������ ���� ��� �� � ������
 //      � ������� ��������� ���� ����-  "argv[1]_nosort.dat"
 if (err) { perror(pnamewordnosort); exit(1); };

 fwrite(pmemword, sizeof(struct word), countnumword, nosortfile);  // ������ � ���� nosortfile = "argv[1]_nosort.dat"

 //fclose(ptxtfile);	// �� �������� �������� ������ ����
 //fclose(pmyfile);		// ���� � ������� ��������� ���� ����
 fclose(nosortfile);		// ���� � ������� ��������� ���� ����
 printf("~~ ������� ���� ���������������� ��������������� ���: ( %s ) ~~\n", pnamewordnosort);  // temp
 //...............................................................
 //free(pnamewordnosort);	//���-�� ������ � ������ ����� *_common.dat ���������-��� ������������-� ������
 return(pnamewordnosort);
 }//    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END writebase()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 */

 /////////////////// ======== ������ � ����(������� ����������) ����  ��������   ==========///////////  
char* writebase2(FILE *phddfile, char* pfilename, struct word *pmemword, int countnumword)//
																						  //phddfile ���� �� hdd ���� � ������� ��������� ���� ����    ??("argv[1]_nosort.dat")?
																						  //pfilename - ���� ��� �������������� ����� ��� �-�� ��� hdd
																						  // pmemword - ���� �� ��� ������ ������ ��������, 
																						  //countnumword - ����� ��� ����������
																						  //, ������� ���� ��� ����� �  ����������� ( ----- )
																						  //�-� ���� ��������� r+� � ����� ��������� ���� �� hdd 
{
	printf("   ~~~ ������ � ���� %s ���������������� ������� �������� �� ������: ~~~  \n", pfilename);
	//puts(argv[0]);  // ���������� � ����������� ����� ������ stdout ������     //temp
	//printf("~~ argv[0] �������� ����������� ��� ��� �-��: ( %s )~~\n", argv[0]);  // temp

	// ~~~~~~~~~~ �������� ��������� �� hdd ���� ���� ���� � ������ pfilename  ~~~~~~~
	errno_t err = 1;   // ����� 1 -  ?????????????????????????????????? ������ �������
					   //FILE *hddfile = phddfile;					// ���� �� ���� � ������� ��������� ���� ����-("argv[1]_nosort.dat")?
	if (flagtext)		//���� ��� ����� �� ����������� ����� ���� ���� �� ������
	{
		err = fopen_s(&phddfile, pfilename, "w+b");
		if (err) {
			perror(pfilename);
			printf("   ~~~ �� �������� ��� ���� w+b %s  ������� ��������  ~~~  \n", pfilename);
			system("pause"); exit(1);
		}
		else printf("   ~~~ ������� ���� ���� %s  ������� ��������  ~~~  \n", pfilename);
	}
	else
	{
		err = fopen_s(&phddfile, pfilename, "r+b");	// ������� ������ ���� ��� �� � �������� 
		if (err) {
			perror(pfilename);
			printf("   ~~~ �� �������� ������ ���� r+b %s  ������� ��������  ~~~  \n", pfilename);
			system("pause"); exit(1);
		}
		else printf("   ~~~ ������ ������ ���� %s  ������� ��������  ~~~  \n", pfilename);
	};

	//err = fopen_s(&phddfile, pfilename, "r+b");	// ������� ������ ���� ��� �� � �������� 
	//if (err) { perror(pfilename); system("pause"); exit(1); };	//� ����� ����-�� ���� ����-"argv[1]nosort.dat"
	//if (err)				// ?? ���� �� ����� NEWTEXT  ????????????????????????????????????????????????????????????
	//{
	//	

	//	err = fopen_s(&phddfile, pfilename, "w+b");
	//	if (err) { perror(pfilename); 
	//	system("pause"); exit(1); } 
	//	else { 
	//		printf("   ~~~ ������� ���� ���� %s  ������� �������� �� ������: ~~~  \n", pfilename);
	//	};
	// };	//� ����� ����-�� ���� ����-"argv[1]nosort.dat"

	fwrite(pmemword, sizeof(struct word), countnumword, phddfile);  // ������ � ���� hddfile = "*pfilename"

																	//fclose(ptxtfile);	// �� �������� �������� ������ ����
																	//fclose(pmyfile);		// ���� � ������� ��������� ���� ����
	fclose(phddfile);		// ���� ���� � ������� ��������� ���� ����
	printf("~~ ������� ���� ���� ���� � ���-� writebase2(): ( %s ) ~~\n", pfilename);  // temp
																					   //...............................................................
																					   //free(pnamewordnosort);	//���-�� ������ � ������ ����� *_common.dat ���������-��� ������������-� ������
	return(pfilename);
}//    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END writebase2()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 /*
 /////////////////// ======== ������ � ����(������� ����������) ����  ��������   ==========///////////
 char* writebase2old(char* pfilename, struct word *pmemword, int countnumword)//
 //pfilename -  ��� �������������� ����� ��� �-�� ��� hdd
 // pmemword - ���� �� ��� ������ ������ ��������, countnumword - ����� ��� ����������
 //, ������� ���� ��� ����� �  ����������� ( ----- )
 //�-� ���� ��������� r+� � ����� ��������� ���� �� hdd
 {
 printf("   ~~~ ������ � ���� %s ���������������� ������� �������� �� ������: ~~~  \n", pfilename);
 //puts(argv[0]);  // ���������� � ����������� ����� ������ stdout ������     //temp
 //printf("~~ argv[0] �������� ����������� ��� ��� �-��: ( %s )~~\n", argv[0]);  // temp

 // ~~~~~~~~~~ �������� ��������� �� ����� ��������� �� hdd ���� ���� ���� � ������   ~~~~~~~
 errno_t err = 1;   // ����� 1 -  ?????????????????????????????????? ������ �������
 FILE *hddfile;					// ���� �� ���� � ������� ��������� ���� ����-("argv[1]_nosort.dat")?
 err = fopen_s(&hddfile, pfilename, "w+b");	// ������� ������ ���� ��� �� � ��������
 if (err) { perror(pfilename); system("pause"); exit(1); };	//� ����� ����-�� ���� ����-"argv[1]nosort.dat"

 fwrite(pmemword, sizeof(struct word), countnumword, hddfile);  // ������ � ���� hddfile = "*pfilename"

 //fclose(ptxtfile);	// �� �������� �������� ������ ����
 //fclose(pmyfile);		// ���� � ������� ��������� ���� ����
 fclose(hddfile);		// ���� ���� � ������� ��������� ���� ����
 printf("~~ ������� ���� ���� ���� � ���-� writebase2(): ( %s ) ~~\n", pfilename);  // temp
 //...............................................................
 //free(pnamewordnosort);	//���-�� ������ � ������ ����� *_common.dat ���������-��� ������������-� ������
 return(pfilename);
 }//    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END writebase2old()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


 ///////////////////////===========  ���������� ���������� 2  =============////////////////////////////
 struct word * alphabet2(struct word *aa, int *bb)// ������� ��������� �� ������ � �������� �� ����� �������� ������,
 // a ��� ������ � ��c ��������,   b ���������� ��������
 {
 int(*pmeasure)(const void *, const void *);  //������ ��������� �� ������� ��� �������� ���������� �  �-� qsort()
 pmeasure = measurealph;						//  � ���������� ��������� ������ �������
 // ����� ���������� ������� qsort � ��������� ���������� �� ��������� ���� ������� measure
 qsort(aa, *bb, sizeof(struct word), pmeasure);	//|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1
 int i;
 for (i = *bb - 32; i <= *bb - 1; i++)
 {
 printf(" ~~~ ������������ ( %s )   ~~~\n", aa[i].en);    // temp
 }
 return aa;
 };//    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END alphabet2()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 ///////////////////////===========  ���������� ���������� 3  =============////////////////////////////
 struct word * alphabet3(struct word *aa, int *psize)// ������� ��������� �� ������ � �������� �� ����� �������� ������,
 // a ��� ������ � ��c ��������, size ���������� ��������
 {											// �������� ����
 int(*pmeasure)(const void *, const void *);  //������ ��������� �� ������� ��� �������� ���������� �  �-� qsort()
 //  � ���������� ��������� ������ �������
 // ����� ���������� ������� qsort � ��������� ���������� �� ��������� ���� ������� measure
 pmeasure = measurealph;
 qsort(aa, *psize, sizeof(struct word), pmeasure);	//|1|1|1|1|1|1|1|1|1|1|1|1|
 #ifdef ALPHABET
 int i;
 for (i = 0; i < *psize ; i++)
 {
 printf(" ~~~ ������������  %d - ( %s )   ~~~\n",i, aa[i].en);    // temp
 }
 #endif //ALPHABET
 return aa;
 };//    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END alphabet3()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 */

 ///////////////////////===========  ���������� ���������� 4  =============////////////////////////////
struct word * alphabet4(struct word *aa, int *psize, int(*pmeasure)(const void *, const void *), int disloc)
	// ������� ��������� �� ������ � �������� �� ����� �������� ������, 
	// aa ��� ������ � ��c ��������, psize - ���� ���������� �������� 
	// *pmeasure -���� �� � �������������� ����������
	// disloc - �������� ���� � ��������� ������� ���������� ��� ����������

{	// ��������� ID ���� ���� ��-� � ����������� �� ����� ???????
	//int(*pmeasure)(const void *, const void *);  
	//������ ��������� �� ����� ��� �������� ���������� �  �-� qsort()
	//  � ���������� ��������� ������ �������
	// ����� ���������� ������� qsort � ��������� ���������� �� ��������� ���� ������� measure
	//pmeasure = measurealph;
	qsort(aa, *psize, sizeof(struct word), pmeasure);	//����� ����������
#ifdef ALPHABET
	int i;
	for (i = 0; i < *psize; i++)
	{
		printf(" ~~~ ������������  %d - ( %s )   ~~~\n", i, aa[i].en);    // temp
	}
#endif //ALPHABET
	return aa;
};//    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END alphabet4()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 

  ///////////////////==========     �-� ����������� ��������� �����  =======/////////////////////////////////
int measurealph(const void * a, const void * b)		//   
													// � -� ���������� ENGL �������� ������� �������� ���� �����(�� ���������� �� ���) 
{
	const char * string1 = (((struct word *)a)->en);
	const char * string2 = (((struct word *)b)->en);
	int temp = _stricmp(string1, string2);	// ���� ������ ��� ������ �������
											// �� ������� �������������� �����
	return temp;
};//    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END measalph()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 

  ///////////////////////===========  ���������� �� ������ id ��������� word   ========////////////////////
struct word * idsort(struct word *pin, int *psize, int(*pmeasure)(const void *, const void *), int disloc)
	// ������� ��������� �� ������ � �������� �� ����� �������� ������, 
	// pin ��� ������ � ��c ��������, psize - ���� ���������� �������� 
	// *pmeasure -���� �� � �������������� ����������
	// disloc - �������� ���� � ��������� ������� ���������� ��� ����������
	// ��������� ID ���� ���� ��-� � ����������� �� ����� ???????
{
	struct word * ptemp = NULL;
	ptemp = (struct word *) malloc((*psize) * sizeof(struct word));
	if (ptemp == NULL)printf("idsort() �� ��������� ������ ��� ���� ������ ptemp \n");
	printf(" \n\n~~~ ����� in idsort() -  id = %d \n", pin[0].id);
	memmove(ptemp, pin, (*psize) * sizeof(struct word));//* sizeof(struct word)

	printf(" \n\n~~~ ����� in idsort() - ��������������� �� ����� ������ �������� ~~~ id = %d \n", pin[0].id);
	// temp
	qsort(ptemp, *psize, sizeof(struct word), pmeasure);	//����� ����������
															//printf("    \n");
#ifdef IDSORT
	printf("This \"Print\" inside to idsort() in engllib 2_c - \n");
	int m;
	for (m = 0; m < *psize; m++)				//
	{													//
		printf(" _ %3d.  id=%3d ___ ( %s )___[ %d ]   \n", m, ptemp[m].id, ptemp[m].en, ptemp[m].repeat);    // temp
	}
#endif
	printf("    \n");
	for (m = 0; m < *psize; m++)
	{
		ptemp[m].repeat_id = m;
	}

	for (m = 0; m < *psize; m++)
	{
		pin[m] = ptemp[m];    // ����������� ������� (��� return) �� ����������
	}
	free(ptemp);
	return pin;
};//    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END idsort()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 

  ///////////////////==========     �-� ��������� ����� �� ����������� =======///////////
int measurerepeat(const void * a, const void * b)		//   
														// � -� ���������� ENGL �������� ������� �������� ���� �����(�� ���������� �� ���) 
														// + ���� a>b 0 if a=b - if a<b
{
	const int  repeat1 = (((struct word *)a)->repeat);
	const int  repeat2 = (((struct word *)b)->repeat);
	int temp = (repeat2)-(repeat1);
	return temp;
};//    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END measurerepeat()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  

  ////////////============   a-� ��������� ������ - ����� �����   ============/////////////////////////
char* rename2(const char* poldname, char *paddstring, int del) // � -� ����������� ��� poldname.ext
															   //�� del �  ��������� paddstring ������� ��� ��� ������� ���� � ����� ���� �� ����
{
	//��� ��� oldname ������������� �� ������ del , ��������� ��� pletteadd
	//� �� ��� ������������ � ��������� �� ������ - pnewname
	char *ptempstrstr = (char*)malloc(strlen(poldname) + strlen(paddstring));
	// ������ ��� ��� ���
	//printf(" ########  inside of rename2(); #########\n ");    // temp
	memset(ptempstrstr, '\0', (strlen(poldname) + strlen(paddstring)));			// ���������� \0 
	strncpy(ptempstrstr, poldname, (strlen(poldname) - del));	// �������� ��� .ext
																//printf(" ~~~����� ����� ptempstrstr, = ( %s )   ~~~\n", ptempstrstr );    // temp
	strcat(ptempstrstr, paddstring);  // ������ ������
	printf(" ~~~������ rename2() �� ����� ptempstrstr,= ( %s ) ~~~\n", ptempstrstr);  // temp
	return (ptempstrstr);
}; //    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END rename2()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 




   ////////===========  ���������� ������������� ����. ��������� repeat  ===========///////
struct word * reduct3(struct word *pa, int *psize)	//��������� ������������� ����� ����� ��� ����
													// ��������� ���� id pa-���� �� ������ ���-��, 
													//psize-���� �� ���-� ����  ����-��� � ���� - ����������� ��� ������������� ������ 
{
	///////////===========  ������ ���� repeat = 1 ��� ���� �������� � ������� ---------------
	int n = *psize;  //���������� ��������� ���������� �������� � �������, ������ �-��� �����������
	int i = 0;
	for (i = 0; i < n; i++)				//������ ���� repeat = 1 ��� ���� �������� � �������
	{
		(((struct word *)pa + i)->repeat) = 1;
	}

	////////// ======= ���� ������� ����� ������ ptempstr � ������������� ���������   ----------------
	struct word *ptempstr = (struct word*)malloc(*psize * sizeof(struct word));  // ���� �� 
																				 //������� ������ � ������������� ���������
																				 // � �� ����� ������������ ��-�� ���-�� �������� �� ��� ��� ����������
	if (ptempstr == NULL)printf("�� ��������� ������ ��� temp � reduct3() \n");
	struct word *prev = (struct word*)malloc(sizeof(struct word));  //����� ��������� 
																	//�� ��������� (�������) ������� ��������� (��� ���������)  
	if (prev == NULL)printf("�� `	````````````````��������� ������ ��� prev � reduct3() \n");
	for (i = 0; i<n; i++)	(((struct word *)ptempstr + i)->repeat) = 1;		//������ 1-��� ���� ����� repeat ������� ptempstr[]
	i = 0;
	ptempstr[0] = pa[0];	// ������� � ���� ���� �������� �������� ������� ����������� ����� ���������
	prev[0] = ptempstr[0]; // �������� ���������� ������� (��� ���������)
	int t = 0;		// �������  �������� ������ ������� ptempstr[t] (������ ��� i)
					// 
	for (i = 1; i<n; i++) // ������� c 1-�� ������� ���� �������� ������ �������� ������� pa[i] ����������� 
	{		//����� ��������  � ����� � ��������� � ��������� ����������� � *prev ���������� ����� ����� *->en
		if (measurealph(prev, (pa + i)) == 0)  // ���� ��������� ����� ��������.....
		{
			(((struct word *)ptempstr + t)->repeat) += 1;  // ������ ���� repeat �������� ptempstr[t] �� ������������� t
		}
		// ����� ���������� ���� ��� � ������� �� ������� � ������ ����� ->en 
		else
		{
			t += 1;					// ���� ������ ���� ������� ptempstr[t]
			ptempstr[t] = pa[i];		// ������� �� ���� ���� �� ������������� pa[i] ��� ������� � ����� ����� ->en
			prev[0] = ptempstr[t];		// �������� � ��������� �������  ������� ���������� �������
		}
	}								// ����� �������� ���� �������� ������� pa[i] ����������� ����� �������� � �����
	*psize = (t + 1);		// ����� ������ ��� ������� ��������
	struct word *pret = (struct word*)malloc(*psize * sizeof(struct word));  // ���� �� �������� ������� ������ ��� ����� �� �
	if (pret == NULL)printf("�� ��������� ������ ��� temp � reduct() \n");
	// ���������� ������������ ������� temp � ��������� ���� � � pret
	int k = 0;
	for (i = 0, k = 0; i <= t; i++, k++)
	{
		pret[i] = ptempstr[k];    // ����������� ������� (��� return) �� ����������
	}
	for (i = 0; i < *psize; i++)  // ���������� "�����������" id
	{
		pret[i].id = i;
	}

#ifdef REDUCT3
	printf(" \n\n~~~ ����� in reduct3() - ��������������� ������ �������� ~~~ \n");
	int m;												// temp
	for (m = 0; m <= t; m++)				//
	{													//
		printf(" _ %3d.  id=%3d --- ( %s )---[ %d ]   \n", m, pret[m].id, pret[m].en, pret[m].repeat);    // temp
	}
	printf(" \n\n~~~ ����� in reduct3() - ��������������� ������ �������� ~~~ pret[0].id = %d\n", pret[0].id);
#endif// REDUCT3
	free(ptempstr);
	free(prev);
	return pret;
}//    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   end reduct2()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 

 ////////===========  � �������� ms � ������� key ��� ����� ��� ��-�� =============///// 
char delayorkey(int ms, char key) // � �������� ms � ������� key ��� ����� ��� ��� ��-��
{
	//blok time or KEY
	printf("clock = %d\n", clock());
	//int ms = 5000;
	int c = clock() + ms;
	int r;
	//char key = '0';
	do {
		r = clock();
		if (_kbhit())
		{
			key = _getch();
			break;
		}
	} while ((r < c));//key != '0' 
	if (r != c)
	{
		printf("enykey is pressed\n");
		printf("Key [ %c ] is pressed\n", key);
		printf("clock = %d\n", clock());
	}
	else
	{
		printf("Key [ %c ] is not pressed\n", key);
		printf("clock = %d\n", clock());
	}

	return key;
};//    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   END delayorkey()   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 


