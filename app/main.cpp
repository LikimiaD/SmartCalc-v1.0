#include <QApplication>

#include "graphwindow.h"
#include "mainapp.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainApp w;
  w.setStyle();
  w.setWindowTitle("Calculator");
  w.show();
  return a.exec();
}
