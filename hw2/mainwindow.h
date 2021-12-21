#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileSystemWatcher>
#include <QMainWindow>
#include "machine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *event);
    void draw(QPainter *painter);
private:
    Ui::MainWindow *ui;
    void openFile(const QString &filename);
    static const QString FILE_NAME;
    QFileSystemWatcher * watcher;
private slots:
    void fileChanged(QString path);
};
#endif // MAINWINDOW_H
