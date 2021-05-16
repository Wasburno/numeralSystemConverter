#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<math.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::pow;

int correctSecondInput(int newSecondInput, string numSysType);
int toDecimal(string numberToDecimal, int type);
void convertMenu(map<int, string> manageSys, int numSys1, int numSys2, int numSys3, int firstInput);
void mainMenu();
void discardSystem(int firstInput);
void convertResult(int toDecimal, int secondInput);
bool validConvertion(int firstInput, int secondInput);
bool validNumber(string number, int numberType);
map<int, string> currentSystems();
string insertFirstInput(int firstInput, map<int, string> manageNumSys);


/**
 * Enum to identify the type of numeral system we are refering in every moment
 * 
 *
 * To have more control over the menus and main inputs, this enums helps to identify all of
 * this stuff presenting in an order way
 */
enum numeralSystem {

	decimal = 1,
	binary,
	octal,
	hexagesimal
};



/**
 * Contain the numeral system you would like to convert
 * 
 *
 * This function prints the main menu of the program. This menu contains the nuemeral
 * systems you're abble to convert. This function also takes the first input of the user.
 */
void mainMenu() {
	int firstInput{ 0 };

	cout << "Choose the numeral system:" << endl << endl;
	cout << "1) decimal" << endl;
	cout << "2) binary" << endl;
	cout << "3) octal" << endl;
	cout << "4) hexagesimal" << endl;

	cin >> firstInput;

	discardSystem(firstInput);
}



/**
 * Map to have a string with the name of the numeral system
 *
 *
 * What this function does is that it creates a map that relate the values of the enum
 * numeralSystem with strings that are nothing more than the name of the respective numeral
 * system.
 */
map<int, string> currentSystems() {

	map<int, string> manageNumSys;
	manageNumSys[decimal] = "decimal";
	manageNumSys[binary] = "binary";
	manageNumSys[octal] = "octal";
	manageNumSys[hexagesimal] = "hexagesimal";

	return manageNumSys;
}


/**
 * Indentify wich numeral system was chosen and removes it from the next menu
 *
 *
 * This function uses the first input of the user to know the numeral system the user choose
 * so in the next menu it can't appear and the user can't reppeat the numeral system
 */
void discardSystem(int firstInput) {

	map<int, string> manageSys;

	manageSys = currentSystems();

	switch (firstInput)
	{
		case decimal: {
			convertMenu(manageSys, binary, octal, hexagesimal, firstInput);
			break;
		}

		case binary: {
			convertMenu(manageSys, decimal, octal, hexagesimal, firstInput);
			break;
		}

		case octal: {
			convertMenu(manageSys, decimal, binary, hexagesimal, firstInput);
			break;
		}

		case hexagesimal: {
			convertMenu(manageSys, decimal, binary, octal, firstInput);
			break;
		}

		default: {
			cout << "Please insert a valid option" << endl;
			mainMenu();
			break;
		}

	}
}


/**
 * Displays the second menu, takes the second input and manage the inputs in general
 *
 *
 * The function starts displaying the second menu only with the numeral systems that were not chosen by
 * the user before and the options are displayed thanks to the map that contains a string with the names
 * of the numeral systems. After the second Input of the user is taken it is corrected giving it a new
 * value that corresponds to the numeral system the user wants to convert (check correctSecondInput())
 * 
 * This function also checks if the convertion between the two inputs is a valid convertion and if it is,
 * it gisves the first input to toDecimal() and the result of that goes to convertResult() with the second
 * input that contains the type of numeral system that the result will be converted
 */
