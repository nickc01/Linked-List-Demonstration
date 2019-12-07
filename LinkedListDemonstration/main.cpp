/*
	Nicholas Cullen
	12/7/19
	Linked List Creator : A program used to create and manipulate a list.

	The program only uses a linked list internally. No other list type, such as vector or arrays, are used.

	A linked list works by using pointers to point to the next element in the list. For example, the first element will contain a value and a pointer to the next element.
	The next element in turn, will have it's own value as well as a pointer to the next element, and so on. The one I used have both a pointer to the next element and a pointer to the previous element for iterating in both directions
*/

#include <string> //Used to gain access to std::string
#include <iostream> //Used to gain access to std::cin and std::cout
#include <conio.h> //Used to gain access to getch(), which is used to get up arrow, down arrow, and enter key inputs

#define WIN32_LEAN_AND_MEAN //Used to make sure we don't include extra features in <Windows.h>
#include <Windows.h> //Used to gain access to colorizing the console and changing the visibility of the cursor

#define UPKEY 72 //The keycode for the Up Arrow
#define DOWNKEY 80 //The keycode for the Down Arrow

//Prevents me from having to use "std::" all over the program
using namespace std;

//--Enums--

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

//Represents the text color of the console. This includes the background and foreground colors
struct TextColor
{
	Color Background = Color::Black;
	Color Foreground = Color::White;

	//Constructor to make it easier to create the struct
	TextColor(Color background, Color foreground) : Background(background), Foreground(foreground) {};
};

//A simple linked list definition. They hold a specified value, as well as the next and previous element in the list
struct LinkedList
{
	//The value the linked list holds
	string Value;
	LinkedList* Previous = nullptr; //The previous element in the list
	LinkedList* Next = nullptr; //The next element in the list
};

//Holds information about selecting an element via GetIndex();
struct SelectedElement
{
	//The current selected element
	LinkedList* Current = nullptr;
	//The element just behind the current one
	LinkedList* Previous = nullptr;
	//The element just next to the current one
	LinkedList* Next = nullptr;
	//The numerical index of the current element
	int Index;

	//Constructor to make it easier to create the struct
	SelectedElement(LinkedList* current, LinkedList* previous, LinkedList* next, int index) : Current(current), Previous(previous), Next(next), Index(index) {}
};

//--Fuctions--

//Sets the current text color of the console. Any new text printed to the console will have the specified colors
void SetColor(Color Background = Color::Black, Color Text = Color::BrightWhite);

//Gets the current color of the text
TextColor GetColor();

//Draws a title bar at the top of the console screen. Both the title text and the text color can be specified
void DrawTitle(string title, TextColor TitleColor = { Color::Black,Color::White }, TextColor SideColor = { Color::Black,Color::White });

//Gets a numerical input value from the user
int GetNumber();

//Hides the blinking console cursor
void HideCursor();

//Shows the blinking console cursor
void ShowCursor();

//Gets a string input value from the user
string GetString();

//Allows the user to select an element from the linked list
SelectedElement GetIndex(string message, bool afterLast = true, TextColor TitleSides = { Color::Black,Color::White }, TextColor Title = { Color::Black, Color::White });

//Prints the entire linked list to the console
void PrintLinkedList(LinkedList* list);

//Swaps two strings with each other by using their pointers
void SwapStrings(string* firstString, string* secondString);


//Clears the linked list and makes it empty
void Clear();

//Adds a new element to the linked list
void Add();

//Removes an element from the linked list
void Remove();

//Inserts a new element into the linked list
void Insert();

//Modify's an existing element in the linked list
void Modify();

//Swaps two elements with each other in the linked list
void Swap();

//Quits the program
void Quit();

//--Variables--

//The Current Console color
TextColor CurrentColor = { Color::Black,Color::BrightWhite };

//The First Element in the Linked List
LinkedList* FirstElement = nullptr;

//Whether the program is quitting or not
bool Quitting = false;


