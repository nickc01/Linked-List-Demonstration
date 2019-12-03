#include <string>
#include <iostream>
//#include <tuple>
#include <conio.h> //Used to gain access to getch();

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define UPKEY 72
#define DOWNKEY 80

using namespace std;

//An enum representing the foreground and background color of the console. Each color corresponds to a number below
enum class Color
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Aqua = 3,
	Red = 4,
	Purple = 5,
	Yellow = 6,
	White = 7,
	Gray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightAqua = 11,
	LightRed = 12,
	LightPurple = 13,
	LightYellow = 14,
	BrightWhite = 15
};

//--Structs--
struct TextColor
{
	Color Background = Color::Black;
	Color Foreground = Color::White;

	TextColor(Color background, Color foreground) : Background(background), Foreground(foreground) {};
};

struct LinkedList
{
	string Value;
	LinkedList* Previous = nullptr;
	LinkedList* Next = nullptr;
};

struct SelectedElement
{
	LinkedList* Current = nullptr;
	LinkedList* Previous = nullptr;
	LinkedList* Next = nullptr;
	int Index;

	SelectedElement(LinkedList* current, LinkedList* previous, LinkedList* next, int index) : Current(current), Previous(previous), Next(next), Index(index) {}
};

//--Fuctions--

//Sets the current text color of the console. Any new text printed to the console will have the specified colors
void SetColor(Color Background = Color::Black, Color Text = Color::BrightWhite);
TextColor GetColor();
void DrawTitle(string title, TextColor TitleColor = { Color::Black,Color::White }, TextColor SideColor = { Color::Black,Color::White });
int GetNumber();
void HideCursor();
void ShowCursor();
string GetString();
//Gets an index within the linked list. Returns the index, the linked list at the current index, and the linked list at the previous index
SelectedElement GetIndex(string message, bool afterLast = true, TextColor TitleSides = { Color::Black,Color::White }, TextColor Title = { Color::Black, Color::White });
void PrintLinkedList(LinkedList* list);

void Clear();
void Add();
void Remove();
void Insert();
void Modify();
void Swap();
void Quit();

//--Variables--
TextColor CurrentColor = { Color::Black,Color::BrightWhite };
LinkedList* CurrentList = nullptr;
bool Quitting = false;

int main()
{
	system("cls");
	while (!Quitting)
	{
		DrawTitle("String Linked List Creator");
		cout << "Current Linked List:\n";
		PrintLinkedList(CurrentList);
		cout << "Pick an option:\n";
		cout << "1 : Clear - Clears the current list\n";
		cout << "2 : Add - Adds a new element to the end of the list\n";
		cout << "3 : Remove - Removes an element from the list\n";
		cout << "4 : Insert - Inserts an element anywhere in the list\n";
		cout << "5 : Modify - Modify an existing element\n";
		cout << "6 : Swap - Swaps the values of two elements\n";
		cout << "7 : Quit - Quits the application\n";
		int selection = GetNumber();
		system("cls");
		switch (selection)
		{
		case 1:
			Clear();
			break;
		case 2:
			Add();
			break;
		case 3:
			Remove();
			break;
		case 4:
			Insert();
			break;
		case 5:
			Modify();
			break;
		case 6:
			Swap();
			break;
		case 7:
			Quit();
			break;
		default:
			break;
		}
	}
	return 0;
}

int GetNumber()
{
	TextColor previousColor = GetColor();
	while (true)
	{
		SetColor(Color::Black, Color::LightPurple);
		cout << "\n/>";
		SetColor(previousColor.Background, previousColor.Foreground);
		string input;
		getline(cin, input);
		if (input == "")
		{
			SetColor(Color::Black, Color::LightRed);
			cout << "Enter a valid number\n";
			continue;
		}
		else
		{
			try
			{
				return stoi(input);
			}
			catch (...)
			{
				SetColor(Color::Black, Color::LightRed);
				cout << "Enter a valid number\n";
				continue;
			}
		}
	}
}

string GetString()
{
	TextColor previousColor = GetColor();
	while (true)
	{
		SetColor(Color::Black, Color::LightPurple);
		cout << "\n/>";
		SetColor(previousColor.Background, previousColor.Foreground);
		string input;
		getline(cin, input);
		if (input == "")
		{
			SetColor(Color::Black, Color::LightRed);
			cout << "Enter a valid string\n";
			continue;
		}
		else
		{
			return input;
		}
	}
}

