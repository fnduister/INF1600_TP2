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
    modelOccurrence = new QStringListModel();
    ui->lineEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete lexique;
    delete(model);
    delete(modelOccurrence);
    delete ui;
}

void MainWindow::on_actioncharger_lexique_triggered()
{
    lexique->initialiserLexique();
    QString filename = QFileDialog::getOpenFileName(this,"Open the lexique");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Connot open file : "+ file.errorString());
    }
    QTextStream in(&file);
    lexique->loadItems(in);
    lexique->buildAutomate();
    ui->lineEdit->setReadOnly(false);
}

void MainWindow::on_lineEdit_textChanged(const QString &newWord)
{
    State* currentState = lexique->getCurrentState();
    QStringList list;
    QChar newInput;

    if(!newWord.isEmpty()){
        newInput = newWord.back();
    }else if(isInJall){
            isInJall = false;
    }


    if(isInJall){
        if(jall_out_pas == newWord){
            isInJall = false;

            for(int wordPosition: resultArray){
                list << lexique->getItems()[wordPosition]->getWord();
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

                    //On met a jour
                    if(ui->checkBox->isChecked()){
                        lexique->sortItems();
                        on_checkBox_toggled(true);
                    }
                }else if(currentState->getPreviousState() != nullptr){
                    //comme on recul on veut le state precedent.
                    currentState = currentState->getPreviousState()->getPreviousState();

                    //on verifie si on est au debut.
                    if(currentState->getPreviousState() != nullptr){
                        resultArray = currentState->getBranchs()[newInput]->getOutput();
                    }

                }

                //mettre a jour la liste de mot a afficher ainsi qu'incrementer son occurence.
                for(int wordPosition: resultArray){
                    list << lexique->getItems()[wordPosition]->getWord();
                    lexique->getItems()[wordPosition]->increaseOccurrence();
                }

                model->setStringList(list);
                ui->listView->setModel(model);

                //on va au state suivant.
                currentState = currentState->getBranchs()[newInput]->getNextState();
                lexique->setCurrentState(currentState);

        }else{
            //si on recule jusqu'au debut alors on n'affiche rien et on recommence au state 0.
            model->setStringList(list);
            ui->listView->setModel(model);
            lexique->setCurrentState(lexique->getStates()[0]);
        }

        currentWord = newWord;

        jall_out_pas = newWord;
   }
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    QStringList listOccurrences;
    if(checked){
        lexique->sortItems();
        for(int i = 0;i < lexique->getNumberShowedOccurrences();i++){
            Word* tempWord = lexique->getSortedItems()[i];
            listOccurrences << tempWord->getWord() << QString(tempWord->getOccurrence()) << QString(tempWord->getUsed());
        }
    }else{
        listOccurrences.empty();
    }

    modelOccurrence->setStringList(listOccurrences);
    ui->listViewOccurrences->setModel(modelOccurrence);
}
