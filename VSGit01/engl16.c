// engl16 второе дополнение для git 21.01.2021
// после сброса - третье дополнение для git 26.01.
// 29 01 21  commit visual
//.............
//...............................



//24/09/20 после RRRengl09 развиваем работу с ininame.dat
// 31/07/20 дробление на мелкие ф-ции sepmini()
// extensmem()
// Начало работать
// Надо добавлять первую сортировку ( по алфавиту)
//
#define _CRT_SECURE_NO_WARNINGS  //   ?? подробнее об предупреждениях ??
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


FILE *ptxtfile; //---> текст который читать - argv[1] первый аргумент ком строки "txt2.txt"
FILE *pmyfile;	//---> указатель на структ. файл в котором сохранять базу слов - argv[2].dat"
FILE *pinifile;	//---> указатель на структ. файл в котором сохранять файлов ininame.dat
FILE *pnosortfile;	//---> указатель на структ. ф в котор сохр несорт базу слов - argv[1]_nosort.dat"
FILE *psortfile;	//---> указатель на структ. ф в котором сохр сорт базу слов - argv[1]_sort.dat"

char *pnamenosort;		//указат на имя ф-ла с запис несорт масс стр 
struct word *pmemword;		//глоб указат -> в main()на первичное выделеие ДИН памяти 
							//под МАССИВ СТРУКТУР (word) для отсепарирования token()
							//далее память будет перерасширятся по этому указателю
struct word *pmemsortword;  // указ на д пам стрктур с отсортированными словами
struct word *palphabetword;  // указ на д пам стр-р с отсорт-ми и сокращенными словами
long amountmem = 0;		//--- РАЗМЕР в байтах дин пам выде-мых под структуры word
long *pamountmem;		//--->укз РАЗМ в б-тах ДИН пам выде-мых под несорт структ word
int countnumword = 0;	//---счётчик инкремента слов а значит и стр при сепар-и
int *pcountnumword;		//--->указатель на счетч слов
struct ininame *pmemininame;			//--->указ на ДИН пам с базой имён программы
int flagtext = NEWTEXT;	//переменная -ФЛАГ режима работы со стар или нов текстом
						//т е будет ли сепарироваться по новой и писаться в нофую базу слов 

						//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%       main     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
