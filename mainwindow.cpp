#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // mainWindow style
    this->setFixedSize(this->size());
    this->setWindowIcon(QIcon(":/icons/translate.ico"));

    // translate pushButton's style
    ui->translate_pushButton->setCursor(Qt::PointingHandCursor);
    ui->translate_pushButton->setStyleSheet("background-color:green ; color:white ; border-radius:10px ; font-size:16px ;");

    // source comboBox items (target languages)
    ui->source_comboBox->addItem("English" , "en");
    ui->source_comboBox->addItem("Persian" , "fa");
    ui->source_comboBox->addItem("Chinese" , "zh");
    ui->source_comboBox->addItem("Russian" , "ru");
    ui->source_comboBox->setCursor(Qt::PointingHandCursor);

    // target comboBox items (target languages)
    ui->target_comboBox->addItem("Persian" , "fa");
    ui->target_comboBox->addItem("English" , "en");
    ui->target_comboBox->addItem("Chinese" , "zh");
    ui->target_comboBox->addItem("Russian" , "ru");
    ui->target_comboBox->setCursor(Qt::PointingHandCursor);

    // plainText's style
    ui->source_lineEdit->setStyleSheet("border-radius:10px ; font-size: 16px ;");
    ui->target_lineEdit->setStyleSheet("border-radius:10px ; font-size: 16px ;");

    // other pushButton's style
    ui->rotate_pushButton->setCursor(Qt::PointingHandCursor);
    ui->rotate_pushButton->setStyleSheet("background-color:white ;");
    ui->rotate_pushButton->setIcon(QIcon(":/icons/change.png"));

    ui->copy_pushButton->setCursor(Qt::PointingHandCursor);
    ui->copy_pushButton->setStyleSheet("background-color:white ;");
    ui->copy_pushButton->setIcon(QIcon(":/icons/clipboard.png"));

    // status label
    status = new QLabel() ;
    ui->statusbar->addWidget(status);

    // make a networkManager
    networkManager = new QNetworkAccessManager() ;


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_translate_pushButton_clicked()
{
    // get input data
    QString sourceText = ui->source_lineEdit->text();
    QString sourceLang = ui->source_comboBox->currentData().toString();
    QString targetLang = ui->target_comboBox->currentData().toString();

    // Create the network request
    QUrl url(QString("https://api.mymemory.translated.net/get?q=%1&langpair=%2|%3")
                 .arg(QUrl::toPercentEncoding(sourceText))
                 .arg(sourceLang)
                 .arg(targetLang));
    QNetworkRequest request(url);

    // Send the request
    QNetworkReply *reply = networkManager->get(request);

    // Handle the reply
    connect(reply, &QNetworkReply::finished, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObject = jsonDoc.object();

            // fetch the translated text and set it to targetLineEdit
            QString translatedText = jsonObject["responseData"].toObject()["translatedText"].toString();
            ui->target_lineEdit->setText(translatedText);

            status->clear();
            status->setStyleSheet("color:green ; font-size:16px ;");
            status->setText("translated");

        } else {
            // Error in getting data
            status->clear();
            status->setStyleSheet("color:red ; font-size:16px ;");
            status->setText(reply->errorString());
        }

        reply->deleteLater();
    });
}


void MainWindow::on_rotate_pushButton_clicked()
{
    // swap source and target language
    int tmpIndex1 = ui->source_comboBox->findText(ui->target_comboBox->currentText()) ;
    int tmpIndex2 = ui->target_comboBox->findText(ui->source_comboBox->currentText()) ;

    ui->source_comboBox->setCurrentIndex(tmpIndex1);
    ui->target_comboBox->setCurrentIndex(tmpIndex2);
}


void MainWindow::on_copy_pushButton_clicked()
{
    // Set the text to the clipboard
    QString text = ui->target_lineEdit->text() ;
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(text);

    status->setStyleSheet("color:green ; font-size:16px ;");
    status->setText("copied !");
}

void MainWindow::on_source_lineEdit_textEdited()
{
    on_translate_pushButton_clicked();
}

