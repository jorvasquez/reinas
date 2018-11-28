#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QBitmap>
#include <QDebug>
#include <QList>
#include <QString>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setLabelsDeReinas(int tableroPos, bool reina);
    ~MainWindow();
    int ponerReina(int i, bool solucion,bool siguiente);
    bool valido(int i );
    void escribeTablero();
    QString  pasarAStrEntero();
    void colocarReinas(QString numero);
    void cambiarImagenes(int tableropos,bool reina);


private slots:



    void on_Siguiente_clicked();

    void on_Siguiente_2_clicked();

private:
    Ui::MainWindow *ui;
    int reinas[9];
    QList <QLabel*> Labels;
};

#endif // MAINWINDOW_H
