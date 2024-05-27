#pragma once

#include <QWidget>
#include "mpvcontroller.h"
#include <QSlider>
#include <QTimer>
#include <QTextStream>
#include <QScrollBar>
#include <QLabel>
class PlayBar : public QWidget{
	Q_OBJECT
	public:
		PlayBar(MpvController * mpv_controller ,QWidget * parent);
		void resize_bar(int w, int h);
		void bar_appear();
		void bar_dissapear();

	private slots:
		//control functions
		void toggle_pause();
		void seek_forward();
		void seek_backward();

		//properties function
		void update_file_length(QString length);
		void update_current_pos(QString pos);
		void time_pos_changed(double pos);
		void duration_changed(double dur);
		void fullscreen_toggle();


		void inc_bar_uptime();


		//bar appearance function
		
		
	private:
		QWidget * parent;
		MpvController * mpv;
		QSlider * video_slider;
		QSlider * volume_slider;
		QSettings settings;
		QTimer * bar_timer;
		int bar_uptime;
		bool visible;
		bool noseek;
		QLabel * duration;
		QLabel * current_time;
		

};