SelectedElement GetIndex(string message,bool afterLast, TextColor TitleSides, TextColor Title)
{
	if (CurrentList != nullptr)
	{
		HideCursor();
		int index = 0;
		int currentIndex = 0;
		while (true)
		{
			system("cls");
			currentIndex = 0;
			DrawTitle(message,Title,TitleSides);
			LinkedList* current = CurrentList;
			TextColor previousColor = GetColor();
			SetColor(Color::Gray, Color::BrightWhite);
			do
			{
				cout << '\n';
				if (currentIndex == index)
				{
					cout << "--->  ";
				}
				else
				{
					cout << "      ";
				}
				cout << currentIndex << " : " << current->Value;
				/*if (currentIndex == index)
				{
					cout << " <---\n";
				}
				else
				{
					cout << '\n';
				}*/
				currentIndex++;
				current = current->Next;
			} while (current != nullptr);

			if (afterLast)
			{
				if (index == currentIndex)
				{
					cout << "\n--->  ";
				}
				else
				{
					cout << "\n      ";
				}
				/*cout << "\t     ";
				if (index == currentIndex)
				{
					cout << "<---\n";
				}
				else
				{
					cout << '\n';
				}*/
			}
			SetColor(previousColor.Background,previousColor.Foreground);
			char inputChar = _getch();
			cout << '\n';
			LinkedList* selection = CurrentList;
			int selectionIndex = 0;
			switch (inputChar)
			{
			case UPKEY:
				if (--index < 0)
				{
					index = 0;
				}
				break;
			case DOWNKEY:
				if (afterLast)
				{
					if (++index > currentIndex)
					{
						index = currentIndex;
					}
				}
				else
				{
					if (++index > currentIndex - 1)
					{
						index = currentIndex - 1;
					}
				}
				break;
			case '\r':
				do
				{
					if (selectionIndex == index)
					{
						ShowCursor();
						return {selection,selection->Previous,selection->Next, selectionIndex};
					}
					else
					{
						selectionIndex++;
						if (selection->Next == nullptr)
						{
							break;
						}
						selection = selection->Next;
					}
				} while (true);
				ShowCursor();
				if (afterLast && selectionIndex == currentIndex)
				{
					return {nullptr,selection,nullptr,selectionIndex};
				}
				return { nullptr,nullptr,nullptr,0 };
				break;
			default:
				break;
			}
		}
	}
	return { nullptr,nullptr,nullptr,0 };
}

void PrintLinkedList(LinkedList* list)
{
	if (list == nullptr)
	{
		cout << "[EMPTY]\n\n";
	}
	else
	{
		cout << "\n[\n";
		LinkedList* current = list;
		do
		{
			cout << '\t' << current->Value << '\n';
			current = current->Next;
		} while (current != nullptr);
		cout << "]\n\n";
	}
}

void Clear()
{
	if (CurrentList != nullptr)
	{
		LinkedList* current = CurrentList;
		while (current->Next != nullptr)
		{
			current = current->Next;
		}
		LinkedList* previous;
		do
		{
			previous = current->Previous;
			delete current;
			current = previous;
		} while (current != nullptr);
		CurrentList = nullptr;
	}
}

void Add()
{
	cout << "Specify the value to add to the end of the list:\n";
	string value = GetString();
	if (CurrentList == nullptr)
	{
		CurrentList = new LinkedList();
		CurrentList->Value = value;
	}
	else
	{
		LinkedList* top = CurrentList;
		while (top->Next != nullptr)
		{
			top = top->Next;
		}
		top->Next = new LinkedList();
		top->Next->Value = value;
		top->Next->Previous = top;
	}
	system("cls");
}

void Remove()
{
	if (CurrentList == nullptr)
	{
		DrawTitle("The list is empty, so there are no elements to remove", { Color::LightRed,Color::Black }, { Color::LightRed,Color::Black });
	}
	else
	{
		SelectedElement selection = GetIndex("Select the element to remove", false, {Color::LightBlue,Color::Black}, { Color::LightGreen,Color::Black });

		LinkedList* current = selection.Current;
		LinkedList* previous = selection.Previous;
		LinkedList* next = selection.Next;

		if (current->Previous != nullptr)
		{
			current->Previous->Next = next;
		}
		if (current->Next != nullptr)
		{
			current->Next->Previous = previous;
		}


		if (current == CurrentList)
		{
			if (current->Next != nullptr)
			{
				CurrentList = current->Next;
				delete current;
			}
			else
			{
				delete CurrentList;
				CurrentList = nullptr;
			}
		}
		else
		{
			delete current;
		}
		system("cls");
	}
}

