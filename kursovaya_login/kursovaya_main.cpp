#pragma once
#include <cstdlib>
#include "Funkcii\Funkcii.h"
#include <Windows.h>
#include "Moduli\Administrator\ModulAdministrator.h"
#include "Moduli\Polzovatel\PolzovatelModul.h"
#include <clocale>
int main()
{
    //system("chcp 1251>nul");
    //setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    //SetConsoleCP(__in UINT wCodePageID);
    //setlocale(LC_ALL, ".866");
    std::locale::global(std::locale(""));
    srand(static_cast<unsigned int>(time(0)));
    std::string login, password;
    bool isRun = true, isMenu = true, isLogin = false, isFail = false;
    int role = 0, accountIndex = -1;
    std::vector<Account> vectorAccounts = getAccounts();
    while (isRun) {
        if (accountIndex!=-1) {
            role = vectorAccounts[accountIndex].role;
            int vibor;
            if (role == 0) {
                startPolzovatel();
            }
            else if (role == 1) {
                startAdministrator(vectorAccounts,accountIndex);
            }
            
        }
        else {
            accountIndex = loginInAccount(vectorAccounts);
        }
    }
    
}