//The main function that runs everything
int main()
{
	//Clear the console screen
	system("cls");

	//Run the program continously until the user wants to quit
	while (!Quitting)
	{
		//Draw the title with the name of the program
		DrawTitle("String Linked List Creator");
		//Prints the entire linked list to the console
		PrintLinkedList(FirstElement);

		//Present the options to the user
		cout << "Pick an option by number:\n";
		cout << "1 : Clear - Clears the current list\n";
		cout << "2 : Add - Adds a new element to the end of the list\n";
		cout << "3 : Remove - Removes an element from the list\n";
		cout << "4 : Insert - Inserts an element anywhere in the list\n";
		cout << "5 : Modify - Modify an existing element\n";
		cout << "6 : Swap - Swaps the values of two elements\n";
		cout << "7 : Quit - Quits the application\n";

		//Get the player's number selection
		int selection = GetNumber();
		//Clear the screen
		system("cls");
		
		//Use a switch statement to determine which functions to call
		switch (selection)
		{
		case 1: //If the first option is selected
			Clear(); //Clear the list
			break;
		case 2: //If the second option is selected
			Add(); //Add a new element to the back of the list
			break;
		case 3: //If the third option is selected
			Remove(); //Remove an element from the list
			break;
		case 4: //If the fourth option is selected
			Insert(); //Insert a new element in the list
			break;
		case 5: //If the fifth option is selected
			Modify(); //Modify an existing value in the list
			break;
		case 6: //If the sixth option is selected
			Swap(); //Swap two values in the list
			break;
		case 7: //If the seventh option is selected
			Quit(); //Quit the application
			break;
		default: //If any other input is selected
			break; //Don't do anything
		}
	}
	//Exit the application
	return 0;
}

//Gets a number from the user
int GetNumber()
{
	//Store the previously set color
	TextColor previousColor = GetColor();

	//Repeat until a valid input is specified
	while (true)
	{
		//Set the text color to purple
		SetColor(Color::Black, Color::LightPurple);
		//Print the prefix
		cout << "\n/>";
		//Set the color back to normal
		SetColor(previousColor.Background, previousColor.Foreground);
		//Get the user's input
		string input;
		getline(cin, input);

		//If the input is blank
		if (input == "")
		{
			//Set the color to red
			SetColor(Color::Black, Color::LightRed);
			//Tell the user that the input is invalid
			cout << "Enter a valid number\n";
			//Go back to the top of the loop
			continue;
		}
		//If the input is not blank
		else
		{
			try
			{
				//Attempt to convert the input into a number
				return stoi(input);
			}
			//If the input is not a valid number
			catch (...)
			{
				//Set the color to red
				SetColor(Color::Black, Color::LightRed);
				//Tell the user that the input is invalid
				cout << "Enter a valid number\n";
				//Go back to the top of the loop
				continue;
			}
		}
	}
}

//Gets a string input from the user
string GetString()
{
	//Store the previous color
	TextColor previousColor = GetColor();

	//Repeat until a valid input is entered
	while (true)
	{
		//Set the color to purple
		SetColor(Color::Black, Color::LightPurple);
		//Print the prefix
		cout << "\n/>";
		//Set the color to the previous color
		SetColor(previousColor.Background, previousColor.Foreground);

		//Get the player's input
		string input;
		getline(cin, input);

		//If the input is blank
		if (input == "")
		{
			//Set the color to red
			SetColor(Color::Black, Color::LightRed);
			//Tell the player that the input is invalid
			cout << "Enter a valid string\n";
			//Go back to the top of the loop
			continue;
		}
		//If the input is valid
		else
		{
			//Return the input
			return input;
		}
	}
}

