#include "mainwindow.h"
#include "object.h"
#include "collision.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}

//int main(){
//    Rectangle rec1(10, 10);
//    rec1.position={10, 10};

//    Rectangle rec2(20, 10);
//    rec2.position={26, 10};

//    bool r_r = Rec_vs_rec(rec1, rec2);

//    std::cout<<r_r<<'\n';

//}
