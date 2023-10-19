#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <vector>
#include <io.h>
#include <exception>
using namespace std;

enum Color
{
	Black, Blue, Green, Cyan, Red, Magenta, Brown,
	LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void setColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Esc = 27 };
void setCursor(int x, int y)
{
	COORD myCoords = { x,y };
	SetConsoleCursorPosition(hStdOut, myCoords);
}

struct Node
{
	int data;
	Node* next;//адрес следующего элемента
};

class myList
{
	Node* Head = nullptr;
	Node* Tail = nullptr;
	int count = 0;
public:

	//конструктор по умолчанию дублирует начальное состояние полей
	myList()
	{
		Head = Tail = nullptr;
		count = 0;
	}

	~myList()
	{
		while (count != 0)
		{
			eraseElementFromHead();
		}
	}

	//метод для удаления элемента с головы списка
	int eraseElementFromHead()
	{
		if (Head != nullptr)
		{
			Node* dell = Head;
			Head = Head->next;//перебросили голову на следующий элемент
			int temp = dell->data;
			delete dell;
			count--;
			//если элемент, который мы удаляем был последним в списке
			if (count == 0)
			{
				Head = Tail = nullptr;
			}
			if (count == 1)//если после удаления остался только один элемент
			{
				Tail = Head;
			}
			return temp;
		}
	}
	//метод для добавления объекта в хвост списка
	void addElement(int data)
	{
		//создаём динамический объект
		Node* newelement = new Node;
		newelement->data = data;

		//если это первый добавляемый в список элемент - то он и голова и хвост
		if (Head == nullptr)
		{
			Head = Tail = newelement;
		}
		//если это не первый элемент - нам нужно добавить его после хвоста 
		//и перебросить указатель хвоста на него
		else
		{
			//за хвостом стоит новый элемент
			Tail->next = newelement;
			Tail = newelement;//этот элемент яввляется хвостом
		}
		count++;
		Tail->next = nullptr;//за хвостовым элементом никого нет
	}
	//показ всего списка
	void printList()
	{
		//если список не пуст
		if (Head != nullptr)
		{
			Node* move = Head;//заппоминаем адрес головы
			while (move != nullptr)
			{
				cout << move->data << "\n";
				//перепрыгиваем на следующий элемент
				move = move->next;
			}
		}
		else
		{
			throw exception("list is empty");
		}
	}

	//добавить в голову
	void addElementtoHead(int a_data)
	{
		if (Head == nullptr)
		{
			addElement(a_data);
		}
		else
		{
			//создаем новый элемент
			Node* newelement = new Node;
			newelement->data = a_data;
			// записываем указатель на следующий элемпент(старая голова)
			newelement->next = Head;
			// Головой назначаем новый элемент
			Head = newelement;
			count++;
		}
	}
	//удалить с позиции

	void eraseFromPos(int position)
	{
		if (position == 0)
		{
			eraseElementFromHead();
		}
		else
		{
			Node* befor;
			Node* dell;
			befor = Head;
			for (size_t i = 0; i < position - 1; i++)
			{
				befor = befor->next;
			}
			dell = befor->next;

			if (dell->next == nullptr)//если элемент. который мы удаляем это хвост
			{
				befor->next = nullptr;
				Tail = befor;
			}
			else
			{
				befor->next = dell->next;
			}
			delete dell;
			count--;
		}
		if (count == 0)
		{
			Head = Tail = nullptr;
		}
		if (count == 1)//если после удаления остался только один элемент
		{
			Tail = Head;
		}



	}

	int getFromPos(int position)
	{
		int tempp;

		if (position == 0)
		{
			tempp = eraseElementFromHead();
		}
		else
		{
			Node* befor;
			Node* dell;
			befor = Head;
			for (size_t i = 0; i < position - 1; i++)
			{
				befor = befor->next;
			}


			dell = befor->next;
			tempp = befor->next->data;

			if (dell->next == nullptr)//если элемент. который мы удаляем это хвост
			{
				befor->next = nullptr;
				Tail = befor;
			}
			else
			{
				befor->next = dell->next;

			}

			delete dell;
			count--;
		}
		if (count == 0)
		{
			Head = Tail = nullptr;
		}
		if (count == 1)//если после удаления остался только один элемент
		{
			Tail = Head;
		}

		return tempp;

	}

	void addToPosition(int position, int data)
	{
		Node* temp = Head;
		Node* newelement = new Node;
		newelement->data = data;

		if (position == 0)
		{
			addElementtoHead(data);
		}
		else
		{
			for (size_t i = 1; i < position; i++)
			{
				temp = temp->next;
			}

			if (temp->next == nullptr)
			{
				temp->next = newelement;
				Tail = newelement;
				Tail->next = nullptr;


			}
			else
			{
				newelement->next = temp->next;
				temp->next = newelement;

			}


			count++;
		}



	}

	int operator[](int index)
	{
		Node* temp;
		temp = Head;
		if (index <= count && index >= 0)
		{
			for (size_t i = 0; i < index; i++)
			{
				temp = temp->next;
			}
			return temp->data;

		}
		else
		{
			throw exception("индекс за границами");

		}
	}

	myList& operator!()
	{

		Node* temp = Head;
		vector <int> Value;
		int a;
		for (size_t i = count; i > 0; i--)
		{
			Value.push_back(getFromPos(i - 1));

		}

		for (auto var : Value)
		{
			a = var;
			addElement(a);

		}

		Value.clear();
		return *this;
	}


};

//ДЗ
	//перегрузить []
	//обработать ситуацию. если позиция за границами списка (перегрузка[])
	//перегрузить ! - инвертировать список
	//получить элемент с позиции
	//добавить на позицию

void main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(0));

	myList list;

	list.addElementtoHead(600);
	list.addElementtoHead(500);
	list.addElementtoHead(400);
	list.addElementtoHead(300);
	list.addElementtoHead(200);
	list.addElementtoHead(100);
	cout << "список без измененийй: " << endl;
	try
	{
		list.printList();
	}
	catch (const std::exception& ex)
	{
		cout << ex.what();
	}

	cout << "\nполучить с индекса 3: ";
	try
	{
		cout << list[3] << endl;
	}
	catch (const std::exception& ex)
	{
		cout << ex.what();

	}
	cout << endl;

	cout << "Удалили с индекса 2: " << endl;
	list.eraseFromPos(2);
	list.printList();
	cout << endl;

	cout << "получили с индекса: " << list.getFromPos(3) << "\n";
	list.printList();
	cout << endl;

	cout << "Реверс листа: " << endl;
	!list;
	list.printList();
	cout << endl;

	cout << "добавили на 3 индекс, число 8: " << endl;
	list.addToPosition(3, 8);
	list.printList();
	cout << endl;


}
