# ПРОЕКТ: VirtualLibrary
1.Изграждане и архитектура
2. Основни класове
	
	1.Book
	•Член-данни
	•Методи
	
	2.Library
	•Имплементация
	•Член-данни
	•Методи 
	
	3.User
	•Член-данни
	•Методи 
	
	4.UserList
	•Имплементация
	•Член-данни
	•Методи 
	
	5.UsefulFunctions
	
3. Тестове
•BookTests
•LibraryTests
•UserTests
•UserListTests
•UsefulFunctionsTests
	
4. Външни източници


## 1. Изграждане и архитектура
Програмата е съставена от 4 основни класа - Book, Library, User и UserList. За тях има съответно .h и .cpp заради разделната компилация. В main метода има списък с потребители registeredUsers, където са запазени регистрираните потребители в файла registeredUsers.txt, а в началото се съхранява информация само за администраторски профил. Има библиотека, а наличните в нея книги се съхраняват във файла availableBooks.txt. 
Потребителят може да избира измежду 9 команди, а именно:
	1.login
	2.register
	3.sort
	4.find
	5.add
	6.remove
	7.display
	8.exit
	9.help
Приема се вход на потребителя, където ако той не съответства на нито една от подадените команди, се извежда съобщение за грешка ‘Invalid command, enter "help"’.
	1.login
	•Потребителят въвежда потребителско име и парола. Ако това потребителско име не фигурира в списъка с регистрираните потребители, извежда се съобщение за грешка и операцията се прекратява.Ако потребителят влезе с профила на администратор, той получава администраторски права и от него няма да се иска да въвежда парола за командите add и remove . Използва методите copyString() и enterPassword() от UsefulFunctions.cpp, както и методите findIndex и setAdminStatus() от класа UserList.
	
	2.register
	•Потребителят въвежда потребителско име и парола и се запазва в списъка с регистрирани потребители. Ако вече има потребител с такава регистрация, извежда се съобщение за грешка и операцията се прекратява. Използва функциите copyString() и enterPassword() от UsefulFunctions.cpp, както и findIndex() и addUser() от класа UserList
	
	3.sort
	•Сортира книгите в библиотеката спрямо даден критерий (автор, заглавие, рейтинг) във възходящ/низходящ ред, спрямо избора на потребителя. Използва метода sort() от класа Library.
	
	4.find
	•Намира книга по даден критерии (автор, заглавие, част от описание). Използва метода find() от класа Library.
	5.add
	•Ако потребителят има администраторски права, създава се книга и тя се добавя към библиотеката, като се въвежда пълна информация за нея (автор,заглавие,описание,име на файл в който е записана, рейтинг). Използват се методите setField() и authorize() от UseulFunctions.cpp,сетъри от класа Book,getAdminStatus() от User и addBook() от класа Library
	
	6.remove
	•Ако потребителят има администраторски права, премахва книга от библиотеката спрямо даден критерий (автор, заглавие, част от описание). Използват се методите  authorize() от UseulFunctions.cpp,и removeBook() от класа Library.
	
	7.display
	•Показва книга, записана в библиотеката, като се избира дали това да стане по страници или изречения. Използват се методите displayBook() и findBy() от Library.
	
	8.exit
	•Приключва изпълнението на програмата
	
	9.help
	•Извежда на потребителя от какви команди може да избира, а именно „login,register,sort\,find,add,remove,display,exit“

________________________________________
________________________________________

## 2.Основни класове

### 1. Book
Класът Book съдържа гетъри и сетъри , както и конструктори, копи конструктор, деструктор, оператор= и move семантики заради динамичната памет. Освен това е дефиниран и операторът за извеждане на книга с цел по-лесна визуализация. Съдържа имплементацията на изброимия тип Rating, който приема стойности UNRATED=0,BAD,OKAY,GOOD,VERY_GOOD, EXCELLENT. 
Член-данни:
	•char* mAuthor
	•char* mTitle
	•char* mFileName
	•char* mDescription
	•Rating mRating
	•unsigned mISBN (international standard book number)
