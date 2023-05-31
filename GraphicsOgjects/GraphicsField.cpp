#include "GraphicsField.h"

GraphicsField::GraphicsField(const std::vector<std::vector<bool>> &fieldMatrix, int cellSize)
        : fieldMatrix_(fieldMatrix), cellSize_(cellSize) {
    setFlag(ItemHasNoContents, false);
}

QRectF GraphicsField::boundingRect() const {
    return QRectF(0, 0, fieldMatrix_[0].size() * cellSize_, fieldMatrix_.size() * cellSize_);
}


void GraphicsField::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    const int numRows = fieldMatrix_.size();
    const int numCols = fieldMatrix_[0].size();

    painter->fillRect(0, 0, numCols * cellSize_, numRows * cellSize_, Qt::darkBlue);

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            QColor color;
            if (fieldMatrix_[row][col] == 1) {
                continue;
            } else {
                color = QColor(0, 0, 0);
            }
            painter->fillRect(col * cellSize_ * 1.0, row * cellSize_ * 1.0, cellSize_, cellSize_ * 1.0, color);
        }
    }

    painter->restore();

}
