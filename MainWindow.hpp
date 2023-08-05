#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QString>
#include <QSize>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	typedef QMap<QString, QSize> CustomSizeHintMap;

	explicit MainWindow();
};

#endif // MAINWINDOW_HPP
