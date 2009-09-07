/****************************************************************************
**
** Copyright (C) 2009 Shawn T. Rutledge (shawn.t.rutledge@gmail.com)
**
** This file is derived from the Qt gif plugin which shipped with
** Qt 4.5.1 and therefore the same license terms apply.
**
****************************************************************************/

#include <qimageiohandler.h>
#include <qstringlist.h>

#ifndef QT_NO_IMAGEFORMATPLUGIN

#ifdef QT_NO_IMAGEFORMAT_GIF
#undef QT_NO_IMAGEFORMAT_GIF
#endif
#include "qgiflibhandler.h"

QT_BEGIN_NAMESPACE

/**
	This GIF image format differs from the Qt 4.5.1 version
	in the following ways:
	1) It can both read and write GIF files
	2) It handles GIF comments
	3) It is linked with giflib rather than being self-contained
*/
class QGIFLibPlugin : public QImageIOPlugin
{
public:
	QGIFLibPlugin();
	~QGIFLibPlugin();

    QStringList keys() const;
    Capabilities capabilities(QIODevice *device, const QByteArray &format) const;
    QImageIOHandler *create(QIODevice *device, const QByteArray &format = QByteArray()) const;
};

QGIFLibPlugin::QGIFLibPlugin()
{
}

QGIFLibPlugin::~QGIFLibPlugin()
{
}

QStringList QGIFLibPlugin::keys() const
{
    return QStringList() << QLatin1String("gif");
}

QImageIOPlugin::Capabilities QGIFLibPlugin::capabilities(QIODevice *device, const QByteArray &format) const
{
	if (format == "gif")
		return Capabilities(CanRead | CanWrite);
	if (!format.isEmpty())
		return 0;
	if (!device)
		return 0;
	if (!device->isOpen())
		return 0;
	Capabilities ret;
	if (device->isReadable() && QGIFLibHandler::canRead(device))
		ret |= CanRead;
	if (device->isWritable())
		ret |= CanWrite;
	return ret;
}

QImageIOHandler *QGIFLibPlugin::create(QIODevice *device, const QByteArray &format) const
{
	QImageIOHandler *handler = new QGIFLibHandler();
	handler->setDevice(device);
	handler->setFormat(format);
	return handler;
}

Q_EXPORT_STATIC_PLUGIN(QGIFLibPlugin)
Q_EXPORT_PLUGIN2(giflib, QGIFLibPlugin)

#endif // QT_NO_IMAGEFORMATPLUGIN

QT_END_NAMESPACE
