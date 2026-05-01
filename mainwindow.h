/**
 * @file		mainwindow.h
 * @brief		Main window module (header file).
 * @details		Contains the definition of the MainWindow class for Qt GUI application.
 * @note		...
 * @author		Arthur Markaryan
 * @date		01.05.2026
 * @version		1.0
 * @license     LGPL v3.0
 * @copyright   Copyright (c) 2026
 *
 * @par ChangeLog:
 * 01.05.2026	v1.0	Base creation
 *
 * @par ToDo: ...
 */

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // _MAINWINDOW_H_
