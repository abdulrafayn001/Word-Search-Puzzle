#include<iostream>
#include<fstream>
using namespace std;
int readRowSize(ifstream&);
int readColSize(ifstream&);
void readRowColSize(ifstream&, int&, int&);
void read(ifstream&, char**, int, int);
void display(char**, int, int);
char** dynamicMemory(int, int);
char* dynamicMemory1D(int);
char** dynamicMemory2D(int);
char** ReadFile(char* FileName,int &row,int &col);//
int SizeOfCharArray(char *arr);
char* reverseCharArray(char*arr);
bool SearchVertical(char* Word, char** Grid, int Row, int Col);
bool SearcHorizontal(char* Word, char** Grid, int Row, int Col);
bool SearchDiagonalLeft(char* Word, char** Grid, int Row, int Col, int i, int j);
bool SearchDiagonalRight(char* Word, char** Grid, int Row, int Col, int i, int j);
bool SearchDiagonal(char* Word, char** Grid, int Row, int Col);
bool CompareWords(char* w1, char* w2);
bool VerifyWord(char* word);
void SaveGame(char** Grid,int row,int col,char* Name,int score,char level);
int maxIndex(int *ptr, int size);
int minIndex(int *ptr, int size);
int HighestScore();
char** Resume(int &row, int &col, char* Name, int &score, char &level);
void Delete(char **ptr, int row);
void small(char* ptr);
void capitalize(char *ptr);
void CopyCharArray(char *&p, char* &q);
void SaveHighestScore(int s, char *Name);
void Play(char Level, char* Name, char **grid, int row, int col, int &score, char &YorN);

void MENU();

int main()
{
	MENU();
	return 0;
}


int readRowSize(ifstream& fin)
{
	int size = 0;
	fin >> size;
	return size;
}
int readColSize(ifstream& fin)
{
	int size = 0;
	fin >> size;
	return size;
}
void readRowColSize(ifstream&fin, int&r, int&c)
{
	fin >> r;
	fin >> c;
}
void read(ifstream&fin, char **ptr, int row, int col)
{
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			fin >> ptr[r][c];
		}
	}
}
void display(char** ptr, int row, int col)
{
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			cout << ptr[r][c] << " ";
		}
		cout << endl;
	}
}


