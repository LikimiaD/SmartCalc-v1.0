#include "graphwindow.h"

#include <QPainter>

#include "ui_graphwindow.h"

GraphWindow::~GraphWindow() {}

GraphWindow::GraphWindow(QWidget *parent) : QDialog(parent) {}

void GraphWindow::setPlotData(const QVector<QPointF> &data) {
  plotData = data;
  update();  // Перерисовка окна
}

void GraphWindow::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, true);

  QRectF bounds = this->rect();
  QPen axisPen(Qt::white, 2);
  painter.setPen(axisPen);
  painter.drawLine(bounds.left(), bounds.center().y(), bounds.right(),
                   bounds.center().y());  // Ось X
  painter.drawLine(bounds.center().x(), bounds.top(), bounds.center().x(),
                   bounds.bottom());  // Ось Y

  if (plotData.isEmpty()) return;

  QVector<QPointF> transformedData;

  double minY = std::numeric_limits<double>::max(),
         maxY = -std::numeric_limits<double>::max();
  for (const QPointF &point : plotData) {
    minY = std::min(minY, point.y());
    maxY = std::max(maxY, point.y());
  }

  for (const QPointF &point : plotData) {
    double x = (point.x() - (-100)) / (200) * bounds.width() + bounds.left();
    double y = (1 - (point.y() - minY) / (maxY - minY)) * bounds.height() +
               bounds.top();
    transformedData << QPointF(x, y);
  }

  QPen graphPen(Qt::red, 2);
  painter.setPen(graphPen);

  // Рисование графика
  for (int i = 1; i < transformedData.size(); ++i) {
    painter.drawLine(transformedData[i - 1], transformedData[i]);
  }
}
