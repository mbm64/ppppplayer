#pragma once
#include "playlist.h"
#include <QBoxLayout>
#include <QListWidget>
#include <QString>
PlaylistWindow::PlaylistWindow(MpvController * controller, QWidget * parent) : QWidget(parent){
	hide();
	this -> controller = controller;
	QHBoxLayout * layout = new QHBoxLayout();
	playlist = new QListWidget();
	layout->addWidget(playlist);
	setLayout(layout);
}

void PlaylistWindow::showEvent(QShowEvent * event){
	int count = controller -> getProperty("playlist/count").toInt();
	int current_index = controller -> getProperty("playlist-pos").toInt();

	playlist->clear();
	for(int i = 0; i< count; i++){
		QString file = controller -> getProperty(QString("playlist/%1/filename").arg(i)).toString();
		playlist->addItem(file);
	}

}
