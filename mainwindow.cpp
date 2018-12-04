#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lexique = new Lexique();
    model = new QStringListModel();
}

MainWindow::~MainWindow()
{
    delete lexique;
    delete ui;
}

void MainWindow::on_actioncharger_lexique_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open the lexique");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Connot open file : "+ file.errorString());
    }
    QTextStream in(&file);
    lexique->loadItems(in);
    lexique->buildAutomate();
}

void MainWindow::on_lineEdit_textChanged(const QString &newWord)
{
    QChar newInput = newWord.back();
    State* currentState = lexique->getCurrentState();
    QStringList list;


    if(isInJall){
        if(jall_out_pas == newWord){
            isInJall = false;

            for(int word: resultArray){
                list << lexique->getItems()[word];
            }
            model->setStringList(list);
            ui->listView->setModel(model);
        }else{
            isInJall = true;
        }
    }else{
        if(!newWord.isEmpty()){

                if(newWord.length() > currentWord.length()){
                    if(currentState->getBranchs()[newInput] == nullptr){
                        isInJall = true;
                            list << "aucun mot correspondant";
                            model->setStringList(list);
                            ui->listView->setModel(model);
                            return;
                    }
                    resultArray = currentState->getBranchs()[newInput]->getOutput();

                }else if(currentState->getPreviousState() != nullptr){
                    //comme on recul on veut le state precedent
                    currentState = currentState->getPreviousState()->getPreviousState();
                    resultArray = currentState->getBranchs()[newInput]->getOutput();
                }

                for(int word: resultArray){
                    list << lexique->getItems()[word];
                }
                model->setStringList(list);
                ui->listView->setModel(model);
                currentState = currentState->getBranchs()[newInput]->getNextState();
                lexique->setCurrentState(currentState);
                currentWord = newWord;

                jall_out_pas = newWord;
            //changer la list dans le widget

        }
   }


}
