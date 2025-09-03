#pragma once

#include "Funkcii.h"
#include <windows.h>

int main()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(static_cast<unsigned int>(time(0)));
    std::string login, password;
    bool isRun = true, isMenu = true, isLogin = false, isFail = false;
    int role = 0;
    //isThereBD();
    while (isRun) {
        if (isLogin) {
            int vibor;
            if (role == 0) {
                std::cout << "Выберите один из пунктов меню:\n1. Выйти из аккаунта\n2. Выйти из приложения\n";
                std::cin >> vibor;
                switch (vibor) {
                case 1: {
                    isLogin = false;
                    break;
                }
                case 2: {
                    isRun = false;
                    break;
                }
                default: {
                    std::cout << "Неправильный выбор!" << std::endl;
                }
                }

            }
            else if (role == 1) {
                std::cout << "Выберите один из пунктов меню:\n1. Добавить аккаунт\n2. Выйти из аккаунта\n3. Выйти из приложения\n";
                std::cin >> vibor;
                switch (vibor) {
                case 1: {
                    int new_role;
                    std::string new_login, new_password;
                    std::cout << "Введите логин нового человека\n";
                    std::cin >> new_login;
                    //if (!checkIfInDB(new_login)) {
                    //    std::cout << "\nВведите пароль нового человека\n";
                    //    std::cin >> new_password;
                    //    std::cout << "\nВведите роль нового человека (1 - администратор, 0 - пользователь)\n";
                    //    std::cin >> new_role;

                    //    newRegistration(new_login, new_password, new_role);
                    //}
                    //else {
                    //    std::cout << "Ошибка: Пользователь уже существует\n";
                    //}


                    break;
                }
                case 2: {
                    isLogin = false;
                    break;

                }
                case 3: {
                    isRun = false;
                    break;
                }
                default: {
                    std::cout << "Неправильный выбор!" << std::endl;
                }
                }
            }
            
        }
        else {
            isLogin = loginInAccount();
        }
    }
    
}