int main(int argc, const char ** argv, const char** env)
{
	system("chcp 1251 > nul");

	//==== проверка сущес-т файл имён - создаём нов или раб с ранее созданным,===
	errno_t err;	//  переменная (int?) для вывода ошибок ? внутр переменная (int?)
					// проверка есть ли ininame.dat файл в котор сохр-ть имена ф-лов "ininame.dat"=======				
	err = fopen_s(&pinifile, "ininame.dat", "r+b");// открыть на чт с дозап

												   //не существует файла имён - создаём урок по новому================
	if (err != 0)//не существует файла имён - создаём урок по новой

	{//%%%%% т е ПЕРВЫЙ урок для нового текста  ==%%%%%%%%%%%%%%%%%%%%%%%
	 //char * ptempin = (char*)malloc(NAMEENGLTEXT);


		puts("\n !!!  не существовал файл пользователя \
 inname.dat с именами баз текстов \n");
		printf("\n    Введите имя файла с английским текстом \n\
 ___ ___________, длнной не больше %d символов \n", NAMEENGLTEXT);
#ifndef DEBUG
		char tempin[NAMEENGLTEXT + 1];	//масс для заполнения именем вх ткст ф-ла
		fgets(tempin, NAMEENGLTEXT, stdin);
#endif // DEBUG
#ifdef DEBUG						//на время отладки
		char tempin[] = "text00.txt";	//врем знач масс для заполн им вх ткст
#endif // DEBUG

		int namesize = strlen(tempin);//разм строки с ИМЕНЕМ вх ф-ла текста
#ifndef DEBUG
		tempin[strlen(tempin) - 1] = '\0';
#endif // !DEBUG
#ifdef DEBUG
		tempin[strlen(tempin)] = '\0';
#endif // DEBUG

		struct ininame memininame;  //структ для настройки урока
		strcpy(memininame.textname, tempin);  // имя англ текста в структуру

		printf("\n    Введенное имя файла с английским текстом \n\
 в буфере tempin - %s \n размер имени текста = %d байт\n\n", tempin, namesize);
		//===========// Формируем имя для базы слов - .dat файла //===================//
		char *pnamewordnosort;  //указ дин строки для преобраз. имя вхдн файла_nosort.dat"
		pnamewordnosort = rename2(tempin, "_nosort.dat", 5);
		printf("\n  имя файла  сепарир но несорт слов \ - %s \n", pnamewordnosort);

		//======// создание по укз pmemininame дин пам с базой имён программы //==========
		pmemininame = (struct ininame*)malloc(sizeof(struct ininame));//глоб указ
		pmemininame = &memininame;// инициализация дин памяти ininame структуры (pdat1name)
		if (pmemininame == NULL)
			printf("Не выделена память под базу имён программы \n");
		else
			printf("  Выделена дин пам pmemininame = %d Bytes \n \
под базу имён программы \n", sizeof(struct ininame));
		//=====// выбор tempkey по умолч через msek или возвр наж клав //=========	
		printf("\n  если надо сделать настройку урока нажмите любую букву\n");
		// 
		char tempkey = '0';
		tempkey = delayorkey(5000, tempkey);
		if (tempkey == '0')//стандартный урок
		{	//тут станд настройки по умолч в pmemininame
			printf("\n  Делаем стандартный урок \n");

		}
		else//тут дополнительные настроки урока в pmemininame
		{
			printf("\n  Дополнительные  нестандартные настройки урока\n");

		};

		//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

		// здесь все операции по сепарированию нового текста простой блок ===================
		{
			// открытие входного txt файла ==============================================
			char* pintextname; //указ на динпамять с именем входн текста зачем?
			pintextname = (char*)malloc(strlen(tempin));//копирование из статич массива
			int ttt = strlen(tempin);
			strcpy(pintextname, tempin, strlen(tempin));  // имя англ текста в

			err = fopen_s(&ptxtfile, pintextname, "r+b");// инициализируется указатель FILE *ptxtfile 
														 //на вх-ой txt ф-л (argv[1])
														 //  и открывается в режиме (rb)-  "txt2.txt" 
			if (err) {
				puts("нет имени входного ф-ла \n");
				perror("нет требуемого - имени входного ф-ла \n");
				system("pause");
				exit(1);
			};  // puts("нет требуемого ком строкой ф-ла \n"); 

				//~~~~~~  перенос ф-ла текста в оперативную динам память, для цього  ---> ================

				//~~~~~~~  определяем РАЗМЕР файла в байтах  ------------------------------------------
			long txtSize = 0;		//--- размер в байтах файла котор будет считан в дин память
									// устанавливаем текущ позицию в конец файла, т е (смещ на 0 относ конца ф-ла)	 
			fseek(ptxtfile, 0, SEEK_END);
			txtSize = ftell(ptxtfile);                       // ПОЛУЧАЕМ РАЗМЕР В БАЙТАХ 
															 // и записываем в txtSize
															 //rewind(ptxtfile);  //+ очистка буфера      														
			fseek(ptxtfile, 0, SEEK_SET);	// перевести текущую поз на начало файла
											//
			printf("Размер памяти входного текста = %d Bytes \n", txtSize);

			//~~~~~~  выделение дин памяти буфеp *ptxtbuf---------------------------------
			char * ptxtbuf;			//--->  локальн указатель на дин пам. ptxtbuf 
									//		для хранения содерж-го из вх-го файла...........
			ptxtbuf = (char*)malloc(sizeof(char) * txtSize); // выделить дин память ptxtbuf для хран-я содерж-го из ф-л а
															 // далее подлежащего разбиению токенами
			if (ptxtbuf == NULL)
			{
				fputs("Ошибка памяти", stderr);
				exit(2);
			}
			printf("~~ выделена дин пам. ptxtbuf для хранения текста из файла ~~\n");

			// ------из ptxtfile считываем файл в буфер	ptxtbuf!!!------------------------------------
			size_t result = fread(ptxtbuf, sizeof(char), txtSize, ptxtfile);  // считываем файл в буфер!!!
			if (result != txtSize)  //если не совпало число считанных байт
			{
				if (feof(ptxtfile)) printf("Преждевременное достижение конца файла.\n");
				else printf("Ошибка при чтении файла.\n");
				exit(3);
			}
			fclose(ptxtfile);	//поработал и закрыл )) файловый ввод из которого читается входной текст

#ifdef TEXT	//~~~~~~  текст выв-ся в станд. поток вывода консоли НА ЭКРАН (для  отладки)===================
			if (puts(ptxtbuf) == EOF) {
				printf("Ошибка при записи из текстов файла \n");
			}  // -> -> -> 
			else {
				printf("Файл текста  считан-записан в ф-ции main нормально\n");
				printf("		~~~ !!!!!Текст выше - это содержащийся в файле %s ~~~       \n \
	!!!!!!!!на который указывала ком строка, далее сепарирование \n", argv[1]);	//  ???*
			}
#endif//     ~~~~~~~~~~~~~~~~~~~~~ после отл можнои убрать  ~~~~~~~~~~~~~~~

			//~~~~~   самое первое выдел памти *pmemword под сепарирование структур прост блок =======================
			{
				printf("  Размер памяти под одну структуру %d байт\n", sizeof(struct word));
				amountmem = MAX_WORD * sizeof(struct word);  //размер начально выд-мой памяти (байт)
				pmemword = (struct word *) malloc(amountmem);   //самое первое выделение памяти 
																//  под сепарацию и занесения строк в структуры 
																//временно - начальное количество MAX_WORD 
				if (pmemword == NULL)printf("Не выделенна память под punsort \n");
				else printf("  Выделенна память punsort = %d Bytes \n  под %d неотсортированных структур \
  и поехали! сепарировать\n",
					MAX_WORD * sizeof(struct word), MAX_WORD);				//    отладка
			}

			//~~~~~~~~~    далее (подготовка аргументов?) вызов ф-ции сепаррования - sepmini() ------   
			pamountmem = &amountmem;  // указ на РАЗМ дин пам БАЙТ для сепарир стр-р(пока= 8 стр)
			pcountnumword = &countnumword; //указ на счётч инкр-та СЛОВ = СТРУКТ при сепар-и 
										   // pmemword - указ на МАССИВ СТРУКТУР (word) для отсепарирования token()
										   //ptxtbuf - указ на дин массив неразбитого текста - копии входн файла
										   //argv[1] - из ком строки имя для отладки printf
										   // вызов сепарирования  long amountword = *pcountnumword / sizeof(struct word); 
			pmemword = sepmini(pmemword, pamountmem, ptxtbuf, pcountnumword, argv[1]);


			//~~~~~~~~~~~~   далее запись в файл базу сепарированных но несортированных структур =================				
			//char *pnamewordnosort;  //указ дин строки для преобраз. имя файла "argv[1]_nosort.dat"
			// ~~~~~~~преобразов имени - арг[1] для несортир-го масс *_nosort.dat вызовом ф - и rename2()
			{//~~~~~~~  преобразов имени - арг [1] ком стр в нов стр *_nosort.dat вызовом ф-и rename2()
			 //pnamewordnosort = rename2(argv[1], "_nosort.dat", 4);
			}
			//~~~~~~~~~~~~ запись в hdd файл(заранее переименов) базу несортир структур  ---///////////////  
			writebase2(pnosortfile, pnamewordnosort, pmemword, countnumword);//
																			 //pnosortfile - указ на откр внутр ф-ции hdd файл в котором сохранять базу слов 
																			 //pnamewordnosort - уже сформированное ранее имя ф-ла для hdd ("argv[1]_nosort.dat")
																			 // pmemword - указ на дин массив несорт структур, 
																			 // countnumword - число несорт структур
																			 //,?? возврат указ имя файла с  структурами ( ----- )????
			puts(pnamewordnosort);		//debug


										//~~~~~~~~~~  запись в  дин пам pdat1name имени файла несорт-ных структ word    ~~~~~~~~~
			pmemininame->idname = 0;
			strncpy(pmemininame->name, pnamewordnosort, EN1);


			//~~~~~~~~~~   запись дин памяти с 1-м именем  XXX_nosort.dat в файл имён "ininame.dat"   	
			err = fopen_s(&pinifile, "ininame.dat", "w+b");//XXX_nosrt.dat сохр в ф-л "ininame.dat"
			if (err)
			{
				puts("\n Ошибка! \n Неудача отытия ранее созданного ф-ла имён пользователя \n");
				system("pause");
				exit(1);
			}
			fwrite(pmemininame, sizeof(struct ininame), QUANTITYNAME, pinifile);//ininame.dat
																				//fwrite()
																				//~~~~~~~~~~   преобразование имени для сортировнного массива  _sort.dat





			free(ptxtbuf); //лок пам ptxtbuf для хранения текста из файла
			free(pmemword);
		}// конец всех операций по сепарированию и сортировке нового текста простой блок
		 // конец всех операций по сепарированию и сортировке нового текста простой блок





		 //..................................................................


		free(pnamewordnosort); //лок дпам - строка для формирования им вхдн ф.._nosort.dat
							   // в стар - pdat1name ????
		system("pause");

	}//end if ....не существует файла имён - создаём урок по новой

	 //...else открыть и раб с РАНЕЕ СОЗДАННЫМ inname.dat и старым текстом
	else//...else открыть и раб с РАНЕЕ СОЗДАННЫМ inname.dat и старым текстом
	{	// т е ПОВТОРНЫЙ урок разобранного ранее текста
		puts("\n !!!  уже существовал файл пользователя \n\
 inname.dat с именами баз текстов \n");








		system("pause");

	}//end else ....раб с ранее созданным inname.dat и старым текстом



	printf("\n\n             The END!   -     конец урока! \n\n\n");
	system("pause");
}  //end main