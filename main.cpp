/**
 * @file        main.cpp
 * @brief       Program entry point for uBak application.
 * @details     This file contains the main() function which:
 *              - Creates a QApplication instance
 *              - Loads and installs system-appropriate language translations
 *              - Creates and displays the main application window
 *              - Starts the Qt event loop
 *
 * @author      Arthur Markaryan
 * @date        01.05.2026
 * @version     1.0
 * @license     LGPL v3.0
 * @copyright   Copyright (c) 2026
 *
 * @par Dependencies:
 * - Qt5/6 Core (QApplication, QLocale, QTranslator)
 * - MainWindow class
 *
 * @par Translation files:
 * Translation files are stored in the :/i18n/ resource path
 * with naming pattern: "uBak_<locale>.qm"
 *
 * @par ChangeLog:
 * 01.05.2026   v1.0    Arthur Markaryan - Initial implementation
 *
 * @see         QApplication::exec()
 * @see         QTranslator::load()
 * @see         MainWindow::show()
 *
 * @return      int - Application exit code (0 for success)
 */

#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "uBak_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
