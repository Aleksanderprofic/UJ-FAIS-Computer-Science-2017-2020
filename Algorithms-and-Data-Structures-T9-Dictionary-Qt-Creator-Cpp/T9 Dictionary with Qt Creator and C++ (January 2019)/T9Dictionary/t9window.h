#pragma once
#include <QMainWindow>
#include "TrieNode.h"

namespace Ui {
class T9Window;
}

class T9Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit T9Window(QWidget *parent = nullptr);
    ~T9Window();
    void load_dictionary(QString fileName);
    bool insert(QString s);
    TrieNode* goDeeper(TrieNode* node, int k, bool creatingNewNodes = true);
    void traverse(TrieNode* actual);
    void performAction(int number);
    void reset();
    bool podpowiedzi(TrieNode* temp, bool firstLetter = false);
    TrieNode* findNextNodeWithStrings(TrieNode* temp);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_hash_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_0_clicked();

    void on_pushButton_star_clicked();

    void on_pushButton_clicked();

private:
    bool endOfSuggestions;
    unsigned int whichWord;
    QString actualText;
    TrieNode* root, *actual, *temp;
    QString* podp;
    Ui::T9Window *ui;
};
