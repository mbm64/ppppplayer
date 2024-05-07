#include "mainwindow.h"
#include "mpvwidget.h"
#include <QPushButton>
#include <QSlider>
#include <QLayout>
#include <QFileDialog>
#include <QDockWidget>
#include <QResizeEvent>
//#include "mpvcontroller.h"
#include "context.h"
#include "playbar.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setMinimumSize(640,480);
	QCoreApplication::setOrganizationName("ppppc");
	QCoreApplication::setApplicationName("PeePeePooPooPlayer");

    m_mpv = new MpvWidget(this);
    m_slider = new QSlider();
    m_slider->setOrientation(Qt::Horizontal);
    //m_openBtn = new QPushButton("Open");
    //m_playBtn = new QPushButton("Pause");
    //QHBoxLayout *hb = new QHBoxLayout();
    //hb->addWidget(m_openBtn);
	//QDockWidget *dock = new QDockWidget();
	//dock -> setFeatures(QDockWidget::NoDockWidgetFeatures);
		//dock->setWidget(pb);
    //hb->addWidget(m_playBtn);
	//hb -> addWidget(pb);
    /*QVBoxLayout *vl = new QVBoxLayout();
    vl->addWidget(m_mpv,5);
	vl -> addWidget(pb,1);*/
    //vl->addWidget(m_slider);
    //vl->addLayout(hb);
    //setLayout(vl);
	setCentralWidget(m_mpv);
	//addDockWidget(Qt::BottomDockWidgetArea,dock);
	

	m_mpv -> setContextMenuPolicy(Qt::CustomContextMenu);
	MpvController *controller = new MpvController(m_mpv,this);
	pb = new PlayBar(controller,this);
	ContextMenu * ctxmen = new ContextMenu(controller,this);
	connect(m_mpv, &QWidget::customContextMenuRequested,ctxmen,&ContextMenu::show_ctx_menu);
	//connect(m_playBtn, &QPushButton::pressed,controller, &MpvController::pause);
}

void MainWindow::openMedia()
{
    QString file = QFileDialog::getOpenFileName(0, "Open a video");
    if (file.isEmpty())
        return;
    m_mpv->command(QStringList() << "loadfile" << file);
}

void MainWindow::seek(int pos)
{
    m_mpv->command(QVariantList() << "seek" << pos << "absolute");
}

void MainWindow::pauseResume()
{
    const bool paused = m_mpv->getProperty("pause").toBool();
    m_mpv->setProperty("pause", !paused);
}

void MainWindow::setSliderRange(int duration)
{
    m_slider->setRange(0, duration);
}






void MainWindow::resizeEvent(QResizeEvent * event){ 
	pb->resize_bar(event ->size().width(), event->size().height());	
}
