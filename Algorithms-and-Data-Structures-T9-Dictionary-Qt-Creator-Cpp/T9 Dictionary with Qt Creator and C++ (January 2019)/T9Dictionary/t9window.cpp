#include "t9window.h"
#include "ui_t9window.h"
#include "TrieNode.h"
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTime>

T9Window::T9Window(QWidget *parent) :
    QMainWindow(parent),
    whichWord(0),
    ui(new Ui::T9Window)
{
    endOfSuggestions = false;
    podp = new QString[2];
    actualText = "";
    ui->setupUi(this);
    root = new TrieNode();
    actual = root;
    temp = root;

    load_dictionary("/Users/profitz/Documents/github/University/Algorithms and Data Structures - C++ (October 2018 - January 2019)/T9Dictionary/slowa");
}

T9Window::~T9Window()
{
    delete ui;
    delete root;
}

void T9Window::load_dictionary(QString fileName) {
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(nullptr, "Warning", file.errorString());
        exit(EXIT_FAILURE);
    }

    QTextStream ts(&file);
    QString line;

    while(!(ts >> line).atEnd()) {
        insert(line);
    }
}

TrieNode* T9Window::goDeeper(TrieNode* node, int k, bool creatingNewNodes) {
    if(creatingNewNodes) {
        if(node->nodes[k] == nullptr) node->nodes[k] = new TrieNode();
        return node->nodes[k];
    }
    return (node == nullptr ? nullptr : node->nodes[k]);
}

void T9Window::traverse(TrieNode* actual) {
    if(actual != nullptr) {
        for(QString s: actual->vector)
            ui->textBrowser->append(s);

        for(int i = 0; i < 8; i++) {
            traverse(actual->nodes[i]);
        }
    }
}

bool T9Window::insert(QString s) {

    if(s.length() > 0) {

         for(int i = 0; i < s.length(); i++) {
              switch(s.toUtf8().at(i)) {
                   case 'a': case 'b': case 'c':
                        actual = goDeeper(actual, 0);
                        break;
                   case 'd': case 'e': case 'f':
                        actual = goDeeper(actual, 1);
                        break;
                   case 'g': case 'h': case 'i':
                        actual = goDeeper(actual, 2);
                        break;
                   case 'j': case 'k': case 'l':
                        actual = goDeeper(actual, 3);
                        break;
                   case 'm': case 'n': case 'o':
                        actual = goDeeper(actual, 4);
                        break;
                   case 'p': case 'q': case 'r': case 's':
                        actual = goDeeper(actual, 5);
                        break;
                   case 't': case 'u': case 'v':
                        actual = goDeeper(actual, 6);
                        break;
                   case 'w': case 'x': case 'y': case 'z':
                        actual = goDeeper(actual, 7);
                        break;
                   default:
                        actual = root;
                        return false;
              }
         }

         actual->addWord(s);
         actual = root;
         return true;
    }
    return false;
}

