#pragma once

#include <QGraphicsScene>

class CGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    CGraphicsScene(QObject *parent);
    ~CGraphicsScene();
};
