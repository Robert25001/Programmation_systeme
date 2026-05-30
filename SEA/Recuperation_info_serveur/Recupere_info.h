#ifndef RECUPERE_INFO_H
#define RECUPERE_INFO_H

#include <QMainWindow>
#include <QProcess>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Recupere_info;
}
QT_END_NAMESPACE

class Recupere_info : public QMainWindow
{
    Q_OBJECT

public:
    Recupere_info(QWidget *parent = nullptr);
    ~Recupere_info();
    void main_programme() ;
    QString recupere_nombre_coeur_cpu() ;
    QString recupere_memoire_total() ;
    QString recupere_memoire_libre() ;
    QString recupere_taille_disque() ;
    QString recupere_architecture_systeme() ;
    QString recupere_nombre_processus() ;
    QString recupere_nombre_logiciel_installes() ;
    QString recupere_adresse_ip() ;
    void setNombre_coeur_cpu(QString _nombre_coeur) ;
    QString getNombre_coeur_cpu() ;
    void setMemoire_total(QString _memoire_total) ;
    QString getMemoire_total() ;
    void setMemoire_libre(QString _memoire_libre) ;
    QString getMemoire_libre() ;
    void setTaille_disque(QString _taille_disque) ;
    QString getTaille_disque() ;
    void setArchitecture_systeme(QString _architecture_systeme) ;
    QString getArchitecture_systeme() ;
    void setNombre_processus(QString _nombre_processus) ;
    QString getNombre_processus() ;
    void setNombre_logiciel_installes(QString _nombre_logiciel_installes) ;
    QString getNombre_logiciel_installes() ;
    void setAdresse_ip(QString _adresse_ip) ;
    QString getAdresse_ip() ;

private:
    Ui::Recupere_info *ui;
    QString nombre_coeur_cpu ;
    QString memoire_total, memoire_libre ;
    QString taille_disque, architecture_systemee ;
    QString nombre_processus, nombre_logiciel_installes ;
    QString adresse_ip ;
};
#endif // RECUPERE_INFO_H
