#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(1720,880);
    ui->setupUi(this);

    MPlayer = new QMediaPlayer();

    ui->pushButton_Play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_Pause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pushButton_Stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButton_Seek_Back->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->pushButton_Seek_Forward->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    ui->horizontalSlider_Audio_Volume->setMinimum(1);
    ui->horizontalSlider_Audio_Volume->setMaximum(100);
    ui->horizontalSlider_Audio_Volume->setValue(30);

    MPlayer->setVolume(ui->horizontalSlider_Audio_Volume->value());

    connect(MPlayer,&QMediaPlayer::durationChanged,this, &MainWindow::durationChanged);
    connect(MPlayer,&QMediaPlayer::positionChanged,this, &MainWindow::positionChanged);

    ui->horizontalSlider_Audio_File_Duration->setRange(0,MPlayer->duration()/1000);

    ui->tableWidget->setRowCount(10);
    for (int i = 0 ; i < 10; i++)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString("Song")));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString("Artist")));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString("Album")));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString("Gen")));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString("0")));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString("0")));
    }

    ui->tableWidget->setColumnWidth(0, 322);
    ui->tableWidget->setColumnWidth(1, 322);
    ui->tableWidget->setColumnWidth(2, 322);
    ui->tableWidget->setColumnWidth(3, 200);
    ui->tableWidget->setColumnWidth(4, 25);
    ui->tableWidget->setColumnWidth(5, 25);

}

MainWindow::~MainWindow()
{
    delete ui;    
}

void MainWindow::updateduration(qint64 duration)
{
    QString timestr;
    if (duration || Mduration)
    {
        QTime CurrentTime((duration / 3600) % 60,(duration/60) %60, duration % 60, (duration * 1000) % 1000);
        QTime totalTime((Mduration / 3600) % 60, (Mduration / 60) %60, Mduration % 60, (Mduration * 1000) % 1000);
        QString format = "mm:ss";
        if (Mduration > 3600)
            format = "hh:mm:ss";
        ui ->label_Value_1->setText(CurrentTime.toString(format));
        ui ->label_Value_2->setText(totalTime.toString(format));
    }
}


void MainWindow::durationChanged(qint64 duration)
{
    Mduration = duration / 1000;
    ui->horizontalSlider_Audio_File_Duration->setMaximum(Mduration);
}

void MainWindow::positionChanged(qint64 progress)
{
    if (!ui->horizontalSlider_Audio_File_Duration->isSliderDown())
    {
        ui->horizontalSlider_Audio_File_Duration->setValue(progress/1000);
    }

    updateduration(progress / 1000);
}

void MainWindow::on_pushButton_Volume_clicked()
{
    if (IS_Muted == false)
    {
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
        IS_Muted = true;
        MPlayer->setMuted(true);
    }
    else
    {
        ui->pushButton_Volume->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        IS_Muted = false;
        MPlayer->setMuted(false);
    }
}


void MainWindow::on_actionOpen_Audio_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Audio File"), "", tr("MP3 Files (*.mp3)"));

    // Convertir la ruta a un formato compatible con URI
    QUrl fileUrl = QUrl::fromLocalFile(fileName);

    // Establecer la URL en el reproductor multimedia
    MPlayer->setMedia(fileUrl);

    // Actualizar la etiqueta con el nombre del archivo
    QFileInfo fileInfo(fileName);
    ui->label_File_Name->setText(fileInfo.fileName());
}


void MainWindow::on_pushButton_Play_clicked()
{
    MPlayer->play();
}


void MainWindow::on_pushButton_Pause_clicked()
{
    MPlayer->pause();
}


void MainWindow::on_pushButton_Stop_clicked()
{
    MPlayer->stop();
}


void MainWindow::on_pushButton_Seek_Forward_clicked()
{
    ui->horizontalSlider_Audio_File_Duration->setValue(ui->horizontalSlider_Audio_File_Duration->value()+100);
    MPlayer->setPosition(ui->horizontalSlider_Audio_File_Duration->value() * 1000);
}


void MainWindow::on_pushButton_Seek_Back_clicked()
{
    ui->horizontalSlider_Audio_File_Duration->setValue(ui->horizontalSlider_Audio_File_Duration->value()-100);
    MPlayer->setPosition(ui->horizontalSlider_Audio_File_Duration->value() * 1000);
}

void MainWindow::on_horizontalSlider_Audio_File_Duration_valueChanged(int value)
{
    // Obtener la duración total de la canción en milisegundos
    qint64 duration = MPlayer->duration();

    // Obtener el valor máximo del slider
    int maxValue = ui->horizontalSlider_Audio_File_Duration->maximum();

    // Calcular la posición basada en la duración total de la canción y el valor del slider
    double position = (static_cast<double>(value) / maxValue) * duration;

    // Redondear al entero más cercano
    qint64 roundedPosition = static_cast<qint64>(position + 0.00005);

    // Establecer la posición de reproducción
    MPlayer->setPosition(roundedPosition);
}

void MainWindow::on_horizontalSlider_Audio_Volume_valueChanged(int value)
{
    MPlayer->setVolume(value);
}
