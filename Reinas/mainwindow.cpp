#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  
    QPixmap bkgnd("image.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    ponerReina(0,0,0);
    for(int n=0;n<64;n++){
        setLabelsDeReinas(n,0);
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
void  MainWindow::setLabelsDeReinas(int tableroPos, bool reina){
    QLabel *label = new QLabel(this);
    Labels.push_back(label);
    label->setGeometry(15+100*(tableroPos%8),15+100*(tableroPos/8),100,100);
    QPixmap pixmap;
    if(((tableroPos%8+tableroPos/8)%2==0)&& !reina){
         pixmap=QPixmap("Negro.png");
    } else if (((tableroPos%8+tableroPos/8)%2==0)&& reina){
         pixmap=QPixmap("NegroR.png");
    } else if (((tableroPos%8+tableroPos/8)%2!=0) && !reina){
         pixmap= QPixmap ("Blanco.png");
    } else {
         pixmap=QPixmap ("BlancoR.png");
    }
    label->setPixmap(pixmap);
    label->setMask(pixmap.mask());
}
void MainWindow::cambiarImagenes(int tableroPos,bool reina){
    QPixmap pixmap;
    if(((tableroPos%8+tableroPos/8)%2==0)  &&!reina){
        pixmap =QPixmap ("Negro.png");
    } else if (((tableroPos%8+tableroPos/8)%2==0)&& reina){
        pixmap=QPixmap("NegroR.png");
    } else if (((tableroPos%8+tableroPos/8)%2!=0) && !reina){
        pixmap= QPixmap ("Blanco.png");
    } else {
       pixmap=QPixmap ("BlancoR.png");
    }
    Labels.at(tableroPos)->setPixmap(pixmap);
    Labels.at(tableroPos)->setMask(pixmap.mask());
}
int MainWindow::ponerReina(int i, bool solucion,bool siguiente)
{
    // Si siguiente es verdadero, entonces construira el ultimoa arbol que retorno y ademas este saldra que es una nueva solucion, pero como siguiente es true
    // entonces no retornara 1 hasta la siguiente solucion
    int k;
    solucion = false;
    if(!siguiente){
    k = 0;
    }else {
        k=reinas[i];
    }
    // inicializa contador de movimientos
    do {
        if(!siguiente){
        k++;
        reinas[i] = k;
        }
        // coloca y anota reina i en k
        if (valido(i)){
            if (i < 8){
                int value=ponerReina(i + 1, solucion,siguiente);
                if(value==1){
                    return 1;
                }
                siguiente=false;
                // vuelta atrás
                if (!solucion)
                    reinas[i] = 0;
            }else {
                if(!siguiente)
                return 1;
                solucion=true;
            }
                // todas las reinas colocadas
            }
    } while(!solucion && (k < 8));
    return 0;
}


bool  MainWindow::valido(int i ){
    int r;
    bool  v = true;
    for(r=1;r<=i-1;r++){
        v=v&&(reinas[r]!=reinas[i]);
        v=v&&((reinas[i] - i) != (reinas[r] - r));
        v=v&&((reinas[i] + i) != (reinas[r] + r));
    }
    return v;
}
QString  MainWindow::pasarAStrEntero(){
    QString strEntero;
    for(int i = 1; i <= 8; i++)
        {
        strEntero+=QChar((reinas[i]+'0'));
        }
    return strEntero;
}

void MainWindow::on_Siguiente_clicked()
{
    QString numero= pasarAStrEntero();
    int value = QString(ui->lineEdit->text()).toInt();
    if (numero.compare("15863724")==0){
        value=1;
    }
    else value++;
    QString s = QString::number(value);
    ui->lineEdit->setText(s);
    ponerReina(0,0,1);
    for(int n=0;n<64;n++){
        cambiarImagenes(n,0);
    }
    for(int n=0;n<numero.length();n++){
        cambiarImagenes(n + (numero.at(n).toLatin1()-'0'-1)*8,1);
    }
}
void MainWindow::on_Siguiente_2_clicked()
{
    close();
}