Класът има и допълнителен статичен член,int count, който се използва за генериране на уникален ISBN номер Член-данните mAuthor, mTitle, mFileName и mDescription са динамични, за да може да имат неограничена дължина.
Член-функции:
	
	private:
	•void setStringValuesToNullptr() – задава началните стойности на динамичната памет на nullptr
	•void copy(const Book& other) - копира обект от тип Book, използва се в оператор= и копи конструктор
	•void free() - изтрива динамичната памет, използва се в оператор= и деструктор
	•void setISBN(unsigned ISBN) – в private секцията, задава уникален номер съответстващ на това коя на брой е книгата.
	public:
	•bool operator==(const Book& other) const - - проверява дали две книги са еднакви като сравнява уникалния им ISBN
	•void print() const - принтира информация за книгата във формат <заглавие> <автор>  <ISBN>
	•void printDetailed() const - принтира детайлна информация за книгата

 Също така съдържа реализирани гетъри, сетъри, голяма шестица и някои конструктори за по-лесно тестване.
________________________________________

### 2.Library

•Имплементация:

Класът Library представлява списък от книги и методи за работа с него. Списъкът е всъщност масив от указатели към обекти от тип Book, за да се избягва многократното копиране на обекти в методи като swap и sort. Когато библиотеката запълни ¾ от капацитета си, вика се метода resize(), който преоразмерява масива и копира първоначалните съдържания. Конструкторът приема име на файл, където да бъдат запазени имената на книгите, налични в библиотеката. В библиотеката могат да бъдат търсени, добавяни, премахвани, сортирани и показвани книги, в зависимост от това какви критерии въведе потребителя (по име, рейтинг, автор). Дефинирани е голямата шесторка заради динамичната памет. Конструкторът по подразбиране е премахнат, за да може винаги при създаване на библиотека да се подава файл, в който да бъдат записани книгите, които тя съдържа.

Член-данни:
	•Book** mBooks
	•int mCount
	•int mCapacity
	•char* mAssociatedFile

Член-функции:
	private
	•void copy(const Library& other)- копира обект от тип Library, използва се в оператор= и копи конструктор. Използва copyString() от UsefulFunctions.cpp
	•void free()- изтрива динамичната памет, използва се в оператор= и деструктор
	•void resize()- използва се за преоразмеряване на масива, когато добавим нов елемент
	•void sortByRating()- сортира по рейтинг. Използва метода sortPredicateAscension() ot UsefulFunctions.cpp за да определи режима на сортиране ( 1 – възходящ ред, 2- низходящ ред ).
	•void sortByString(char* (Book::* function)() const)- сортира спрямо някакъв низ, който трябва да е от член-данните на книгата, използва се за сортиране спрямо автор или заглавие. Предвидено е да приема гетър от класа книга (getAuthor() или getTitle() ). Използва метода sortPredicateAscension() ot UsefulFunctions.cpp за да определи режима на сортиране ( 1 – възходящ ред, 2- низходящ ред ), и сравнява книгите според полето, на което съответства подадения гетър.
	•int findByString(char* input, char* (Book::* function)() const) const- намира книга спрямо някакъв критерий, въведен от потребителя и низ, който трябва да е от член-данните на книгата (getAuthor() getTitle() ). Функцията игнорира разликата между големи и малки букви. Използва copyString(), toLowerString() от UsefulFunctions.cpp. Ако няма такава книга, връща -1.
	•int findByISBN(char* input) const- намира книга спрямо ISBN номера и. Ако няма такава книга, връща -1.
	•int findByDescription(char* input) const- намира книга като проверява дали някоя книга съдържа част от описанието, подадено от потребителя. Използва copyString(), toLowerString() от UsefulFunctions.cpp. Ако няма такава книга, връща -1.
	public:
	•void sort()- сортира библиотеката спрямо поле, въведено от потребителя. Използва sortPredicate() от UsefulFunctions.cpp, който връща режим за сортиране ( 1-по заглавие, 2-по автор, 3-по рейтинг ). Използва sortByString(), sortByRating() и print().
	•void addBook(const Book& bookToAdd)- добавя книга в библиотеката. Записва книгата във файла с книги на библиотеката
	•void removeBook(const Book& bookToRemove)- премахва книга от библиотеката и съдържа опция да се изтрие файлът, който се асоциира с нея, в зависимост от това дали потребителят въведе “Y” за да, или „N“ за не. Изтрива името и от списъка с налични книги в библиотекатa, като замества името и с празния низ.
	•Book& findBy() const- намира книга според някакъв критерий и я връща. Използва findPredicate() и copyString() от UsefulFunctions.cpp, за да се определи режима, според който става търсенето ( 1 – заглавие, 2 – автор, 3 –ISBN, 4 – част от описание ). Ако върне -1, книгата не е намерена и се хвърла изключение.
	•void find() const- намира книга според някакъв критерий и я принтира. Използва findBy() и printDetailed() от класа Book.
	•void displayBook(const Book& book) const показва съдържанието на книгата, като има режим, който определя дали книгата ще се показва по страници или по изречения. (1-по страници, 2 – по изречения).
	•void print()- принтира всяка книга от библиотеката. 
