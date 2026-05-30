#include "Recupere_info.h"
#include "./ui_Recupere_info.h"
#include <QTimer>

Recupere_info::Recupere_info(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Recupere_info)
{
    QTimer *timer = new QTimer(this);
    ui->setupUi(this);
    main_programme();
    connect(timer, &QTimer::timeout, this, &Recupere_info::main_programme);
    timer->start(1000);
}

Recupere_info::~Recupere_info()
{
    delete ui;
}

void Recupere_info::main_programme()
{
    recupere_nombre_coeur_cpu() ;
    recupere_memoire_total() ;
    recupere_memoire_libre() ;
    recupere_taille_disque() ;
    recupere_architecture_systeme() ;
    recupere_nombre_processus() ;
    recupere_nombre_logiciel_installes() ;
    recupere_adresse_ip() ;
}

QString Recupere_info::recupere_nombre_coeur_cpu()
{
    QProcess process;
    process.start("/bin/bash", QStringList() << "-c" << "nproc");

    // Attend la fin de l'exécution (bloquant)
    process.waitForFinished();

    // Récupère la sortie standard
    QByteArray output = process.readAllStandardOutput();
    QString resultat = QString::fromLocal8Bit(output).trimmed();

    setNombre_coeur_cpu(resultat);
    ui->nombre_cpu->setText("Nombre de coeurs CPU: " + getNombre_coeur_cpu()) ;
    return resultat ;
}


QString Recupere_info::recupere_memoire_total()
{
    QProcess process;
    process.start("/bin/bash", QStringList()<< "-c" << "free -m | awk '/^Mem:/{print $2}'");

    // Attend la fin de l'exécution (bloquant)
    process.waitForFinished();

    // Récupère la sortie standard
    QByteArray output = process.readAllStandardOutput();
    QString resultat = QString::fromLocal8Bit(output).trimmed();

    setMemoire_total(resultat);
    ui->memoire_total->setText("Mémoire totale: " + getMemoire_total() + "M") ;
    return resultat ;
}

QString Recupere_info::recupere_memoire_libre()
{
    QProcess process;
    process.start("/bin/bash", QStringList()<< "-c" << "free -m | awk '/^Mem:/{print $7}'");

    // Attend la fin de l'exécution (bloquant)
    process.waitForFinished();

    // Récupère la sortie standard
    QByteArray output = process.readAllStandardOutput();
    QString resultat = QString::fromLocal8Bit(output).trimmed();

    setMemoire_libre(resultat);
    ui->memoire_libre->setText("Mémoire libre: " + getMemoire_libre() + "M") ;
    return resultat ;
}

QString Recupere_info::recupere_taille_disque()
{
    QProcess process;
    process.start("/bin/bash", QStringList()<< "-c" << "df -h / | awk 'NR==2{print $2}'");

    // Attend la fin de l'exécution (bloquant)
    process.waitForFinished();

    // Récupère la sortie standard
    QByteArray output = process.readAllStandardOutput();
    QString resultat = QString::fromLocal8Bit(output).trimmed();

    setTaille_disque(resultat);
    ui->taille_disque->setText("Taille du disque: " + getTaille_disque()) ;
    return resultat ;
}

QString Recupere_info::recupere_architecture_systeme()
{
    QProcess process;
    process.start("/bin/bash", QStringList() << "-c" << "uname -m");

    // Attend la fin de l'exécution (bloquant)
    process.waitForFinished();

    // Récupère la sortie standard
    QByteArray output = process.readAllStandardOutput();
    QString resultat = QString::fromLocal8Bit(output).trimmed();

    setArchitecture_systeme(resultat);
    ui->architecture_systeme->setText("Architecture du système: " + getArchitecture_systeme()) ;
    return resultat ;
}

QString Recupere_info::recupere_nombre_processus()
{
    QProcess process;
    process.start("/bin/bash", QStringList() << "-c" << "ps -e h | wc -l");

    // Attend la fin de l'exécution (bloquant)
    process.waitForFinished();

    // Récupère la sortie standard
    QByteArray output = process.readAllStandardOutput();
    QString resultat = QString::fromLocal8Bit(output).trimmed();

    setNombre_processus(resultat);
    ui->nombre_processus->setText("Nombre de processus: " + getNombre_processus()) ;
    return resultat ;
}

QString Recupere_info::recupere_nombre_logiciel_installes()
{
    QProcess process;
    process.start("/bin/bash", QStringList() << "-c" << "dpkg -l | grep -c \"^ii\"");

    // Attend la fin de l'exécution (bloquant)
    process.waitForFinished();

    // Récupère la sortie standard
    QByteArray output = process.readAllStandardOutput();
    QString resultat = QString::fromLocal8Bit(output).trimmed();

    setNombre_logiciel_installes(resultat);
    ui->nombre_logiciels_installes->setText("Nombre de logiciels installés: " + getNombre_logiciel_installes()) ;
    return resultat ;
}

QString Recupere_info::recupere_adresse_ip()
{
    QProcess process;
    process.start("/bin/bash", QStringList()<< "-c" << "hostname -I | awk '{print $1}'");

    // Attend la fin de l'exécution (bloquant)
    process.waitForFinished();

    // Récupère la sortie standard
    QByteArray output = process.readAllStandardOutput();
    QString resultat = QString::fromLocal8Bit(output).trimmed();

    setAdresse_ip(resultat);
    ui->adresse_ip->setText("Adresse IP: " + getAdresse_ip()) ;
    return resultat ;
}

void Recupere_info::setNombre_coeur_cpu(QString _nombre_coeur)
{
    nombre_coeur_cpu = _nombre_coeur ;
}

QString Recupere_info::getNombre_coeur_cpu()
{
    return nombre_coeur_cpu ;
}

void Recupere_info::setMemoire_total(QString _memoire_total)
{
    memoire_total = _memoire_total;
}

QString Recupere_info::getMemoire_total()
{
    return memoire_total ;
}

void Recupere_info::setMemoire_libre(QString _memoire_libre)
{
    memoire_libre = _memoire_libre ;
}

QString Recupere_info::getMemoire_libre()
{
    return memoire_libre ;
}

void Recupere_info::setTaille_disque(QString _taille_disque)
{
    taille_disque = _taille_disque;
}

QString Recupere_info::getTaille_disque()
{
    return taille_disque ;
}
void Recupere_info::setArchitecture_systeme(QString _architecture_systeme)
{
    architecture_systemee = _architecture_systeme ;
}

QString Recupere_info::getArchitecture_systeme()
{
    return architecture_systemee ;
}

void Recupere_info::setNombre_processus(QString _nombre_processus)
{
    nombre_processus = _nombre_processus ;
}

QString Recupere_info::getNombre_processus()
{
    return nombre_processus ;
}

void Recupere_info::setNombre_logiciel_installes(QString _nombre_logiciel_installes)
{
    nombre_logiciel_installes = _nombre_logiciel_installes ;
}

QString Recupere_info::getNombre_logiciel_installes()
{
    return nombre_logiciel_installes ;
}

void Recupere_info::setAdresse_ip(QString _adresse_ip)
{
    adresse_ip = _adresse_ip ;
}

QString Recupere_info::getAdresse_ip()
{
    return adresse_ip ;
}
