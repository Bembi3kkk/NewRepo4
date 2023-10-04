
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#define O cout<<
#define P cin>>
#define E <<endl;

using namespace std;

#pragma region structura
struct Card {
    string cardnumber;
    double balance;
    Card(string number, double balance1):cardnumber(number), balance(balance1) {}
};
#pragma endregion 


#pragma region newcard
void create(vector<Card>& cards) {
    string cardnumber;
    O "Введите номер карты (8 цифр): ";
    P cardnumber;
    if (cardnumber.length() != 8) {
        cout << "Ошибка! Номер карты должен содержать 8 цифр." E
        return;
    }
    for (const Card& card : cards) {
        if (card.cardnumber == cardnumber) {
            cout << "Ошибка! Карта с таким номером уже существует." E
            return;
        }
    }
    double balance1 = 0;
    cards.push_back(Card(cardnumber, balance1));
    ofstream file("cards.txt", ios::app);
    if (file.is_open()) {
        file << cardnumber << ' ' << balance1 E
        file.close();
    }
    cout << "Карта создана!" << endl;
}
#pragma endregion 

#pragma region popolnenie
void popolnit(vector<Card>& cards) {
    string cardnumber;
    O "Введите номер карты: ";
    P cardnumber;

    double popoln;
    O "Введите сумму для пополнения: ";
    P popoln;
    bool found = false;
    for (Card& card : cards) {
        if (card.cardnumber == cardnumber) {
            card.balance += popoln;
            found = true;
            break;
        }
    }

    if (found) {
        ofstream file("cards.txt");
        if (file.is_open()) {
            for (const Card& card : cards) {
                file << card.cardnumber << " " << card.balance << endl;
            }
            file.close();
        }
        cout << "Счет успешно пополнен." << endl;
    }
    else {
        cout << "Ошибка! Карта с таким номером не найдена." << endl;
    }
}
#pragma endregion 

#pragma region sniatie--
void sniatie(vector<Card>& cards) {
    string cardnumber;
    cout << "Введите номер карты: ";
    cin >> cardnumber;
    double popoln;
    cout << "Введите сумму для снятия: ";
    cin >> popoln;
    bool found = false;
    for (Card& card : cards) {
        if (card.cardnumber == cardnumber) {
            if (card.balance >= popoln) {
                card.balance -= popoln;
                found = true;
            }
            else {
                cout << "Ошибка! Недостаточно средств на счете." << endl;
            }
            break;
        }
    }
    if (found) {
        ofstream file("cards.txt");
        if (file.is_open()){
            for (const Card&card:cards) {
                file<<card.cardnumber<<' '<<card.balance<<endl;
            }
            file.close();
        }
        cout << "Указанная вами сумма снята."<<endl;
    }
    else {
        cout << "Ошибка! Карта с таким номером не найдена." << endl;
    }
}
#pragma endregion 

#pragma region balance
void balance(){
    string cardnumber;
    int ball;
    O "Введите номер карты: ";
    P cardnumber;
    ifstream cardFile(cardnumber + ".txt");
    if (!cardFile) {
        O "Карта не найдена!" E
        return;
    }
    cardFile>>ball;
    cardFile.close();
   O "Текущий баланс: "<<ball<<" грн" E
}
#pragma endregion 



#pragma region main
int main() {
    setlocale(LC_ALL, "RUS");
    vector<Card> cards;
    ifstream file("cards.txt");
    if (file.is_open()) {
        string cardnumber;
        double balance;
        while (file >> cardnumber >> balance) {
            cards.push_back(Card(cardnumber, balance));
        }
        file.close();
    }

    while (true) {
        cout << "Выберите действие:" << endl;
        cout << "1. Создать карту" << endl;
        cout << "2. Пополнить счет" << endl;
        cout << "3. Снять деньги" << endl;
        cout << "4. Проверить баланс" << endl;
        cout << "5 Выход" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            create(cards);
            break;
        case 2:
            popolnit(cards);
            break;
        case 3:
            sniatie(cards);
            break;
            return 0;
        case 4:
            balance(cards);
            break;
        case 5:
            break;
        }
    }
#pragma endregion 