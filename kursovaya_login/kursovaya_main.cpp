#pragma once
#include "Funkcii\Funkcii.h"
#include <Windows.h>
#include <clocale>
#include "Moduli\Administrator\ModulAdministrator.h"
#include "Moduli\Polzovatel\PolzovatelModul.h"
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::locale::global(std::locale(""));
    srand(static_cast<unsigned int>(time(0)));
    bool isRun = true, isLogin = false;
    int role = 0, accountIndex = -1;
    std::vector<Account> vectorAccounts = getAccounts();
    while (isRun) {
        if (accountIndex!=-1) {
            role = vectorAccounts[accountIndex].role;
            int vibor;
            if (role == 0) {
                startPolzovatel() == 1;
            }
            else if (role == 1) {
                startAdministrator(vectorAccounts, accountIndex) == 1;
            }
            return 0;
        }
        else {
            accountIndex = loginInAccount(vectorAccounts);
        }
    }
    return 1;
}