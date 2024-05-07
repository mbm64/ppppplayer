#pragma once
#include <QObject>
#include <QWidget>
#include "mpvwidget.h"
#include <QSettings>
class MpvController : public QWidget{
	Q_OBJECT
	public:
		MpvController(MpvWidget *mpv_widget,QWidget *parent = nullptr);
	private:
		QWidget *parent;
		MpvWidget *mpv;
		QTime *clipstart;
		QTime *clipend;
		QSettings settings;
		int volume;
	public slots:
		void file_open();
		void pause();
		void get_start_time();
		void get_end_time();
		void clip_it();
		void set_volume(int vol);
	private slots:
		void handle_mpv_event(mpv_event *event);
	signals:
		void set_start_time(QString);
		void set_end_time(QString);
		// file length (sec)
		void file_loaded(int video_length);
		void time_pos_change(double pos);
		void duration_change(double duration);

};
