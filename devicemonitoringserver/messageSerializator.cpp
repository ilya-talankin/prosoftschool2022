#include "messageSerializator.h"

std::string MessageSerializer::serializate(const MessageStruct& message)
{
    std::ostringstream serialMessage;
    serialMessage << message.messageType;
    if (message.messageType == METERAGE)
    {
        serialMessage << std::to_string(message.measurements.timeStamp);
        serialMessage << ":";
        serialMessage << std::to_string(message.measurements.value);
    }

    if (message.messageType == COMMAND)
    {
        serialMessage << message.adjustment;
    }

    if (message.messageType == ERROR)
    {
        serialMessage << static_cast<int> (message.errorType);
    }

    return serialMessage.str();
};

MessageStruct MessageSerializer::deSerializate(std::string serialMessage)
{
    MessageStruct message;
    message.messageType = std::stoi(serialMessage.substr(0, 1));

    if (message.messageType == METERAGE)
    {
        short separatorIndex = serialMessage.find(":");
        std::string strTime = serialMessage.substr(1, separatorIndex - 1);
        std::string strValue = serialMessage.substr(separatorIndex + 1);
        message.measurements.timeStamp = std::stoll(strTime);
        message.measurements.value = std::stoi(strValue);
    }

    if (message.messageType == COMMAND)
    {
        message.adjustment = std::stoi(serialMessage.substr(1));
    }

    if (message.messageType == ERROR)
    {
        message.errorType = std::stoi(serialMessage.substr(1));
    }

    return message;
};
