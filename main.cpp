#include "library.h"
#include <iostream>
#include <fstream>
using namespace std;
int main()
{
	Book b1("Agatha Christie","ABC murders","abcmurders.txt","A short mystery novel");
	/*Book b2("Fredrik Backman", "A man called Ove", "Ove.txt", "A heartwarming story about an old man and his life");
	Book b3("Mikhail Bugakov", "Master and Margarita", "Margarita.txt", "A glimpse into the everyday life of russian folk, the devil and his companions");
	Book b4("Jonas Jonasson", "The girl who saved the king of Sweden", "Nombeko.txt", "The story of a Nigerian girl who gets out of the slumps");
	Book b5("Thomas Mann", "The Buddenbrooks", "Buddenbrooks.txt", "The slow demise of a once rich and well-respected family");
	Library lib;
	lib.addBook(b1);
	lib.addBook(b2);
	lib.addBook(b3);
	lib.addBook(b4);
	lib.addBook(b5);
	lib.Sort();*/
	ofstream out(b1.getFileName());
	out << b1;
	return 0;
}