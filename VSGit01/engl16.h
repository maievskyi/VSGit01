#pragma once
#ifndef ENGL09_H 
#define ENGL09_H
#define NAMEENGLTEXT 64 // max ������ ����� ����� ���� ������ 
#define EN 32 //������ ���� ������ (������ �����) � ������ word
#define EN1 256 //������ ����� ����� ��� ���������� � ����������� word 
#define RU 32 //������ ��� ������ � ������ word
#define MAX_WORD 8//��������� ������ ������� �������� word
#define MULT_DIN_MEM 2 // � ������� ��� ��� ��� ������ ���� ��� ��� ������������ EOF
#define NAMENOSORT 64 //������ ��-�� ��������������� ���������������� �-��
#define NEWTEXT 1 //���� ��� ���� ������ ������
#define OLDTEXT 0 //���� ��� ���� ������� ������
#define QUANTITYCHARNAME 256 //?? ���-�� ���� � ����� ������ � ���� ��� �-� ����� ??
#define QUANTITYNAME 8 // ���-�� ������� ��������� ���-��� � ������� ��� �-� ���������
// #define d ((&struct word a.c)-(&struct word a)) 


#define TEXT 
//#define SEPARATED  // sepmini()
//#define M_SORT		// main()
#define SORT
//#define ALPHABET // ������������ alphabet3()
//#define REDUCT3  //_________________________________
#define IDSORT

//#define MAX_WORD1 100 //������ ������� ������ word

//�-� ����� ��������� �� � ������ � ������� ������� - str word *pmemword
// ������� ��������� � ���������� � �-�,
// pamountmem ���� �� ������ � ��� str word
//multipl ����� ����� ��� ������ ��� ������ ��� token() 
//ptxtbuf ����. �� ��� ������ ����������� ������ - ����� ����� �����
//pcount - ��������� ����� ������������ ���� ��� �������
// ����� ��� ������� ������� ������� (����������������) �������� � ���� �������
// arv1 ��� ������������� ����� ��� ������ �������� ����� - ����� ������ ��� fprint()????
struct word * sepmini(struct word *pmemword, long *pamountmem, char *ptxtbuf, int *pcount, char const *arv1);  //�-� �����
																											   // 

																											   //�-� ������ ������ int size ��� ������ struct word *mem �� ������� *pnewsize �� 
																											   //������� *pnewsize  � ���������� � ���� ������ ������ ������ struct word *pmemword 
																											   // � ����� ????????????????? ���� �� ��� ������
struct word *extensmem(struct word *pmemword, long *pamountmem, long newamountword, int *pcountnumword);

char* writebase(const char **argv, struct word *pmemword, int countnumword);	//, char *pnamenosort

char* writebase2(FILE *phddfile, char * namefilehdd, struct word *pmemword, int countnumword);	// 
																								// phddfile ���� �� hdd ���� � ������� ��������� ���� ���� 
																								//  namefilehdd - ��� �� �����; pmemword - ���� �� ������ ��������, 
																								//countnumword - ����� ������ ��������; ������� ���� ��� ����� �������� - namefilehdd;
																								//�-� ���� ��������� r+� � ����� ��������� ���� �� hdd 

struct word * alphabet2(struct word *, int *);  // ������� ���� ��� � ��������  
												//�� ����� ���� ������, ��� ������ � ��� ��������,  ���������� �������� 
struct word * alphabet3(struct word *aa, int *psize);
// ������� ��������� �� ������ � �������� �� ����� �������� ������, 
// aa ��� ������ � ��c ��������,  psize ���������� �������� 
struct word * alphabet4(struct word *aa, int *psize, int(*pmeasure)(const void *, const void*), int disloc);
// ������� ��������� �� ������ � �������� �� ����� �������� ������, 
// aa ��� ������ � ��c ��������,  psize ���������� �������� 
// *pmeasure -���� �� � �������������� ����������
// disloc - �������� ���� � ��������� ������� ���������� ��� ����������
int measurealph(const void *, const void *);   //
											   // � -� ���������� ENGL �������� ������� �������� ���� �����(�� ���������� �� ���)
											   // ���� ������ ��� ������ ������� �� ������� �������������� �����

struct word * idsort(struct word *pin, int *psize, int(*pmeasure)(const void *, const void *), int disloc);
// ������� ��������� �� ������ � �������� �� ����� �������� ������, 
// aa ��� ������ � ��c ��������, psize - ���� ���������� �������� 
// *pmeasure -���� �� � �������������� ����������
// disloc - �������� ���� � ��������� ������� ���������� ��� ����������
// ��������� ID ���� ���� ��-� � ����������� �� ����� ???????

int measurerepeat(const void * a, const void * b);//
												  // � -� ���������� ENGL �������� ������� �������� ���� �����(�� ���������� �� ���) 

struct word * reduct3(struct word *pa, int *psize);// pa-���� �� ������ ���-��, 
												   //psize-���� �� ���-� ����  ����-��� � ���� 

void rename1(const char* oldname, char *letteadd, char *newname); //� -� ��������  ������ �
																  //����� ����� oldname, ��������� - ��� letteadd 
char* rename2(const char* poldname, char *paddstring, int del); // � -� ����������� ��� poldname.ext
																//�� del �  ��������� paddstring ������� ��� ��� ������� ���� � ����� ���� �� ����
char delayorkey(int ms, char key); // � �������� ms � ������� key ��� 
struct word       // ��� ��� �������� ���� � ��������� � �� �
{
	int id;  // ���������� id ���������
	int repeat_id;	// ��������� �� ����������� � ������
	int random_id;	// ������������ ��������� � ������
	int temp_id;	//
	int temp2_id;	//

	int repeat;	// ���������� ���������� ����� � ������


				//char rait;  // �������
				//����� � ������ ����;
	char en[EN];    //������ �������� - �������� �� #define
	char ru[RU];	// �� ��
	char tempchar; // ������� �������� ��� ������ ��� �����  F3
	int tempint;
};
struct ininame       // ��� ��� �������� ��� ������ � ������ ����
{				//����� � ������ ����;
	int idname;
	char textname[EN1];    //��� ����� ���� ������ 
	char name[EN1];    //��� �����
					   //char namepath[EN1];	// c ������ ����
					   //int number;  // ������ �����
					   //char namehelp[EN1]; // ��������� � �����

};

#endif#pragma once
