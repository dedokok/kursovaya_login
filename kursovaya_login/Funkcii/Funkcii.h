#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "../IndividualZadanie/IndividualClass.cpp"
#include <vector>
#include "Account.cpp"
#include "sha256.h" //взял библиотеку https://create.stephan-brumme.com/hash-library/ для хеширования
//эти 2 для toLower для поиска логина с списке
#include <algorithm>
#include <cctype> 
//для звёздочек в консоли
#include <conio.h>
//для считывания файлов
#include <nlohmann/json.hpp>


bool zapisAccount(std::string login, std::string password, int role, std::vector<Account>& vectorAccounts, bool isChange);
bool inputIntSsilka(int messCode, int &parametr, int messType);
bool getAccept();
bool checkCorrStr(std::string strokaForCheck);
bool inputStrSsilka(int messCode,std::string &stroka, int messType);

int checkLogin(std::string v_login, std::string v_password, std::vector<Account> &vectorAccounts);
int checkIfInDB(std::string login, std::vector<Account>&vectorAccounts);
int loginInAccount(std::vector<Account>& vectorAccounts);
int inputInt(int messCode, int messType);

std::string vvodParol();
std::string inputStr(int messCode, int messType);
std::string saultGen();

std::vector<Account> getAccounts();
std::vector<Account> inputNewAccountData(std::vector<Account> vectorAccounts,bool isAdministrator);


void printMessage(int messageCode);
void printErrorMessage(int messageCode);
void printViborMessage(int messageCode);
void isThereBD();
void printShapkaAccounts();
void printAccounts(std::vector<Account>& vectorAccounts, int startI, int kolvoPrint);
void printShapka(int shapkaIndex);


//функция получения информации об аккаунте (полиморфизм)
template <class T>
void printSomeInfo(T &p) {
	p.printSomeInfo();
}