#include <WiFiEspAT.h>
#include <PubSubClient.h>
#include "State.h"

WiFiClient netClient;
PubSubClient client(netClient);

State *state;

struct Connection {
  const char *id;
  const char *user;
  const char *pass;
};

Connection connection;

#define stateTopicPower "7SegmentClock/state/POWER"
#define cmdTopicPower "7SegmentClock/cmd/POWER"

void mqttCallback(char *topic, byte *payload, unsigned int length)
{
    if (strcmp(topic, cmdTopicPower) == 0) {
        state->powerOn = payload[0] == '1';
        client.publish(stateTopicPower, (state->powerOn ? "1" : "0"));
    }
}

void connect()
{
    while (!client.connected())
    {
        Serial.println("Connecting to MQTT...");

        if (client.connect(connection.id, connection.user, connection.pass))
        {
            Serial.println("connected");
            client.subscribe(cmdTopicPower);
        }
        else
        {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

void initMQTT(State *SegmentClock, const char * server, uint16_t port, const char *id, const char *user, const char *pass)
{
    state = SegmentClock;

    connection.id = id;
    connection.user = user;
    connection.pass = pass;

    Serial.println("Connecting to MQTT");

    client.setServer(server, port);
    client.setCallback(mqttCallback);

    connect();
}

void loopMQTT()
{
    if (!client.loop())
    {
        connect();
    }
}
