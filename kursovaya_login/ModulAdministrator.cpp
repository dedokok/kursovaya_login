//#include <fstream>
//#include <string>
//#include <iostream>
//#include <vector>
//#include "Account.cpp"
//#include "sha256.h" //взял библиотеку https://create.stephan-brumme.com/hash-library/ для хеширования
////эти 2 для toLower для поиска логина с списке
//#include <algorithm>
//#include <cctype> 
//#include "Funkcii.cpp"
//
////для звёздочек в консоли
//#include <conio.h>

//std::vector<Account>getUserList() {
//	std::ifstream in;
//	std::vector<Account> userList;
//	in.open("database.txt");
//	std::string line = "", hashed_pass;
//	if (in.is_open()) {
//		while (std::getline(in, line)) {
//			userList.push_back(isRightLine(line));
//		}
//	}
//	in.close();
//	return userList;
//}
//
//void outUserList(std::vector<Account>userList) {
//	for (int i = 0; i < userList.size(); i++) {
//		std::cout << userList[i].login << " " << userList[i].role << " " << userList[i].sault;
//	}
//}
//
//
//
//void startAdministrator() {
//	int vibor;
//	bool isRunAdm = true;
//	while (isRunAdm) {
//		std::cout << "Выберите пункт меню:\n1.Работа с учётными записями\n2.Работа с данными\n";
//		std::cin >> vibor;
//		switch (vibor) {
//		case 1:
//		{
//			bool isRunUchZap = true;
//			while (isRunUchZap) {
//				std::vector<Account>userList;
//				std::cout << "Выберите пункт меню:\n1.Просмотр всех учётных записей\n2. Добавление учётной записи\n3. Редактирование учётной записи\n4.Удаление учётной записи\n";
//				std::cin >> vibor;
//				switch (vibor) {
//				case 1:
//				{
//					if (userList.size() ==0) {
//						userList = getUserList();
//					}
//					
//					break;
//				}
//				case 2:
//				{
//
//				}
//				}
//			}
//		}
//			
//		}
//	}
//}