void displayReverse(char** ptr, int row, int col)
{
	for (int r = row - 1; r >= 0; r--)
	{
		for (int c = col - 1; c >= 0; c--)
		{
			cout << " ";
		}
		cout << endl;
	}
}
char **dynamicMemory(int row, int col)
{
	char**temp = nullptr;
	temp = dynamicMemory2D(row);
	for (int r = 0; r < row; r++)
	{
		temp[r] = dynamicMemory1D(col);
	}
	return temp;
}
char* dynamicMemory1D(int size)
{
	char *temp = nullptr;
	temp = new char[size];
	return temp;
}
char** dynamicMemory2D(int row)
{
	char **temp = nullptr;
	temp = new char *[row];
	return temp;
}
int SizeOfCharArray(char *arr)
{
	int count = 0;
	while (arr[count] != '\0')
	{
		count++;
	}
	return count;
}
char* reverseCharArray(char*arr)
{
	int size = SizeOfCharArray(arr), start = 0, end = size - 1;
	char *ReversedArray = new char[size + 1];
	while (end >= 0)
	{
		ReversedArray[start] = arr[end];
		start++;
		end--;
	}
	ReversedArray[size] = '\0';
	return ReversedArray;
}
char** ReadFile(char* FileName, int &row, int &col)
{
	char **Grid = nullptr;
	ifstream fin(FileName);
	if (!fin.is_open())
	{
		cout << "File not Open" << endl;
	}
	else
	{
		row = readRowSize(fin);
		col = readColSize(fin);
		Grid = dynamicMemory(row, col);
		read(fin, Grid, row, col);
		
	}
	fin.close();
	return Grid;
}
bool SearchVertical(char* Word, char** Grid, int Row, int Col)
{
	
	for (int i = 0; i < Row; i++)
	{
		int x = 0;
		for (int j = 0; j < Col; j++)
		{
			if (Grid[i][j] == Word[x])
			{
				x++;
			}
			else
			{
				x = 0;
			}
			if (x == SizeOfCharArray(Word))
			{
				return true;
			}
		}
	}
	return false;
}
bool SearcHorizontal(char* Word, char** Grid, int Row, int Col)
{

	for (int i = 0; i < Row; i++)
	{
		int x = 0;
		for (int j = 0; j < Col; j++)
		{
			if (Grid[j][i] == Word[x])
			{
				x++;
			}
			else
			{
				x = 0;
			}
			if (x == SizeOfCharArray(Word))
			{
				return true;
			}
		}
	}
	return false;
}
bool SearchDiagonalLeft(char* Word, char** Grid, int Row, int Col, int i, int j)
{
	int x = 0;
	while ((i < Row) && (j < Col))
	{
		if (Grid[i][j] == Word[x])
		{
			x++;
		}
		else
		{
			x = 0;
		}
		if (x == SizeOfCharArray(Word))
		{
			return true;
		}
		i++;
		j++;
	}
	return false;
}
bool SearchDiagonalRight(char* Word, char** Grid, int Row, int Col, int i, int j)
{
	int x = 0;
	while ((j >= 0) && (i < Col))
	{
		if (Grid[i][j] == Word[x])
		{
			x++;
		}
		else
		{
			x = 0;
		}
		if (x == SizeOfCharArray(Word))
		{
			return true;
		}
		i++;
		j--;
	}
	return false;
}
bool SearchDiagonal(char* Word, char** Grid, int Row, int Col)
{
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			if (SearchDiagonalLeft(Word, Grid, Row, Col, i, j) || SearchDiagonalRight(Word, Grid, Row, Col, i, j))
			{
				return true;
			}
		}
	}
	return false;
}
bool CompareWords(char* w1, char* w2)
{
	if (SizeOfCharArray(w1) != SizeOfCharArray(w2))
	{
		return false;
	}
	int i = 0;
	while (w1[i] != '\0')
	{
		if (w1[i] != w2[i])
		{
			return false;
		}
		i++;
	}
	return true;
}
bool VerifyWord(char* word)
{
	ifstream fin("dictionary.txt");
	if (!fin.is_open())
	{
		cout << "File Not Found" << endl;
	}
	else
	{
		char read[100];
		while (!fin.eof())
		{
			fin >> read;
			if (CompareWords(read, word))
			{
				return true;
			}
		}
	}
	fin.close();
	return false;
}
void SaveGame(char** Grid, int row, int col, char* Name, int score,char level)
{
	ofstream fout;
	fout.open("Pausedgame.txt", std::ios::app);
	if (!fout.is_open())
	{
		cout << "File Not Found" << endl;
	}
	else
	{
		fout << row << " " << col << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				fout << Grid[i][j];
			}
			fout << endl;
		}
		fout << Name << endl;
		fout << score << endl;
		fout << level << endl;
	}
	fout.close();
}
void small(char* ptr)
{
	int i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] >= 'A' && ptr[i] <= 'Z')
			ptr[i] += 32;
		i++;
	}
}
void capitalize(char *ptr)
{
	int i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] >= 'a' && ptr[i] <= 'z')
			ptr[i] -= 32;
		i++;
	}
}
int minIndex(int *ptr, int size)
{
	int temp = ptr[0], i = 0, index = -1;
	while (i < size)
	{
		if (ptr[i] < temp)
		{
			index = i;
			temp = ptr[i];
		}
		i++;
	}
	return index;
}
void CopyCharArray(char *&p, char* &q)
{
	int i = 0;
	for (; i < SizeOfCharArray(p); i++)
	{
		q[i] = p[i];
	}
	q[i] = '\0';
}
void SaveHighestScore(int s,char *Name)
{
	int size = 5, i = 0;
	char *name=new char[60];
	int *ptr = new int[size];
	char **ctr = dynamicMemory(5, 60);
	ifstream fin("Highrecord.txt");
	if (!fin.is_open())
	{
		cout << "File Not Found" << endl;
	}
	else
	{
		while (fin.getline(name, 50, ','))
		{
			CopyCharArray(name, ctr[i]);
			//ctr[i] = name;
			//cout << ctr[i];
			fin >> ptr[i];
			i++;
		}
		if (i < size)
		{
			ptr[i] = s;
			CopyCharArray(Name, ctr[i]);
			//ctr[i] = Name;
			i++;
		}
		else
		{
			int index = minIndex(ptr, size);
			if (ptr[index] < s)
			{
				ptr[index] = s;
				CopyCharArray(Name, ctr[index]);
				//ctr[index] = Name;
			}
		}
		fin.close();
	}
	/*for (int l = 0; l < i; l++)
	{
		cout << ctr[l] << endl;
	}*/
	ofstream fout("Highrecord.txt");
	if (!fout.is_open())
	{
		cout << "File Not Found" << endl;
	}
	else
	{
		int k = 0;
		while (k < i)
		{
			if (k != 0)
				fout << endl;
			fout << ctr[k] << ',' << ptr[k];
			k++;
		}
	}
	fout.close();
	for (int r = 0; r < size; r++)
	{
		delete[] ctr[r];
		ctr[r] = nullptr;
	}
	delete[] ctr;
	ctr = nullptr;
	delete[]ptr;
	ptr = nullptr;
}
void Play(char Level, char* Name, char **grid, int row, int col, int &score, char &YorN)
{
	bool run = true;
	do
	{
		YorN = '\0';
		cout << "Player Name: " << Name << endl;
		cout << "Score: " << score << endl;
		char word[100];
		cout << "Enter Word to Search: ";
		cin >> word;
		if (Level == 'e' || Level == 'E')
		{
			small(word);
			if (VerifyWord(word))
			{
				capitalize(word);
				run = ((SearcHorizontal(word, grid, row, col)) || (SearchVertical(word, grid, row, col)));
				if (run)
					score++;
			}
			else
			{
				cout << "Entered Word Not Found in Dictionary." << endl;
				cout << "Enter a Valid Word" << endl;
				run = false;
			}
		}
		else
		if (Level == 'm' || Level == 'M')
		{
			small(word);
			if (VerifyWord(word))
			{
				capitalize(word);
				char *reversedWord = reverseCharArray(word);
				run = ((SearcHorizontal(word, grid, row, col)) || (SearchVertical(word, grid, row, col)) || (SearcHorizontal(reversedWord, grid, row, col)) || (SearchVertical(reversedWord, grid, row, col)));
				if (run)
					score++;
			}
			else
			{
				cout << "Entered Word Not Found in Dictionary." << endl;
				cout << "Enter a Valid Word" << endl;
				run = false;
			}
		}
		else
		if (Level == 'h' || Level == 'H')
		{
			small(word);
			if (VerifyWord(word))
			{
				capitalize(word);
				char *reversedWord = reverseCharArray(word);
				run = ((SearcHorizontal(word, grid, row, col)) || (SearchVertical(word, grid, row, col)) || (SearcHorizontal(reversedWord, grid, row, col)) || (SearchVertical(reversedWord, grid, row, col)) || (SearchDiagonal(word, grid, row, col)) || (SearchDiagonal(reversedWord, grid, row, col)));
				if (run)
					score++;
			}
			else
			{
				run = false;
			}
		}
		if (run != true)
			break;
		do
		{
			cout << "Do You Want to Pause Your Game" << endl;
			cout << "Enter y/Y or n/N : ";
			cin >> YorN;
		} while (!(YorN == 'Y' || YorN == 'y' || YorN == 'N' || YorN == 'n'));
	} while ((YorN != 'Y' && YorN != 'y'));
}
int maxIndex(int *ptr, int size)
{
	int temp = ptr[0], i = 0, index = 0;
	if (size <= 0)
		index = -1;
	while (i < size)
	{
		if (ptr[i] > temp)
		{
			index = i;
			temp = ptr[i];
		}
		i++;
	}
	return index;
}
int HighestScore()
{
	int size = 5, i = 0,m;
	char name[60];
	int *ptr = new int[size];
	char **ctr = dynamicMemory(5, 60);
	ifstream fin("Highrecord.txt");
	if (!fin.is_open())
	{
		cout << "File Not Found" << endl;
	}
	else
	{
		int s = 0;
		while (!fin.eof())
		{
			fin.getline(name, 50, ',');
			ctr[s] = name;
			fin >> ptr[s];
			s++;
		}
		if (s != 0)
		{
			m = maxIndex(ptr, s);
			cout << "Highest Score" << endl;
			cout << "Name: " << ctr[m] << endl;
			cout << "Score: " << ptr[m] << endl;
		}
		else
		{
			cout << "No Result Found" << endl;
		}
	}
	fin.close();
	delete[]ptr;
	ptr = nullptr;
	return m;
}
void Delete(char **ctr,int size)
{
	for (int r = 0; r < size; r++)
	{
		delete[] ctr[r];
		ctr[r] = nullptr;
	}
	delete[] ctr;
	ctr = nullptr;
}
char** Resume(int &row, int &col, char* Name, int &score, char &level)
{
	char** Grid = nullptr;
	ifstream fin("Pausedgame.txt");
	if (!fin.is_open())
	{
		cout << "File Not Found" << endl;
	}
	else
	{
		readRowColSize(fin, row, col);
		Grid = dynamicMemory(row, col);
		read(fin, Grid, row, col);
		fin >> Name;
		fin >> score;
		fin >> level;
	}
	fin.close();
	return Grid;
}