void convertMenu(map<int, string> manageSys, int numSys1, int numSys2, int numSys3, int firstInput) {

	int secondInput{ 0 }, correctedInput{ 0 }, decimal{0};
	bool isValid{ false };
	vector<int> remainingSystems{ numSys1, numSys2, numSys3 };
	string firstNumber{ "" };

	cout << "Convert to: " << endl << endl;
	for (int i = 0; i < remainingSystems.size(); i++)
	{
		cout << i + 1 << ")" << manageSys[remainingSystems[i]] << endl;
	}
	cin >> secondInput;

	correctedInput = correctSecondInput(secondInput, manageSys[remainingSystems[secondInput - 1]]);
	secondInput = correctedInput;

	isValid = validConvertion(firstInput, secondInput);


	if (isValid)
	{
		firstNumber = insertFirstInput(firstInput, manageSys);
		decimal = toDecimal(firstNumber, firstInput);
		convertResult(decimal, secondInput);
		
		

	}
	else
	{
		cout << "Not a valid convertion, select the numeral systems again" << endl << endl;
		mainMenu();
	}
}



/**
 * Gives the second Input the value that correspond to the correct numeral system
 *
 *
 * When the second menu is displayed the user enter the input so he can interact and choose
 * the numeral system which the fisrt input will be converted, but in order to give a great
 * user experience the order of the systems in the menu is altered. this function modifies
 * the second input so it could have the value that correspond to the correct numeral system
 * the user wants int the enum numeralSystem
 */
int correctSecondInput(int newSecondInput, string numSysType) {
	if (numSysType == "decimal")
	{
		newSecondInput = decimal;
	}
	else if (numSysType == "binary")
	{
		newSecondInput = binary;
	}
	else if (numSysType == "octal")
	{
		newSecondInput = octal;
	}
	else if (numSysType == "hexagesimal")
	{
		newSecondInput = hexagesimal;
	}

	return newSecondInput;
}



/**
 * Checks if the first input can be converted with the second input
 *
 *
 * This is a really simple function it only checks if the first input is the same as the second input
 * or if the second input correspond to an actual numeral system
 */
bool validConvertion(int firstInput, int secondInput) {

	if (firstInput == secondInput)
	{
		return false;
	}
	else if (secondInput != decimal && secondInput != binary && secondInput != octal && secondInput != hexagesimal)
	{
		return false;
	}
	else
	{
		return true;
	}

}



/**
 * The user insert the number he wants to convert 
 *
 *
 * In this function the user inserts the number he wants to convert no matter
 * which numeral system it belongs, there's another function that verifies if 
 * the number is actually correct
 */
string insertFirstInput(int firstInput, map<int, string> manageNumSys) {

	bool wasValid{ false };
	
	string firstNumber{ "" };

	cout << "insert the number you want to convert, remember it needs to be a " << manageNumSys[firstInput] << " number: " << endl;
	cin >> firstNumber;

	wasValid = validNumber(firstNumber, firstInput);

	if (wasValid)
	{
		return firstNumber;
	}
	else
	{
		insertFirstInput(firstInput, manageNumSys);
	}

}



/**
 * Checks if the number that user inserted is correct in relation of the numeral system it belongs
 *
 *
 * The number that was inserted by the user is put on a test that checks if the number belongs to the numeral
 * system that was established by the first input
 */
bool validNumber(string number, int numberType) {

	bool isValidNumber{ true };

	switch (numberType)
	{
	case decimal: {
		for (char term : number)
		{
			if (!isdigit(term))
			{
				isValidNumber = false;
			}
		}

		return isValidNumber;

		break;
	}


	case binary: {
		for (char term : number)
		{
			if (term != '0' && term != '1')
			{
				isValidNumber = false;
			}
		}
		return isValidNumber;

		break;
	}


	case octal: {
		for (char term : number)
		{
			if (term != '0' && term != '1' && term != '2' && term != '3'
				&& term != '4' && term != '5' && term != '6' && term != '7')
			{
				isValidNumber = false;
			}
		}
		return isValidNumber;

		break;
	}


	case hexagesimal: {
		for (char term : number)
		{
			if (!isxdigit(term))
			{
				isValidNumber = false;
			}
		}
		return isValidNumber;

		break;
	}


	default:
		return false;
		break;
	}
}