//Allows the user to select an element from the linked list
SelectedElement GetIndex(string message,bool includeIndexAfterLastElement, TextColor TitleSides, TextColor Title)
{
	//If the linked list is not empty
	if (FirstElement != nullptr)
	{
		//Hide the console cursor
		HideCursor();
		int arrowIndex = 0; //Used to store the current index of the arrow
		int iteratorIndex = 0; //Used when iterating over all the elements in the linked list. After the arrow is drawn, this stores the length of the linked list
		//Continously loop until the user has selected an element
		while (true)
		{
			//Clear the screen
			system("cls");
			//Reset the iterator
			iteratorIndex = 0;
			//Draw the specified title message
			DrawTitle(message,Title,TitleSides);
			//Tell the user that they can select a specific element using the arrow keys
			cout << "\nUse the arrow keys to select the element. Then press enter to confirm\n";
			//Get the first element in the list
			LinkedList* current = FirstElement;
			//Store the previous color
			TextColor previousColor = GetColor();
			//Set the background color to gray
			SetColor(Color::Gray, Color::BrightWhite);
			//Repeat until the end of the linked list is reached
			do
			{
				//Go to a new line
				cout << '\n';
				//If the arrow index is the same as the index of this current element in the linked list
				if (iteratorIndex == arrowIndex)
				{
					//Display an arrow next to the element
					cout << "--->  ";
				}
				//If it's not the same
				else
				{
					//Don't display an arrow
					cout << "      ";
				}
				//Print the index and value of the linked list element
				cout << iteratorIndex << " : " << current->Value;
				//Increment the iterator
				iteratorIndex++;
				//Go to the next element
				current = current->Next;
			//If there is no next element to go to, then break from the loop.
			} while (current != nullptr);

			//If the index after the last element can also be selected
			if (includeIndexAfterLastElement)
			{
				//If arrow index is at the index past the last element
				if (arrowIndex == iteratorIndex)
				{
					//Print an arrow
					cout << "\n--->  ";
				}
				//If it's not the same
				else
				{
					//Don't display an arrow
					cout << "\n      ";
				}
			}
			//Set the color to the previously set color
			SetColor(previousColor.Background,previousColor.Foreground);
			//Get the player's key press
			char inputChar = _getch();
			//Go to the next line
			cout << '\n';
			//Use a switch statement to determine what to do depending on the keypress
			switch (inputChar)
			{
			case UPKEY: //If the up key is pressed
				//Decrement the Arrow Index to move the arrow down, while making sure it doesn't dip below zero
				if (--arrowIndex < 0)
				{
					arrowIndex = 0;
				}
				break;
			case DOWNKEY: //If the down key is pressed
				//If the index after the last element can be selected
				if (includeIndexAfterLastElement)
				{
					//Increment the arrow index to move the arrow up, while making sure it doesn't go above the size of the linked list
					if (++arrowIndex > iteratorIndex)
					{
						arrowIndex = iteratorIndex;
					}
				}
				//If the index after the last element cannot be selected
				else
				{
					//Increment the arrow index to move the arrow up, while making sure it doesn't ggo past the last index
					if (++arrowIndex > iteratorIndex - 1)
					{
						arrowIndex = iteratorIndex - 1;
					}
				}
				break;
			case '\r': //If the enter key is pressed
				{
					LinkedList* selection = FirstElement; //Used to store the selection once it's been found
					int selectionIndex = 0; //Used to store the selection's index once it's been found
					//Loop over the entire linked list and find the index that is the same as the arrow index
					do
					{
						//If the selection is the same as the arrow's index. Then we have found the selection
						if (selectionIndex == arrowIndex)
						{
							//Show the cursor again
							ShowCursor();
							//Return the selection
							return { selection,selection->Previous,selection->Next, selectionIndex };
						}
						//If the selection is not the same as the arrow's index
						else
						{
							//Increment the selection index to the next element and try again
							selectionIndex++;
							//If there is no next element
							if (selection->Next == nullptr)
							{
								//Exit the loop
								break;
							}
							//Go to the next element
							selection = selection->Next;
						}
					} while (true);
					//Show the cursor again
					ShowCursor();
					//If the index after the last has been selected
					if (includeIndexAfterLastElement && selectionIndex == iteratorIndex)
					{
						//Return that as the selection
						return { nullptr,selection,nullptr,selectionIndex };
					}
					//Return nothing is nothing has been selected
					return { nullptr,nullptr,nullptr,0 };
					break;
				}
			}
		}
	}
	//Return nothing is nothing has been selected
	return { nullptr,nullptr,nullptr,0 };
}

