#include <QtTest/QtTest>
#include "GAIAPropertyBase.h"

class TestProperty : public GAIAPropertyBase
{
public:
    TestProperty()
    {
        getVendorId = 0x0495;
        getCommandId = 0x0603;
        getResponseVendorId = 0x0495;
        getResponseCommandId = 0x0703;

        setVendorId = 0x0495;
        setCommandId = 0x080b;
        setResponseVendorId = 0x0495;
        setResponseCommandId = 0x090b;
        setTypes = {UINT8};

        invocationVendorId = 0x0495;
        invocationCommandId = 0x1401;
        invocationResponseVendorId = 0x0495;
        invocationResponseCommandId = 0x1501;
        parameterTypes = {UINT8};
        resultTypes = {UINT8, BOOL, STRING};

        valueTypes = {UINT8};
    }
};

class GAIAPropertyBaseTests : public QObject
{
    Q_OBJECT

private slots:
    void commandGetBuildsExpectedPacket()
    {
        TestProperty property;
        QCOMPARE(property.commandGet(), QByteArray::fromHex("ff03000004950603"));
    }

    void commandSetBuildsExpectedPacket()
    {
        TestProperty property;
        QCOMPARE(property.commandSet({QChar(1)}), QByteArray::fromHex("ff0300010495080b01"));
    }

    void commandInvocationBuildsExpectedPacket()
    {
        TestProperty property;
        QCOMPARE(property.commandInvocation({QChar(2)}), QByteArray::fromHex("ff0300010495140102"));
    }

    void parseValueResponse()
    {
        TestProperty property;
        QSignalSpy spy(&property, SIGNAL(valueChanged()));

        property.parse(QByteArray::fromHex("ff030001049507032a"));

        QCOMPARE(spy.count(), 1);
        QCOMPARE(property.getValue().size(), 1);
        QCOMPARE(property.getValue().at(0).toInt(), 42);
    }

    void parseInvocationResult()
    {
        TestProperty property;
        QSignalSpy spy(&property, SIGNAL(resultChanged()));

        QByteArray packet = QByteArray::fromHex("ff030006049515010201");
        packet.append("Desk", 4);
        property.parse(packet);

        QCOMPARE(spy.count(), 1);
        QCOMPARE(property.getResult().size(), 3);
        QCOMPARE(property.getResult().at(0).toInt(), 2);
        QCOMPARE(property.getResult().at(1).toBool(), true);
        QCOMPARE(property.getResult().at(2).toString(), QString("Desk"));
    }

    void sendGetEmitsPacket()
    {
        TestProperty property;
        QSignalSpy spy(&property, SIGNAL(sendData(QByteArray)));
        property.sendGet();
        QCOMPARE(spy.count(), 1);
        QCOMPARE(spy.takeFirst().at(0).toByteArray(), QByteArray::fromHex("ff03000004950603"));
    }
};

QTEST_MAIN(GAIAPropertyBaseTests)
#include "test_GAIAPropertyBase.moc"
