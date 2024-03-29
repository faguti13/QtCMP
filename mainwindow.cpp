#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "principallist.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <unordered_set>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(1250,660);
    ui->setupUi(this);

    // Configurar el temporizador para actualizar la memoria cada segundo
    memoryUpdateTimer = new QTimer(this);
    connect(memoryUpdateTimer, SIGNAL(timeout()), this, SLOT(updateMemoryUsage()));
    memoryUpdateTimer->start(1000); // Actualizar cada segundo

    // Inicializar la información de memoria
    updateMemoryUsage();

    MPlayer = new QMediaPlayer();

    // Conectar la señal mediaStatusChanged a handleMediaStatusChanged
    connect(MPlayer, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::handleMediaStatusChanged);

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

    connect(ui->tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(on_tableWidget_cellClicked(int, int)));

    ui->horizontalSlider_Audio_File_Duration->setRange(0,MPlayer->duration()/1000);

    principalLIst listaPrincipal; // llama al constructor principalLIst

    Node** nodeArray = listaPrincipal.getArrayList();

    std::unordered_set<std::string> uniqueArtists = listaPrincipal.getUniqueArtists();
    updateUniqueSingers(uniqueArtists);

    // Imprime los artistas almacenados en el conjunto
    std::cout << "Diferentes artistas en la lista:" << std::endl;
    for (const auto& artist : uniqueArtists) {
        std::cout << artist << std::endl;
    };


    int numNodes = 0;
    while (nodeArray[numNodes] != nullptr) {
        ++numNodes;
    }

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setRowCount(numNodes);
    for (int i = 0; i < numNodes; ++i) {
        QTableWidgetItem *itemTitle = new QTableWidgetItem(QString::fromStdString(nodeArray[i]->title));
        QTableWidgetItem *itemArtist = new QTableWidgetItem(QString::fromStdString(nodeArray[i]->artist));
        QTableWidgetItem *itemAlbum = new QTableWidgetItem(QString::fromStdString(nodeArray[i]->album));
        QTableWidgetItem *itemGenre = new QTableWidgetItem(QString::fromStdString(nodeArray[i]->genre));
        QTableWidgetItem *itemUpVotes = new QTableWidgetItem(QString::number(nodeArray[i]->upVotes));
        QTableWidgetItem *itemDownVotes = new QTableWidgetItem(QString::number(nodeArray[i]->downVotes));

        // Almacena la referencia del nodo en la columna 0
        itemTitle->setData(Qt::UserRole, QVariant::fromValue(nodeArray[i]));

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

// Declaración de variables miembro en la clase MainWindow para mantener el índice actual
int currentSongIndex = -1; // Inicializado en -1 para indicar que no hay canción en reproducción

void MainWindow::on_pushButton_Seek_Forward_clicked()
{
    int nextIndex = currentSongIndex + 1;

    if (nextIndex < ui->tableWidget->rowCount()) {
        currentSongIndex = nextIndex;

        QTableWidgetItem *nextItem = ui->tableWidget->item(nextIndex, 0);

        if (nextItem && nextItem->data(Qt::UserRole).isValid()) {
            // Obtén el nodo asociado a la celda de la siguiente canción
            Node* nextNode = qvariant_cast<Node*>(nextItem->data(Qt::UserRole));

            // Obtén la información de la siguiente canción
            std::string songName = nextItem->text().toStdString();
            std::string artistName = ui->tableWidget->item(nextIndex, 1)->text().toStdString();
            std::string albumName = ui->tableWidget->item(nextIndex, 2)->text().toStdString();
            std::string genre = ui->tableWidget->item(nextIndex, 3)->text().toStdString();

            // Establece la información en el label
            QString songInfo = QString::fromStdString("Now playing: " + songName + " - " + artistName + " - " + albumName + " (" + genre + ")");
            ui->label_File_Name->setText(songInfo);

            // Obtén el path del archivo de la siguiente canción
            std::string filePath = nextNode->reference;

            // Convierte la ruta a un formato compatible con URI
            QUrl fileUrl = QUrl::fromLocalFile(QString::fromStdString(filePath));

            // Establece la URL en el reproductor multimedia
            MPlayer->setMedia(fileUrl);

            // Inicia la reproducción de la siguiente canción
            MPlayer->play();
        }
    }
}

void MainWindow::on_pushButton_Seek_Back_clicked()
{
    int prevIndex = currentSongIndex - 1;

    if (prevIndex >= 0) {
        currentSongIndex = prevIndex;

        QTableWidgetItem *prevItem = ui->tableWidget->item(prevIndex, 0);

        if (prevItem && prevItem->data(Qt::UserRole).isValid()) {
            // Obtén el nodo asociado a la celda de la canción anterior
            Node* prevNode = qvariant_cast<Node*>(prevItem->data(Qt::UserRole));

            // Obtén la información de la canción anterior
            std::string songName = prevItem->text().toStdString();
            std::string artistName = ui->tableWidget->item(prevIndex, 1)->text().toStdString();
            std::string albumName = ui->tableWidget->item(prevIndex, 2)->text().toStdString();
            std::string genre = ui->tableWidget->item(prevIndex, 3)->text().toStdString();

            // Establece la información en el label
            QString songInfo = QString::fromStdString("Now playing: " + songName + " - " + artistName + " - " + albumName + " (" + genre + ")");
            ui->label_File_Name->setText(songInfo);

            // Obtén el path del archivo de la canción anterior
            std::string filePath = prevNode->reference;

            // Convierte la ruta a un formato compatible con URI
            QUrl fileUrl = QUrl::fromLocalFile(QString::fromStdString(filePath));

            // Establece la URL en el reproductor multimedia
            MPlayer->setMedia(fileUrl);

            // Inicia la reproducción de la canción anterior
            MPlayer->play();
        }
    }
}


void MainWindow::on_horizontalSlider_Audio_File_Duration_valueChanged(int value)
{
    // Obtener la duración total de la canción en milisegundos
    qint64 duration = MPlayer->duration();

    // Obtener el valor máximo del slider
    int maxValue = ui->horizontalSlider_Audio_File_Duration->maximum();

    // Calcular la posición basada en la duración total de la canción y el valor del slider
    double position = (static_cast<double>(value) / maxValue) * duration;

    // Establecer la posición de reproducción
    MPlayer->setPosition(position);
}

void MainWindow::on_horizontalSlider_Audio_Volume_valueChanged(int value)
{
    MPlayer->setVolume(value);
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    if (column == 0) {
        QTableWidgetItem *item = ui->tableWidget->item(row, column);

        // Verifica si el elemento tiene datos asociados
        if (item && item->data(Qt::UserRole).isValid()) {
            // Obtén el nodo asociado a la celda
            Node* node = qvariant_cast<Node*>(item->data(Qt::UserRole));

            // Obtén la información de la canción
            std::string songName = item->text().toStdString();
            std::string artistName = ui->tableWidget->item(row, 1)->text().toStdString();
            std::string albumName = ui->tableWidget->item(row, 2)->text().toStdString();
            std::string genre = ui->tableWidget->item(row, 3)->text().toStdString();

            // Establece la información en el label
            QString songInfo = QString::fromStdString("Now playing: " + songName + " - " + artistName + " - " + albumName + " (" + genre + ")");
            ui->label_File_Name->setText(songInfo);

            // Obtén el path del archivo de la canción
            std::string filePath = node->reference;

            // Convierte la ruta a un formato compatible con URI
            QUrl fileUrl = QUrl::fromLocalFile(QString::fromStdString(filePath));

            // Establece la URL en el reproductor multimedia
            MPlayer->setMedia(fileUrl);

            // Inicia la reproducción
            MPlayer->play();
        }
    }
}

void MainWindow::updateMemoryUsage()
{
    QFile file("/proc/self/statm");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString result = in.readLine();
        file.close();

        QStringList tokens = result.split(" ", QString::SkipEmptyParts);
        if (tokens.size() >= 1) {
            qint64 pages = tokens.at(0).toLongLong();
            qint64 pageSize = 4; // Tamaño de página típico en Linux (en kilobytes)
            qint64 memoryInKB = pages * pageSize;
            double memoryInMB = static_cast<double>(memoryInKB) / 1024;

            ui->memorylabel->setText(QString("Memoria en uso: %1 MB").arg(memoryInMB, 0, 'f', 2));
        }
    }
}

