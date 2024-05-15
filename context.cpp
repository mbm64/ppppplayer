#include "context.h"
#include "settings_tab.h"
#include <QTextStream>
#include <QLocale>
#include <util.h>
#include <QFileInfo>
//#include "mpvcontroller.h"
ContextMenu::ContextMenu(MpvController *controller, QWidget *parent) : QWidget(parent){
	this -> controller = controller;
	ctx_menu = new QMenu(this);
	QMenu * file = ctx_menu -> addMenu("File");
	QAction * open_file = file -> addAction("Open File");
	QAction * open_folder = file -> addAction("Open Folder");
	history = file -> addMenu("Recently Watched");
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
	//subtitles 
	subtitles = ctx_menu -> addMenu("Subtitles");
	audio = ctx_menu -> addMenu("Audio");
	
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
	connect(open_folder, &QAction::triggered,controller, &MpvController::folder_open);

	}
void ContextMenu::show_ctx_menu(const QPoint &pos){
	init_tracks();
	init_history();
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

void ContextMenu::init_tracks(){
	subtitles ->clear();
	audio -> clear();
	int tracks = controller -> getProperty("track-list/count").toInt();
	int sid = controller -> getProperty("sid").toInt();	
	int aid = controller -> getProperty("aid").toInt();
	QTextStream out(stdout);
	out <<QString("%1 tracks sid: %2 aid: %3\n").arg(tracks).arg(sid).arg(aid);
	QAction * nonesubs = subtitles -> addAction("None");
	connect(nonesubs,&QAction::toggled, this, [this](const bool &b){ if(b) controller->setProperty("sid",0); });
	nonesubs -> setCheckable(true);
	if(sid == 0) nonesubs -> setChecked(true);
	//connect(nonesubs, &QAction::toggled,)
	QAction * noneaud =audio -> addAction("None");
	noneaud -> setCheckable(true);
		connect(noneaud,&QAction::toggled, this, [this](const bool &b){ if(b) controller->setProperty("aid",0); });
	if(aid==0) noneaud -> setChecked(true);
	for(int i = 0; i< tracks; i++){
		QString prefix = QString("track-list/%1/%2").arg(i);
		int id = controller -> getProperty(prefix.arg("id")).toInt();
		QString type = controller -> getProperty(prefix.arg("type")).toString();
		QString title = controller -> getProperty(prefix.arg("title")).toString();
		QString lang = controller -> getProperty(prefix.arg("lang")).toString();
		if(lang.size() > 2) lang = iso3to2(lang); 
		QLocale local(lang);
		//out << QString("%1 %2 %3 %4\n").arg(lang).arg(local.language()).arg(local.name()).arg(QLocale::languageToString(local.language()));
		
		QAction * action = new QAction();
		if(type != "video"){
			if(!title.isEmpty())action ->setText(title);
			else{
				QLocale language(lang);
				action ->setText(QLocale::languageToString(language.language()));
			}
			action -> setCheckable(true);

		}
		if(type == "audio"){
			audio -> addAction(action);
			if(id == aid) action ->setChecked(true);
			connect(action,&QAction::toggled, this, [id,this](const bool &b){ if(b) controller->setProperty("aid", id); });
		}
		else if(type == "sub"){
			subtitles -> addAction(action);	
			if(id == sid) action -> setChecked(true);
			connect(action,&QAction::toggled, this, [id,this](const bool &b){ if(b) controller->setProperty("sid", id); });
		}
		else{
			delete action;
		}	
	}


}

void ContextMenu::init_history(){
	QStringList vid_history = settings.value("history/videos",QStringList()).toStringList();
	for(QString s : vid_history){
		QFileInfo file(s);
		if(!file.exists()) continue;

		history ->addAction(file.fileName());	
	}

}
