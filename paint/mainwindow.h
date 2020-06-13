#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

class Canvas;

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
    void closeEvent(QCloseEvent *event) override;

private slots:
    void open();
    void save();
    void brushColor();
    void brushWidth();

private:
    void createActions();
    void createMenus();

    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    Canvas *canvasArea;
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;

    QAction *openAction;
    QList<QAction *> saveAsActionsList;
    QAction *setBrushColorAction;
    QAction *setBrushWidthAction;
    QAction *exitAction;
    QAction *clearAction;


;    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