void MainWindow::on_checkBox_CommunityPlaylist_toggled(bool checked)
{
    if(checked == true){
        std::cout<<"Community playlist on"<<std::endl;
    }
    else
    {
        std::cout<<"Community playlist off"<<std::endl;
    }
}


void MainWindow::on_checkBox_Pagination_toggled(bool checked)
{
    if(checked == true){
        std::cout<<"Pagination on"<<std::endl;
    }
    else
    {
        std::cout<<"Pagination off"<<std::endl;
    }
}

void MainWindow::handleMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
        playNextSong();
    }
}

void MainWindow::playNextSong()
{
    int nextIndex = currentSongIndex + 1;

    if (nextIndex < ui->tableWidget->rowCount()) {
        currentSongIndex = nextIndex;

        QTableWidgetItem *nextItem = ui->tableWidget->item(nextIndex, 0);

        if (nextItem && nextItem->data(Qt::UserRole).isValid()) {
            Node* nextNode = qvariant_cast<Node*>(nextItem->data(Qt::UserRole));
            std::string songName = nextItem->text().toStdString();
            std::string artistName = ui->tableWidget->item(nextIndex, 1)->text().toStdString();
            std::string albumName = ui->tableWidget->item(nextIndex, 2)->text().toStdString();
            std::string genre = ui->tableWidget->item(nextIndex, 3)->text().toStdString();

            QString songInfo = QString::fromStdString("Now playing: " + songName + " - " + artistName + " - " + albumName + " (" + genre + ")");
            ui->label_File_Name->setText(songInfo);

            std::string filePath = nextNode->reference;
            QUrl fileUrl = QUrl::fromLocalFile(QString::fromStdString(filePath));

            MPlayer->setMedia(fileUrl);
            MPlayer->play();
        }
    }
}

void MainWindow::updateUniqueSingers(const std::unordered_set<std::string>& uniqueArtists) {
    QLayoutItem *child;
    while ((child = ui->verticalLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Itera sobre los nombres de los artistas y agregar un botón para cada uno al layout vertical
    for (const auto& artist : uniqueArtists) {
        QPushButton *button = new QPushButton(QString::fromStdString(artist));
        ui->verticalLayout->addWidget(button);

        // Conectar la señal de clic del botón a una función para manejar el evento
        connect(button, &QPushButton::clicked, [=]() {
            std::cout << "Clic en el botón de " << artist << std::endl;
            // ACÁ VA EL CÓDIGO QUE MOSTRARIA SOLO LAS CANCIONES DE DICHO CANTANTE EN LA INTERFAZ GRÁFICA
        });
    }
}
