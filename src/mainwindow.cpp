#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QPen>
#include <QBrush>
#include <QRandomGenerator>

// VertexItem implementation
VertexItem::VertexItem(int id, qreal x, qreal y, QGraphicsItem* parent)
    : QGraphicsEllipseItem(x, y, 30, 30, parent), vertexId(id)
{
    setPen(QPen(Qt::black, 2));
    setBrush(QBrush(Qt::lightGray));
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    
    // Create label as child item so it moves with the vertex
    labelItem = new QGraphicsTextItem(this);
    labelItem->setPlainText(QString::number(id));
    labelItem->setDefaultTextColor(Qt::black);
    
    // Center the text in the circle (circle is 30x30, so center is at 15,15)
    // Adjust for text bounding box - calculate AFTER setting the text
    QFont font = labelItem->font();
    font.setPointSize(12);
    font.setBold(true);
    labelItem->setFont(font);
    
    // Force update of bounding rect by calling documentSize or similar
    labelItem->document()->markContentsDirty(0, labelItem->document()->characterCount());
    
    QRectF textRect = labelItem->boundingRect();
    qreal textWidth = textRect.width();
    qreal textHeight = textRect.height();
    
    // Position text so its center aligns with circle center (15, 15)
    // Use setPos with calculated offset to center it
    labelItem->setPos(15.0 - textWidth / 2.0, 15.0 - textHeight / 2.0);
    labelItem->setFlag(QGraphicsItem::ItemIgnoresParentOpacity, false);
}

int VertexItem::getId() const {
    return vertexId;
}

void VertexItem::setLabelVisible(bool visible) {
    if (labelItem) {
        labelItem->setVisible(visible);
    }
}

