// РАБОТА С папкАМИ И ПАПКАМИ
// 
// Удаление папка из папки
// Переименование папка
// Поиск папка
//

#include <stdio.h> //для работы с папками (удаление, переименование)
#include <io.h> //удаление
#include <string>
#include <direct.h>
#include <iostream>
using namespace std;




void RenameDirectory()
{
	string oldName;
	string newName;
	cout << "Введите имя папки, которую нужно переименовать" << endl;
	cin.ignore();
	getline(cin, oldName);

	cout << "Введите новое имя папки" << endl;
	getline(cin, newName);

	//если надо переименовать папк в другой папке, то вводим полный адрес (D:/NewFolder/File.txt/)

	if (rename(oldName.c_str(), newName.c_str()) != 0) //c_str() преобразовывает стринг в чар
	{
		cout << "Ошибка! Проверьте имена папок" << endl;
	}
	else
	{
		cout << "Папка успешно переименована" << endl;
	}
}

void RemoveDirectory()
{
	string name;
	cout << "Введите имя папка, который нужно удалить" << endl;
	cin.ignore();
	getline(cin, name);


	if (_rmdir(name.c_str()) != 0) //_rmdir для папок
	{
		cout << "Ошибка! Проверьте имя папки" << endl;
	}
	else
	{
		cout << "Папка успешно удалена" << endl;
	}
}



void SearchDirectory()
{
	//(D:/NewFolder/File.txt/)
	// нажать ентр - покажет все папкы в директории
	//* - показывает все папкы

	string folderPath;
	string mask;
	cout << "Введите полный путь" << endl;
	cin.ignore();
	getline(cin, folderPath);

	cout << "Введите маску" << endl;
	getline(cin, mask);

	string searchPattern = folderPath + mask;


	_finddata_t fileinfo; //поиск папка

	intptr_t handle = _findfirst(searchPattern.c_str(), &fileinfo); //_findfirst  -если папкик есть, передает 0, в любых других случаях -1, intptr_t - тип данных

	if (handle == -1)
	{
		cout << "Папка не найдена или неверно указан путь" << endl;
		return;
	}
	do
	{

		char timeBuff[26];


		cout << "Имя папки: " << fileinfo.name << endl;
		cout << "Атрибуты: " << fileinfo.attrib << endl;


		ctime_s(timeBuff, sizeof(timeBuff), &fileinfo.time_create);
		string timeStr2(timeBuff);
		cout << "Время создания: " << timeStr2 << endl;


		cout << "Размер папка: " << fileinfo.size << endl << endl;
	} while (_findnext(handle, &fileinfo) == 0);  //_findnext  ищет папкы, если функция возвращает 0, то цикл выполняется

	_findclose(handle); //закрывает поиск

}


void CreateDirectory()
{
	string name;
	cout << "Введите имя создаваемой папки: " << endl;
	cin.ignore();
	getline(cin, name);

	if (_mkdir(name.c_str()) == -1)
	{
		cout << "Ошибка! Проверьте имя папки" << endl;
	}
	else
	{
		cout << "Папка успешно создана" << endl;
	}

}

int main()
{
	setlocale(LC_ALL, "Ru");

	char ch;

	do {

		cout << "1 - Переименовать папку" << endl;
		cout << "2 - Удалить папку" << endl;
		cout << "3 - Поиск папки" << endl;
		cout << "4 - Создать папку" << endl;
		cout << "0 - Выход" << endl;

		cin >> ch;

		switch (ch)
		{
		case '1':
		{
			RenameDirectory();
			break;
		}
		case '2':
		{
			RemoveDirectory();
			break;
		}
		case '3':
		{
			SearchDirectory();
			break;
		}
		case '4':
		{
			CreateDirectory();
			break;
		}
		}
	} while (ch != '0');
}
