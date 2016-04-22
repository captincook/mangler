#ifndef HIERACHICALVIEWER_HPP
#define HIERACHICALVIEWER_HPP

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTreeWidget>

class HierarchicalViewer : public QTreeWidget
{
    Q_OBJECT
public:
    explicit HierarchicalViewer(QWidget *parent = 0);
    QTreeWidgetItem *addRoot(const char *name);
    QTreeWidgetItem *addChild(QTreeWidgetItem *parent, const char *name);
signals:

public slots:
};

#endif // HIERACHICALVIEWER_HPP
