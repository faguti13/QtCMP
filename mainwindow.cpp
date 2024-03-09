#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "principallist.h"
#include "Node.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(1250,640);
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

    connect(ui->tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(on_tableWidget_cellClicked(int, int)));

    ui->horizontalSlider_Audio_File_Duration->setRange(0,MPlayer->duration()/1000);

    principalLIst listaPrincipal; // llama al constructor principalLIst

    Node** nodeArray = listaPrincipal.getArrayList();

    // for (int i = 0; nodeArray[i] != nullptr; ++i) {
    //     std::cout << "Canción: " << nodeArray[i]->title << " , " << nodeArray[i]->artist << std::endl;
    // }

    // No olvides liberar la memoria cuando ya no la necesites
    // delete[] nodeArray;

    int numNodes = 0;
    while (nodeArray[numNodes] != nullptr) {
        ++numNodes;
    }

    ui->tableWidget->setRowCount(numNodes);
    for (int i = 0; i < numNodes; ++i) {
        QTableWidgetItem *itemTitle = new QTableWidgetItem(QString::fromStdString(nodeArray[i]->title));
        QTableWidgetItem *itemArtist = new QTableWidgetItem(QString::fromStdString(nodeArray[i]->artist));
        QTableWidgetItem *itemAlbum = new QTableWidgetItem(QString::fromStdString(nodeArray[i]->album));
        QTableWidgetItem *itemGenre = new QTableWidgetItem(QString::fromStdString(nodeArray[i]->genre));
        QTableWidgetItem *itemUpVotes = new QTableWidgetItem(QString::number(nodeArray[i]->upVotes));
        QTableWidgetItem *itemDownVotes = new QTableWidgetItem(QString::number(nodeArray[i]->downVotes));

        ui->tableWidget->setItem(i, 0, itemTitle);
        ui->tableWidget->setItem(i, 1, itemArtist);
        ui->tableWidget->setItem(i, 2, itemAlbum);
        ui->tableWidget->setItem(i, 3, itemGenre);
        ui->tableWidget->setItem(i, 4, itemUpVotes);
        ui->tableWidget->setItem(i, 5, itemDownVotes);
    }

    ui->tableWidget->setColumnWidth(0, 290);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 290);
    ui->tableWidget->setColumnWidth(3, 120);
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

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    if (column == 0) {  // Suponiendo que la columna 0 contiene el título de la canción
        QTableWidgetItem *item = ui->tableWidget->item(row, column);

        // Verifica si el elemento tiene datos asociados (podrías haber configurado datos personalizados en addItem)
        if (item->data(Qt::UserRole).isValid()) {
            // Obtén la información de la canción asociada a la fila/columna
            Node* node = qvariant_cast<Node*>(item->data(Qt::UserRole));

            // Obtén la ruta del archivo de la canción
            std::string filePath = node->reference;

            // Convierte la ruta a un formato compatible con URI
            QUrl fileUrl = QUrl::fromLocalFile(QString::fromStdString(filePath));

            // Establece la URL en el reproductor multimedia
            MPlayer->setMedia(fileUrl);

            // Actualiza la etiqueta con el nombre del archivo
            QFileInfo fileInfo(QString::fromStdString(filePath));
            ui->label_File_Name->setText(fileInfo.fileName());

            // Inicia la reproducción
            MPlayer->play();
        }
    }

}

