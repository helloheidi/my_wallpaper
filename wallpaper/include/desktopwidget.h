#pragma once

#include <QWidget>
#include <qlabel.h>
#include <QPixmap>
#include <QVideoWidget>
#include <QMediaPlayer>
class DesktopWidget  : public QWidget
{
	Q_OBJECT

public:
	DesktopWidget(QWidget *parent = nullptr);
	~DesktopWidget();

	static QSet<QString> imageFormats;
	static QSet<QString> videoFormats;

	HWND GetBackground();
	void SetBackground(HWND child);	

	void SetimageMode(const int& iamgeMode) { imageMode_ = iamgeMode; };
	void SetfilePath(const QString& filePath) { filePath_ = filePath; };

	int screenWidth;
	int screenHeight;

private:
	QLabel* bklabel;//放壁纸
	int imageMode_;
	QString filePath_;

	QMediaPlayer* videoPlayer;
	QVideoWidget* videoWidget;
	
	void showImage(QString filePath);
	void showVideo(QString filePath);

public slots:
	void UpdateWallpaper();
	void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
};
