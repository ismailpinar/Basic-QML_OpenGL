#ifndef VERIDOLDUR_H
#define VERIDOLDUR_H

#include <QList>
#include <Nokta.h>
#include <QObject>



class veriDoldur : public QObject
{

    Q_OBJECT
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
public:

    veriDoldur();
    QList<Nokta> Doldur();


    void setAuthor(const QString &a) {
        if (a != m_author) {
            m_author = a;
            //YaziYaz(m_author + "dsd");
            emit authorChanged();
        }
    }
    QString author() const {
        return m_author;
    }

    void YaziYaz(QString yazi);

signals:
    void authorChanged();

private:
    QString m_author = "sadsczx";
};

#endif // VERIDOLDUR_H
