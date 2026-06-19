#include <QtTest/QtTest>
#include "BluetoothSocketWrapper.h"

class BluetoothSocketWrapperTests : public QObject
{
    Q_OBJECT

private slots:
    void defaultSocketIsClosed()
    {
        BluetoothSocketWrapper wrapper;
        QVERIFY(!wrapper.isOpen());
        QVERIFY(wrapper.readAll().isEmpty());
    }

    void writeFailsWhenClosed()
    {
        BluetoothSocketWrapper wrapper;
        QCOMPARE(wrapper.write(QByteArray("abc", 3)), qint64(-1));
    }

    void invalidAddressDoesNotOpen()
    {
        BluetoothSocketWrapper wrapper;
        wrapper.connectToService("not-a-bt-address");
        QTest::qWait(200);
        QVERIFY(!wrapper.isOpen());
    }
};

QTEST_MAIN(BluetoothSocketWrapperTests)
#include "test_BluetoothSocketWrapper.moc"
