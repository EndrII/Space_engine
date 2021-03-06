#ifndef ERESURSE_H
#define ERESURSE_H
#include "SpaceEngine/System/ESprite.h"
#include "SpaceEngine/System/ELanguage.h"
#include <QMap>
#define FROM_NAME 0
typedef QMap<us,us> craftList;
class EResurse
{
private:
    ui _id;//unikalnii id
protected:
    QString _name, _descript,_url;
    QImage *Picture;
    craftList craft;// te elementi kotorie nugni dlya sozdaniya etogo elementa
    ui mass;
    /**
     * @brief loadImage загрузит картинку
     */

    void loadImage();
    void deleteImage();

public:
    /**
     * @brief EResurse rонструктор
     * @param url путь к основному файлу ()
     * @param name индекс имени ресурса в языковом файле
     * @param val количество в стеке
     * @param descript индекс описания в языковом файле
     */
    explicit EResurse(const QString &url, const ui &id, const QString &name="none", const ui val=1, const QString &descript=0);
    /**
     * @brief picture
     * @return  вернет пиутограмму
     */
    QImage* picture();
    /**
     * @brief setUrl new url for the resurs
     * @param url
     */
    void setUrl(const QString& url);
    /**
     * @brief setmass установит новое число данного ресурса
     * @param val
     */
    void setMass(const ui& val);
    /**
     * @brief getmass
     * @return вернет количество ресурсов в этом стеке
     */
    ui getMass()const;

    /**
     * @brief id вернет ид ресурса
     * @return
     */
    ui id()const;
    /**
     * @brief url
     * @return вернет путь к файу генерации
     */
    const QString& url()const;
    /**
     * @brief getCraft элементы для создания этого элемента
     * @return вернет списов для создания (если он пуст значит предмет оздать нельзя)
     */
    craftList * getCraft();
    /**
     * @brief setName установит новое имя
     * @param IndexName индекс нового имени в языковом файле
     */
    void setName(const QString &IndexName);
    /**
     * @brief setPicture установит ресурсу новое изображение
     * @param _default
     */
    void setPicture(const QString& url, bool _default=false);

    /**
     * @brief setDescription установит новое описание
     * @param desc индекс нового описания в языковом файле
     */
    void setDescription(const QString &desc);
    /**
     * @brief name
     * @return вернет имя ресурса (ткст)
     */
    const QString& name();
    /**
     * @brief desc вернет описания ресурса (тест)
     * @return
     */
    const QString &desc();
    /**
     * @brief rwaName
     * @return вернет оригинальное название в файле языков
     */
    const QString & rawName()const;
    /**
     * @brief idDesc
     * @return вернет оригинальное название описание в файле языков
     */
    const QString & rawDesc()const;
    /**
     * @brief isValid
     * @return true if the object valid
     */
    bool isValid()const;
    ~EResurse();
    friend QDataStream& operator >>(QDataStream &stream,EResurse& res);
    friend QDataStream& operator <<(QDataStream &stream,EResurse& res);

};

#endif // ERESURSE_H
