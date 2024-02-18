#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>
#include <QVector>
namespace Ui {
class GraphWindow;
}

class GraphWindow : public QDialog {
  Q_OBJECT

 public:
  explicit GraphWindow(QWidget *parent = nullptr);
  ~GraphWindow();
  void setPlotData(const QVector<QPointF> &data);

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  Ui::GraphWindow *ui;
  QVector<QPointF> plotData;
};

#endif  // GRAPHWINDOW_H
