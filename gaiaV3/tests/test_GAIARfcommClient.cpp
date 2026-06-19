#include <QtTest/QtTest>
#include "GAIARfcommClient.h"

class TestRfcommClient : public GAIARfcommClient
{
public:
    QList<QByteArray> split(const QByteArray &data) const
    {
        return packetSplitter(data);
    }
};

class GAIARfcommClientTests : public QObject
{
    Q_OBJECT

private slots:
    void packetSplitter_data()
    {
        QTest::addColumn<QByteArray>("input");
        QTest::addColumn<int>("expectedCount");
        QTest::addColumn<QByteArray>("expectedFirst");

        const QByteArray one = QByteArray::fromHex("ff030000001d0003");
        const QByteArray two = one + QByteArray::fromHex("ff03000004950703");

        QTest::newRow("empty") << QByteArray() << 0 << QByteArray();
        QTest::newRow("short") << QByteArray::fromHex("ff03") << 0 << QByteArray();
        QTest::newRow("one packet") << one << 1 << one;
        QTest::newRow("two packets") << two << 2 << one;
        QTest::newRow("trailing partial") << (one + QByteArray::fromHex("ff0300")) << 1 << one;
    }

    void packetSplitter()
    {
        QFETCH(QByteArray, input);
        QFETCH(int, expectedCount);
        QFETCH(QByteArray, expectedFirst);

        TestRfcommClient client;
        const auto packets = client.split(input);
        QCOMPARE(packets.size(), expectedCount);
        if (expectedCount > 0)
            QCOMPARE(packets.first(), expectedFirst);
    }

    void deviceNameSignalOnlyWhenChanged()
    {
        TestRfcommClient client;
        QSignalSpy spy(&client, SIGNAL(deviceNameChanged()));

        client.setDeviceName("MOMENTUM 4");
        client.setDeviceName("MOMENTUM 4");
        client.setDeviceName("ACCENTUM");

        QCOMPARE(client.getDeviceName(), QString("ACCENTUM"));
        QCOMPARE(spy.count(), 2);
    }
};

QTEST_MAIN(GAIARfcommClientTests)
#include "test_GAIARfcommClient.moc"
