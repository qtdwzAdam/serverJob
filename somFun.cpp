
#include "somFun.h"

QString getIPAddress()
{
    QString ipAddress;
    int flag = 1;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
            if(flag == 1)
            {
                ipAddress.append(ipAddressesList.at(i).toString());
                flag = 0;
            }else{
                ipAddress.append("\n");
                ipAddress.append(ipAddressesList.at(i).toString());
            }
            //break;
        }
    }
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    return ipAddress;
}