________________________________________
### 3. User
Класът User представлява потребител с име и парола, който може да има администраторски права 
Член-данни:
	•char* mUsername
	•char* mPassword
	•bool mIsAdmin

Член-функции:
•void setStringValuesToNullptr() – задава началните стойности на динамичната памет на nullptr
•void copy(const Book& other)- копира обект от тип User, използва се в оператор= и копи конструктор
•void free()- изтрива динамичната памет, използва се в оператор= и деструктор
•bool operator==(const User& other) const- проверява дали два потребитела са едни и същи като сравнява потребителското им име и паролата
•operator<< - записва потребителя в поток
Съдържа гетъри, сетъри и конструктори
________________________________________
### 4.UserList

Имплементация:
	
•Класът Library представлява списък от потребители и методи за работа с тях. Списъкът е всъщност масив от указатели към обекти от тип User, за да се избягва многократното копиране на обекти в методи като swap и sort. Когато списъкът запълни ¾ от капацитета си, вика се метода resize(), който преоразмерява масива и копира първоначалните съдържания. Конструкторът приема име на файл, където да бъдат запазени имената на потребителите, регисетрирани в приложението. В списъка могат да бъдат търсени и добавяни, потребители. Дефинирани е голямата шесторка заради динамичната памет. Конструкторът по подразбиране е премахнат, за да може винаги при създаване на списък да се подава файл, в който да бъдат записани потребителите, които той съдържа.

Член-данни:
	•User** mUsers
	•int mCount
	•int mCapacity
	•char* mAssociatedFile
Count държи броя на досегашните потребители, добавени в списъка, a capacity е максималният брой, който масивът Users може да съхранява. Когато се запълни 3/4 от капацитета, масивът разширява капацитета си, за да побере още потребители. AssociatedFile е името на файла, в който се записват имената на потребителите, регистрирани в списъка. 
	
Член-функции:
	•void copy(const UserList& other)- копира обект от тип UserList, използва се в оператор= и копи конструктор. Използва copyString() от UsefulFunctions.cpp
	•void free()- изтрива динамичната памет, използва се в оператор= и деструктор
	•void resize() - използва се за преоразмеряване на масива, когато добавим нов елемент
	•int findIndex(char* userName) const - намира индекса на потребител спрямо потребителското му име
	•void addUser(const User& userToAdd)- добавя потребител в списъка и го записва във файл. Връща -1 ако няма такъв потребител.
	•operator<< - записва списъка в поток
Съдържа гетъри, сетъри и конструктори. Конструкторът по подразбиране е премахнат, за да може винаги при създаване на списък да се подава файл, в който да бъдат записани потребителите, които са регистрирани.
________________________________________

