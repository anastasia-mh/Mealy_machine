#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QPainter>

const QString MainWindow::FILE_NAME = QDir::currentPath() + "/../hw2/input.json";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    openFile(FILE_NAME);
    watcher = new QFileSystemWatcher(this);
    connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(fileChanged(QString)));
    watcher->addPath(FILE_NAME);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileChanged(QString path)
{
    if (QFile::exists(path)) {
        watcher->addPath(path);
    }
    openFile(FILE_NAME);
}

void MainWindow::openFile(const QString &filename)
{
    int error = Machine::load(filename);

    switch(error){
    case 0:
        break;
    case 1:
    {
        QMessageBox::critical(this, "Ошибка загрузки", "Не удалось открыть файл.");
        break;
    }
    case 2:
    {
        QMessageBox::critical(this, "Ошибка загрузки", "Файл пуст.");
        break;
    }
    default:
    {
        QMessageBox::critical(this, "Ошибка загрузки", QString("Произошла неизвестная ошибка: %1").arg(error));
    }
    }
}

void MainWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QPainter *painter = new QPainter(this);
    QFont font = painter->font();
    font.setPixelSize(20);
    painter->setFont(font);
    QPen pen = painter->pen();
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    //переместить пэйнтр
    int h = height();
    painter->translate(QPoint(0, h/2));
    draw(painter);
    delete painter;
}

void MainWindow::draw(QPainter *painter)
{
    Machine::doPainting(painter);
}