void Insert()
{
	auto selection = GetIndex("Select a place to insert. The element will be placed between the place you select and the previous element",true, { Color::LightBlue,Color::Black }, { Color::LightGreen,Color::Black });
	cout << "Specify the value to be inserted:\n";
	string value = GetString();

	LinkedList* current = selection.Current;
	LinkedList* oldPrevious = selection.Previous;

	LinkedList* newElement = new LinkedList();
	newElement->Value = value;

	if (oldPrevious != nullptr)
	{
		oldPrevious->Next = newElement;
		newElement->Previous = oldPrevious;
	}
	else
	{
		CurrentList = newElement;
	}
	if (current != nullptr)
	{
		current->Previous = newElement;
		newElement->Next = current;
	}
	system("cls");
}

void Modify()
{
	if (CurrentList == nullptr)
	{
		DrawTitle("The list can't be modified if it's empty", { Color::LightRed,Color::Black }, { Color::LightRed,Color::Black });
	}
	else
	{
		SelectedElement selection = GetIndex("Pick an element to modify", false, { Color::LightBlue,Color::Black }, { Color::LightGreen,Color::Black });

		cout << "Specify a new Value:\n";

		selection.Current->Value = GetString();
		system("cls");
	}
}

void Swap()
{
	if (CurrentList == nullptr)
	{
		DrawTitle("Elements cannot be swapped if the list is empty", { Color::LightRed,Color::Black }, { Color::LightRed,Color::Black });
	}
	else if (CurrentList->Next == nullptr)
	{
		DrawTitle("There has to be two or more elements in order to swap", { Color::LightRed,Color::Black }, { Color::LightRed,Color::Black });
	}
	else
	{
		SelectedElement first = GetIndex("Pick the first element to swap with", false, { Color::LightBlue,Color::Black }, { Color::LightBlue,Color::Black });
		SelectedElement second = GetIndex("Pick the second element to swap with", false, { Color::LightGreen,Color::Black }, { Color::LightGreen,Color::Black });
		while (first.Current == second.Current)
		{
			second = GetIndex("Please pick a different element to swap with", false, { Color::LightRed,Color::Black }, { Color::LightRed,Color::Black });
		}

		string temp = first.Current->Value;

		first.Current->Value = second.Current->Value;

		second.Current->Value = temp;
		system("cls");
	}
}

void Quit()
{
	Quitting = true;
}

//Sets the current text color of the console. Any new text printed to the console will have the specified colors
void SetColor(Color Background, Color Text)
{
	CurrentColor = {Background,Text};

	//Retrieve the handle to the console window
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//Set the background and text color the console
	SetConsoleTextAttribute(consoleHandle, static_cast<int>(Text) + (static_cast<int>(Background) * 16));
}

TextColor GetColor()
{
	return CurrentColor;
}

void HideCursor()
{
	//Retrieve the handle to the console window
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO info;

	GetConsoleCursorInfo(consoleHandle, &info);

	info.bVisible = false;

	SetConsoleCursorInfo(consoleHandle, &info);
}

void ShowCursor()
{
	//Retrieve the handle to the console window
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO info;

	GetConsoleCursorInfo(consoleHandle, &info);

	info.bVisible = true;

	SetConsoleCursorInfo(consoleHandle, &info);
}

void DrawTitle(string title, TextColor TitleColor, TextColor SideColor)
{
	auto previousColor = GetColor();

	CONSOLE_SCREEN_BUFFER_INFO info;
	//Retrieve the handle to the console window
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(consoleHandle,&info);

	int width = info.dwSize.X;

	if (title.size() >= width)
	{
		SetColor(TitleColor.Background,TitleColor.Foreground);
		cout << title << "\n\n";
	}
	else
	{
		int leftSide = (width - title.size()) / 2;
		int rightSide = (width - title.size() - leftSide);
		SetColor(SideColor.Background, SideColor.Foreground);
		for (int i = 0; i < leftSide; i++)
		{
			cout << '-';
		}
		SetColor(TitleColor.Background, TitleColor.Foreground);
		cout << title;
		SetColor(SideColor.Background, SideColor.Foreground);
		for (int i = 0; i < rightSide; i++)
		{
			cout << '-';
		}
		cout << "\n\n";
	}
	SetColor(previousColor.Background, previousColor.Foreground);
}