### 5. UsefulFunctions
usefulFunctions.h и usefulFunctions.cpp съдържат често използвани функции, за да могат да бъдат преизползвани.
	•void copyString(char*& destination,char* source)- копира съдържанието от един стринг в друг, като се грижи и за динамичната памет, както и размерността, която трябва да бъде заделена. copyString() се използва основно в сетъри, които приемат char* . copyString() работи с инициализирани указатели и той е причината и за метода setStringValuesToNullptr(), който се вика при създаването на Book и User ако няма подадени стойности.
	•int sortPredicate()- използва се, за да се определи спрямо какъв критерий ще бъде сортиран списъка от книги в класа Library. Иска се от потребителя да въведе дали иска да сортира спрямо автор, заглавие или рейтинг, и в зависимост от входа връща режим, според който ще се случва сортирането (1 – заглавие, 2 – автор, 3 - рейтинг). Има списък с предварителни стойности criteria, който се използва заедно с функцията criterionInput() от UsefulFunctions.cpp, за да може да се валидира дали въведените от потребителя критерий съвпадат с тези, за които сортировката се поддържа (Title, Author, Rating).
	•bool sortPredicateAscension()- използва се, за да се определи дали списъка от книги в класа Library ще бъде сортиран във възходящ или низходящ ред. Има списък с предварителни стойности criteria, който се използва заедно с функцията criterionInput() от UsefulFunctions.cpp, за да може да се валидира дали въведените от потребителя критерий съвпадат с тези, за които сортирането се поддържа (Ascending, Descending).
	•int findPredicate()-използва се, за да се определи спрямо какъв критерий ще бъде търсена книга в списъка от книги в класа Library. Има списък с предварителни стойности criteria, който се използва заедно с функцията criterionInput() от UsefulFunctions.cpp, за да може да се валидира дали въведените от потребителя критерий съвпадат с тези, за които търсенето се поддържа (Title, Author, ISBN, Description).
	•char* criterionInput(const char** criteriaToCheck,int criteriaCount) - позволява на потребителя да въведе от конзолата критерий, който ще бъде използван в сортировката или търсенето. Използва validateCriterion() от UsefulFunctions.cpp за да валидира съответния критерий
	•bool validateCriterion(char* inputCriterion,const char** criteriaToCheck, int criteriaCount)- проверява, дали критерият, въведен от потребителя, е в коректен формат, като проверява дали въведеният от потребителя критерий съответства на някой от наличните.
	•void readByPages(istream& file)- чете файла на съответната книга за определен брой страници, въведени от потребителя и добавя пауза накрая
	•void readSentence(istream& file)- чете изречение от файла на съответната книга
	•void readBySentences(istream& file) - чете файла на съответната за определен брой изречения, въведени от потребителя, и добавя пауза накрая.
	•char toLowerChar(char& c)- Ако символ е главна буква, връща го в малка
	•char* toLowerString(char* input)- Връща низ, където всички букви са малки, използва метода toLowerChar() от UsefulFunctions.cpp
	•void setField(Book& book,const char* fieldName,void (Book::*function)(char* input))- задава поле на книга спрямо името на полето, използва се при създаване на книга в метода addBook(). От потребителя се иска да въведе стойност на полето и тя ще бъде зададена, спрямо това кой е сетърът, зададен като параметър function. Предвидено е функцията да се използва за задаване на полета от тип char*, тоест да се подават сетърите setTitle(),setAuthor(),setDescription(),setFileName() от Book. Използвa copyString() UsefulFunctions.cpp
	•void enterPassword(char* input,char encryptChar)- въвежда паролата от потребителя, като я показва на конзолата като последователност от encryptChar използва се в . Използва се в authorize(), където се криптира с ‚*‘ . Използва _getch() метода от <conio.h>, а идеята е взаимствана от https://www.dreamincode.net/forums/topic/238072-censor-password-in-c/ , отговорът на потребител "staycrisp" . Отделно, идеята за триене на символ е взаимствана от https://stackoverflow.com/questions/3745861/how-to-remove-last-character-put-to-stdcout , потребител "bjskishore123"
	•bool authorize(const char* pass)- проверява дали въведената от потребителя парола съвпада с администраторската, за да получи права да извърши операциите addBook() и removeBook(), използва enterPassword() от UsefulFunctions.cpp


