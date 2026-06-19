#ifndef QBT_GAIAPROPERTYMANAGERBASE_H
#define QBT_GAIAPROPERTYMANAGERBASE_H


#include <QtCore/QObject>
#include "gaiaV3_export.h"
#include "GAIAPropertyBase.h"

class GAIA_V3_EXPORT GAIAPropertyManagerBase: public QObject {
    Q_OBJECT

public:
    virtual ~GAIAPropertyManagerBase() = default;

public slots:
    GAIAPropertyBase *getProperty(const QByteArray &vendorCommand, bool notify = true);
    virtual GAIAPropertyBase *getPropertyFromVendorCommand(const quint16 &vendorId, const quint16 &commandId) = 0;


protected:
    QMap<quint32, GAIAPropertyBase*> m_properties;

signals:
    void propertyAdded(const QByteArray &vendorCommand);

};


#endif //QBT_GAIAPROPERTYMANAGERBASE_H