void T9Window::performAction(int number) {
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    endOfSuggestions = false;
    actual = goDeeper(actual, number, false);

    if(actual != nullptr) {
        temp = actual;

        if(actual->vector.empty()) {
            podp[0] = "";
            podp[1] = "";
            QString table[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
            long rand = 0;

            if(table[number].length() == 3) {
                rand = random()%3;
            } else rand = random()%4;

            switch(rand) {
                case 0:
                    actualText.append(table[number].at(0));
                    break;
                case 1:
                    actualText.append(table[number].at(1));
                    break;
                case 2:
                    actualText.append(table[number].at(2));
                    break;
                case 3:
                    actualText.append(table[number].at(3));
                    break;
            }
            ui->textBrowser->setText(actualText);
            whichWord = 0;
            podpowiedzi(temp);
        } else {
            actualText = actual->vector[0];
            ui->textBrowser->setText(actualText);
            whichWord = 1;
            podpowiedzi(temp);
        }
    } else {
            ui->textEdit->clear();
            ui->textEdit_2->clear();
            ui->textBrowser->setText("Nie ma takiego słowa. Sprobuj od nowa!");
            reset();
    }
}

bool T9Window::podpowiedzi(TrieNode* temp, bool firstLetter) {
    if(temp == nullptr) return false;
    else {
        bool end = false;
        if((temp->vector.size() > whichWord)) {
            if(!firstLetter) {
                podp[0] = temp->vector[whichWord++];
                ui->textEdit->setText(podp[0]);
                ui->textEdit->setAlignment(Qt::AlignCenter);
                firstLetter = true;
                this->temp = temp;
            }
            if(temp->vector.size() > whichWord) {
                podp[1] = temp->vector[whichWord];
                ui->textEdit_2->setText(podp[1]);
                ui->textEdit_2->setAlignment(Qt::AlignCenter);
                this->temp = temp;
                return true;
            }
        }

        int i = 0;
        while(!end && i < 8 && temp != nullptr) {
            TrieNode* temp2 = nullptr;
            while(temp2 == nullptr && i < 8) {
                whichWord = 0;
                temp2 = findNextNodeWithStrings(temp->nodes[i++]);
            }
            if(temp2 != nullptr) {
                if(!firstLetter && (temp2->vector.size() > whichWord)) {
                    firstLetter = true;
                    podp[0] = temp2->vector[whichWord++];
                    ui->textEdit->setText(podp[0]);
                    ui->textEdit->setAlignment(Qt::AlignCenter);
                    this->temp = temp2;
                }
                if(temp2->vector.size() > whichWord) {
                    podp[1] = temp2->vector[whichWord];
                    ui->textEdit_2->setText(podp[1]);
                    ui->textEdit_2->setAlignment(Qt::AlignCenter);
                    this->temp = temp2;
                    return true;
                }
                end = podpowiedzi(temp2, firstLetter);
            }
        }
        if(end) return true;
        return false;
    }
}

TrieNode* T9Window::findNextNodeWithStrings(TrieNode* node) {
    if(node != nullptr) {
        if(!node->vector.empty()) return node;

        TrieNode* tmp = nullptr;
        int i = 0;
        while(tmp == nullptr && i < 8) {
            tmp = findNextNodeWithStrings(node->nodes[i++]);
        }
        return tmp;
    }
    return nullptr;
}
// Akcja gdy wcisniemy # -> wypisanie nastepnego slowa
void T9Window::on_pushButton_hash_clicked()
{
    if(podp[0].length() > 0) {
        actualText = podp[0];

        ui->textBrowser->setText(actualText);
        ui->textEdit->clear();
        ui->textEdit_2->clear();

        if(!endOfSuggestions) {
            if(!podpowiedzi(temp)) {
                endOfSuggestions = true;
            } else actual = temp;
        } else {
            actual = nullptr;
            ui->textBrowser->setText(podp[0]);
        }
    }
}
// Akcja gdy wcisniemy "2"
void T9Window::on_pushButton_2_clicked()
{
    performAction(0);
}
// Akcja gdy wcisniemy "3"
void T9Window::on_pushButton_3_clicked()
{
    performAction(1);
}
// Akcja gdy wcisniemy "4"
void T9Window::on_pushButton_4_clicked()
{
    performAction(2);
}
// Akcja gdy wcisniemy "5"
void T9Window::on_pushButton_5_clicked()
{
    performAction(3);
}
// Akcja gdy wcisniemy "6"
void T9Window::on_pushButton_6_clicked()
{
    performAction(4);
}
// Akcja gdy wcisniemy "7"
void T9Window::on_pushButton_7_clicked()
{
    performAction(5);
}
// Akcja gdy wcisniemy "8"
void T9Window::on_pushButton_8_clicked()
{
    performAction(6);
}
// Akcja gdy wcisniemy "9"
void T9Window::on_pushButton_9_clicked()
{
    performAction(7);
}
// Akcja gdy wcisniemy "0"
void T9Window::on_pushButton_0_clicked()
{
    ui->textBrowser->clear();
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    reset();
}
// Akcja gdy wcisniemy "*"
void T9Window::on_pushButton_star_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser->setTextColor(QColor::fromHslF(0.7,0.7,0.7, 1));
    ui->textBrowser->append("\n\nT9 Dictionary");
    ui->textBrowser->setAlignment(Qt::AlignCenter);
    ui->textBrowser->append("\n\nCreated by");
    ui->textBrowser->setAlignment(Qt::AlignCenter);
    ui->textBrowser->append("\nAleksander Profic");
    ui->textBrowser->setAlignment(Qt::AlignCenter);

    ui->textBrowser->setTextColor(QColor::fromHslF(1,1,1,1));
}
// Akcja gdy wcisniemy "1"
void T9Window::on_pushButton_clicked()
{
    if(actualText.length() >= 3) {
        ui->textEdit->clear();
        ui->textEdit_2->clear();

        if(actual != nullptr) {
            ui->textBrowser->setText("Lista pasujących słów:");
            traverse(actual);
        }
        else ui->textBrowser->setText("Nie ma takiego słowa. Sprobuj od nowa!");
        reset();
    }
}
// Powrot do danych poczatkowych
void T9Window::reset()
{
    endOfSuggestions = false;
    whichWord = 0;
    podp[0] = "";
    podp[1] = "";
    actualText = "";
    actual = root;
    temp = root;
}
