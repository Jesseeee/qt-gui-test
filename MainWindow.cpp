#include "MainWindow.hpp"

#include <QActionGroup>
#include <QLayout>
#include <QMenu>
#include <QFontDatabase>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QProgressBar>

static QString progressBarColor("\
QProgressBar { \
	border: 1px solid gray;\
	border-radius: 4px;\
	text-align: center;\
}\
\
QProgressBar::chunk {\
	background-color: %1;\
	width: 20px;\
	margin: 1px;\
}\
");

MainWindow::MainWindow()
	: QMainWindow()
{
	QFontDatabase::addApplicationFont(":/images/valueFont.ttf");
	QFontDatabase::addApplicationFont(":/images/font.ttf");

	QFont valueFont("Digital-7", 30);
	QFont textFont("VWThesis MIB Regular", 15);

	QPixmap pixmap(":/images/dial_background_0c.png");
	pixmap = pixmap.scaled(266, 266, Qt::AspectRatioMode::KeepAspectRatio);

	QProgressBar *progressBar = new QProgressBar;
	progressBar->setRange(0, 100);
	progressBar->setStyleSheet(progressBarColor.arg("red"));

	// TURBO

	QLabel *turbo = new QLabel(this);
	turbo->setPixmap(pixmap);

	QLabel *turboTextName = new QLabel(this);
	turboTextName->setAlignment(Qt::AlignmentFlag::AlignCenter);
	turboTextName->setFont(textFont);
	turboTextName->setText("Boost");
	turboTextName->setStyleSheet("color: rgb(255, 0, 0);");

	QLabel *turboTextValue = new QLabel(this);
	turboTextValue->setFont(valueFont);
	turboTextValue->setAlignment(Qt::AlignmentFlag::AlignCenter);
	turboTextValue->setText("0,0");
	turboTextValue->setStyleSheet("color: rgb(255, 0, 0);");

	QLabel *turboTextUnit = new QLabel(this);
	turboTextValue->setFont(textFont);
	turboTextValue->setAlignment(Qt::AlignmentFlag::AlignCenter);
	turboTextValue->setText("Bar");
	turboTextValue->setStyleSheet("color: rgb(255, 0, 0);");

	QLabel *needleTurbo = new QLabel(this);

	QPixmap needleTurboPixmap(":/images/needle2.png");
	needleTurboPixmap = needleTurboPixmap.scaled(230, 230, Qt::AspectRatioMode::KeepAspectRatio);

	QTransform transformTurbo;
	transformTurbo.rotate(45);
	QPixmap rotatedNeedlePixmap = needleTurboPixmap.transformed(transformTurbo);

	needleTurbo->setPixmap(rotatedNeedlePixmap);
	needleTurbo->setAlignment(Qt::AlignmentFlag::AlignCenter);

	// EGT

	QLabel *egt = new QLabel(this);
	egt->setPixmap(pixmap);

	QLabel *egtTextName = new QLabel(this);
	egtTextName->setAlignment(Qt::AlignmentFlag::AlignCenter);
	egtTextName->setFont(textFont);
	egtTextName->setText("EGT");
	egtTextName->setStyleSheet("color: rgb(255, 0, 0);");

	QLabel *egtTextValue = new QLabel(this);
	egtTextValue->setFont(valueFont);
	egtTextValue->setAlignment(Qt::AlignmentFlag::AlignCenter);
	egtTextValue->setText("0");
	egtTextValue->setStyleSheet("color: rgb(255, 0, 0);");

	QLabel *egtTextUnit = new QLabel(this);
	egtTextUnit->setGeometry(0, 120, 0, 0);
	egtTextUnit->setFont(textFont);
	egtTextUnit->setAlignment(Qt::AlignmentFlag::AlignCenter);
	egtTextUnit->setText("°C");
	egtTextUnit->setStyleSheet("color: rgb(255, 0, 0);");

	QLabel *needleEgt = new QLabel(this);
	QPixmap needleEgtPixmap(":/images/needle2.png");
	needleEgtPixmap = needleEgtPixmap.scaled(230, 230, Qt::AspectRatioMode::KeepAspectRatio);

	QPixmap rotatedEgtPixmap = needleEgtPixmap.transformed(transformTurbo);
	needleEgt->setPixmap(rotatedEgtPixmap);
	needleEgt->setAlignment(Qt::AlignmentFlag::AlignCenter);

	// TPS

	QLabel *tps = new QLabel(this);
	tps->setPixmap(pixmap);

	QLabel *tpsTextName = new QLabel(this);
	tpsTextName->setAlignment(Qt::AlignmentFlag::AlignCenter);
	tpsTextName->setFont(textFont);
	tpsTextName->setText("TPS");
	tpsTextName->setStyleSheet("color: rgb(255, 0, 0);");

	QLabel *tpsTextValue = new QLabel(this);
	tpsTextValue->setFont(valueFont);
	tpsTextValue->setAlignment(Qt::AlignmentFlag::AlignCenter);
	tpsTextValue->setText("0");
	tpsTextValue->setStyleSheet("color: rgb(255, 0, 0);");

	QLabel *tpsTextUnit = new QLabel(this);
	tpsTextUnit->setFont(textFont);
	tpsTextUnit->setAlignment(Qt::AlignmentFlag::AlignCenter);
	tpsTextUnit->setText("%");
	tpsTextUnit->setStyleSheet("color: rgb(255, 0, 0);");

	QLabel *needleTps = new QLabel(this);
	QPixmap needleTpsPixmap(":/images/needle2.png");
	needleTpsPixmap			 = needleTpsPixmap.scaled(230, 230, Qt::AspectRatioMode::KeepAspectRatio);
	QPixmap rotatedTpsPixmap = needleTpsPixmap.transformed(transformTurbo);
	needleTps->setPixmap(rotatedTpsPixmap);
	needleTps->setAlignment(Qt::AlignmentFlag::AlignCenter);

	// SLIDERS
	QSlider *sliderTurbo = new QSlider(Qt::Orientation::Horizontal, this);
	sliderTurbo->setMinimum(-100);
	sliderTurbo->setMaximum(250);
	sliderTurbo->setTickPosition(QSlider::TickPosition::NoTicks);
	sliderTurbo->setTickInterval(1);
	QObject::connect(sliderTurbo,
					 &QSlider::valueChanged,
					 [turboTextValue, needleTurboPixmap, needleTurbo](int value)
					 {
						 float fVal = value / 100.0;
						 turboTextValue->setText(QString::number(fVal));
						 float		needleAngle = 45.0 + ((fVal - -1.0) * 270.0) / (2.5 - -1.0);
						 QTransform t;
						 t.rotate(needleAngle);
						 QPixmap rotatedPixmap = needleTurboPixmap.transformed(t);
						 needleTurbo->setPixmap(rotatedPixmap);
					 });
	sliderTurbo->setValue(0);

	QSlider *sliderEgt = new QSlider(Qt::Orientation::Horizontal, this);
	sliderEgt->setMinimum(0);
	sliderEgt->setMaximum(800);
	sliderEgt->setTickPosition(QSlider::TickPosition::NoTicks);
	sliderEgt->setTickInterval(5);
	QObject::connect(sliderEgt,
					 &QSlider::valueChanged,
					 [egtTextValue, needleEgtPixmap, needleEgt](int value)
					 {
						 float fVal = value;
						 egtTextValue->setText(QString::number(fVal));
						 float		needleAngle = 45.0 + ((fVal - 0) * 270.0) / (800 - 0);
						 QTransform t;
						 t.rotate(needleAngle);
						 QPixmap rotatedPixmap = needleEgtPixmap.transformed(t);
						 needleEgt->setPixmap(rotatedPixmap);
					 });
	sliderEgt->setValue(0);

	QSlider *sliderTps = new QSlider(Qt::Orientation::Horizontal, this);
	sliderTps->setMinimum(0);
	sliderTps->setMaximum(100);
	sliderTps->setTickPosition(QSlider::TickPosition::NoTicks);
	sliderTps->setTickInterval(1);
	QObject::connect(sliderTps,
					 &QSlider::valueChanged,
					 [tpsTextValue, needleTpsPixmap, needleTps](int value)
					 {
						 float fVal = value;
						 tpsTextValue->setText(QString::number(fVal));
						 float		needleAngle = 45.0 + ((fVal - 0) * 270.0) / (100 - 0);
						 QTransform t;
						 t.rotate(needleAngle);
						 QPixmap rotatedPixmap = needleTpsPixmap.transformed(t);
						 needleTps->setPixmap(rotatedPixmap);
					 });
	sliderTps->setValue(0);

	// -------------------- LAYOUTS --------------------
	// --------- MAIN LAYOUT ---------
	QWidget		*widget = new QWidget;
	QGridLayout *lay	= new QGridLayout(widget);

	// --------- TURBO LAYOUT ---------
	QHBoxLayout *layTurboH = new QHBoxLayout;
	QVBoxLayout *layTurboV = new QVBoxLayout;

	layTurboV->addSpacing(150);
	layTurboV->addWidget(turboTextName);
	layTurboV->addWidget(turboTextUnit);
	layTurboV->addSpacing(150);
	layTurboH->addSpacing(0);
	layTurboH->addLayout(layTurboV);

	lay->addWidget(turbo, 0, 0); // Dial
	lay->addWidget(turboTextValue, 0, 0); // Value
	lay->addWidget(needleTurbo, 0, 0); // Needle
	lay->addLayout(layTurboH, 0, 0);

	// --------- EGT LAYOUT ---------
	QHBoxLayout *layEgtH = new QHBoxLayout;
	QVBoxLayout *layEgtV = new QVBoxLayout;
	layEgtV->addSpacing(150);
	layEgtV->addWidget(egtTextName);
	layEgtV->addWidget(egtTextUnit);
	layEgtV->addSpacing(150);
	layEgtH->addSpacing(0);
	layEgtH->addLayout(layEgtV);
	lay->addWidget(egt, 0, 1);
	lay->addWidget(egtTextValue, 0, 1);
	lay->addWidget(needleEgt, 0, 1);
	lay->addLayout(layEgtH, 0, 1);

	// --------- TPS LAYOUT ---------
	QHBoxLayout *layTpsH = new QHBoxLayout;
	QVBoxLayout *layTpsV = new QVBoxLayout;
	layTpsV->addSpacing(150);
	layTpsV->addWidget(tpsTextName);
	layTpsV->addWidget(tpsTextUnit);
	layTpsV->addSpacing(150);
	layTpsH->addSpacing(0);
	layTpsH->addLayout(layTpsV);
	lay->addWidget(tps, 0, 2);
	lay->addWidget(tpsTextValue, 0, 2);
	lay->addWidget(needleTps, 0, 2);
	lay->addLayout(layTpsH, 0, 2);

	// --------- SLIDERS LAYOUT ---------
	lay->addWidget(sliderTurbo, 1, 0);
	lay->addWidget(sliderEgt, 1, 1);
	lay->addWidget(sliderTps, 1, 2);
	// lay.addWidget(self.progress_bar,2,0)
	setCentralWidget(widget);
}
