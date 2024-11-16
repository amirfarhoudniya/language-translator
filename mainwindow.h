#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QJsonValue>
#include <QLabel>
#include <QClipboard>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_translate_pushButton_clicked();

    void on_rotate_pushButton_clicked();

    void on_copy_pushButton_clicked();

    void on_source_lineEdit_textEdited();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
    QLabel *status ;

};
#endif // MAINWINDOW_H