QVariant VertexItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionHasChanged) {
        // Notify parent window to update edge positions
        if (scene()) {
            MainWindow* mw = qobject_cast<MainWindow*>(scene()->parent());
            if (mw) {
                mw->updateGraphFromVertex();
            }
        }
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , nextVertexId(1)
{
    ui->setupUi(this);
    
    // Create graphics scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 580, 480);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    
    // Set default start vertex to 20 (variant 20)
    ui->startVertexSpinBox->setValue(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawGraph() {
    // Clear only edges and labels, keep vertices at their current positions
    for (QGraphicsLineItem* line : edgeItems) {
        scene->removeItem(line);
        delete line;
    }
    for (QGraphicsTextItem* label : edgeLabelItems) {
        scene->removeItem(label);
        delete label;
    }
    edgeItems.clear();
    edgeLabelItems.clear();
    
    // Draw edges first (so they appear behind vertices)
    auto vertices = graph.getAllVertices();
    for (int from : vertices) {
        auto neighbors = graph.getNeighbors(from);
        for (const auto& neighbor : neighbors) {
            int to = neighbor.first;
            int weight = neighbor.second;
            
            // Only draw each edge once (for undirected graphs)
            if (from < to || !graph.hasEdge(to, from)) {
                // Get positions
                VertexItem* fromItem = vertexItems.value(from, nullptr);
                VertexItem* toItem = vertexItems.value(to, nullptr);
                
                if (fromItem && toItem) {
                    qreal x1 = fromItem->x() + 15;
                    qreal y1 = fromItem->y() + 15;
                    qreal x2 = toItem->x() + 15;
                    qreal y2 = toItem->y() + 15;
                    
                    // Draw line
                    QGraphicsLineItem* line = scene->addLine(x1, y1, x2, y2, QPen(Qt::black, 2));
                    edgeItems.append(line);
                    
                    // Draw weight label in the middle of the edge
                    QGraphicsTextItem* weightLabel = scene->addText(QString::number(weight));
                    weightLabel->setPos((x1 + x2) / 2 - 10, (y1 + y2) / 2 - 10);
                    weightLabel->setZValue(1); // Ensure label is above the line
                    edgeLabelItems.append(weightLabel);
                }
            }
        }
    }
}

void MainWindow::updateGraphDisplay() {
    drawGraph();
}

void MainWindow::updateGraphFromVertex() {
    drawGraph();
}

void MainWindow::on_addVertexButton_clicked() {
    bool ok;
    QString label = QInputDialog::getText(this, "Добавить вершину", 
        "Введите идентификатор вершины:", QLineEdit::Normal, 
        QString::number(nextVertexId), &ok);
    
    if (ok && !label.isEmpty()) {
        int vertexId = label.toInt();
        if (graph.hasVertex(vertexId)) {
            QMessageBox::warning(this, "Ошибка", "Вершина с таким номером уже существует!");
            return;
        }
        graph.addVertex(vertexId, label);
        
        // Create vertex at random position
        int index = vertexItems.size();
        qreal x = 50 + (index % 6) * 90 + QRandomGenerator::global()->bounded(20);
        qreal y = 50 + (index / 6) * 70 + QRandomGenerator::global()->bounded(20);
        
        // Create vertex circle (movable) - label is now created inside VertexItem constructor
        VertexItem* ellipse = new VertexItem(vertexId, x, y);
        scene->addItem(ellipse);
        vertexItems[vertexId] = ellipse;
        
        updateGraphDisplay();
        nextVertexId++;
    }
}

void MainWindow::on_addEdgeButton_clicked() {
    bool ok1, ok2, ok3;
    int from = QInputDialog::getInt(this, "Добавить ребро", 
        "Введите начальную вершину:", 0, 0, 999, 1, &ok1);
    if (!ok1) return;
    
    int to = QInputDialog::getInt(this, "Добавить ребро", 
        "Введите конечную вершину:", 0, 0, 999, 1, &ok2);
    if (!ok2) return;
    
    int weight = QInputDialog::getInt(this, "Добавить ребро", 
        "Введите вес ребра:", 1, 1, 1000, 1, &ok3);
    if (!ok3) return;
    
    if (!graph.hasVertex(from) || !graph.hasVertex(to)) {
        QMessageBox::warning(this, "Ошибка", "Одна или обе вершины не существуют!");
        return;
    }
    
    graph.addEdge(from, to, weight, false); // Undirected graph
    updateGraphDisplay();
}

void MainWindow::on_removeVertexButton_clicked() {
    bool ok;
    int vertexId = QInputDialog::getInt(this, "Удалить вершину", 
        "Введите номер вершины для удаления:", 0, 0, 999, 1, &ok);
    
    if (ok) {
        if (!graph.hasVertex(vertexId)) {
            QMessageBox::warning(this, "Ошибка", "Вершина не существует!");
            return;
        }
        graph.removeVertex(vertexId);
        updateGraphDisplay();
    }
}

void MainWindow::on_removeEdgeButton_clicked() {
    bool ok1, ok2;
    int from = QInputDialog::getInt(this, "Удалить ребро", 
        "Введите начальную вершину:", 0, 0, 999, 1, &ok1);
    if (!ok1) return;
    
    int to = QInputDialog::getInt(this, "Удалить ребро", 
        "Введите конечную вершину:", 0, 0, 999, 1, &ok2);
    if (!ok2) return;
    
    if (!graph.hasEdge(from, to)) {
        QMessageBox::warning(this, "Ошибка", "Ребро не существует!");
        return;
    }
    
    graph.removeEdge(from, to);
    updateGraphDisplay();
}

void MainWindow::highlightPath(const std::vector<int>& path, const QString& algorithmName) {
    if (path.empty()) {
        ui->resultText->setText(algorithmName + ": Путь не найден или граф пуст.");
        return;
    }
    
    // Build result string
    QString result = algorithmName + ":\nПуть: ";
    for (size_t i = 0; i < path.size(); ++i) {
        result += QString::number(path[i]);
        if (i < path.size() - 1) {
            result += " -> ";
        }
    }
    
    ui->resultText->setText(result);
    
    // Highlight vertices in the path
    for (int vertexId : path) {
        if (vertexItems.contains(vertexId)) {
            vertexItems[vertexId]->setBrush(QBrush(Qt::yellow));
        }
    }
}

void MainWindow::showDistances(const std::map<int, int>& distances, const QString& algorithmName) {
    QString result = algorithmName + " (начальная вершина):\n\n";
    result += "Кратчайшие расстояния от вершины:\n";
    
    for (const auto& pair : distances) {
        result += "Вершина " + QString::number(pair.first) + ": ";
        if (pair.second == std::numeric_limits<int>::max()) {
            result += "недостижима\n";
        } else {
            result += QString::number(pair.second) + "\n";
        }
    }
    
    ui->resultText->setText(result);
}

void MainWindow::showFloydMatrix(const std::vector<std::vector<int>>& matrix) {
    QString result = "Алгоритм Флойда-Уоршелла:\n\nМатрица кратчайших расстояний:\n\n";
    
    int n = matrix.size();
    
    // Header
    result += "     ";
    for (int j = 0; j < n; ++j) {
        result += QString("%1 ").arg(j, 3);
    }
    result += "\n";
    
    // Matrix
    for (int i = 0; i < n; ++i) {
        result += QString("%1: ").arg(i, 3);
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] >= std::numeric_limits<int>::max() / 2) {
                result += "  ∞ ";
            } else {
                result += QString("%1 ").arg(matrix[i][j], 3);
            }
        }
        result += "\n";
    }
    
    ui->resultText->setText(result);
}

