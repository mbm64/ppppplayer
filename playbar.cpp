#include "playbar.h"
#include <QPushButton>
#include <QSlider>
#include <QBoxLayout>
#include <QTextStream>
PlayBar::PlayBar(MpvController * mpv_controller, QWidget * parent) : QWidget(parent)
{
	this -> mpv = mpv;
	setMinimumSize(640, 120);
	//size handling
	setGeometry(0,parent->height()-120,parent ->width(),120);
	QVBoxLayout * playbar = new QVBoxLayout();
	video_slider = new QSlider();
	video_slider ->setMinimum(0);
	video_slider -> setMaximum(1000);
	video_slider -> setOrientation(Qt::Horizontal);
	playbar -> addWidget(video_slider);



	QHBoxLayout * playbar_options = new QHBoxLayout();

	volume_slider = new QSlider();
	volume_slider -> setOrientation(Qt::Horizontal);
	volume_slider -> setMinimum(0);
	volume_slider -> setMaximum(100);
	volume_slider -> setSliderPosition(settings.value("play/volume",100).toInt());
	connect(volume_slider, &QSlider::valueChanged, mpv_controller, &MpvController::set_volume);
	
	QPushButton * seek_backward_button = new QPushButton("<");
	QPushButton * seek_forward_button = new QPushButton(">");
	QPushButton * pause_button = new QPushButton("Pause");
	connect(pause_button, &QPushButton::pressed,mpv_controller,&MpvController::pause);
	QPushButton * full_screen = new QPushButton("fs");
	connect(full_screen, &QPushButton::pressed, this, &PlayBar::fullscreen_toggle);
	playbar_options -> addWidget(volume_slider, 0, Qt::AlignLeft);
	playbar_options ->addStretch(99);
	playbar_options -> addWidget(seek_backward_button, 0 ,Qt::AlignRight);
	playbar_options -> addWidget(pause_button,0,Qt::AlignHCenter);
	playbar_options -> addWidget(seek_forward_button,0,Qt::AlignLeft);
	playbar_options ->addStretch(99);
	playbar_options -> addWidget(full_screen,0,Qt::AlignRight);

	playbar -> addLayout(playbar_options);
	setLayout(playbar);

	//controller connects 
	connect(mpv_controller, &MpvController::time_pos_change, this, &PlayBar::time_pos_changed);
	connect(mpv_controller,&MpvController::duration_change,this,&PlayBar::duration_changed);




}
void PlayBar::resize_bar(int w, int h){
	setGeometry(0,h-120,w,120);
}
void PlayBar::duration_changed(double duration){

	video_slider -> setMaximum((int)(duration*1000));
}
void PlayBar::time_pos_changed(double pos){
	video_slider -> setSliderPosition((int) (pos*1000));	
}

void PlayBar::fullscreen_toggle(){
	if(parentWidget() ->isFullScreen()){
		parentWidget()-> showNormal();
	}
	else{
		parentWidget()->showFullScreen();
	}
}


//todo 
void PlayBar::toggle_pause(){}
void PlayBar::seek_forward(){}
void PlayBar::seek_backward(){}
void PlayBar::update_file_length(QString length){}
void PlayBar::update_current_pos(QString pos){}