//Prints the entire list to the console
void PrintLinkedList(LinkedList* list)
{
	//Print the initial text
	cout << "Current Linked List:\n";
	//If the list does not exist
	if (list == nullptr)
	{
		//Tell the user that the list is empty
		cout << "[EMPTY]\n\n";
	}
	//If the list is not empty
	else
	{
		//Print the opening tag
		cout << "\n[\n";
		LinkedList* current = list; //Used to store the current linked list element to be printed
		//Loop until the entire linked list has been iterated over
		do
		{
			//Print the current linked list element
			cout << '\t' << current->Value << '\n';
			//Go to the next element
			current = current->Next;
		//If there is no next element to go to, then we have reached the end of the list, so we exit the loop
		} while (current != nullptr);
		//Print the closing tag
		cout << "]\n\n";
	}
}

//Swaps two string values with each other by using their pointers
void SwapStrings(string* firstString, string* secondString)
{
	//Store the first value in the temporary variable
	string temp = *firstString;
	//Set the first value to the second
	(*firstString) = *secondString;
	//Set the second value to the temporary
	(*secondString) = temp;
}

//Clears the entire linked list
void Clear()
{
	//If the list is not empty
	if (FirstElement != nullptr)
	{
		LinkedList* current = FirstElement; //Used to store the current linked list element to be iterated over

		//Repeat until we have reached the end of the list. The variable "current" will now store the last element in the linked list
		while (current->Next != nullptr)
		{
			current = current->Next;
		}
		LinkedList* previous; //Used to store the previous element. This is needed to iterate backwards in the linked list

		//Repeat until all the elements in the linked list are destroyed, going from the last element to the first
		do
		{
			//Go to the previous element to the current one
			previous = current->Previous;
			//Delete the current element
			delete current;
			//Set current to the previous element
			current = previous;
		//If there is no previous element to go to, then we have reached the beginning of the list, and all elements have been destroyed
		} while (current != nullptr);
		FirstElement = nullptr;
	}
}

//Adds a new element to the back of the list
void Add()
{
	//Tell the user to specify what value is to be added to the list
	cout << "Specify the value to add to the end of the list:\n";
	//Get the player's input string
	string value = GetString();

	//If the list is empty
	if (FirstElement == nullptr)
	{
		//Create the first element in the list
		FirstElement = new LinkedList();
		//Set the first element's value to the player specified string
		FirstElement->Value = value;
	}
	//if the list is not empty
	else
	{
		LinkedList* top = FirstElement; //Used to iterate over the linked list. Once the iterating is done, this will store the last element in the linked list
		//Repeat until we have reached the end of the linked list
		while (top->Next != nullptr)
		{
			top = top->Next;
		}
		//Create the next element in the list
		top->Next = new LinkedList();
		//Set the next element's value
		top->Next->Value = value;
		//Update it's previous element
		top->Next->Previous = top;
	}
	//Clear the screen
	system("cls");
}