void MENU()
{
	cout << "Welcome to Word Search Puzzle Game" << endl;
	int row = 0, col = 0, x = 0, score = 0;
	char FileName[] = "Board.txt", isPause = '\0', level = 'e';
	char**Grid = ReadFile(FileName, row, col);
	char Name[100];
	display(Grid, row, col);
	do
	{
		cout << "Enter 1 to Play New Game" << endl;
		cout << "Enter 2 to Resume Game" << endl;
		cout << "Enter 3 to Select Level" << endl;
		cout << "Enter 4 to Print Hight Score" << endl;
		cout << "Enter 5 to Exit" << endl;
		cout << "Enter : ";
		cin >> x;
		if (x == 1)
		{
			score = 0;
			isPause = '\0';
			level = 'e';
			cout << "Enter Your Name: ";
			cin >> Name;
			Play(level, Name, Grid, row, col, score, isPause);
			if (isPause == 'Y' || isPause == 'y')
			{
				SaveGame(Grid, row, col, Name, score, level);
			}
			else
			{
				SaveHighestScore(score, Name);
				cout << "Your Score is: " << score << endl;
			}
		}
		else
		if (x == 2 && (isPause == 'y' || isPause == 'Y'))
		{
			isPause = '\0';
			Delete(Grid, row);
			Grid=Resume(row, col, Name, score, level);
			display(Grid, row, col);
			Play(level, Name, Grid, row, col, score, isPause);
		}
		else
		if (x == 3)
		{
			score = 0;
			isPause = '\0';
			cout << "Enter e/E for Easy" << endl;
			cout << "Enter m/M for Medium" << endl;
			cout << "Enter h/H for Hard" << endl;
			do
			{
				cout << "Select Level: ";
				cin >> level;
			} while (!(level == 'e' || level == 'm' || level == 'h' || level == 'E' || level == 'M' || level == 'H'));
			cout << "Enter Your Name: ";
			cin >> Name;
			Play(level, Name, Grid, row, col, score, isPause);
			if (isPause == 'Y' || isPause == 'y')
			{
				SaveGame(Grid, row, col, Name, score, level);
			}
			else
			{
				SaveHighestScore(score, Name);
				cout << "Your Score is: " << score << endl;
			}
		}
		else
		if (x == 4)
		{
			HighestScore();
		}
	} while (x != 5);
}
