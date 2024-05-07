#pragma once

#include <QWidget>
#include "mpvcontroller.h"
#include <QSlider>
class PlayBar : public QWidget{
	Q_OBJECT
	public:
		PlayBar(MpvController * mpv_controller ,QWidget * parent);
		void resize_bar(int w, int h);

	private slots:
		void toggle_pause();
		void seek_forward();
		void seek_backward();
		void update_file_length(QString length);
		void update_current_pos(QString pos);
		void time_pos_changed(double pos);
		void duration_changed(double duration);
		void fullscreen_toggle();
		
	private:
		QWidget * parent;
		MpvController * mpv;
		QSlider * video_slider;
		QSlider * volume_slider;
		QSettings settings;
		

};
