#ifndef TRIMMEDIMAGEINFO_H
#define TRIMMEDIMAGEINFO_H

#include <QImage>

class TrimmedImageInfo
{
public:
    TrimmedImageInfo();
    ~TrimmedImageInfo();

    void reset();
    void trimmed();
    int width()const;
    int sourceWidth()const;
    int height()const;
    int sourceHeight()const;
    QPoint sourceOrigin()const;

    void setImage(const QString& path);
    const QImage* img() const;
private:
    TrimmedImageInfo(const TrimmedImageInfo& o);
    TrimmedImageInfo& operator=(const TrimmedImageInfo& o);
private:
    QRect   _trimmed;
    QImage  _img;

};

#endif // TRIMMEDIMAGEINFO_H