//Removes an element from the list
void Remove()
{
	//If the linked list is empty, then there is nothing to remove
	if (FirstElement == nullptr)
	{
		//Draw a title, signifying an error
		DrawTitle("The list is empty, so there are no elements to remove", { Color::LightRed,Color::Black }, { Color::LightRed,Color::Black });
	}
	//If the linked list is not empty
	else
	{
		//Tell the user to select an element to remove
		SelectedElement selection = GetIndex("Select the element to remove", false, {Color::LightBlue,Color::Black}, { Color::LightGreen,Color::Black });

		LinkedList* current = selection.Current; //The currently selected element to remove
		LinkedList* previous = selection.Previous; //The element previous to the current
		LinkedList* next = selection.Next; //The element next to the current


		//If there is a previous element
		if (current->Previous != nullptr)
		{
			//Update it's next element
			current->Previous->Next = next;
		}
		//If there is a next element
		if (current->Next != nullptr)
		{
			//Update it's previous element
			current->Next->Previous = previous;
		}

		//If the selected element to delete is the first element in the linked list
		if (current == FirstElement)
		{
			//If it has a next element to go to
			if (current->Next != nullptr)
			{
				//Set the first element to the next value
				FirstElement = current->Next;
				//Delete the current value
				delete current;
			}
			//If there is no other element to go to, then that means that this is the only element left in the list
			else
			{
				//Delete the first element
				delete FirstElement;
				FirstElement = nullptr;
			}
		}
		//If the element is not the first element
		else
		{
			//Delete it like normal
			delete current;
		}
		//Clear the screen
		system("cls");
	}
}

//Used to insert a new value into the linked list
void Insert()
{
	//Tell the player to select where the element should be inserted
	auto selection = GetIndex("Select a place to insert. The element will be placed between the place you select and the previous element",true, { Color::LightBlue,Color::Black }, { Color::LightGreen,Color::Black });
	//Ask the player what value they want to add
	cout << "Specify the value to be inserted:\n";
	//Get the player's input
	string value = GetString();

	LinkedList* current = selection.Current; //The current element
	LinkedList* oldPrevious = selection.Previous; //The prevous element

	//The new element will be inserted between the "current" element and the "oldPrevious" element

	//Create the new element
	LinkedList* newElement = new LinkedList();
	//Set it's value to the user's input
	newElement->Value = value;

	//If there is a previous element from the current
	if (oldPrevious != nullptr)
	{
		//Update it's next element
		oldPrevious->Next = newElement;
		//Update the newElement's previous one
		newElement->Previous = oldPrevious;
	}
	//If there is no previous element from the current, then that means that the first element is the currently selected index
	else
	{
		//Set the newly inserted element as the first element
		FirstElement = newElement;
	}
	//If there even was a previous first element
	if (current != nullptr)
	{
		//Update it's previous element
		current->Previous = newElement;
		//Update the new element's next one
		newElement->Next = current;
	}
	//Clear the screen
	system("cls");
}

//Used to modify an existing element in the list
void Modify()
{
	//If the list is empty, then there is nothing to modify
	if (FirstElement == nullptr)
	{
		//Draw the title, signifying an error
		DrawTitle("The list can't be modified if it's empty", { Color::LightRed,Color::Black }, { Color::LightRed,Color::Black });
	}
	//If the list is not empty
	else
	{
		//Ask the player what element they want to modify
		SelectedElement selection = GetIndex("Pick an element to modify", false, { Color::LightBlue,Color::Black }, { Color::LightGreen,Color::Black });

		//Tell the player to specify a new value for the element
		cout << "Specify a new Value:\n";

		//Get the player's input and update the selection's value
		selection.Current->Value = GetString();
		//Clear the screen
		system("cls");
	}
}