/**
 * Transforms the number entered by the user to a base 10 number
 *
 *
 * No matter which number the user entered as long as it was a valid one, this number
 * will be converted into a base 10 number to make easier the convertion from decimal
 * to any other numeral system
 */
int toDecimal(string numberToDecimal, int type) {

	int result{ 0 }, aux{ 0 }, term{ 0 };
	int exponent = numberToDecimal.size() - 1;


	switch (type)
	{
	case decimal: {
		return stoi(numberToDecimal);
		break;
	}

	case binary: {

		for (int i = 0; i <numberToDecimal.size(); i++)
		{

			if (numberToDecimal[i] == '1')
			{
				aux = 1 * (pow(2, exponent));
			}
			result += aux;
			aux = 0;
			exponent--;
		}

		return result;
		break;

	}

	case octal: {

		for (int i = 0; i < numberToDecimal.size(); i++)
		{
			term = numberToDecimal[i] - '0';

			aux = (pow(8, exponent) * term);

			result += aux;
			aux = 0;
			exponent--;
		}

		return result;
		break;
	}

	case hexagesimal: {

		for (int i = 0; i < numberToDecimal.size(); i++)
		{
			if (isdigit(numberToDecimal[i]))
			{
				term = numberToDecimal[i] - '0';
			}
			else
			{
				term = numberToDecimal[i] - 87;
			}

			aux = term * (pow(16, exponent));

			result += aux;
			aux = 0;
			exponent--;
		}

		return result;
		break;
	}
	default:
		break;
	}

}



/**
 * Finally converts the base 10 number to the system chosen by the user
 *
 *
 * The result of converting the number entered by the user to decimal is now used to
 * be converted into any other of the numeral systems that the user also chose, this is
 * done by doing some arithmetic operations
 */
void convertResult(int toDecimal, int secondInput) {
	
	vector<int>numeralArr;
	int aux{ 0 };

	switch (secondInput)
	{
	case decimal: {
		cout << endl << endl << "Convertion to decimal: " << endl << toDecimal << endl;
		break;
	}


	case binary: {
		while (toDecimal > 0)
		{
			aux = toDecimal % 2;

			numeralArr.push_back(aux);

			toDecimal /= 2;
		}
		cout << endl << endl << "Convertion to binary: " << endl;

		for (int i = numeralArr.size(); i > 0; i--)
		{
			cout << numeralArr[i - 1];
		}
		break;
	}


	case octal: {

		while (toDecimal > 0)
		{
			aux = toDecimal % 8;

			numeralArr.push_back(aux);

			toDecimal /= 8;
		}
		cout << endl << endl << "Convertion to octal: " << endl;
		for (int i = numeralArr.size(); i > 0; i--)
		{
			cout << numeralArr[i - 1];
		}

		break;
	}


	case hexagesimal: {

		while (toDecimal > 0)
		{
			aux = toDecimal % 16;

			numeralArr.push_back(aux);

			toDecimal /= 16;
		}
		cout << endl << endl << "Convertion to hexadeciaml: " << endl;
		for (int i = numeralArr.size(); i > 0; i--)
		{
			if (numeralArr[i - 1] == 10)
			{
				cout << 'A';
			}
			else if (numeralArr[i - 1] == 11)
			{
				cout << 'B';
			}
			else if (numeralArr[i - 1] == 12)
			{
				cout << 'C';
			}
			else if (numeralArr[i - 1] == 13)
			{
				cout << 'D';
			}
			else if (numeralArr[i - 1] == 14)
			{
				cout << 'E';
			}
			else if (numeralArr[i - 1] == 15)
			{
				cout << 'F';
			}
			else
			{
				cout << numeralArr[i - 1];
			}
		}

		break;
	}


	default:
		break;
	}
}



/**
 * It's the main function
 *
 *
 *Last but not least, this is the main function, without it nothing could be posible :)
 */
int main() {
	mainMenu();
}