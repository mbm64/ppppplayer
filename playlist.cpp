#pragma once
#include "playlist.h"
#include <QBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <QFileInfo>
#include <QAction>
#include <QPushButton>
PlaylistWindow::PlaylistWindow(MpvController * controller, QWidget * parent) : QWidget(parent){
	hide();
	this -> controller = controller;
	this->setWindowFlag(Qt::Dialog);
	this -> setMinimumSize(600,400);
	QVBoxLayout * layout = new QVBoxLayout();
	playlist = new QListWidget();
	layout->addWidget(playlist,1);
	QPushButton * exit = new QPushButton("Exit"); 
	connect(exit, &QPushButton::pressed, this, &QWidget::hide);
	layout -> addWidget(exit,0);
	
	setLayout(layout);
}

void PlaylistWindow::showEvent(QShowEvent * event){
	int count = controller -> getProperty("playlist/count").toInt();
	int current_index = controller -> getProperty("playlist-pos").toInt();
	
	playlist->clear();
	for(int i = 0; i< count; i++){
		QString filename = controller -> getProperty(QString("playlist/%1/filename").arg(i)).toString();
		QFileInfo file(filename);
		//if(!file.exists()) continue;
		playlist->addItem(file.fileName());
		connect(playlist, &QListWidget::itemDoubleClicked, this, &PlaylistWindow::item_chosen);
		//connect(item, &QAction::triggered, controller,)
			//addItem(file.fileName());

		
	}

}

void PlaylistWindow::item_chosen(QListWidgetItem * item){
	int index = playlist->row(item);	
	controller ->play_playlist_index(index);


}