## 3. Тестове
Тестването е направено използвайки doctest.h файла и може да се активира като се добави следният код в main метода:
________________________________________
doctest::Context context; context.addFilter("test-case-exclude", "*math*");
	context.setOption("abort-after", 5);              
	context.setOption("order-by", "name");            

	context.applyCommandLine(argc, argv);
	
	context.setOption("no-breaks", true);     

	int res = context.run(); 

	if (context.shouldExit()) 
		return res;         

	int client_stuff_return_code = 0;
	

	return res + client_stuff_return_code;
	
________________________________________
### BookTests
Тестовете за класа се съхраняват във файла bookTets.cpp. Поддържат се следните TEST_CASES:
	•TEST_CASE("Default constructor test")
	•TEST_CASE("Contructor with constant char* test")
	•TEST_CASE("Contructor with dynamic char* test")
	•TEST_CASE("Copy contructor test")
	•TEST_CASE("Move contructor test")
	•TEST_CASE("Operator = test")
	•TEST_CASE("Operator = test for moving objects")
	•TEST_CASE("Operator == test")
	•TEST_CASE("Setters test")
	•TEST_CASE("Getters test")

### LibraryTests 
Тестовете за класа се съхраняват във файла libraryTests.cpp. Поддържат се следните TEST_CASES:

	•TEST_CASE("Copy constructor")
	•TEST_CASE("Move constructor")
	•TEST_CASE("Getters")
	•TEST_CASE("Operator =")
	•TEST_CASE("Operator = for moving ojects")
	•TEST_CASE("Remove deletes book name from file with available books")
	•TEST_CASE("Add book") – този тест е закоментиран, понеже се изисква вход от потребителя за него.
	•TEST_CASE("Remove") - този тест е закоментиран, понеже се изисква вход от потребителя за него.
	•TEST_CASE("Sort") - този тест е закоментиран, понеже се изисква вход от потребителя за него.
	•TEST_CASE("Find By") - този тест е закоментиран, понеже се изисква вход от потребителя за него.




### UserTests
Тестовете за класа се съхраняват във файла userTests.cpp. Поддържат се следните TEST_CASES:

	•TEST_CASE("Default contructor test")
	•TEST_CASE("Contructor with constant char* test")
	•TEST_CASE("Contructor with dynamic char* test")
	•TEST_CASE("Copy contructor test")
	•TEST_CASE("Move constructor test")
	•TEST_CASE("Operator = test")
	•TEST_CASE("Operator = test for moving objects")
	•TEST_CASE("Setters test")
	•TEST_CASE("Getters test")
 
### UserListTests
Тестовете за класа се съхраняват във файла userListTests.cpp. Поддържат се следните TEST_CASES:

	•TEST_CASE("Copy constructor test")
	•TEST_CASE("Move constructor test")
	•TEST_CASE("Getters")
	•TEST_CASE("Operator =")
	•TEST_CASE("Operator = for moving ojects")
	•TEST_CASE("Add user")
	•TEST_CASE("Find Index")

### UsefulFunctionsTests
Тестовете за класа се съхраняват във файла usefulFunctionsTests.cpp. Поддържат се следните TEST_CASES:

	•TEST_CASE("Copy string accepting nullptr as source")
	•TEST_CASE("Copy string accepting nullptr as destination")
	•TEST_CASE("Copy string with dynamic char* source")
	•TEST_CASE("Copy string with const char* source")
	•TEST_CASE("Validate criterion")
	•TEST_CASE("To lower char")
	•TEST_CASE("To lower string")


## 4. Външни източници
	•Във функцията enterPassword() от UsefulFunctions.cpp се използва идея, взаимствана от https://www.dreamincode.net/forums/topic/238072-censor-password-in-c/ , отговорът на потребител "staycrisp" . Отделно, идеята за триене на символ е взаимствана от https://stackoverflow.com/questions/3745861/how-to-remove-last-character-put-to-stdcout , потребител "bjskishore123"


