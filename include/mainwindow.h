#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMap>
#include <vector>
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class VertexItem : public QGraphicsEllipseItem {
public:
    VertexItem(int id, qreal x, qreal y, QGraphicsItem* parent = nullptr);
    int getId() const { return vertexId; }
    
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    
private:
    int vertexId;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addVertexButton_clicked();
    void on_addEdgeButton_clicked();
    void on_removeVertexButton_clicked();
    void on_removeEdgeButton_clicked();
    void on_bfsButton_clicked();
    void on_dfsButton_clicked();
    void on_dijkstraButton_clicked();
    void on_floydButton_clicked();
    void on_clearButton_clicked();
    void on_startVertexSpinBox_valueChanged(int value);
    void on_endVertexSpinBox_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    Graph graph;
    QGraphicsScene *scene;
    QMap<int, VertexItem*> vertexItems;
    QMap<int, QGraphicsTextItem*> labelItems;
    QList<QGraphicsLineItem*> edgeItems;
    QList<QGraphicsTextItem*> edgeLabelItems;
    
    int nextVertexId;
    
    void updateGraphDisplay();
    void drawGraph();
    
public:
    void updateGraphFromVertex();

private:
    void highlightPath(const std::vector<int>& path, const QString& algorithmName);
    void showDistances(const std::map<int, int>& distances, const QString& algorithmName);
    void showFloydMatrix(const std::vector<std::vector<int>>& matrix);
};

#endif // MAINWINDOW_H