void MainWindow::on_bfsButton_clicked() {
    int startVertex = ui->startVertexSpinBox->value();
    
    if (!graph.hasVertex(startVertex)) {
        QMessageBox::warning(this, "Ошибка", "Начальная вершина не существует!");
        return;
    }
    
    std::vector<int> result = graph.bfs(startVertex);
    highlightPath(result, "Обход в ширину (BFS)");
}

void MainWindow::on_dfsButton_clicked() {
    int startVertex = ui->startVertexSpinBox->value();
    
    if (!graph.hasVertex(startVertex)) {
        QMessageBox::warning(this, "Ошибка", "Начальная вершина не существует!");
        return;
    }
    
    std::vector<int> result = graph.dfs(startVertex);
    highlightPath(result, "Обход в глубину (DFS)");
}

void MainWindow::on_dijkstraButton_clicked() {
    int startVertex = ui->startVertexSpinBox->value();
    
    if (!graph.hasVertex(startVertex)) {
        QMessageBox::warning(this, "Ошибка", "Начальная вершина не существует!");
        return;
    }
    
    std::map<int, int> distances = graph.dijkstra(startVertex);
    showDistances(distances, "Алгоритм Дейкстры");
}

void MainWindow::on_floydButton_clicked() {
    if (graph.getVerticesCount() == 0) {
        QMessageBox::warning(this, "Ошибка", "Граф пуст!");
        return;
    }
    
    std::vector<std::vector<int>> matrix = graph.floydWarshall();
    showFloydMatrix(matrix);
}

void MainWindow::on_clearButton_clicked() {
    graph.clear();
    
    // Delete all vertex items (labels are children, so they'll be deleted automatically)
    for (VertexItem* item : vertexItems) {
        scene->removeItem(item);
        delete item;
    }
    
    // Delete all edge items
    for (QGraphicsLineItem* line : edgeItems) {
        scene->removeItem(line);
        delete line;
    }
    
    // Delete all edge label items
    for (QGraphicsTextItem* label : edgeLabelItems) {
        scene->removeItem(label);
        delete label;
    }
    
    vertexItems.clear();
    edgeItems.clear();
    edgeLabelItems.clear();
    ui->resultText->clear();
    nextVertexId = 1;
}

void MainWindow::on_startVertexSpinBox_valueChanged(int value) {
    // Update can be used to refresh display or validate
}

void MainWindow::on_endVertexSpinBox_valueChanged(int value) {
    // Update can be used to refresh display or validate
}
