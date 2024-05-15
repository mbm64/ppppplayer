#pragma once
#include <QWidget>
#include <QApplication>
#include <QMenu>
#include "mpvcontroller.h"
class ContextMenu : public QWidget {
	Q_OBJECT
	public:
	ContextMenu(MpvController*controller, QWidget *parent = nullptr);

	public slots:
		void show_ctx_menu(const QPoint &pos);
		void set_clip_start_time(QString s);
		void set_clip_end_time(QString s);
	private:
		QMenu * ctx_menu;
		QAction *clip_start_time;
		QAction *clip_end_time;
		QMenu * subtitles;
		QMenu * audio;
		QMenu * history;
		MpvController * controller;
		QSettings settings;


		void init_tracks();
		void init_history();
};
