#pragma once
#include <QObject>
#include <QWidget>
#include "mpvwidget.h"
#include <QSettings>
class MpvController : public QWidget{
	Q_OBJECT
	public:
		MpvController(MpvWidget *mpv_widget,QWidget *parent = nullptr);

		QVariant getProperty(QString property);
		void setProperty(QString property, QVariant value);
	private:
		QWidget *parent;
		MpvWidget *mpv;
		QString clipstart;
		QString clipend;
		QSettings settings;
		int volume;
		bool seek_paused;

		void play_init();
		void file_load();
		QString time_pos_string();
	public slots:
		void file_open();
		void folder_open();
		void pause();
		void stop();
		void get_start_time();
		void get_end_time();
		void clip_it();
		void set_volume(int vol);
		void seek(int pos);
		void seek_pause();
		void seek_unpause();
		void seek_forward();
		void seek_backward();
		void seek_time(int secs);
		void play_playlist_index(int ind);
		void screenshot();
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
