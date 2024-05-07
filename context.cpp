#include "context.h"
#include "settings_tab.h"
//#include "mpvcontroller.h"
ContextMenu::ContextMenu(MpvController *controller, QWidget *parent) : QWidget(parent){
	ctx_menu = new QMenu(this);
	QMenu * file = ctx_menu -> addMenu("File");
	QAction * open_file = file -> addAction("Open File");
	QAction * open_folder = file -> addAction("Open Folder");
	QAction * settings = ctx_menu -> addAction("Settings");
	
	QMenu * clip = ctx_menu -> addMenu("Clip");
	//clip functionality
	QAction * set_start_clip = clip -> addAction("Set Start Clip Time");
	clip_start_time = clip ->addAction("Not Set");
	clip_start_time->setEnabled(false);
	QAction * set_end_clip = clip -> addAction("Set End Clip Time");	
	clip_end_time = clip ->addAction("Not Set");
	clip_end_time -> setEnabled(false);
	QAction * clip_it = clip -> addAction("Clip It");
	//clip_it->setEnabled(false);

	ctx_menu -> addSeparator();
	QAction * quit = ctx_menu -> addAction("Quit");
	connect(set_start_clip, &QAction::triggered, controller, &MpvController::get_start_time);
	connect(controller, &MpvController::set_start_time, this, &ContextMenu::set_clip_start_time);
	connect(set_end_clip,&QAction::triggered,controller,&MpvController::get_end_time);
	connect(controller, &MpvController::set_end_time, this, &ContextMenu::set_clip_end_time);
	connect(clip_it, &QAction::triggered,controller, &MpvController::clip_it);
	//connect(controller, &MpvController::set_start_time, this,);
	Settings *settings_tab = new Settings(parent);
	connect(settings, &QAction::triggered, settings_tab, &Settings::show_settings);
	connect(quit, &QAction::triggered, qApp, QApplication::quit);
	connect(open_file, &QAction::triggered, controller,&MpvController::file_open);

	}
void ContextMenu::show_ctx_menu(const QPoint &pos){
	ctx_menu -> exec(this -> mapToGlobal(pos));
}
void ContextMenu::set_clip_start_time(QString s){	
	if(s.isEmpty()) clip_start_time ->setText("Not Set");
	else clip_start_time -> setText(s);

	
}
void ContextMenu::set_clip_end_time(QString s){
	if(s.isEmpty()) clip_end_time ->setText("Not Set");
	else clip_end_time -> setText(s);
}