//Used to swap the values of two elements
void Swap()
{
	//If the linked list is empty, then it's impossible to swap
	if (FirstElement == nullptr)
	{
		//Draw the title, signifying an error
		DrawTitle("Elements cannot be swapped if the list is empty", { Color::LightRed,Color::Black }, { Color::LightRed,Color::Black });
	}
	//If there is only one element in the list, there is nothing for it to swap with
	else if (FirstElement->Next == nullptr)
	{
		//Draw the title, signifying an error
		DrawTitle("There has to be two or more elements in order to swap", { Color::LightRed,Color::Black }, { Color::LightRed,Color::Black });
	}
	//If there are 2 or more elements in the list, then it is possible to swap
	else
	{
		//Ask the player what's the first element they want to swap with
		SelectedElement first = GetIndex("Pick the first element to swap with", false, { Color::LightBlue,Color::Black }, { Color::LightBlue,Color::Black });
		//Ask the player what's the second element they want to swap with
		SelectedElement second = GetIndex("Pick the second element to swap with", false, { Color::LightGreen,Color::Black }, { Color::LightGreen,Color::Black });
		//If the first and second selections are the same, repeatly ask them for a different selection
		while (first.Current == second.Current)
		{
			second = GetIndex("Please pick a different element to swap with", false, { Color::LightRed,Color::Black }, { Color::LightRed,Color::Black });
		}

		//Swap the values of the first and second elements
		SwapStrings(&first.Current->Value,&second.Current->Value);
		//Clear the screen
		system("cls");
	}
}

//Quits the application
void Quit()
{
	//Set the quitting value to true
	Quitting = true;
}

//Sets the current text color of the console. Any new text printed to the console will have the specified colors
void SetColor(Color Background, Color Text)
{
	//Set the current color being used
	CurrentColor = {Background,Text};

	//Retrieve the handle to the console window
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//Set the background and text color the console
	SetConsoleTextAttribute(consoleHandle, static_cast<int>(Text) + (static_cast<int>(Background) * 16));
}

//Gets the current color being used
TextColor GetColor()
{
	//Get the current color
	return CurrentColor;
}

//Hides the cursor from the console window
void HideCursor()
{
	//Retrieve the handle to the console window
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO info; //Used to store info about the cursor

	//Get the current info about the cursor
	GetConsoleCursorInfo(consoleHandle, &info);

	//Set it's visiblity to false
	info.bVisible = false;

	//Set the info of the cursor so that it becomes invisible
	SetConsoleCursorInfo(consoleHandle, &info);
}

//Shows the cursor in the console window
void ShowCursor()
{
	//Retrieve the handle to the console window
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO info; //Used to store info about the cursor
	
	//Get the current info about the cursor
	GetConsoleCursorInfo(consoleHandle, &info);

	//Set it's visiblity to true
	info.bVisible = true;

	//Set the info of the cursor so that it becomes visible
	SetConsoleCursorInfo(consoleHandle, &info);
}

//Draws a title bar at the top of the console screen. Both the title text and the text color can be specified
void DrawTitle(string title, TextColor TitleColor, TextColor SideColor)
{
	//Store the previously set color
	auto previousColor = GetColor();

	//Used to store info about the console screen
	CONSOLE_SCREEN_BUFFER_INFO info;

	//Retrieve the handle to the console window
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//Get the info about the console screen
	GetConsoleScreenBufferInfo(consoleHandle,&info);

	//Get the width of the console screen
	int width = info.dwSize.X;

	//If the title is too big to fit within a single line
	if (title.size() >= width)
	{
		//Set the color
		SetColor(TitleColor.Background,TitleColor.Foreground);
		//Print the title as is
		cout << title << "\n\n";
	}
	//If the title fits within a single line
	else
	{
		//Get the excess spacing on the left side
		int leftSide = (width - title.size()) / 2;
		//Get the excess spacing on the right side
		int rightSide = (width - title.size() - leftSide);
		//Set the siding color
		SetColor(SideColor.Background, SideColor.Foreground);
		//Fill the left side with dashes
		for (int i = 0; i < leftSide; i++)
		{
			cout << '-';
		}
		//Set the title color
		SetColor(TitleColor.Background, TitleColor.Foreground);
		//Print the title
		cout << title;
		//Set the siding color
		SetColor(SideColor.Background, SideColor.Foreground);
		//Fill the right side with dashes
		for (int i = 0; i < rightSide; i++)
		{
			cout << '-';
		}
		//Go to two new lines
		cout << "\n\n";
	}
	//Set the color back to what it was previously
	SetColor(previousColor.Background, previousColor.Foreground);
}